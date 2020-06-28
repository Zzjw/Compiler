#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
struct treenode{
	std::string content;
	std::vector<treenode> children;
};
class Parser{
  public:
  	Parser();
  	void parsing();
  	treenode parse_decl();
  	treenode parse_factor();
  	void putresult();
  	void printSyntaxTree(treenode &node);
  	void puterror();
  	void match(std::string key);
  private:
  	std::vector<std::pair<std::string, std::string>> tokens;
  	treenode root;
  	std::string error;
  	int curidx;
};
#endif
