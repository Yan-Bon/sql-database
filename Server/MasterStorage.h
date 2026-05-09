#pragma once
#include <mutex>
#include "Storage.h"
#include "IndexInfo.h"
#include "IndexName.h"
#include "IndexGroups.h"

using guid = Storage::guid;

class MasterStorage {
private:
	std::mutex mtx;
	Storage storage;
	RBTreeNameIndex nameIndex;
	RBTreeInfoIndex infoIndex;
	GroupHashIndex groupIndex;
	enum Color {RED, BLACK};
public:
	MasterStorage(std::string storagePath)
		: storage(storagePath),
		nameIndex(&storage),
		infoIndex(&storage),
		groupIndex(&storage) {}

	guid insert(StudentEntity& entity);

	StudentEntity* searchByName(char name[64]);

	StudentEntity* searchByInfo(std::string& info);

	std::vector<std::shared_ptr<StudentEntity>> searchByGroup(unsigned int group);

	bool remove(guid id);

	bool Update(char n[64], StudentEntity* newSe);

	std::vector<unsigned int> getAllGroups();


	std::vector<std::shared_ptr<StudentEntity>> searchByNameMask(std::string& mask);


	std::vector<std::shared_ptr<StudentEntity>> searchByRatingRange(double minRating, double maxRating);


	std::vector<std::shared_ptr<StudentEntity>> searchByGroups(std::vector<unsigned int>& groups);


	std::vector<std::shared_ptr<StudentEntity>> getAllStudents();


	std::vector<std::shared_ptr<StudentEntity>> searchByRating(double rating);

	bool removeByEntity(StudentEntity* student);
	void optimize() {};
};
