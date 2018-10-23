#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc == 1) {
		puts("Choice file");
		return 0;
	}

	char* FileName = argv[1];
	FILE* source = fopen(FileName, "r");
	if (!source) {
		puts("File not exist");
		return 0;
	}


#ifdef _FROM_VS
	system("pause");
#endif
	return 0;
}