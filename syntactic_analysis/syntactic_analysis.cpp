#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "Parser.h"

using namespace std;

void showUsage(const char *program) {
	printf("\nUsage: %s $(source file path) [$(target file path)]\n", program);
	exit(0);
}

int main(int argc, char *argv[]){
	if (argc!=2 && argc!=3) {
		showUsage(argv[0]);
	}
	freopen(argv[1], "r", stdin);
	if (argc == 3) freopen(argv[2], "w", stdout);
	
	Parser parser;
	parser.parsing();
	parser.putresult();
}

