#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
class Scanner {
  public:
  	Scanner();
	bool scan();
	bool isDigtal(char ch) const; 
	bool isAlphabet(char ch) const;
	bool isSymbol(char ch) const;
	void puterror() const;
	void putresult() const;
	std::vector<std::pair<std::string, std::string>> lexicalAnalysis() const;
  private:
	int row, col;
	std::string error;	
	std::vector<std::pair<std::string, std::string>> result;
};
#endif
