#include "functions.h"
using namespace std;

/// <summary>
/// �������� �� ��������� � ������� ���������� �� ������
/// </summary>
/// <param name="message">���������, ��������� �� �����</param>
void exit_error(const char* message) {
	puts(message);
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ || __CYGWIN__ )
    system("pause");
#endif
	exit(0);
}

/// <summary>
/// ������� ���������� �����
/// </summary>
/// <param name="file_name">��� �����</param>
/// <param name="data">��������� ������</param>
/// <returns>-1 ���� ���� �� ������, ����� ���������� ��������� ����</returns>
int read_file(const char* file_name, char*& data) {
	FILE* source = fopen(file_name, "r");
	if (!source) return -1;
	size_t source_size = 0;
	while (~getc(source)) source_size++;
	fseek(source, 0L, SEEK_SET);
	data = new char[source_size + 1];
	for (size_t i = 0; i < source_size; ++i) data[i] = getc(source);
	data[source_size] = '\0';
	fclose(source);
	return static_cast<int>(source_size);
}

/// <summary>
/// ��������� ������ �� �����(split by '\n')
/// </summary>
/// <param name="data">������</param>
/// <returns>���������� �����</returns>
vector<string> split_lines(char*& data) {
	vector<string> lines;
	int ind = 0;
	for (int i = 0; data[i] != '\0'; ++i) {
		if (lines.size() == ind) lines.emplace_back("");
		if (data[i] == '\n') ind++;
		else lines[ind].push_back(data[i]);
	}
	return lines;
}

/// <summary>
/// �������, ��������� ������ �����������
/// </summary>
/// <param name="source">�������� ��� ���������</param>
/// <param name="source_size">������ ��������� ����</param>
/// <returns>��������� ���������</returns>
char* parce_code(const char* source, size_t source_size) {
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