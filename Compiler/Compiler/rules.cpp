#include "rules.h"
#include <initializer_list>
using namespace std;

template<typename... T>
rule::rule(string left_str, const T&... rights) {
	left = get_index(left_str);
	if (left == -1) throw runtime_error("Dictionary not include " + left_str);
	if (!is_determinal(left)) throw runtime_error("Left part of rules can't include terminal: " + left_str);
	right.clear();
	for (auto&& s : initializer_list<string>{ rights... }) {
		right.push_back(get_index(s));
		if (right.back() == -1) throw runtime_error("Dictionary not include " + s);
	}
}

vector<rule> rules;

void initial_rules() {
	rules.push_back(rule("<Program>", "<Var_declare>", "<Calculation_descr>"));
	rules.push_back(rule("<Var_declare>", "<Prefix_var_declare>", "logical", ";"));
	rules.push_back(rule("<Prefix_var_declare>", "var", "ident", ":"));
	rules.push_back(rule("<Prefix_var_declare>", "var", "ident", "<Var_list>", ":"));
	rules.push_back(rule("<Var_list>", ",", "ident", "<Var_list>"));
	rules.push_back(rule("<Var_list>", ",", "ident"));
	rules.push_back(rule("<Calculation_descr>", "begin", "<Function_list>", "end"));
	rules.push_back(rule("<Function_list>", "<Assignment>"));
	rules.push_back(rule("<Function_list>", "<Assignment>", "<Function_list>"));
	rules.push_back(rule("<Function_list>", "<Function>"));
	rules.push_back(rule("<Function_list>", "<Function>", "<Function_list>"));
	rules.push_back(rule("<Assignment>", "ident", "=", "<Expression>", ";"));
	rules.push_back(rule("<Expression>", "<Unary_op>", "<Sub_expression>"));
	rules.push_back(rule("<Expression>", "<Sub_expression>"));
	rules.push_back(rule("<Sub_expression>", "(", "<Expression>", ")"));
	rules.push_back(rule("<Sub_expression>", "<Operand>"));
	rules.push_back(rule("<Sub_expression>", "<Sub_expression>", "<Binary_op>", "<Sub_expression>"));
	rules.push_back(rule("<Unary_op>", "not"));
	rules.push_back(rule("<Binary_op>", "and"));
	rules.push_back(rule("<Binary_op>", "or"));
	rules.push_back(rule("<Binary_op>", "equ"));
	rules.push_back(rule("<Operand>", "ident"));
	rules.push_back(rule("<Operand>", "<Const>"));
	rules.push_back(rule("<Const>", "0"));
	rules.push_back(rule("<Const>", "1"));
	rules.push_back(rule("<Function>", "read", "(", "ident", "<Var_list>", ")", ";"));
	rules.push_back(rule("<Function>", "write", "(", "ident", "<Var_list>", ")", ";"));
	rules.push_back(rule("<Function>", "if", "<Expression>", "then", "<Function_list>", "else", "<Function_list>","end_if", ";"));
	rules.push_back(rule("<Function>", "<Prefix_io>", ")", ";"));
	rules.push_back(rule("<Function>", "<Prefix_io>", ")", ";"));
	rules.push_back(rule("<Prefix_io>", "write", "(", "ident"));
	rules.push_back(rule("<Prefix_io>", "read", "(", "ident"));
}