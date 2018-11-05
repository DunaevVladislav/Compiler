#define _CRT_SECURE_NO_WARNINGS

#include "Grammar.h"
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
	size_t source_size = read_file(file_name, source);
	thread thr(initial);
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
	cout << "terminals\tindex\t\tlines\t\tposition\n";
	for (auto t : terms) {
		cout << get_info(t) << endl;
	}
    exit_error("");
	return 0;
}