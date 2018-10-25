#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cctype>
#include <stdio.h>

using namespace std;

/// <summary>
/// ������� ���������� �����
/// </summary>
/// <param name="file_name">��� �����</param>
/// <param name="data">��������� ������</param>
/// <returns>-1 ���� ���� �� ������, ����� ���������� ��������� ����</returns>
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
/// �������, ��������� ������ �����������
/// </summary>
/// <param name="source">�������� ��� ���������</param>
/// <param name="source_size">������ ��������� ����</param>
/// <returns>��������� ���������</returns>
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
/// ����� ����� � ���������
/// </summary>
/// <param name="argc">���������� ���������� ��������� ������</param>
/// <param name="argv">��������� ��������� ������</param>
/// <returns>��� �������</returns>
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