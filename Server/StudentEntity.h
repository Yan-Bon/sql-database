#pragma once
#include <cstring>
#include <string>

struct StudentEntity
{
public:
	char name[64]; //Key FIO
	unsigned int group; //Key group number
	double rating; //key 
	std::string info; //Dynamic data
	StudentEntity() = default;
	StudentEntity(std::string n, unsigned int g, double rat, std::string in) : group(g), rating(rat), info(in) {
		strncpy(name, n.c_str(), n.size());
		name[n.size()] = '\0';
	}

	// Move constructor
	StudentEntity(StudentEntity&& other) noexcept
		: group(other.group), rating(other.rating), info(std::move(other.info))
	{
		strncpy(name, other.name, sizeof(name));
		// Clear the source
		other.group = 0;
		other.rating = 0.0;
		memset(other.name, 0, sizeof(other.name));
	}
	StudentEntity(StudentEntity* other)
	{
		if (other)
		{
			strncpy(name, other->name, sizeof(name));
			group = other->group;
			rating = other->rating;
			info = other->info;
		}
	}
	// Copy assignment
	StudentEntity& operator=(const StudentEntity& other)
	{
		if (this != &other)
		{
			strncpy(name, other.name, sizeof(name));
			group = other.group;
			rating = other.rating;
			info = other.info;
		}
		return *this;
	}

	// Move assignment
	StudentEntity& operator=(StudentEntity&& other) noexcept
	{
		if (this != &other)
		{
			strncpy(name, other.name, sizeof(name));
			group = other.group;
			rating = other.rating;
			info = std::move(other.info);

			// Clear the source
			other.group = 0;
			other.rating = 0.0;
			memset(other.name, 0, sizeof(other.name));
		}
		return *this;
	}
};

struct StudentEntityHeader {

	unsigned long long id;
	unsigned int fullSize; //with header
	bool IsDeleted;
public:

	StudentEntityHeader() = default;

	StudentEntityHeader(unsigned int id, unsigned int fullSize, unsigned int fileOffset, bool IsDeleted)
		: id(id), fullSize(fullSize), IsDeleted(IsDeleted)
	{
	}
};

