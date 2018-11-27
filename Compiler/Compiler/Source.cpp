#define _CRT_SECURE_NO_WARNINGS
#include "grammar.h"
#include "functions.h"

using namespace std;

/// <summary>
/// ����� ����� � ���������
/// </summary>
/// <param name="argc">���������� ���������� ��������� ������</param>
/// <param name="argv">��������� ��������� ������</param>
/// <returns>��� ������</returns>
int main(int argc, char* argv[]) {
	try {
		parce_args(argc - 1, argv + 1);
		check_help();
		vector<string> lines;
		vector<term* > terms;
		get_terminals(terms, lines);
		analysis_grammar(terms, lines);
		translation(lines, terms);
		ouput_success_result();
		dispose(terms);
	}
	catch (const runtime_error& e) {
		exit_error(e.what());
	}
	return 0;
}