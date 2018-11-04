#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cctype>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
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
int read_file(char* file_name, char*& data);

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