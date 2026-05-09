#pragma once
#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "IndexName.h"

using guid = Storage::guid;

size_t RBTreeNameIndex::computeHash(char name[64])
{
    std::hash<std::string> hasher;
    return hasher(std::string(name));
}

IndexTreeNode* RBTreeNameIndex::searchNode(size_t hash)
{
    IndexTreeNode* current = root;
    while (current != nullptr) {
        if (hash == current->hash) {
            return current;
        }
        else if (hash < current->hash) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

void RBTreeNameIndex::rotateLeft(IndexTreeNode* x)
{
    IndexTreeNode* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBTreeNameIndex::rotateRight(IndexTreeNode* x)
{
    IndexTreeNode* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RBTreeNameIndex::fixInsert(IndexTreeNode* k)
{
    while (k != root && k->parent->color == Color::RED) {
        if (k->parent == k->parent->parent->left) {
            IndexTreeNode* u = k->parent->parent->right;
            if (u != nullptr && u->color == Color::RED) {
                u->color = Color::BLACK;
                k->parent->color = Color::BLACK;
                k->parent->parent->color = Color::RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    rotateLeft(k);
                }
                k->parent->color = Color::BLACK;
                k->parent->parent->color = Color::RED;
                rotateRight(k->parent->parent);
            }
        }
        else {
            IndexTreeNode* u = k->parent->parent->left;
            if (u != nullptr && u->color == Color::RED) {
                u->color = Color::BLACK;
                k->parent->color = Color::BLACK;
                k->parent->parent->color = Color::RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rotateRight(k);
                }
                k->parent->color = Color::BLACK;
                k->parent->parent->color = Color::RED;
                rotateLeft(k->parent->parent);
            }
        }
    }
    root->color = Color::BLACK;
}

IndexTreeNode* RBTreeNameIndex::minimum(IndexTreeNode* node)
{
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void RBTreeNameIndex::transplant(IndexTreeNode* u, IndexTreeNode* v)
{
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

void RBTreeNameIndex::fixDelete(IndexTreeNode* x)
{
    while (x != root && (x == nullptr || x->color == Color::BLACK)) {
        if (x == x->parent->left) {
            IndexTreeNode* w = x->parent->right;
            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                x->parent->color = Color::RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == Color::BLACK) &&
                (w->right == nullptr || w->right->color == Color::BLACK))
            {
                w->color = Color::RED;
                x = x->parent;
            }
            else {
                if (w->right == nullptr || w->right->color == Color::BLACK) {
                    if (w->left != nullptr) {
                        w->left->color = Color::BLACK;
                    }
                    w->color = Color::RED;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = Color::BLACK;
                if (w->right != nullptr) {
                    w->right->color = Color::BLACK;
                }
                rotateLeft(x->parent);
                x = root;
            }
        }
        else {
            IndexTreeNode* w = x->parent->left;
            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                x->parent->color = Color::RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if ((w->right == nullptr || w->right->color == Color::BLACK) &&
                (w->left == nullptr || w->left->color == Color::BLACK))
            {
                w->color = Color::RED;
                x = x->parent;
            }
            else {
                if (w->left == nullptr || w->left->color == Color::BLACK) {
                    if (w->right != nullptr) {
                        w->right->color = Color::BLACK;
                    }
                    w->color = Color::RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = Color::BLACK;
                if (w->left != nullptr) {
                    w->left->color = Color::BLACK;
                }
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    if (x != nullptr) {
        x->color = Color::BLACK;
    }
}

void RBTreeNameIndex::clear(IndexTreeNode* node)
{
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void RBTreeNameIndex::insert(StudentEntity& entity, guid id)
{
    size_t hash = computeHash(entity.name);

    IndexTreeNode* newNode = new IndexTreeNode(hash, id);
    IndexTreeNode* parent = nullptr;
    IndexTreeNode* current = root;

    while (current != nullptr) {
        parent = current;
        if (hash < current->hash) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (parent == nullptr) {
        root = newNode;
    }
    else if (hash < parent->hash) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    fixInsert(newNode);
}

StudentEntity* RBTreeNameIndex::search(char name[64])
{
    size_t hash = computeHash(name);
    IndexTreeNode* node = searchNode(hash);
    return node ? storage->Read(node->id) : nullptr;
}

std::pair<bool,guid> RBTreeNameIndex::searchId(char name[64])
{
	std::pair<bool, guid> res;
	size_t hash = computeHash(name);
	IndexTreeNode* node = searchNode(hash);
	if (!node) {
		res.first = false;
		return res;
	}
	res.first = true;
	res.second = node->id;
	return res;
}

bool RBTreeNameIndex::remove(char name[64])
{
    size_t hash = computeHash(name);
    IndexTreeNode* z = searchNode(hash);
    if (z == nullptr) return false;

    IndexTreeNode* y = z;
    IndexTreeNode* x;
    Color y_original_color = y->color;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr) {
                x->parent = y;
            }
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;
    if (y_original_color == Color::BLACK) {
        fixDelete(x);
    }

    return true;
}

bool RBTreeNameIndex::contains(char name[64])
{
    size_t hash = computeHash(name);
    IndexTreeNode* node = searchNode(hash);
    return node != nullptr && storage->Contains(node->id);
}

std::vector<guid> RBTreeNameIndex::getAll(char name[64])
{
    std::vector<guid> result;
    size_t hash = computeHash(name);

    std::function<void(IndexTreeNode*)> traverse = [&](IndexTreeNode* node) {
        if (node == nullptr) return;
        if (node->hash == hash) {
            result.push_back(node->id);
        }
        if (hash <= node->hash) {
            traverse(node->left);
        }
        if (hash >= node->hash) {
            traverse(node->right);
        }
    };

    traverse(root);
    return result;
}
