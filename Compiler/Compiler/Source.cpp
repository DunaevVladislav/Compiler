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
/// <returns>код ошикбки</returns>
int main(int argc, char* argv[]) {
	if (argc == 1) exit_error("Choice file");

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


	vector<term*> terms;
	try {
		terms = split_on_terminals(lines);
	}
	catch (exception& e) {
		exit_error(e.what());
	}
	terms.push_back(new term(get_index(END_OF_TAPE), -1, -1));
	cout << "terminals\tindex\t\tlines\t\tposition\n";
	for (auto t : terms) {
		cout << get_info(t) << endl;
	}
	check_grammar(terms);
	exit_error("");
	return 0;
}