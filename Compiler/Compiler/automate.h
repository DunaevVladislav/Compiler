#pragma once
#include "grammar.h"
#include <vector>
#include <string>

using namespace std;

/// <summary>
/// ����������������� ���������� �������
/// </summary>
extern vector<int>** automate;

/// <summary>
/// ������������� ��������
/// </summary>
void initial_automate();

/// <summary>
/// ������������ ������
/// </summary>
void dispose_automate();