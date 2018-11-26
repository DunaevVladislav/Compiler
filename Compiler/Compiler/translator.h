#pragma once
#include "grammar.h"
#include "grammar_defines.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/// <summary>
/// Структура правил перевода
/// </summary>
struct translator_node {
	/// <summary>
	/// Вектор значений
	/// Содержит строки, в которые осуществляется перевод при применение определнного правила
	/// </summary>
	vector<string> value;
	/// <summary>
	/// Вектор индексов правил
	/// Содержит индексы лексем, перевод которых должен быть вставлен после каждой строки
	/// </summary>
	vector<int> lexeme_indexes;
	/// <summary>
	/// Конструктор translator_node
	/// </summary>
	/// <param name="First">Первая строка</param>
	/// <param name="...translations">int, string... индексы лексем и строки</param>
	explicit translator_node(const string& str);
};

/// <summary>
/// Правила перевода
/// </summary>
extern vector<translator_node> tranlation_rules;

/// <summary>
/// Инициализация транслятора
/// </summary>
void initial_translation();

/// <summary>
/// Применяет правило трансляции
/// </summary>
/// <param name="translation_magazine">Магазин транслятора</param>
/// <param name="ind_rules">Индекс правила</param>
string apply_rule(const vector<string>& translation_magazine, const int& ind_rules);