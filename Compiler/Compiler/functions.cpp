#include "functions.h"
using namespace std;

/// <summary>
/// Выходить из программы с выводом информации об ошибке
/// </summary>
/// <param name="message">Сообщение, выводимое на экран</param>
void exit_error(const char* message) {
	puts(message);
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ || __CYGWIN__ )
    system("pause");
#endif
	exit(0);
}

/// <summary>
/// функция считывания файла
/// </summary>
/// <param name="file_name">имя файла</param>
/// <param name="data">считанные данные</param>
/// <returns>-1 если файл не найден, иначе количество считанных байт</returns>
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
/// Разделяет строку на линни(split by '\n')
/// </summary>
/// <param name="data">Строка</param>
/// <returns>Полученные линии</returns>
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
/// функция, убирающая лишнии раздилители
/// </summary>
/// <param name="source">исходный код программы</param>
/// <param name="source_size">размер исходного кода</param>
/// <returns>результат обработки</returns>
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