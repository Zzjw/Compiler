#include <cstdio>

#include "Scanner.h"
#include "token_def.h"
Scanner::Scanner() {
	row = 1;
	col = 0;
}

bool Scanner::scan() {
	char ch;
	std::string cur;
	tokentype curtype = NONE;
	while((ch = getchar()) != EOF) {
		col++;
		if (ch == '\n') ++row, col = 1;
		if (isDigtal(ch)) 
			switch (curtype) {
				case NONE:
				case NUM: curtype = NUM; cur.push_back(ch); break;
				case STRING:
				case IDorKEY: cur.push_back(ch); break;
				case SYMBOL: 
					if (isMember(symbols, cur)) result.push_back({"SYM", cur});
					else {
						error = "invalid operator symbol!";
						return 0;
					}
					cur.clear();
					cur.push_back(ch);
					curtype = NUM;
			}
		else if (isAlphabet(ch))
			switch (curtype) {
				case NONE:
				case IDorKEY: curtype = IDorKEY; cur.push_back(ch); break;
				case STRING: cur.push_back(ch); break;
				case NUM: error="number only can be made by digit!"; return 0;
				case SYMBOL: 
					if (isMember(symbols, cur)) result.push_back({"SYM", cur});
					else {
						error = "invalid operator symbol!";
						return 0;
					}
					cur.clear();
					cur.push_back(ch);
					curtype = IDorKEY;
			}
		else if (isSymbol(ch))
			switch (curtype) {
				case NONE:
				case SYMBOL: curtype = SYMBOL; cur.push_back(ch); break;
				case IDorKEY: 
					if (isMember(keywords, cur)) result.push_back({"KEY", cur});
					else result.push_back({"ID", cur});
					cur.clear();
					cur.push_back(ch);
					curtype = SYMBOL;
					break;
				case STRING: cur.push_back(ch); break;
				case NUM: 
					result.push_back({"NUM", cur});
					cur.clear();
					cur.push_back(ch);
					curtype = SYMBOL;
			}
		else if (ch=='\n' || ch=='\t' || ch==' ')
			switch (curtype) {
				case SYMBOL:  
					if (isMember(symbols, cur)) result.push_back({"SYM", cur});
					else {
						error = "invalid operator symbol!";
						return 0;
					}
					curtype = NONE; 
					cur.clear();
					break;
				case IDorKEY: 
					if (isMember(keywords, cur)) result.push_back({"KEY", cur});
					else result.push_back({"ID", cur});
					cur.clear();
					curtype = NONE; 
					break;
				case STRING: cur.push_back(ch); break;
				case NUM: 
					result.push_back({"NUM", cur});
					cur.clear();
					curtype = NONE; 
					break;
			}
		else if (ch=='{') 
			switch (curtype) {
				case SYMBOL:  
					if (isMember(symbols, cur)) result.push_back({"SYM", cur});
					else {
						error = "invalid operator symbol!";
						return 0;
					}
					curtype = ANNOTATION; 
					cur.clear();
					break;
				case IDorKEY: 
					if (isMember(keywords, cur)) result.push_back({"KEY", cur});
					else result.push_back({"ID", cur});
					cur.clear();
					curtype = ANNOTATION; 
					break;
				case NUM: 
					result.push_back({"NUM", cur});
					cur.clear();
					curtype = ANNOTATION; 
					break;
				case STRING: cur.push_back(ch); break;
				case ANNOTATION:
					error = "should have } before here!";
					return 0;
				case NONE: curtype = ANNOTATION; break;
			}
		else if (ch=='}') 
			switch (curtype) {
				case NONE:
				case SYMBOL: 
				case IDorKEY: 
				case NUM: 
					error = "should have '{' before here!";
					break;
				case STRING: cur.push_back(ch); break;
				case ANNOTATION:
					curtype = NONE;
			}
		else if (ch=='\'')
			switch (curtype) {
				case NONE: curtype = STRING; break;
				case SYMBOL: 
					if (isMember(symbols, cur)) result.push_back({"SYM", cur});
					else {
						error = "invalid operator symbol!";
						return 0;
					}
					curtype = STRING; 
					cur.clear();
					break;
				case IDorKEY: 
				case NUM: 
					error = "the symbol ' cannot be written here!";
					break;
				case STRING: result.push_back({"STR", cur}); curtype = NONE; cur.clear(); break;
			}
		else 
			switch (curtype) {
				case STRING: cur.push_back(ch);
				case ANNOTATION: break;
				case NONE: 
				case SYMBOL: 
				case IDorKEY: 
				case NUM: 
					error = "invalid char!";
					break;
			}
	}
	
	switch (curtype) {
		case STRING: error = "should be have symbol ' !"; return 0;
		case ANNOTATION: error = "should be have symbol } !"; return 0;
		case SYMBOL: 
			if (isMember(symbols, cur)) result.push_back({"SYM", cur});
			else {
				error = "invalid operator symbol!";
				return 0;
			}
			curtype = STRING; 
			break;
		case IDorKEY: 
			if (isMember(keywords, cur)) result.push_back({"KEY", cur});
			else result.push_back({"ID", cur});
			break;
		case NUM: 
			result.push_back({"NUM", cur});
	}
	return 1;
} 


bool Scanner::isDigtal(char ch) const {
	return ch>='0' && ch<='9';
}
bool Scanner::isAlphabet(char ch) const {
	return (ch>='a' && ch<='z') || (ch>='A' && ch<='Z');
}
bool Scanner::isSymbol(char ch) const {
	std::string symbolchar{"+-*/><=;():,"};
	return isMember(symbolchar, ch);
}
void Scanner::puterror() const {
	printf("error in row=%d, column=%d: %s", row, col, error.c_str());
}
void Scanner::putresult() const {
	int cnt = 0;
	for (auto &tmp: result) {
		printf("(%s,%s)%c", tmp.first.c_str(), tmp.second.c_str(), "\n\t"[(++cnt)%4!=0]);
	}
}
std::vector<std::pair<std::string, std::string>> Scanner::lexicalAnalysis() const {
	return result;
}
