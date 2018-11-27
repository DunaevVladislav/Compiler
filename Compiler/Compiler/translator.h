#pragma once
#include "grammar.h"
#include "grammar_defines.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/// <summary>
/// ��������� ������ ��������
/// </summary>
struct translator_node {
	/// <summary>
	/// ������ ��������
	/// �������� ������, � ������� �������������� ������� ��� ���������� ������������ �������
	/// </summary>
	vector<string> value;
	/// <summary>
	/// ������ �������� ������
	/// �������� ������� ������, ������� ������� ������ ���� �������� ����� ������ ������
	/// </summary>
	vector<int> lexeme_indexes;
	/// <summary>
	/// ����������� translator_node
	/// </summary>
	/// <param name="str">������, ������� �� ������� ���������� ������ ��� �������������� �������</param>
	explicit translator_node(const string& str);
};

/// <summary>
/// ������� ��������
/// </summary>
extern vector<translator_node> tranlation_rules;

/// <summary>
/// ������������� �����������
/// </summary>
void initial_translation();

/// <summary>
/// ��������� ������� ����������
/// </summary>
/// <param name="translation_magazine">������� �����������</param>
/// <param name="ind_rules">������ �������</param>
string apply_rule(const vector<string>& translation_magazine, const int& ind_rules);