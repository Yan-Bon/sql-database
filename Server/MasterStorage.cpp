#pragma once
#include <algorithm>
#include "MasterStorage.h"

using guid = Storage::guid;

guid MasterStorage::insert(StudentEntity& entity) {
	std::lock_guard<std::mutex> lock(mtx);
    guid id = storage.Write(entity);
    nameIndex.insert(entity, id);
    infoIndex.insert(entity, id);
    groupIndex.insert(entity, id);
    return id;
}

StudentEntity* MasterStorage::searchByName(char name[64]) {
	std::lock_guard<std::mutex> lock(mtx);
    return nameIndex.search(name);
}

StudentEntity* MasterStorage::searchByInfo(std::string& info) {
	std::lock_guard<std::mutex> lock(mtx);
    return infoIndex.search(info);
}

std::vector<std::shared_ptr<StudentEntity>> MasterStorage::searchByGroup(unsigned int group) {
	std::lock_guard<std::mutex> lock(mtx);
    return groupIndex.search(group);
}

bool MasterStorage::remove(guid id) {
	std::lock_guard<std::mutex> lock(mtx);
    StudentEntity* entity = storage.Read(id);
    if (entity) {
        nameIndex.remove(entity->name);
        infoIndex.remove(entity->info);
        groupIndex.remove(*entity);
        return storage.Delete(id);
    }
	delete entity;
    return false;
}

bool MasterStorage::Update(char n[64], StudentEntity* newSe)
{
	auto res_id = nameIndex.searchId(n);
	if (!res_id.first)
		return false;
	storage.Delete(res_id.second);
	storage.Write(*newSe);
	insert(*newSe);
	return true;
}

std::vector<unsigned int> MasterStorage::getAllGroups() {
	std::lock_guard<std::mutex> lock(mtx);
    return groupIndex.getAllGroups();
}

std::vector<std::shared_ptr<StudentEntity>> MasterStorage::searchByNameMask(std::string& mask)
{
	std::lock_guard<std::mutex> lock(mtx);
	std::vector<std::shared_ptr<StudentEntity>> res;
	if (mask.size() > 63)
		return res;

	char buf[64];
	for (int id = 0; id <= storage.getLastGuid(); ++id) {
		if (storage.ReadName(buf, id)){
			bool isEqualMask = true;
			for (int j = 0; j < mask.size() && j < 64; ++j) {
				if (mask[j] != buf[j]) {
					isEqualMask = false;
					break;
				}
			}
			if (isEqualMask) {
				StudentEntity* se = storage.Read(id);
				if (se == nullptr)
					throw std::runtime_error("Storage reading in searchByNameMask. Error code : 7135");
				res.push_back(std::make_shared<StudentEntity>(se));
			}
			else
				continue;
		}
	}
	return res;
}

std::vector<std::shared_ptr<StudentEntity>> MasterStorage::searchByRatingRange(double minRating, double maxRating)
{
	std::lock_guard<std::mutex> lock(mtx);
	std::vector<std::shared_ptr<StudentEntity>> res;
	for (int id = 0; id <= storage.getLastGuid(); ++id){
		StudentEntity* p_se = storage.Read(id);
		if (!p_se)
			continue;
		if (p_se->rating >= minRating
			&& p_se->rating <= maxRating)
			res.push_back(std::make_shared<StudentEntity>(p_se));
		else {
			delete p_se;
		}
	}
    return res;
}

std::vector<std::shared_ptr<StudentEntity>> MasterStorage::searchByGroups(std::vector<unsigned int>& groups)
{
	std::lock_guard<std::mutex> lock(mtx);
	std::vector<std::shared_ptr<StudentEntity>> res;
	for (int i = 0; i < groups.size(); ++i) {
	std::vector<std::shared_ptr<StudentEntity>> tempVec = groupIndex.search(groups[i]);
		res.insert(res.end(), std::make_move_iterator(tempVec.begin()), std::make_move_iterator(tempVec.end()));
	}
	return res;
}

std::vector<std::shared_ptr<StudentEntity>> MasterStorage::getAllStudents()
{
	std::vector<std::shared_ptr<StudentEntity>> res;
	std::shared_ptr<StudentEntity> psh;
	for (int i = 0; i <= storage.getLastGuid(); ++i) {
		StudentEntity* p = storage.Read(i);
		if (!p)
			continue;
		else
			psh = std::make_shared<StudentEntity>(p);
		res.push_back(psh);
	}
	return res;

}

std::vector<std::shared_ptr<StudentEntity>> MasterStorage::searchByRating(double rating)
{
	std::vector<std::shared_ptr<StudentEntity>> res;
	std::shared_ptr<StudentEntity> psh;
	for (int i = 0; i < storage.getLastGuid(); ++i) {
		StudentEntity* p = storage.Read(i);
		if (!p)
			continue;
		if (p->rating != rating) {
			delete p;
			continue;
		}
		psh = std::make_shared<StudentEntity>(p);
		res.push_back(psh);
	}
	return res;
}

bool MasterStorage::removeByEntity(StudentEntity* student)
{
	std::lock_guard<std::mutex> lock(mtx);
	std::pair<bool, guid> res = nameIndex.searchId(student->name);
	if (!res.first)
		return false;
	return storage.Delete(res.second);
}
