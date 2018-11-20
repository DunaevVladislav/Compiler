#define _CRT_SECURE_NO_WARNINGS

#include "grammar.h"
#include "functions.h"
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <string>
#include <thread>

using namespace std;

/// <summary>
/// точка входа в программу
/// </summary>
/// <param name="argc">количество аргументов командной строки</param>
/// <param name="argv">аргументы командной строки</param>
/// <returns>код ошибки</returns>
int main(int argc, char* argv[]) {
	if (argc == 1) exit_error("Choice file");
	thread parce_thread([&]() {parce_args(argc - 1, argv + 1); });

	char* file_name = argv[1], *source;
	thread thr([&]() {
		try {
			initial();
		}
		catch (exception& e) {
			exit_error(e.what());
		}
	});
	if (!~read_file(file_name, source)) exit_error("File not exist");

	thr.join();
	vector<string> lines = split_lines(source);
	parce_thread.join();

	vector<term*> terms;
	try {
		terms = split_on_terminals(lines);
	}
	catch (exception& e) {
		exit_error(e.what());
	}
	terms.push_back(new term(get_index(END_OF_TAPE), -1, -1));
	output_terminal_analysis(terms);
	vector<int> form_rules;
	try {
		form_rules = upstream_analysis(terms);
	}
	catch (exception& e) {
		exit_error(e.what());
	}
	pair<int, int> error_pos;
	int check_ident_res = check_error_ident(lines, terms, error_pos);
	if (check_ident_res != NO_ERROR_IN_DECLARE_IDENT) {
		string error;
		if (check_ident_res == UNKNOWN_IDENT) error = "Unknown identifier: ";
		if (check_ident_res == REDECLARED_IDENT) error = "Redclared identifier: ";
		error.append("line " + to_string(error_pos.first + 1) + " position " + to_string(error_pos.second + 1));
		exit_error(error.c_str());
	}
	exit_error("SUCCESS");
	return 0;
}