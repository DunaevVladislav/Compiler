#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
/// <summary>
/// Аргумент командной строки для вывода восходящего разбора
/// </summary>
#define ARG_ANALYSIS "-oa"
/// <summary>
/// Имя файла, в который выводится восходящий разбор
/// </summary>
extern string analysis_file_name;
/// <summary>
/// Выводить ли восходящий разбор
/// </summary>
extern bool out_analysis;

/// <summary>
/// Аргумент командной строки для вывода разбора исходного кода на терминалы
/// </summary>
#define ARG_TERMINAL_ANALYSIS "-ota"
/// <summary>
/// Имя файла, в который выводится разбор исходного кода на терминалы
/// </summary>
extern string terminal_analysis_file_name;
/// <summary>
/// Выводить ли разбор исходного кода на терминалы
/// </summary>
extern bool out_terminal_analysis;

/// <summary>
/// Аргумент, для указания файла, в который будет скопмилирована программа
/// </summary>
#define ARG_OUTPUT_FILE "-o"
/// <summary>
/// Имя файла в который осуществляется вывод скомпилированного кода
/// </summary>
extern string output_file_name;
/// <summary>
/// Выводить ли скомпилированный код в указанный файл
/// </summary>
extern bool out_file_declared;

/// <summary>
/// Аргумент, для вывода help
/// </summary>
#define ARG_HELP "-h"
/// <summary>
/// Выводить ли help
/// </summary>
extern bool out_help;

/// <summary>
/// Имя файла с исходным кодом программы
/// </summary>
extern string input_file_name;

/// <summary>
/// Функция устанавливающие необходимые флаг для работы с аргументами командной строки
/// </summary>
/// <param name="argc">Количество аргументов</param>
/// <param name="argv">Аргументы</param>
void parce_args(const int& argc, char* argv[]);