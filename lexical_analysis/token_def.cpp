#include "token_def.h"
bool isMember(const std::vector<std::string> Set, std::string member) {
	for (auto &element: Set) {
		if (element == member) return true;
	}
	return false;
}


bool isMember(const std::string Set, char member) {
	for (auto &element: Set) {
		if (element == member) return true;
	}
	return false;
}

bool isValid(char member) {
	for (auto &element: validchars) {
		if (element == member) return true;
	}
	return false;
}
