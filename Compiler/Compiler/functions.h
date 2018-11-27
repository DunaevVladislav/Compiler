#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "grammar.h"
#include <cstdio>
#include <cctype>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <thread>
using namespace std;

/// <summary>
/// Выходить из программы с выводом информации об ошибке
/// </summary>
/// <param name="message">Сообщение, выводимое на экран</param>
void exit_error(const char* message);

/// <summary>
/// функция считывания файла
/// </summary>
/// <param name="file_name">имя файла</param>
/// <param name="data">считанные данные</param>
/// <returns>-1 если файл не найден, иначе количество считанных байт</returns>
int read_file(const char* file_name, char*& data);

/// <summary>
/// Разделяет строку на линни(split by '\n')
/// </summary>
/// <param name="data">Строка</param>
/// <returns>Полученные линии</returns>
vector<string> split_lines(char*& data);

/// <summary>
/// функция, убирающая лишнии раздилители
/// </summary>
/// <param name="source">исходный код программы</param>
/// <param name="source_size">размер исходного кода</param>
/// <returns>результат обработки</returns>
char* parce_code(const char* source, size_t source_size = 0);

/// <summary>
/// Выводит информацию о разборе исходного кода на терминалы (если установлен соотвествующий аргумент)
/// </summary>
/// <param name="terms">Терминалы</param>
void output_terminal_analysis(const vector<term*>& terms);

/// <summary>
/// Проверяет необходимость вывода help
/// Выводит его при необходимости
/// </summary>
void check_help();

/// <summary>
/// Считывает исходный код из файла и вызывает функции для разбивание его на терминалы
/// </summary>
/// <param name="terms">Терминалы</param>
/// <param name="lines">Исходный код, построчно</param>
void get_terminals(vector<term*>& terms,  vector<string>& lines);

/// <summary>
/// Вызывает восходящее распознование и проверку идентификаторов
/// </summary>
/// <param name="terms">Терминалы</param>
/// <param name="lines">Исходный код, построчно</param>
void analysis_grammar(const vector<term*>& terms, const vector<string>& lines);

/// <summary>
/// Выводит информацию об успешной компиляции
/// </summary>
void ouput_success_result();

/// <summary>
/// Освобождение ресурсов
/// </summary>
void dispose(const vector<term*>& terms);