#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
/// <summary>
/// �������� ��������� ������ ��� ������ ����������� �������
/// </summary>
#define ARG_ANALYSIS "-oa"
/// <summary>
/// ��� �����, � ������� ��������� ���������� ������
/// </summary>
extern string analysis_file_name;
/// <summary>
/// �������� �� ���������� ������
/// </summary>
extern bool out_analysis;

/// <summary>
/// �������� ��������� ������ ��� ������ ������� ��������� ���� �� ���������
/// </summary>
#define ARG_TERMINAL_ANALYSIS "-ota"
/// <summary>
/// ��� �����, � ������� ��������� ������ ��������� ���� �� ���������
/// </summary>
extern string terminal_analysis_file_name;
/// <summary>
/// �������� �� ������ ��������� ���� �� ���������
/// </summary>
extern bool out_terminal_analysis;

/// <summary>
/// ��������, ��� �������� �����, � ������� ����� �������������� ���������
/// </summary>
#define ARG_OUTPUT_FILE "-o"
/// <summary>
/// ��� ����� � ������� �������������� ����� ����������������� ����
/// </summary>
extern string output_file_name;
/// <summary>
/// �������� �� ���������������� ��� � ��������� ����
/// </summary>
extern bool out_file_declared;

/// <summary>
/// ��������, ��� ������ help
/// </summary>
#define ARG_HELP "-h"
/// <summary>
/// �������� �� help
/// </summary>
extern bool out_help;

/// <summary>
/// ��� ����� � �������� ����� ���������
/// </summary>
extern string input_file_name;

/// <summary>
/// ������� ��������������� ����������� ���� ��� ������ � ����������� ��������� ������
/// </summary>
/// <param name="argc">���������� ����������</param>
/// <param name="argv">���������</param>
void parce_args(const int& argc, char* argv[]);