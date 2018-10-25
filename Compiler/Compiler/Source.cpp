#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cctype>
#include <stdio.h>

using namespace std;

/// <summary>
/// функция считывания файла
/// </summary>
/// <param name="file_name">имя файла</param>
/// <param name="data">считанные данные</param>
/// <returns>-1 если файл не найден, иначе количество считанных байт</returns>
int read_file(char* file_name, char*& data) {
	FILE* source = fopen(file_name, "r");
	if (!source) return -1;
	size_t source_size = 0;
	while (~getc(source)) source_size++;
	fseek(source, 0L, SEEK_SET);
	data = new char[source_size + 1];
	for (size_t i = 0; i < source_size; ++i) data[i] = getc(source);
	data[source_size] = '\0';
	fclose(source);
	return source_size;
}

/// <summary>
/// функция, убирающая лишнии раздилители
/// </summary>
/// <param name="source">исходный код программы</param>
/// <param name="source_size">размер исходного кода</param>
/// <returns>результат обработки</returns>
char*& parce_code(const char* source, size_t source_size = 0) {
	if (!source_size) source_size = strlen(source);
	char* code = new char[source_size];
	int ptr = -1;
	for (size_t i = 0; i < source_size; ++i) {
		if (!isspace(source[i])) code[++ptr] = source[i];
		else if (ptr != -1 && code[ptr] != ' ') code[++ptr] = ' ';
	};
	if (ptr == -1 || code[ptr] != ' ') ptr++;
	code[ptr] = '\0';
	return code;
}


/// <summary>
/// точка входа в программу
/// </summary>
/// <param name="argc">количество аргументов командной строки</param>
/// <param name="argv">аргументы командной строки</param>
/// <returns>код ошикбки</returns>
int main(int argc, char* argv[]) {
	if (argc == 1) {
		puts("Choice file");
		return 0;
	}

	char* file_name = argv[1], *source;
	size_t source_size = read_file(file_name, source);
	if (!~read_file(file_name, source)) {
		puts("File not exist");
		return 0;
	}
	char* code = parce_code(source, source_size);
	printf("%s", code);
	if (code[0] != '\0') delete[] code;
	if (source[0] != '\0') delete[] source;
	system("pause");
	return 0;
}