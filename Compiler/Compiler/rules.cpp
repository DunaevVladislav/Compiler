#include "rules.h"
using namespace std;

/// <summary>
/// Объявление шаблона с переменным количеством параметров
/// </summary>
template<typename... T>
/// <summary>
/// Конструктор rule
/// </summary>
/// <param name="left_str">Левая часть правила</param>
/// <param name="...rights">Правая часть правила</param>
rule::rule(const string& left_str, const T&... rights) {
	vector<string> args = { rights... };
	left = get_index(left_str);
	if (left == -1) throw runtime_error("Dictionary not include " + left_str);
	if (!is_determinal(left)) throw runtime_error("Left part of rules can't include terminal: " + left_str);
	right.clear();
	for (string& s : args) {
		right.push_back(get_index(s));
		if (right.back() == -1) throw runtime_error("Dictionary not include " + s);
	}
}

/// <summary>
/// Правила
/// </summary>
vector<rule> rules;

/// <summary>
/// Инициализация правил
/// </summary>
void initial_rules() {
	rules.emplace_back(rule("<Program>", "<Var_declare>", "<Calculation_descr>"));
	rules.emplace_back(rule("<Var_declare>", "<Prefix_var_declare>", "logical", ";"));
	rules.emplace_back(rule("<Prefix_var_declare>", "var", "ident", ":"));
	rules.emplace_back(rule("<Prefix_var_declare>", "var", "ident", "<Var_list>", ":"));
	rules.emplace_back(rule("<Var_list>", ",", "ident", "<Var_list>"));
	rules.emplace_back(rule("<Var_list>", ",", "ident"));
	rules.emplace_back(rule("<Calculation_descr>", "begin", "<Function_list>", "end"));
	rules.emplace_back(rule("<Function_list>", "<Assignment>"));
	rules.emplace_back(rule("<Function_list>", "<Assignment>", "<Function_list>"));
	rules.emplace_back(rule("<Function_list>", "<Function>"));
	rules.emplace_back(rule("<Function_list>", "<Function>", "<Function_list>"));
	rules.emplace_back(rule("<Assignment>", "ident", "=", "<Expression>", ";"));
	rules.emplace_back(rule("<Expression>", "<Unary_op>", "<Sub_expression>"));
	rules.emplace_back(rule("<Expression>", "<Sub_expression>"));
	rules.emplace_back(rule("<Sub_expression>", "(", "<Expression>", ")"));
	rules.emplace_back(rule("<Sub_expression>", "<Operand>"));
	rules.emplace_back(rule("<Sub_expression>", "<Sub_expression>", "<Binary_op>", "<Sub_expression>"));
	rules.emplace_back(rule("<Unary_op>", "not"));
	rules.emplace_back(rule("<Binary_op>", "and"));
	rules.emplace_back(rule("<Binary_op>", "or"));
	rules.emplace_back(rule("<Binary_op>", "equ"));
	rules.emplace_back(rule("<Operand>", "ident"));
	rules.emplace_back(rule("<Operand>", "<Const>"));
	rules.emplace_back(rule("<Const>", "0"));
	rules.emplace_back(rule("<Const>", "1"));
	rules.emplace_back(rule("<Function>", "read", "(", "ident", "<Var_list>", ")", ";"));
	rules.emplace_back(rule("<Function>", "write", "(", "ident", "<Var_list>", ")", ";"));
	rules.emplace_back(rule("<Function>", "if", "<Expression>", "then", "<Function_list>", "else", "<Function_list>", "end_if", ";"));
	rules.emplace_back(rule("<Function>", "<Prefix_io>", ")", ";"));
	rules.emplace_back(rule("<Function>", "<Prefix_io>", ")", ";"));
	rules.emplace_back(rule("<Prefix_io>", "write", "(", "ident"));
	rules.emplace_back(rule("<Prefix_io>", "read", "(", "ident"));
}