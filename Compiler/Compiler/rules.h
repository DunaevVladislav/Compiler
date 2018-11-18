#pragma once
#include "grammar.h"
#include <vector>
#include <string>

using namespace std;

/// <summary>
/// ������������������ ������� �������
/// </summary>
struct rule {
	/// <summary>
	/// ������ �����, ���������� ����� ������ �������
	/// </summary>
	int left;
	/// <summary>
	/// ������ ����� �������
	/// </summary>
	vector<int> right;
	/// <summary>
	/// ���������� ������� � ���������� ����������� ����������
	/// </summary>
	template<typename... T>
	/// <summary>
	/// ����������� rule
	/// </summary>
	/// <param name="left_str">����� ����� �������</param>
	/// <param name="...rights">������ ����� �������</param>
	rule(const string& left_str, const T&... rights);
};

/// <summary>
/// �������
/// </summary>
extern vector<rule> rules;

/// <summary>
/// ������������� ������
/// </summary>
void initial_rules();