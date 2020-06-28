#include "Parser.h"
#include <iostream>
using namespace std;
Parser::Parser(){
 	char ch;
 	string key, val;
 	int f = 0;
	while ((ch=getchar()) != EOF) {
		if (f==0 && ch =='(') f++; 
		else if (f==1 && ch!=',') key.push_back(ch);
		else if (f==1) f++;
		else if (f==2 && ch!=')') val.push_back(ch);
		else if (f==2) {
			f=0;
			tokens.push_back({key, val});
			key.clear(), val.clear();
		}
	}
	curidx = 0;
}

void Parser::parsing() {
	bool f = 1;
	while (curidx<tokens.size()) {
		if (tokens[curidx].second=="int" || tokens[curidx].second=="bool" || tokens[curidx].second=="char") {
			root.children.push_back(parse_decl());
		}
	} 
}

treenode Parser::parse_decl() {
	treenode node;
	node.content = tokens[curidx++].second;
	while (1) {
		node.children.push_back(parse_factor());
		if (curidx<tokens.size() && tokens[curidx].second == ",") ++curidx;
		else if (curidx<tokens.size() && tokens[curidx].second == ";") {
			++curidx;
			break;
		}
		else {
			error = "there must be ';'!";
			puterror();
			break;	
		}
	}
	return node;
}

treenode Parser::parse_factor() {
	treenode node;
	if (curidx<tokens.size()) {
		error = "there must be ID!";
		puterror();
		return node;
	}
	node.content = tokens[curidx++].second;
}

void Parser::putresult() {

}


void Parser::printSyntaxTree(treenode &node) {

}

void Parser::puterror() {
	printf("error in %d-th token: %s", curidx, error.c_str());
	exit(0);
}

void Parser::match(string key) {

}
