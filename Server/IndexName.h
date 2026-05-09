#pragma once
#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "Storage.h"
#include "IndexTreeNode.h"

using guid = Storage::guid;


class RBTreeNameIndex
{
   private:
    IndexTreeNode* root;
    Storage* storage;

 
    size_t computeHash(char name[64]);
 
    IndexTreeNode* searchNode(size_t hash);
  
    void rotateLeft(IndexTreeNode* x);
    void rotateRight(IndexTreeNode* x);

    void fixInsert(IndexTreeNode* k);
    IndexTreeNode* minimum(IndexTreeNode* node);
	void transplant(IndexTreeNode* u, IndexTreeNode* v);
	void fixDelete(IndexTreeNode* x);
	void clear(IndexTreeNode* node);
   public:
    RBTreeNameIndex(Storage* storage) : root(nullptr), storage(storage) {}

    ~RBTreeNameIndex() { clear(root); }


	void insert(StudentEntity& entity, guid id);

	StudentEntity* search(char name[64]);
	std::pair<bool, guid> searchId(char name[64]);

 
	bool remove(char name[64]);


	bool contains(char name[64]);

  
	std::vector<guid> getAll(char name[64]);
};
