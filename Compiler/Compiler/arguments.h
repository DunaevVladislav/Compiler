#pragma once
#include <stdio.h>
#include <string.h>
/// <summary>
/// Аргумент командной строки для вывода восходящего разбора
/// </summary>
#define ARG_ANALYSIS "-oa"
/// <summary>
/// Файл, в который выводится восходящий разбор
/// </summary>
#define DEFAULT_ANALYSIS_FILE "analysis.txt"
/// <summary>
/// Выводить ли восходящий разбор
/// </summary>
extern bool out_analysis;

/// <summary>
/// Аргумент командной строки для вывода разбора исходного кода на терминалы
/// </summary>
#define ARG_TERMINAL_ANALYSIS "-ota"
/// <summary>
/// Файл, в который выводится разбор исходного кода на терминалы
/// </summary>
#define DEFAULT_TERMINAL_ANALYSIS_FILE "terminal_analysis.txt"
/// <summary>
/// Выводить ли разбор исходного кода на терминалы
/// </summary>
extern bool out_terminal_analysis;

/// <summary>
/// Функция устанавливающие необходимые флаг для работы с аргументами командной строки
/// </summary>
/// <param name="argc">Количество аргументов</param>
/// <param name="argv">Аргументы</param>
void parce_args(const int& argc, char* argv[]);