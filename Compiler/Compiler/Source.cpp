#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cctype>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <set>

using namespace std;

vector<string> terminals = {
	"var",
	"begin",
	"end",
	"logical",
	"not",
	"and",
	"equ",
	"or",
	"read",
	"write",
	"if",
	"then",
	"else",
	"end_if",
	"0",
	"1",
	"ident",
	";",
	":",
	",",
	"=",
	"(",
	")",
};

vector<string> determinals = {
	"<Program>",
	"<Var_declare>",
	"<Var_list>",
	"<Prefix_var_declare>",
	"<Calculation_descr>",
	"<Function_list>",
	"<Assignment>",
	"<Function>",
	"<Expression>",
	"<Sub_expression>",
	"<Unary_op>",
	"<Binary_op>",
	"<Operand>",
	"<Const>",
};

vector<string> dictionary;
map<string, int> ind_dictionary;

set<char> separators = {
	';',
	':',
	',',
	'=',
	'(',
	')',
	' ',
	'\n',
	'\t',
};

struct term {
	int val, indLines, indPos;
};


void exit_error(const char* message) {
	puts(message);
	system("pause");
	exit(0);
}


vector<term> split_on_terminals(vector<string> & lines) {
	vector<term> res;
	auto add_res = [&](string s, int i, int j) {
		if (s.empty()) return;
		auto it = ind_dictionary.find(s);
		if (it == ind_dictionary.end() || it->second >= terminals.size()) {
			if (separators.count(s[0])) return;
			string msg = "Unknown terminal: line " + to_string(i + 1) + " position " + to_string(j + 1);
			if (it == ind_dictionary.end()) {
				bool ok = true;
				for (char c : s) {
					if (!isalpha(c)) {
						ok = false;
						break;
					}
				}
				if (ok) {
					if (s.length() > 11) {
						msg = "Identificator length exceeds 11 symbols: line " + to_string(i + 1) + " position " + to_string(j + 1);
					}
					else {
						s = "ident";
						it = ind_dictionary.find(s);
					}
				}
			}
			if (s != "ident")
				exit_error(msg.c_str());
		}
		term t;
		t.val = it->second;
		t.indLines = i;
		t.indPos = j;
		res.emplace_back(t);
	};
	for (int i = 0; i < lines.size(); ++i) {
		int l = 0;
		for (int j = 0; j < lines[i].length(); ++j) {
			if (separators.count(lines[i][j])) {
				add_res(lines[i].substr(l, j - l), i, l);
				l = j;
				add_res(lines[i].substr(l, 1), i, l);
				l++;
			}
		}
		add_res(lines[i].substr(l), i, l);
	}
	return res;
}

/// <summary>
/// функция считывания файла
/// </summary>
/// <param name="file_name">имя файла</param>
/// <param name="data">считанные данные</param>
/// <returns>-1 если файл не найден, иначе количество считанных байт</returns>
int read_file(char* file_name, char*& data) {
	FILE* source = fopen(file_name, "r");
	if (!source) return -1;
	size_t source_size = 0;
	while (~getc(source)) source_size++;
	fseek(source, 0L, SEEK_SET);
	data = new char[source_size + 1];
	for (size_t i = 0; i < source_size; ++i) data[i] = getc(source);
	data[source_size] = '\0';
	fclose(source);
	return source_size;
}

vector<string> split_lines(char*& data) {
	vector<string> lines;
	int ind = 0;
	for (int i = 0; data[i] != '\0'; ++i) {
		if (lines.size() == ind) lines.emplace_back("");
		if (data[i] == '\n') ind++;
		else lines[ind].push_back(data[i]);
	}
	return lines;
}

/// <summary>
/// функция, убирающая лишнии раздилители
/// </summary>
/// <param name="source">исходный код программы</param>
/// <param name="source_size">размер исходного кода</param>
/// <returns>результат обработки</returns>
char*& parce_code(const char* source, size_t source_size = 0) {
	if (!source_size) source_size = strlen(source);
	char* code = new char[source_size];
	int ptr = -1;
	for (size_t i = 0; i < source_size; ++i) {
		if (!isspace(source[i])) code[++ptr] = source[i];
		else if (ptr != -1 && code[ptr] != ' ') code[++ptr] = ' ';
	};
	if (ptr == -1 || code[ptr] != ' ') ptr++;
	code[ptr] = '\0';
	return code;
}

void initialDictionaries() {
	for (string s : terminals)dictionary.emplace_back(s);
	for (string s : determinals)dictionary.emplace_back(s);
	for (int i = 0; i < dictionary.size(); ++i) {
		ind_dictionary.insert({ dictionary[i], i });
	}
}


/// <summary>
/// точка входа в программу
/// </summary>
/// <param name="argc">количество аргументов командной строки</param>
/// <param name="argv">аргументы командной строки</param>
/// <returns>код ошикбки</returns>
int main(int argc, char* argv[]) {
	if (argc == 1) exit_error("Choice file");

	char* file_name = argv[1], *source;
	size_t source_size = read_file(file_name, source);
	if (!~read_file(file_name, source)) exit_error("File not exist");

	initialDictionaries();
	vector<string> lines = split_lines(source);
	auto terms = split_on_terminals(lines);
	cout << "terminals\tindex\t\tlines\t\tposition\n";
	for (auto t : terms) {
		cout << terminals[t.val] << "\t\t" << t.val << "\t\t" << t.indLines << "\t\t" << t.indPos << endl;
	}

	/*char* code = parce_code(source, source_size);
	printf("%s", code);
	if (code[0] != '\0') delete[] code;
	if (source[0] != '\0') delete[] source;*/
	system("pause");
	return 0;
}