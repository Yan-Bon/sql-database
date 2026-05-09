#pragma once
#include "StudentEntity.h"
#include <fstream>
#include <unordered_map>
#include "f_log_stream.h"
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <memory>
enum class Color { RED, BLACK };

class Storage
{
public: 
	Storage(std::string storage) : _storagePath(storage) {};
	typedef unsigned long long guid;
	StudentEntity* Read(guid id);
	guid Write(StudentEntity& se);
	bool Delete(guid id);
	bool Contains(guid id);
	bool SpaceOptimization();
	bool CloseAll();
	bool ReadName(char toName[64], guid id);
	std::pair<bool, double> ReadRating(guid id);
	guid getLastGuid() { return nextAvaibableId-1; };
	
private:
	guid WriteInNewSlot(StudentEntity& se, StudentEntityHeader& header);
	guid WriteInDeletedSlot(StudentEntity& se, StudentEntityHeader& header, guid slot);
	f_log_stream* CreateNewStorage();
	StudentEntityHeader calculateHeader(StudentEntity& se);
	std::tuple<bool, guid> isAvaibableDeletedSlots(size_t size);
	std::tuple<int, int> findSlotInPage(f_log_stream* iof, guid id);
	bool makeCursorOnSlotInPage(f_log_stream* iof, guid id);
	f_log_stream* findSlotHeaderStart(guid id);
	unsigned int get_file_size(f_log_stream* iof, std::ios_base::seekdir return_to);
	
	const unsigned int fileMaxSize = 4096;
	std::vector<f_log_stream*> storages;
	std::unordered_map<guid, f_log_stream*> slotsInFilesMap;
	
	std::set<guid> deletedSlotsSet;
	std::map<size_t, guid> deletedSlotsBySize;

	std::string _storagePath;
	guid nextAvaibableId = 0;
};


