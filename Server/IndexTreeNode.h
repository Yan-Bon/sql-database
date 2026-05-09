#pragma once
#include "Storage.h"

using guid = Storage::guid;

struct IndexTreeNode
{
	size_t hash;
	guid id;
	Color color;
	IndexTreeNode* left;
	IndexTreeNode* right;
	IndexTreeNode* parent;

	IndexTreeNode(size_t h, guid g, Color c = Color::RED,
		IndexTreeNode* l = nullptr, IndexTreeNode* r = nullptr,
		IndexTreeNode* p = nullptr)
		: hash(h), id(g), color(c), left(l), right(r), parent(p)
	{}
};
