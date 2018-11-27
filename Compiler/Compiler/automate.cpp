#include "automate.h"
#include <vector>
#include <string>
#include <initializer_list>

using namespace std;

/// <summary>
/// Детерминированный восходящий автомат
/// </summary>
vector<int>** automate;

/// <summary>
/// Объявление шаблона с переменным количеством параметров
/// </summary>
template<typename... T>
/// <summary>
/// Добавить в автомат переходы
/// </summary>
/// <param name="magazine_top">Символ на вершине автомата</param>
/// <param name="terminal">Символ на входной ленте</param>
/// <param name="...transitions">Допустимые переходы</param>
void _add_in_automate(const string& magazine_top, const string& terminal, const T&... transitions) {
	vector<int> args = { transitions... };
	int term_ind = get_index(terminal);
	if (!is_terminal(term_ind)) throw runtime_error("Terminal dictionary not include " + terminal);
	int mag_ind = get_index(magazine_top);
	if (mag_ind == -1) throw runtime_error("Dictionary not include " + magazine_top);
	for (int& s : args) {
		automate[term_ind][mag_ind].push_back(s - 1);
	}
}

/// <summary>
/// Инициализация автомата
/// </summary>
void initial_automate() {
	automate = new vector<int>*[terminals.size()];
	for (int i = 0; i < terminals.size(); ++i) {
		automate[i] = new vector<int>[dictionary.size()];
	}
	_add_in_automate("var", "ident", 0);
	_add_in_automate("begin", "read", 0);
	_add_in_automate("begin", "write", 0);
	_add_in_automate("begin", "if", 0);
	_add_in_automate("begin", "ident", 0);
	_add_in_automate("end", END_OF_TAPE, 7);
	_add_in_automate("logical", ";", 0);

	_add_in_automate("not", "0", 18);
	_add_in_automate("not", "1", 18);
	_add_in_automate("not", "ident", 18);
	_add_in_automate("not", "(", 18);
	_add_in_automate("and", "0", 19);
	_add_in_automate("and", "1", 19);
	_add_in_automate("and", "ident", 19);
	_add_in_automate("and", "(", 19);
	_add_in_automate("equ", "0", 21);
	_add_in_automate("equ", "1", 21);
	_add_in_automate("equ", "ident", 21);
	_add_in_automate("equ", "(", 21);
	_add_in_automate("or", "0", 20);
	_add_in_automate("or", "1", 20);
	_add_in_automate("or", "ident", 20);
	_add_in_automate("or", "(", 20);

	_add_in_automate("read", "(", 0);
	_add_in_automate("write", "(", 0);

	_add_in_automate("if", "0", 0);
	_add_in_automate("if", "1", 0);
	_add_in_automate("if", "ident", 0);
	_add_in_automate("if", "(", 0);
	_add_in_automate("then", "read", 0);
	_add_in_automate("then", "write", 0);
	_add_in_automate("then", "if", 0);
	_add_in_automate("then", "ident", 0);
	_add_in_automate("else", "read", 0);
	_add_in_automate("else", "write", 0);
	_add_in_automate("else", "if", 0);
	_add_in_automate("else", "ident", 0);
	_add_in_automate("end_if", ";", 0);

	_add_in_automate("0", "and", 24);
	_add_in_automate("0", "equ", 24);
	_add_in_automate("0", "or", 24);
	_add_in_automate("0", ";", 24);
	_add_in_automate("0", ")", 24);
	_add_in_automate("0", "then", 24);
	_add_in_automate("1", "and", 25);
	_add_in_automate("1", "equ", 25);
	_add_in_automate("1", "or", 25);
	_add_in_automate("1", ";", 25);
	_add_in_automate("1", ")", 25);
	_add_in_automate("1", "then", 25);

	_add_in_automate("ident", "and", 22);
	_add_in_automate("ident", "equ", 22);
	_add_in_automate("ident", "or", 22);
	_add_in_automate("ident", ";", 22);
	_add_in_automate("ident", "then", 22);
	_add_in_automate("ident", ":", 6, 0);
	_add_in_automate("ident", ",", 0);
	_add_in_automate("ident", "=", 0);
	_add_in_automate("ident", ")", 6, 31,32, 22);

	_add_in_automate(";", "begin", 2);
	_add_in_automate(";", "end", 12, 26, 27, 28, 29, 30);
	_add_in_automate(";", "read", 12, 26, 27, 28, 29, 30);
	_add_in_automate(";", "write", 12, 26, 27, 28, 29, 30);
	_add_in_automate(";", "if", 12, 26, 27, 28, 29, 30);
	_add_in_automate(";", "ident", 12, 26, 27, 28, 29, 30);
	_add_in_automate(";", "else", 12, 26, 27, 28, 29, 30);
	_add_in_automate(";", "end_if", 12, 26, 27, 28, 29, 30);

	_add_in_automate(":", "logical", 3, 4);
	_add_in_automate(",", "ident", 0);

	_add_in_automate("=", "not", 0);
	_add_in_automate("=", "0", 0);
	_add_in_automate("=", "1", 0);
	_add_in_automate("=", "ident", 0);
	_add_in_automate("=", "(", 0);

	_add_in_automate("(", "not", 0);
	_add_in_automate("(", "0", 0);
	_add_in_automate("(", "1", 0);
	_add_in_automate("(", "ident", 0);
	_add_in_automate("(", "(", 0);


	_add_in_automate(")", "and", 15);
	_add_in_automate(")", "equ", 15);
	_add_in_automate(")", "or", 15);
	_add_in_automate(")", ";", 15, 0);
	_add_in_automate(")", ")", 15);
	_add_in_automate(")", "then", 15);

	_add_in_automate("<Program>", END_OF_TAPE, SUCCESS + 1);
	_add_in_automate("<Var_declare>", "begin", 0);
	_add_in_automate("<Var_list>", ":", 5, 0);
	_add_in_automate("<Var_list>", ")", 5, 0);
	_add_in_automate("<Prefix_var_declare>", "logical", 0);
	_add_in_automate("<Calculation_descr>", END_OF_TAPE, 1);
	
	_add_in_automate("<Function_list>", "end", 9, 11, 0);
	_add_in_automate("<Function_list>", "else", 9, 11, 0);
	_add_in_automate("<Function_list>", "end_if", 9, 11, 0);

	_add_in_automate("<Assignment>", "end", 8);
	_add_in_automate("<Assignment>", "read", 0);
	_add_in_automate("<Assignment>", "write", 0);
	_add_in_automate("<Assignment>", "if", 0);
	_add_in_automate("<Assignment>", "ident", 0);
	_add_in_automate("<Assignment>", "else", 8);
	_add_in_automate("<Assignment>", "end_if", 8);

	_add_in_automate("<Function>", "end", 10);
	_add_in_automate("<Function>", "read", 0);
	_add_in_automate("<Function>", "write", 0);
	_add_in_automate("<Function>", "if", 0);
	_add_in_automate("<Function>", "ident", 0);
	_add_in_automate("<Function>", "else", 10);
	_add_in_automate("<Function>", "end_if", 10);

	_add_in_automate("<Expression>", "then", 0);
	_add_in_automate("<Expression>", ";", 0);
	_add_in_automate("<Expression>", ")", 0);

	_add_in_automate("<Sub_expression>", "and", 17, 0);
	_add_in_automate("<Sub_expression>", "equ", 17, 0);
	_add_in_automate("<Sub_expression>", "or", 17, 0);
	_add_in_automate("<Sub_expression>", ";", 17, 13, 14);
	_add_in_automate("<Sub_expression>", ")", 17, 13, 14);
	_add_in_automate("<Sub_expression>", "then", 17, 13, 14);

	_add_in_automate("<Unary_op>", "0", 0);
	_add_in_automate("<Unary_op>", "1", 0);
	_add_in_automate("<Unary_op>", "ident", 0);
	_add_in_automate("<Unary_op>", "(", 0);

	_add_in_automate("<Binary_op>", "0", 0);
	_add_in_automate("<Binary_op>", "1", 0);
	_add_in_automate("<Binary_op>", "ident", 0);
	_add_in_automate("<Binary_op>", "(", 0);

	_add_in_automate("<Operand>", "and", 16);
	_add_in_automate("<Operand>", "equ", 16);
	_add_in_automate("<Operand>", "or", 16);
	_add_in_automate("<Operand>", ";", 16);
	_add_in_automate("<Operand>", ")", 16);
	_add_in_automate("<Operand>", "then", 16);

	_add_in_automate("<Const>", "and", 23);
	_add_in_automate("<Const>", "equ", 23);
	_add_in_automate("<Const>", "or", 23);
	_add_in_automate("<Const>", ";", 23);
	_add_in_automate("<Const>", ")", 23);
	_add_in_automate("<Const>", "then", 23);

	_add_in_automate("<Prefix_io>", ")", 0);

	_add_in_automate(MAGAZINE_BOTTOM, "var", 0);
 }

 /// <summary>
/// Освобождение памяти
/// </summary>
 void dispose_automate() {
	 for (int i = 0; i < terminals.size(); ++i) {
		 delete[] automate[i];
	 }
	 delete[] automate;
 }