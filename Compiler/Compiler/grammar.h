#pragma once
#include "rules.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cctype>
#include <exception>
using namespace std;

/// <summary>
/// ������������ ������ ���������������
/// </summary>
const size_t _MAX_IDENT_LENGTH = 11;

/// <summary>
/// ������������� ��������
/// </summary>
void initial();

/// <summary>
/// �������� �� ������ ���������������
/// </summary>
/// <param name="s">����������� ������</param>
/// <returns>-1 - �������������, � ������ > 11; 0 - �� �������������; 1 - �������������</returns>
int is_ident(string s);

/// <summary>
/// ������ ����� �� �������
/// </summary>
/// <param name="s">�����</param>
/// <returns>-1 - ���� ����� ��� � �������, ����� ������ �����</returns>
int get_index(string s);

/// <summary>
/// �������� �� ����� ������������ ��������
/// </summary>
/// <param name="s">����������� �����</param>
/// <returns>�������� �� ����� ������������ ��������</returns>
bool is_terminal(string s);

/// <summary>
/// �������� �� ����� � �������� index ������������ ��������
/// </summary>
/// <param name="index">index ������������ �����</param>
/// <returns>�������� �� ����� � �������� index ������������ ��������</returns>
bool is_terminal(int index);

/// <summary>
/// �������� �� ����� �������������� ��������
/// </summary>
/// <param name="s">����������� �����</param>
/// <returns>�������� �� ����� �������������� ��������</returns>
bool is_determinal(string s);

/// <summary>
/// �������� �� ����� � �������� index �������������� ��������
/// </summary>
/// <param name="index">index ������������ �����</param>
/// <returns>�������� �� ����� � �������� index �������������� ��������</returns>
bool is_determinal(int index);

/// <summary>
/// ��������
/// </summary>
struct term {
	/// <summary>
	/// ������ ���������
	/// </summary>
	int val;
	/// <summary>
	/// ������ ������, � ������� ���������� ��������
	/// </summary>
	int indLines;
	/// <summary>
	/// ������� � ������, ��� ������ ��������
	/// </summary>
	int indPos;
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="val">������ ���������</param>
	/// <param name="indLines">������ ������, � ������� ���������� ��������</param>
	/// <param name="indPos">������� � ������, ��� ������ ��������</param>
	term(int val, int indLines, int indPos) :
		val(val), indLines(indLines), indPos(indPos) {};
};

/// <summary>
/// ��������� ������ �� ������������ �������
/// </summary>
/// <param name="lines">������</param>
/// <returns>���������� ���������</returns>
/// <exception cref="exception">���� ����� �� �������� ����������</exception>
vector<term*> split_on_terminals(vector<string> & lines);

/// <summary>
/// ���������� � ���������
/// </summary>
/// <param name="trm">��������</param>
/// <returns>������, ��������������� ���������� � ��������� </returns>
string get_info(term* trm);