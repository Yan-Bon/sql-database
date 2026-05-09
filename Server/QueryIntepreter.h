#pragma once
#include <vector>
#include <mutex>
#include <string>
#include <memory>
#include "MasterStorage.h"

class QueryInterpreter {
private:
	MasterStorage& storage;
	std::vector<std::shared_ptr<StudentEntity>> currentSelection;
	std::vector<std::string> lastPrintedFields;
public:
	QueryInterpreter(MasterStorage& storageRef)
		: storage(storageRef) {}
	std::string RESPONSE();
	void execute(std::string& query);

private:
	void handleSelect(std::string& body);
	void handleReselect(std::string& body);
	void handlePrint(std::string& body);
	void handleInsert(std::string& body);
	void handleUpdate(std::string& body);
	void handleDelete(std::string& body);
	void handleOptimize();

	std::vector<std::shared_ptr<StudentEntity>> intersect(
		std::vector<std::shared_ptr<StudentEntity>>& a, std::vector<std::shared_ptr<StudentEntity>>& b);
	std::vector<std::string> split(std::string& s, char delimiter);
	std::string trim(std::string& str);

	std::map<std::string, std::string> parseCriteriaString(std::string& input);
	std::vector<std::shared_ptr<StudentEntity>> filterByCriteria(std::string& criteria,std::vector<std::shared_ptr<StudentEntity>>& base);
	std::vector<std::shared_ptr<StudentEntity>> filterByCriteria(std::string& criteria, std::vector<std::shared_ptr<StudentEntity>>&& base = std::vector<std::shared_ptr<StudentEntity>>());
	std::vector<unsigned int> parseGroupCriteria(std::string& groupCrit);
	std::pair<double, double> parseRatingCriteria(std::string& ratingCrit);
	std::vector<std::string> parseArguments(const std::string& argsLine);

};
