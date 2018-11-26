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
	vector<int> lexeme_index;
	/// <summary>
	///  онструктор translator_node
	/// </summary>
	/// <param name="First">ѕерва€ строка</param>
	/// <param name="...translations">int, string... индексы лексем и строки</param>
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
