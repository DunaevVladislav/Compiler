#include "arguments.h"

/// <summary>
/// �������� �� ���������� ������
/// </summary>
bool out_analysis = false;

/// <summary>
/// ������� ��������������� ����������� ���� ��� ������ � ����������� ��������� ������
/// </summary>
/// <param name="argc">���������� ����������</param>
/// <param name="argv">���������</param>
void parce_args(const int & argc, char * argv[])
{
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], ARG_ANALYSIS) == 0) {
			out_analysis = true;
		}
	}
}
