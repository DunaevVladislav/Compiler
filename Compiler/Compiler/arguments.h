#pragma once
#include <stdio.h>
#include <string.h>
/// <summary>
/// �������� ��������� ������ ��� ������ ����������� �������
/// </summary>
#define ARG_ANALYSIS "-oa"
/// <summary>
/// ����, � ������� ��������� ���������� ������
/// </summary>
#define DEFAULT_ANALYSIS_FILE "analysis.txt"
/// <summary>
/// �������� �� ���������� ������
/// </summary>
extern bool out_analysis;

/// <summary>
/// ������� ��������������� ����������� ���� ��� ������ � ����������� ��������� ������
/// </summary>
/// <param name="argc">���������� ����������</param>
/// <param name="argv">���������</param>
void parce_args(const int& argc, char* argv[]);