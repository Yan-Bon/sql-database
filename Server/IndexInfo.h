#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "IndexTreeNode.h"
#include "Storage.h"



using guid = Storage::guid;
class RBTreeInfoIndex {
   private:
    IndexTreeNode* root;
    Storage* storage;


    size_t computeHash(std::string& info);

  
    IndexTreeNode* searchNode(size_t hash);

   
    void rotateLeft(IndexTreeNode* x);

    void rotateRight(IndexTreeNode* x);

    void fixInsert(IndexTreeNode* k);

    IndexTreeNode* minimum(IndexTreeNode* node);

    void transplant(IndexTreeNode* u, IndexTreeNode* v);

    void fixDelete(IndexTreeNode* x);

   public:
    RBTreeInfoIndex(Storage* storage) : root(nullptr), storage(storage) {}

    ~RBTreeInfoIndex() {

    }


    void insert(StudentEntity& entity, guid id);

  
    StudentEntity* search(std::string& info);


    bool remove(std::string& info);
 
    bool contains(std::string& info);
};
