#include "QueryIntepreter.h"
#include "MasterStorage.h"
#include <thread>
#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

void QueryInterpreter::execute(std::string& query) {
    std::string trimmed = trim(query);
    std::string crites;
    if (trimmed.starts_with("SELECT")) {
        crites = trimmed.substr(6, trimmed.size() - 10);
        handleSelect(crites); 
    } else if (trimmed.starts_with("RESPONSE")) {
        auto args = parseArguments(trimmed.substr(5, trimmed.size() - 8));
        lastPrintedFields = args; 
    } else if (trimmed.starts_with("RESELECT")) {
        crites = trimmed.substr(8, trimmed.size() - 12);
        handleReselect(crites);
    } else if (trimmed.starts_with("PRINT")) {
        crites = trimmed.substr(5, trimmed.size() - 9);
        handlePrint(crites);
    } else if (trimmed.starts_with("INSERT")) {
        crites = trimmed.substr(6, trimmed.size() - 10);
        
        handleInsert(crites);
        
    } else if (trimmed.starts_with("UPDATE")) {
        crites = trimmed.substr(6, trimmed.size() - 10);
        handleUpdate(crites);
    } else if (trimmed.starts_with("DELETE")) {
        crites = trimmed.substr(6, trimmed.size() - 10);
        handleDelete(crites);
    } else if (trimmed.starts_with("OPTIMIZE")) {
        handleOptimize();
    } else {
        std::cout << "Unknown command : 135\n";
    }
}

void QueryInterpreter::handleSelect(std::string& body) {
	 currentSelection = filterByCriteria(body);
}

void QueryInterpreter::handleReselect(std::string& body) {
    currentSelection = filterByCriteria(body, currentSelection);
}

std::vector<std::shared_ptr<StudentEntity>> QueryInterpreter::filterByCriteria(
    std::string& criteria, std::vector<std::shared_ptr<StudentEntity>>& base) {
    std::map<std::string, std::string> parsedCriteria =
        parseCriteriaString(criteria);

    std::vector<std::shared_ptr<StudentEntity>> result;
    std::vector<std::shared_ptr<StudentEntity>> candidates;

    // Èìÿ
    if (parsedCriteria.count("name")) {
        std::string mask = parsedCriteria["name"];
        if (mask.ends_with("*")) mask.pop_back();

        candidates = storage.searchByNameMask(mask);
    }

   
    if (parsedCriteria.count("group")) {
        auto groups = parseGroupCriteria(parsedCriteria["group"]);
        auto groupMatched = storage.searchByGroups(groups);
        if (candidates.empty())
            candidates = groupMatched;
        else
            candidates = intersect(candidates, groupMatched);
    }


    if (parsedCriteria.count("rating")) {
        auto [minR, maxR] = parseRatingCriteria(parsedCriteria["rating"]);
        auto ratingMatched = storage.searchByRatingRange(minR, maxR);
        if (candidates.empty())
            candidates = ratingMatched;
        else
            candidates = intersect(candidates, ratingMatched);
    }

  
    if (!base.empty()) {
        return intersect(candidates, base);
    }
    return base;
}
std::vector<std::shared_ptr<StudentEntity>> QueryInterpreter::filterByCriteria(
    std::string& criteria, std::vector<std::shared_ptr<StudentEntity>>&& base) {
    std::map<std::string, std::string> parsedCriteria =
        parseCriteriaString(criteria);
	
    std::vector<std::shared_ptr<StudentEntity>> result;
    std::vector<std::shared_ptr<StudentEntity>> candidates;

 
    if (parsedCriteria.count("name")) {
        std::string mask = parsedCriteria["name"];
        if (mask.ends_with("*")) mask.pop_back();
        candidates = storage.searchByNameMask(mask);
    }

 
    if (parsedCriteria.count("group")) {
        auto groups = parseGroupCriteria(parsedCriteria["group"]);
        auto groupMatched = storage.searchByGroups(groups);
        if (candidates.empty())
            candidates = groupMatched;
        else
            candidates = intersect(candidates, groupMatched);
    }


    if (parsedCriteria.count("rating")) {
        auto [minR, maxR] = parseRatingCriteria(parsedCriteria["rating"]);
        auto ratingMatched = storage.searchByRatingRange(minR, maxR);
        if (candidates.empty())
            candidates = ratingMatched;
        else
            candidates = intersect(candidates, ratingMatched);
    }


    if (!base.empty()) {
        return intersect(candidates, base);
    }
    return candidates;
}

void QueryInterpreter::handleInsert(std::string& body) {
    auto tokens = split(body, ' ');
    if (tokens.size() < 4) {
        std::cerr << "Invalid INSERT syntax\n";
        return;
    }

    std::string name = tokens[0];

    unsigned int group = std::stoi(tokens[1]);
    double rating = std::stod(tokens[2]);
    std::string info;

    for (size_t i = 3; i < tokens.size(); ++i) {
        if (i > 3) info += " ";
        info += tokens[i];
    }

    StudentEntity entity(name, group, rating, info);
    storage.insert(entity);
}

