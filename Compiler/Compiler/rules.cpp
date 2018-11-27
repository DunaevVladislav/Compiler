#include "rules.h"
using namespace std;

/// <summary>
/// ���������� ������� � ���������� ����������� ����������
/// </summary>
template<typename... T>
/// <summary>
/// ����������� rule
/// </summary>
/// <param name="left_str">����� ����� �������</param>
/// <param name="...rights">������ ����� �������</param>
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
/// �������
/// </summary>
vector<rule> rules;

/// <summary>
/// ������������� ������
/// </summary>
void initial_rules() {
	rules.emplace_back("<Program>", "<Var_declare>", "<Calculation_descr>");
	rules.emplace_back("<Var_declare>", "<Prefix_var_declare>", "logical", ";");
	rules.emplace_back("<Prefix_var_declare>", "var", "ident", ":");
	rules.emplace_back("<Prefix_var_declare>", "var", "ident", "<Var_list>", ":");
	rules.emplace_back("<Var_list>", ",", "ident", "<Var_list>");
	rules.emplace_back("<Var_list>", ",", "ident");
	rules.emplace_back("<Calculation_descr>", "begin", "<Function_list>", "end");
	rules.emplace_back("<Function_list>", "<Assignment>");
	rules.emplace_back("<Function_list>", "<Assignment>", "<Function_list>");
	rules.emplace_back("<Function_list>", "<Function>");
	rules.emplace_back("<Function_list>", "<Function>", "<Function_list>");
	rules.emplace_back("<Assignment>", "ident", "=", "<Expression>", ";");
	rules.emplace_back("<Expression>", "<Unary_op>", "<Sub_expression>");
	rules.emplace_back("<Expression>", "<Sub_expression>");
	rules.emplace_back("<Sub_expression>", "(", "<Expression>", ")");
	rules.emplace_back("<Sub_expression>", "<Operand>");
	rules.emplace_back("<Sub_expression>", "<Sub_expression>", "<Binary_op>", "<Sub_expression>");
	rules.emplace_back("<Unary_op>", "not");
	rules.emplace_back("<Binary_op>", "and");
	rules.emplace_back("<Binary_op>", "or");
	rules.emplace_back("<Binary_op>", "equ");
	rules.emplace_back("<Operand>", "ident");
	rules.emplace_back("<Operand>", "<Const>");
	rules.emplace_back("<Const>", "0");
	rules.emplace_back("<Const>", "1");
	rules.emplace_back("<Function>", "read", "(", "ident", "<Var_list>", ")", ";");
	rules.emplace_back("<Function>", "write", "(", "ident", "<Var_list>", ")", ";");
	rules.emplace_back("<Function>", "if", "<Expression>", "then", "<Function_list>", "else", "<Function_list>", "end_if", ";");
	rules.emplace_back("<Function>", "<Prefix_io>", ")", ";");
	rules.emplace_back("<Function>", "<Prefix_io>", ")", ";");
	rules.emplace_back("<Prefix_io>", "read", "(", "ident");
	rules.emplace_back("<Prefix_io>", "write", "(", "ident");
}