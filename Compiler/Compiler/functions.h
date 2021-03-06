#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "grammar.h"
#include <cstdio>
#include <cctype>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <thread>
using namespace std;

/// <summary>
/// �������� �� ��������� � ������� ���������� �� ������
/// </summary>
/// <param name="message">���������, ��������� �� �����</param>
void exit_error(const char* message);

/// <summary>
/// ������� ���������� �����
/// </summary>
/// <param name="file_name">��� �����</param>
/// <param name="data">��������� ������</param>
/// <returns>-1 ���� ���� �� ������, ����� ���������� ��������� ����</returns>
int read_file(const char* file_name, char*& data);

/// <summary>
/// ��������� ������ �� �����(split by '\n')
/// </summary>
/// <param name="data">������</param>
/// <returns>���������� �����</returns>
vector<string> split_lines(char*& data);

/// <summary>
/// �������, ��������� ������ �����������
/// </summary>
/// <param name="source">�������� ��� ���������</param>
/// <param name="source_size">������ ��������� ����</param>
/// <returns>��������� ���������</returns>
char* parce_code(const char* source, size_t source_size = 0);

/// <summary>
/// ������� ���������� � ������� ��������� ���� �� ��������� (���� ���������� �������������� ��������)
/// </summary>
/// <param name="terms">���������</param>
void output_terminal_analysis(const vector<term*>& terms);

/// <summary>
/// ��������� ������������� ������ help
/// ������� ��� ��� �������������
/// </summary>
void check_help();

/// <summary>
/// ��������� �������� ��� �� ����� � �������� ������� ��� ���������� ��� �� ���������
/// </summary>
/// <param name="terms">���������</param>
/// <param name="lines">�������� ���, ���������</param>
void get_terminals(vector<term*>& terms,  vector<string>& lines);

/// <summary>
/// �������� ���������� ������������� � �������� ���������������
/// </summary>
/// <param name="terms">���������</param>
/// <param name="lines">�������� ���, ���������</param>
void analysis_grammar(const vector<term*>& terms, const vector<string>& lines);

/// <summary>
/// ������� ���������� �� �������� ����������
/// </summary>
void ouput_success_result();

/// <summary>
/// ������������ ��������
/// </summary>
void dispose(const vector<term*>& terms);