void QueryInterpreter::handleUpdate(std::string& body) {
    auto pos = body.find("SET");
    if (pos == std::string::npos) {
        std::cerr << "UPDATE missing SET\n";
        return;
    }

    std::string temp = body.substr(0, pos);
    std::string criteria = trim(temp);
    temp = body.substr(pos + 3);
    std::string assignments = trim(temp);

    auto selection = filterByCriteria(criteria);
    auto assigns = parseCriteriaString(assignments);  // ïåðåèñïîëüçóåì

	StudentEntity updatedSe;

    for (auto student : selection) {
		updatedSe = *student;
        if (assigns.count("name")) {
            strncpy(updatedSe.name, assigns["name"].c_str(), 63);
			updatedSe.name[63] = '\0';
        }
        if (assigns.count("group")) {
			updatedSe.group = std::stoi(assigns["group"]);
        }
        if (assigns.count("rating")) {
			updatedSe.rating = std::stod(assigns["rating"]);
        }
        if (assigns.count("info")) {
			updatedSe.info = assigns["info"];
        }
		storage.Update(student->name, &updatedSe);
    }
}
void QueryInterpreter::handleDelete(std::string& body) {
    std::string trimmedBody = trim(body);

    auto selection = filterByCriteria(trimmedBody);
    for (auto student : selection) {
        storage.removeByEntity(student.get());
    }
}
void QueryInterpreter::handlePrint(std::string& body) {
    std::vector<std::string> fields = split(body, ' ');

    for (std::shared_ptr<StudentEntity> student : currentSelection) {
        for (std::string& field : fields) {
            if (field == "name")
                std::cout << student->name << " ";
            else if (field == "group")
                std::cout << student->group << " ";
            else if (field == "rating")
                std::cout << student->rating << " ";
            else if (field == "info")
                std::cout << student->info << " ";
        }
        std::cout << "\n";
    }
}
void QueryInterpreter::handleOptimize() { storage.optimize(); }
std::string QueryInterpreter::trim(std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? ""
                                        : str.substr(start, end - start + 1);
}

std::vector<std::string> QueryInterpreter::split(std::string& s,
                                                 char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream stream(s);
    std::string token;
    while (std::getline(stream, token, delimiter)) {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}

std::map<std::string, std::string> QueryInterpreter::parseCriteriaString(
    std::string& input) {
    std::map<std::string, std::string> result;
    auto tokens = split(input, ' ');
    for (const auto& token : tokens) {
        auto pos = token.find('=');
        if (pos != std::string::npos) {
            std::string key = token.substr(0, pos);
            std::string value = token.substr(pos + 1);
            result[trim(key)] = trim(value);
        }
    }
    return result;
}

std::vector<unsigned int> QueryInterpreter::parseGroupCriteria(
    std::string& groupCrit) {
    std::vector<unsigned int> result;
    auto parts = split(groupCrit, ',');
    for (const auto& part : parts) {
        auto dash = part.find('-');
        if (dash != std::string::npos) {
            unsigned int from = std::stoi(part.substr(0, dash));
            unsigned int to = std::stoi(part.substr(dash + 1));
            for (unsigned int i = from; i <= to; ++i) result.push_back(i);
        } else {
            result.push_back(std::stoi(part));
        }
    }
    return result;
}

std::pair<double, double> QueryInterpreter::parseRatingCriteria(
    std::string& ratingCrit) {
    auto dash = ratingCrit.find('-');
    if (dash != std::string::npos) {
        std::string left = ratingCrit.substr(0, dash);
        std::string right = ratingCrit.substr(dash + 1);
        double min = left.empty() || left == "*" ? 0.0 : std::stod(left);
        double max = right.empty() || right == "*" ? 10000.0 : std::stod(right);
        return {min, max};
    } else {
        double exact = std::stod(ratingCrit);
        return {exact, exact};
    }
}
std::vector<std::shared_ptr<StudentEntity>> QueryInterpreter::intersect(
    std::vector<std::shared_ptr<StudentEntity>>& a, std::vector<std::shared_ptr<StudentEntity>>& b) {
	std::vector<long long>* pia = (std::vector<long long>*)&a, *pib = (std::vector<long long>*)&b;
    std::vector<std::shared_ptr<StudentEntity>> result;

	for(int ib = b.size()-1; ib >= 0; --ib) {
		for (int ia = a.size() - 1; ia >= 0; --ia)
		{
			if (!strcmp(a[ia]->name, b[ib]->name)) {
				result.push_back(a[ia]);
			}
		}
	}
	a.clear();
	b.clear();
	return result;
}

std::string QueryInterpreter::RESPONSE() {
    json jArray = json::array();
    std::vector<std::string> fields = lastPrintedFields;
    if (fields.empty()) {
        fields = {"name", "group", "rating", "info"};
    }

    for (auto student : currentSelection) {
        if (!student) continue;

        json j;

        for (auto field : fields) {
            std::string f = field;
            std::transform(f.begin(), f.end(), f.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (f == "name")
                j["name"] = std::string(student->name);
            else if (f == "group")
                j["group"] = student->group; //unsigned int
            else if (f == "rating")
                j["rating"] = student->rating; //double
            else if (f == "info")
                j["info"] = student->info; //std::string
        }

        jArray.push_back(j);
    }
    return jArray.is_null() ? "[]" : jArray.dump(2);
}

std::vector<std::string> QueryInterpreter::parseArguments(
    const std::string& argsLine) {
    std::vector<std::string> args;
    std::istringstream iss(argsLine);
    std::string token;

    while (iss >> token) {
        args.push_back(token);
    }
    return args;
}
