#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

#include "Storage.h"



using guid = Storage::guid;
class GroupHashIndex {
   private:
    std::unordered_map<unsigned int, std::vector<guid>> groupIndex;
    Storage* storage;

   public:
    GroupHashIndex(Storage* storage) : storage(storage) {}


    void insert(StudentEntity& entity, guid id);


    std::vector<std::shared_ptr<StudentEntity>> search(unsigned int group);

 
    bool remove(StudentEntity& entity);

 
    bool containsGroup(unsigned int group);

 
    bool contains(StudentEntity& entity);

  
    std::vector<unsigned int> getAllGroups();
};
