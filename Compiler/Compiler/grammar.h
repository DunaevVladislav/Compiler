#pragma once
#include "rules.h"
#include "automate.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cctype>
#include <exception>
using namespace std;

const string END_OF_TAPE = "▲▲▲";

/// <summary>
/// Максимальный размер индентификатора
/// </summary>
const size_t _MAX_IDENT_LENGTH = 11;

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
int is_ident(string s);

/// <summary>
/// Индекс слова из словаря
/// </summary>
/// <param name="s">Слово</param>
/// <returns>-1 - если слова нет в словаре, иначе индекс слова</returns>
int get_index(string s);

/// <summary>
/// Является ли слово термианльным символом
/// </summary>
/// <param name="s">Проверяемое слово</param>
/// <returns>Является ли слово терминальныи символом</returns>
bool is_terminal(string s);

/// <summary>
/// Является ли слово с индексом index терминальным символом
/// </summary>
/// <param name="index">index проверяемого слова</param>
/// <returns>Является ли слово с индексом index терминальным символом</returns>
bool is_terminal(int index);

/// <summary>
/// Является ли слово нетермианльным символом
/// </summary>
/// <param name="s">Проверяемое слово</param>
/// <returns>Является ли слово нетерминальным символом</returns>
bool is_determinal(string s);

/// <summary>
/// Является ли слово с индексом index нетерминальным символом
/// </summary>
/// <param name="index">index проверяемого слова</param>
/// <returns>Является ли слово с индексом index нетерминальным символом</returns>
bool is_determinal(int index);

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
	int indLines;
	/// <summary>
	/// Позиция в строке, где найден терминал
	/// </summary>
	int indPos;
	/// <summary>
	/// Конструктор
	/// </summary>
	/// <param name="val">Индекс терминала</param>
	/// <param name="indLines">Индекс строки, в котором встретился терминал</param>
	/// <param name="indPos">Позиция в строке, где найден терминал</param>
	term(int val, int indLines, int indPos) :
		val(val), indLines(indLines), indPos(indPos) {};
};

/// <summary>
/// Разделить строки на терминальные символы
/// </summary>
/// <param name="lines">Строки</param>
/// <returns>Полученные терминалы</returns>
/// <exception cref="exception">Если слово не является терминалом</exception>
vector<term*> split_on_terminals(vector<string> & lines);

/// <summary>
/// Информация о терминале
/// </summary>
/// <param name="trm">Терминал</param>
/// <returns>Строку, предоставляющую информацию о терминале </returns>
string get_info(term* trm);