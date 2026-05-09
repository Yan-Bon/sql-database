#include "Storage.h"

#include <exception>
#include <iostream>

#include "f_log_stream.h"
using guid = Storage::guid;
StudentEntity* Storage::Read(guid id) {
	if (slotsInFilesMap.find(id) == slotsInFilesMap.end()) return nullptr;

	if (deletedSlotsSet.find(id) != deletedSlotsSet.end()) return nullptr;

	f_log_stream* iof = slotsInFilesMap[id];
	if (!iof->is_open())
		throw std::runtime_error("File from pool was not open");

	if (!makeCursorOnSlotInPage(iof, id))
		return nullptr;
	StudentEntityHeader header;
	StudentEntity* se = new StudentEntity();
	int sizenostring = 64 + sizeof(unsigned int) + sizeof(double);

	iof->read((char*)&header, sizeof(StudentEntityHeader));
	if (header.IsDeleted)
		return nullptr;
	iof->read((char*)se, sizeof(StudentEntity) - sizeof(std::string));
	int strlen = header.fullSize - (sizeof(StudentEntityHeader) + sizenostring);
	se->info.resize(strlen, '0');
	// std::cout << "tellg - " << iof->tellg();
	// std::cout << "tellp - " << iof->tellp();
	iof->read(&se->info[0], strlen);
return se;
}

Storage::guid Storage::Write(StudentEntity& se) {
    StudentEntityHeader header = calculateHeader(se);
    header.id = nextAvaibableId++;
    std::tuple<bool, guid> av = isAvaibableDeletedSlots(header.fullSize);
    if (std::get<0>(av)) {
        WriteInDeletedSlot(se, header, std::get<1>(av));
        return header.id;
    }
    return WriteInNewSlot(se, header);
}

bool Storage::Delete(guid id) {
    if (!Contains(id)) return false;

    auto iof = findSlotHeaderStart(id);
	if (iof != nullptr)
	{
		StudentEntityHeader header;
		iof->read((char*)&header, sizeof(StudentEntityHeader));
		iof->seekp(-1 * sizeof(StudentEntityHeader), std::ios::cur);

		header.IsDeleted = true;
		iof->write((char*)&header, sizeof(StudentEntityHeader));

		deletedSlotsBySize.insert(std::pair<size_t, guid>(header.fullSize, id));
		deletedSlotsSet.insert(id);
	}
    return true;
}

bool Storage::Contains(guid id) {
    return slotsInFilesMap.find(id) != slotsInFilesMap.end() &&
           deletedSlotsSet.find(id) == deletedSlotsSet.end();
}

bool Storage::SpaceOptimization() { return false; }

bool Storage::CloseAll() {
    for (int i = 0; i < storages.size(); ++i) {
        auto iof = storages[i];
        iof->flush();
    }
    return true;
}

bool Storage::ReadName(char toName[64], guid id) {
    auto iof = findSlotHeaderStart(id);
	StudentEntityHeader header;
    if (iof == nullptr) return false;
	iof->read((char*) & header, sizeof(StudentEntityHeader));
	if (header.IsDeleted)
		return false;
    iof->read(toName, 64);
    return true;
}

std::pair<bool, double> Storage::ReadRating(guid id) {
    std::pair<bool, double> res;
	StudentEntityHeader header;
    auto iof = findSlotHeaderStart(id);
    if (iof == nullptr) {
        res.first = false;
    } else {
		iof->read((char*)&header, sizeof(StudentEntityHeader));
		if (header.IsDeleted)
			res.first = false;
		else {
			iof->seekg(sizeof(StudentEntity::name) +
				sizeof(unsigned int),
				std::ios::cur);
			iof->read((char*)&res.second, sizeof(StudentEntity::name));
			res.first = true;
		}
    }
    return res;
}

guid Storage::WriteInNewSlot(StudentEntity& se, StudentEntityHeader& header) {
    f_log_stream* iof;
    if (storages.size() == 0 ||
        (get_file_size(storages.back(), std::ios::end) >=
         (fileMaxSize - header.fullSize))) {
        iof = CreateNewStorage();
    } else {
        iof = storages[storages.size() - 1];
        iof->seekp(0, std::ios_base::end);
        iof->seekg(0, std::ios_base::end);
    }

    iof->write((char*)&header, sizeof(StudentEntityHeader));
    iof->write((char*)&se, sizeof(StudentEntity) - sizeof(std::string));
    iof->write(&(se.info[0]), se.info.size());
    const char null = '\0';
    iof->write(&null, 1);
    iof->seekg(0, std::ios::beg);
    slotsInFilesMap.insert(std::pair<guid, f_log_stream*>(header.id, iof));

    return header.id;
}

