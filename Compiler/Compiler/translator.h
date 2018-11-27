#pragma once
#include "grammar.h"
#include "grammar_defines.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/// <summary>
/// —труктура правил перевода
/// </summary>
struct translator_node {
	/// <summary>
	/// ¬ектор значений
	/// —одержит строки, в которые осуществл€етс€ перевод при применение определнного правила
	/// </summary>
	vector<string> value;
	/// <summary>
	/// ¬ектор индексов правил
	/// —одержит индексы лексем, перевод которых должен быть вставлен после каждой строки
	/// </summary>
	vector<int> lexeme_indexes;
	/// <summary>
	///  онструктор translator_node
	/// </summary>
	/// <param name="str">—трока, котора€ на которую происходит замена при соответсвующей свертки</param>
	explicit translator_node(const string& str);
};

/// <summary>
/// ѕравила перевода
/// </summary>
extern vector<translator_node> tranlation_rules;

/// <summary>
/// »нициализаци€ трансл€тора
/// </summary>
void initial_translation();

/// <summary>
/// ѕримен€ет правило трансл€ции
/// </summary>
/// <param name="translation_magazine">ћагазин трансл€тора</param>
/// <param name="ind_rules">»ндекс правила</param>
string apply_rule(const vector<string>& translation_magazine, const int& ind_rules);