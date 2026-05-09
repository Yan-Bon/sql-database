#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include "IndexGroups.h"
#include "Storage.h"



void GroupHashIndex::insert(StudentEntity& entity, guid id) {
    unsigned int group = entity.group;
    groupIndex[group].push_back(id);
}

std::vector<std::shared_ptr<StudentEntity>> GroupHashIndex::search(unsigned int group) {
    std::vector<std::shared_ptr<StudentEntity>> result;
    auto it = groupIndex.find(group);
    if (it != groupIndex.end()) {
        for (guid id : it->second) {
			StudentEntity* entity = storage->Read(id);
            if (entity != nullptr) {
				std::shared_ptr<StudentEntity> se = std::make_shared<StudentEntity>(entity);
                result.push_back(se);
            }
        }
    }
    return result;
}

bool GroupHashIndex::remove(StudentEntity& entity) {
    unsigned int group = entity.group;
    auto it = groupIndex.find(group);
    if (it != groupIndex.end()) {
        auto& ids = it->second;
        for (auto idIt = ids.begin(); idIt != ids.end(); ++idIt) {
            if (*idIt == storage->Write(entity)) {
                ids.erase(idIt);
                if (ids.empty()) {
                    groupIndex.erase(it);
                }
                return true;
            }
        }
    }
    return false;
}

bool GroupHashIndex::containsGroup(unsigned int group) {
    return groupIndex.find(group) != groupIndex.end();
}

bool GroupHashIndex::contains(StudentEntity& entity) {
    auto it = groupIndex.find(entity.group);
    if (it != groupIndex.end()) {
        guid targetId = storage->Write(entity);
        for (guid id : it->second) {
            if (id == targetId) {
                return true;
            }
        }
    }
    return false;
}

std::vector<unsigned int> GroupHashIndex::getAllGroups() {
    std::vector<unsigned int> groups;
    for (const auto& pair : groupIndex) {
        groups.push_back(pair.first);
    }
    return groups;
}
