#include "translator.h"


/// <summary>
/// Конструктор translator_node
/// </summary>
/// <param name="First">Первая строка</param>
/// <param name="...translations">int, string... индексы лексем и строки</param>
inline translator_node::translator_node(const string& str)
{
	int cur_rules = tranlation_rules.size();
	int prev = 0, pos;
	while ((pos = str.find(_START_INDEX_OF_LEXEM, prev)) != string::npos) {
		value.emplace_back(str.substr(prev, pos - prev));
		prev = pos + 2;
		pos = str.find(_END_INDEX_OF_LEXEM, prev);
		if (pos == string::npos) throw runtime_error((string)"Not found \"" + _END_INDEX_OF_LEXEM + "\" in translation rule " + to_string(tranlation_rules.size() + 1));
		string lexem = str.substr(prev, pos - prev);
		int ind_lexem = get_index(lexem);
		if (ind_lexem == -1) throw runtime_error("Dictionary not include " + lexem);
		auto it = find(rules[cur_rules].right.begin(), rules[cur_rules].right.end(), ind_lexem );
		auto fst = it;
		if (it == rules[cur_rules].right.end()) throw runtime_error((string)"Not found \"" + lexem + "\" in translation rules " + to_string(tranlation_rules.size() + 1));
		while (count(lexeme_index.begin(), lexeme_index.end(), (it - rules[cur_rules].right.begin())))
			it = find(it + 1, rules[cur_rules].right.end(),ind_lexem);
		if (it == rules[cur_rules].right.end())	it = fst;
		lexeme_index.emplace_back(it - rules[cur_rules].right.begin());
		prev = pos + 1;
	}
	value.emplace_back(str.substr(prev));
}

/// <summary>
/// Правила перевода
/// </summary>
vector<translator_node> tranlation_rules;

/// <summary>
/// Первые еще не использованный индекс в правилах
/// </summary>
unsigned int _first_unused_index;

