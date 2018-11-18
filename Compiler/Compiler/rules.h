#pragma once
#include "grammar.h"
#include <vector>
#include <string>

using namespace std;

/// <summary>
/// Лексикографическое правило свертки
/// </summary>
struct rule {
	/// <summary>
	/// Индекс слова, являющийся левой частью правила
	/// </summary>
	int left;
	/// <summary>
	/// Правая часть правила
	/// </summary>
	vector<int> right;
	/// <summary>
	/// Объявление шаблона с переменным количеством параметров
	/// </summary>
	template<typename... T>
	/// <summary>
	/// Конструктор rule
	/// </summary>
	/// <param name="left_str">Левая часть правила</param>
	/// <param name="...rights">Правая часть правила</param>
	rule(const string& left_str, const T&... rights);
};

/// <summary>
/// Правила
/// </summary>
extern vector<rule> rules;

/// <summary>
/// Инициализация правил
/// </summary>
void initial_rules();