guid Storage::WriteInDeletedSlot(StudentEntity& se, StudentEntityHeader& header,
                                 guid slot) {
	auto iof = findSlotHeaderStart(slot);
	if (iof == nullptr) {
		WriteInNewSlot(se, header);	
		return -1;
	}

    StudentEntityHeader oldheader;
    auto originalPos = iof->tellg();
    iof->read((char*)&oldheader, sizeof(StudentEntityHeader));
    bool isgood = iof->iof.good();
    iof->seekg(originalPos);
    isgood = iof->iof.good();
    iof->write((char*)&header, sizeof(StudentEntityHeader));
    isgood = iof->iof.good();

    iof->write((char*)&se, sizeof(StudentEntity) - sizeof(std::string));
    isgood = iof->iof.good();

    iof->write(&(se.info[0]), se.info.size());
    const char null = '\0';
    iof->write(&null, 1);

    // —оздаем новый слот, т.к. после образки свободного осталс€ свободный кусок
    oldheader.fullSize -= header.fullSize;
    iof->write((char*)&oldheader, sizeof(StudentEntityHeader));

    // ќбновл€ем значение свободной €чейки в deletedSlots
    auto it =
        std::find_if(deletedSlotsBySize.begin(), deletedSlotsBySize.end(),
                     [&slot](const auto& pair) { return pair.second == slot; });

    if (it != deletedSlotsBySize.end()) {
        deletedSlotsBySize.erase(it);
    }
    deletedSlotsBySize.insert(
        std::pair<size_t, guid>(oldheader.fullSize, slot));
    ////////////////

    //
    iof->seekg(0, std::ios::beg);
    slotsInFilesMap.insert(std::pair<guid, f_log_stream*>(header.id, iof));
    return header.id;
}

f_log_stream* Storage::CreateNewStorage() {
    f_log_stream* newStream = new f_log_stream();
    newStream->pageId = storages.size();
    newStream->open(
        _storagePath + std::to_string(storages.size()),
        std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
    if (!newStream->is_open()) {
        throw std::runtime_error("Failed to open file-storage");
    }
    storages.push_back(newStream);
    return newStream;
}

StudentEntityHeader Storage::calculateHeader(StudentEntity& se) {
    StudentEntityHeader header;
    // char name[64]; //Key FIO
    // unsigned int group; //Key group number
    // double rating; //key
    // std::string info; //Dynamic data
    header.fullSize = sizeof(StudentEntityHeader) + 64 + sizeof(unsigned int) +
                      sizeof(double) + se.info.size() + 1;
    header.IsDeleted = false;
    return header;
}

std::tuple<bool, guid> Storage::isAvaibableDeletedSlots(size_t size) {
    auto iter =
        deletedSlotsBySize.lower_bound(size + sizeof(StudentEntityHeader));
    if (iter == deletedSlotsBySize.end())
        return std::tuple<bool, guid>(false, 0);
    else
        return std::tuple<bool, guid>(true, iter->second);
}

std::tuple<int, int> Storage::findSlotInPage(f_log_stream* iof, guid id) {
    int offset = 0;
    iof->seekg(0, std::ios::beg);
    StudentEntityHeader header;
    for (int i = 0; i < iof->tellg(); ++i) {
        iof->read((char*)&header, sizeof(StudentEntityHeader));
        iof->seekg(header.fullSize - sizeof(StudentEntityHeader),
                   std::ios::cur);
        if (header.id == id) break;
        offset += header.fullSize;
    }
    iof->seekg(0, std::ios::beg);
    return std::tuple<int, int>(offset, header.fullSize);
}

bool Storage::makeCursorOnSlotInPage(f_log_stream* iof, guid id) {
    if (iof->iof.fail()) std::cout << "\n123";
    if (iof->iof.bad()) std::cout << "\n456";
    if (iof->iof.eof()) std::cout << "\n789";

    bool isFound = false;
    iof->seekg(0);
    iof->iof.clear();
    auto filesize = get_file_size(iof, std::ios::beg);

    StudentEntityHeader header;
    if (!iof->is_open()) throw std::runtime_error("File was not opened : 1245");
    for (int i = 0; i < filesize;) {
        iof->seekg(i, std::ios::beg);
        iof->read((char*)&header, sizeof(StudentEntityHeader));
        iof->seekg(header.fullSize - sizeof(StudentEntityHeader),
                   std::ios::cur);
        if (header.id == id) {
            isFound = true;
            iof->seekg(i, std::ios::beg);
            iof->seekp(i, std::ios::beg);
            return true;
        }
        i += header.fullSize + 4;
    }
    return false;
}

f_log_stream* Storage::findSlotHeaderStart(guid id) {
    if (slotsInFilesMap.find(id) == slotsInFilesMap.end()) return nullptr;

    auto iof = slotsInFilesMap[id];
    if (!iof->is_open()) throw std::runtime_error("File is not open : 1523");

	if (!makeCursorOnSlotInPage(iof, id))
		return nullptr;

    return iof;
}

unsigned int Storage::get_file_size(f_log_stream* iof,
                                    std::ios_base::seekdir return_to) {
    iof->seekg(0, std::ios::end);
    int x = iof->tellg();
    iof->seekg(0, return_to);
    iof->seekp(0, return_to);
    return x;
}
