#pragma once
#include "rules.h"
#include "automate.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cctype>
#include <exception>
#include <iostream>
#include "grammar_defines.h"
using namespace std;

/// <summary>
/// Инициализация словарей
/// </summary>
void initial();

/// <summary>
/// Полный словарь грамматики
/// </summary>
extern vector<string> dictionary;

/// <summary>
/// Терминальные символы
/// </summary>
extern vector<string> terminals;

/// <summary>
/// Нетерминальные символы
/// </summary>
extern vector<string> determinals;

/// <summary>
/// Является ли строка идентификатором
/// </summary>
/// <param name="s">Проверяемая строка</param>
/// <returns>-1 - идентификатор, с длиной > 11; 0 - не идентификатор; 1 - идентификатор</returns>
int is_ident(const string& s);

/// <summary>
/// Индекс слова из словаря
/// </summary>
/// <param name="s">Слово</param>
/// <returns>-1 - если слова нет в словаре, иначе индекс слова</returns>
int get_index(const string& s);

/// <summary>
/// Является ли слово термианльным символом
/// </summary>
/// <param name="s">Проверяемое слово</param>
/// <returns>Является ли слово терминальныи символом</returns>
bool is_terminal(const string& s);

/// <summary>
/// Является ли слово с индексом index терминальным символом
/// </summary>
/// <param name="index">index проверяемого слова</param>
/// <returns>Является ли слово с индексом index терминальным символом</returns>
bool is_terminal(const int& index);

/// <summary>
/// Является ли слово нетермианльным символом
/// </summary>
/// <param name="s">Проверяемое слово</param>
/// <returns>Является ли слово нетерминальным символом</returns>
bool is_determinal(const string& s);

/// <summary>
/// Является ли слово с индексом index нетерминальным символом
/// </summary>
/// <param name="index">index проверяемого слова</param>
/// <returns>Является ли слово с индексом index нетерминальным символом</returns>
bool is_determinal(const int& index);

/// <summary>
/// Терминал
/// </summary>
struct term {
	/// <summary>
	/// Индекс терминала
	/// </summary>
	int val;
	/// <summary>
	/// Индекс строки, в котором встретился терминал
	/// </summary>
	int ind_lines;
	/// <summary>
	/// Позиция в строке, где найден терминал
	/// </summary>
	int ind_pos;
	/// <summary>
	/// Конструктор
	/// </summary>
	/// <param name="val">Индекс терминала</param>
	/// <param name="indLines">Индекс строки, в котором встретился терминал</param>
	/// <param name="indPos">Позиция в строке, где найден терминал</param>
	term(const int& val, const int& indLines, const int& indPos) :
		val(val), ind_lines(indLines), ind_pos(indPos) {};
};

/// <summary>
/// Разделить строки на терминальные символы
/// </summary>
/// <param name="lines">Строки</param>
/// <returns>Полученные терминалы</returns>
/// <exception cref="exception">Если слово не является терминалом</exception>
vector<term*> split_on_terminals(const vector<string> & lines);

/// <summary>
/// Информация о терминале
/// </summary>
/// <param name="trm">Терминал</param>
/// <returns>Строку, предоставляющую информацию о терминале </returns>
string get_info(const term* trm);

/// <summary>
/// Восходящий анализ по заданным правилам
/// </summary>
/// <param name="input_line">Терминалы на входной ленте</param>
/// <returns>Последовательность номером правил, которые приведут к получению исходной ленты</returns>
vector<int> upstream_analysis(const vector<term*>& input_line);

/// <summary>
/// Возвращает идентификатор из входной ленты
/// </summary>
/// <param name="lines">Входная лента</param>
/// <param name="ind_lines">Индекс строки</param>
/// <param name="ind_pos">Индекс позиции начала идентификатора</param>
/// <returns>Идентификатор</returns>
string get_real_ident(const vector<string>& lines, const int& ind_lines, const int& ind_pos);

/// <summary>
/// Проверка кода на неизвестные идентификаторы или повторное объявление
/// </summary>
/// <param name="lines">Исходный код</param>
/// <param name="terms">Терминалы</param>
/// <param name="error_pos">Позиция найденного ошибочного идентификатора</param>
/// <returns>-1 - не найден ошибочный идентификатор, 0 - повтороное объявление, 1 - неизвестный идентификатор</returns>
int check_error_ident(const vector<string>& lines, const vector<term*>& terms, pair<int, int>&error_pos);