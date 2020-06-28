#ifndef TOKEN_DEF_H
#define TOKEN_DEF_H
#include <vector>
#include <string>
enum tokentype{
	STRING, NUM, IDorKEY, ANNOTATION, SYMBOL, NONE
};
const std::vector<std::string> keywords{"or", "and", "int", "bool", "char", "while", "do", "if", "then", "else", "end", "repeat", "until", "read", "write"};
const std::vector<std::string> symbols{">", "<=", ">=", ",", ";", ":=", "+", "-", "*", "/", "(", ")", "<", "="};
const std::string validchars{"0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM:+=-*/(){}:<>='\t\n "};
bool isMember(const std::vector<std::string> Set, std::string member);
bool isMember(const std::string Set, char member);
bool isValid(char ch);
#endif