/// <summary>
/// Инициализация транслятора
/// </summary>
void initial_translation()
{
	//1
	tranlation_rules.emplace_back(string() + 
		"#define _CRT_SECURE_NO_WARNINGS" _NL
		"#define USINT unsigned short int" _NL
		"#include <stdio.h>" _NL
		"void cast(USINT& _a) {" _NL
		"__asm {" _NL
		"push eax" _NL
		"push ecx" _NL
		"mov eax, _a" _NL
		"mov ecx, [eax]" _NL
		"cmp ecx, 0" _NL
		"je end_cast" _NL
		"mov ecx, 1" _NL
		"mov [eax], ecx" _NL
		"end_cast:" _NL
		"pop ecx" _NL
		"pop eax" _NL
		"}}" _NL
		_START_INDEX_OF_LEXEM + "<Var_declare>" + _END_INDEX_OF_LEXEM _NL
		_START_INDEX_OF_LEXEM + "<Calculation_descr>" + _END_INDEX_OF_LEXEM 
	);

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Prefix_var_declare>" + _END_INDEX_OF_LEXEM
	);

	tranlation_rules.emplace_back(string() +
		"USINT _" + 
		_START_INDEX_OF_LEXEM + "ident" + _END_INDEX_OF_LEXEM +
		" = 0;"
	);

	tranlation_rules.emplace_back(string() +
		"USINT _" +
		_START_INDEX_OF_LEXEM + "ident" + _END_INDEX_OF_LEXEM +
		" = 0;" _NL
		_START_INDEX_OF_LEXEM + "<Var_list>" + _END_INDEX_OF_LEXEM
	);

	//5
	tranlation_rules.emplace_back(string() +
		"USINT _" +
		_START_INDEX_OF_LEXEM + "ident" + _END_INDEX_OF_LEXEM +
		" = 0;" _NL
		_START_INDEX_OF_LEXEM + "<Var_list>" + _END_INDEX_OF_LEXEM
	);

	tranlation_rules.emplace_back(string() +
		"USINT _" +
		_START_INDEX_OF_LEXEM + "ident" + _END_INDEX_OF_LEXEM +
		" = 0;"
	);

	tranlation_rules.emplace_back(string() +
		"int main() {" _NL
		"__asm {" _NL
		"push eax" _NL
		"push ebx" _NL
		_START_INDEX_OF_LEXEM + "<Function_list>" + _END_INDEX_OF_LEXEM _NL
		"pop ebx" _NL
		"pop eax" _NL
		"}" _NL
		"return 0;" _NL
		"}"
	);

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Assignment>" + _END_INDEX_OF_LEXEM
	);

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Assignment>" + _END_INDEX_OF_LEXEM _NL
		_START_INDEX_OF_LEXEM + "<Function_list>" + _END_INDEX_OF_LEXEM
	);

	//10
	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Function>" + _END_INDEX_OF_LEXEM
	);

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Function>" + _END_INDEX_OF_LEXEM _NL
		_START_INDEX_OF_LEXEM + "<Function_list>" + _END_INDEX_OF_LEXEM
	);

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Expression>" + _END_INDEX_OF_LEXEM _NL
		"pop eax" _NL
		"mov [" +
		_START_INDEX_OF_LEXEM + "ident" + _END_INDEX_OF_LEXEM
		"], ax"
	);

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Sub_expression>" + _END_INDEX_OF_LEXEM _NL
		"pop eax" _NL
		_START_INDEX_OF_LEXEM + "<Unary_op>" + _END_INDEX_OF_LEXEM _NL
		"push eax"
	);

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Sub_expression>" + _END_INDEX_OF_LEXEM
	);

	//15
	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Expression>" + _END_INDEX_OF_LEXEM
	);

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Operand>" + _END_INDEX_OF_LEXEM
	);
	
	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Sub_expression>" + _END_INDEX_OF_LEXEM _NL
		_START_INDEX_OF_LEXEM + "<Sub_expression>" + _END_INDEX_OF_LEXEM _NL
		"pop eax" _NL
		"pop ebx" _NL
		_START_INDEX_OF_LEXEM + "<Binary_op>" + _END_INDEX_OF_LEXEM _NL
		"pop eax"
	);

	tranlation_rules.emplace_back(string() +
		"xor eax, 1"
	);

	tranlation_rules.emplace_back(string() +
		"and eax, ebx"
	);

	//20
	tranlation_rules.emplace_back(string() +
		"or eax, ebx"
	);

	tranlation_rules.emplace_back(string() +
		"xor eax, ebx" _NL
		"xor eax, 1"
	); 

	tranlation_rules.emplace_back(string() +
		"xor eax, eax" _NL
		"mov ax, [" +
		_START_INDEX_OF_LEXEM + "ident" + _END_INDEX_OF_LEXEM + 
		"]" _NL
		"push eax"
	);

	tranlation_rules.emplace_back(string() +
		"mov ax," +
		_START_INDEX_OF_LEXEM + "<Const>" + _END_INDEX_OF_LEXEM _NL
		"push eax"
	);

	tranlation_rules.emplace_back("0");

	//25
	tranlation_rules.emplace_back("1");

	tranlation_rules.emplace_back("");

	tranlation_rules.emplace_back("");

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Expression>" + _END_INDEX_OF_LEXEM _NL
		"pop eax" +
		"cmp eax, 1" + 
		"jne else" + _NEW_INDEX _NL
		_START_INDEX_OF_LEXEM + "<Function_list>" + _END_INDEX_OF_LEXEM _NL
		"jmp end_if" + _NEW_INDEX _NL
		"else" + _NEW_INDEX + ":" + _NL
		_START_INDEX_OF_LEXEM + "<Function_list>" + _END_INDEX_OF_LEXEM _NL
		"end_if" + _NEW_INDEX + ":"
	);

	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Prefix_io>" + _END_INDEX_OF_LEXEM
	);

	//30
	tranlation_rules.emplace_back(string() +
		_START_INDEX_OF_LEXEM + "<Prefix_io>" + _END_INDEX_OF_LEXEM
	);

	tranlation_rules.emplace_back(string() +
		"push offset " +
		_START_INDEX_OF_LEXEM + "ident" + _END_INDEX_OF_LEXEM _NL
		"push offset __format" _NL
		"call scanf" _NL
		"add esp, 8" _NL
		"push offset " +
		_START_INDEX_OF_LEXEM + "ident" + _END_INDEX_OF_LEXEM _NL
		"call cast" _NL
		"add esp, 4"
	);

	tranlation_rules.emplace_back(string() +
		"push offset " +
		_START_INDEX_OF_LEXEM + "ident" + _END_INDEX_OF_LEXEM _NL
		"push offset __format" _NL
		"call printf" _NL
		"add esp, 8"
	);
}