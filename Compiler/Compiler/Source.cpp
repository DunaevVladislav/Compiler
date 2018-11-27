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
	try {
		vector<string> lines;
		vector<term* > terms;
		parce_args(argc - 1, argv + 1);
		check_help();
		get_terminals(terms, lines);
		analysis_grammar(terms, lines);
		translation(lines, terms);
		ouput_success_result();
	}
	catch (const runtime_error& e) {
		exit_error(e.what());
	}
	return 0;
}