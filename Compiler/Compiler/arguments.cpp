#include "arguments.h"

/// <summary>
/// Выводить ли восходящий разбор
/// </summary>
bool out_analysis = false;
/// <summary>
/// Имя файла, в который выводится восходящий разбор
/// </summary>
string analysis_file_name;

/// <summary>
/// Выводить ли разбор исходного кода на терминалы
/// </summary>
bool out_terminal_analysis = false;
/// <summary>
/// Имя файла, в который выводится разбор исходного кода на терминалы
/// </summary>
string terminal_analysis_file_name;

/// <summary>
/// Имя файла в который осуществляется вывод скомпилированного кода
/// </summary>
string output_file_name;

/// <summary>
/// Выводить ли скомпилированный код в указанный файл
/// </summary>
bool out_file_declared = false;

/// <summary>
/// Имя файла с исходным кодом программы
/// </summary>
string input_file_name;

/// <summary>
/// Выводить ли help
/// </summary>
bool out_help = false;

/// <summary>
/// Проверяет имя файла на валидность
/// </summary>
/// <param name="file_name">Имя файла</param>
/// <returns>Результат проверки</returns>
bool _validate_filename(const char* file_name) {
	FILE* fdsc = fopen(file_name, "w");
	if (fdsc) {
		fclose(fdsc);
		return true;
	}
	return false;
}

/// <summary>
/// Функция устанавливающие необходимые флаг для работы с аргументами командной строки
/// </summary>
/// <param name="argc">Количество аргументов</param>
/// <param name="argv">Аргументы</param>
void parce_args(const int & argc, char * argv[])
{
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], ARG_OUTPUT_FILE) == 0) {
			out_file_declared = true;
			if (i + 1 >= argc)
				throw runtime_error((string)"Not found file name after " + ARG_OUTPUT_FILE);
			output_file_name = argv[++i];
			if (!_validate_filename(output_file_name.c_str()))
				throw runtime_error((string)"Can't create file: " + output_file_name);
			continue;
		}
		if (strcmp(argv[i], ARG_ANALYSIS) == 0) {
			out_analysis = true;
			if (i + 1 >= argc)
				throw runtime_error((string)"Not found file name after " + ARG_ANALYSIS);
			analysis_file_name = argv[++i];
			if (!_validate_filename(analysis_file_name.c_str()))
				throw runtime_error((string)"Can't create file: " + analysis_file_name);
			continue;
		}
		if (strcmp(argv[i], ARG_TERMINAL_ANALYSIS) == 0) {
			out_terminal_analysis = true;
			if (i + 1 >= argc)
				throw runtime_error((string)"Not found file name after " + ARG_ANALYSIS);
			terminal_analysis_file_name = argv[++i];
			if (!_validate_filename(terminal_analysis_file_name.c_str()))
				throw runtime_error((string)"Can't create file: " + terminal_analysis_file_name);
			continue;
		}
		if (strcmp(argv[i], ARG_HELP) == 0) {
			out_help = true;
			continue;
		}
		input_file_name = argv[i];
	}
}
