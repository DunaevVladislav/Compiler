#include "arguments.h"

/// <summary>
/// �������� �� ���������� ������
/// </summary>
bool out_analysis = false;
/// <summary>
/// ��� �����, � ������� ��������� ���������� ������
/// </summary>
string analysis_file_name;

/// <summary>
/// �������� �� ������ ��������� ���� �� ���������
/// </summary>
bool out_terminal_analysis = false;
/// <summary>
/// ��� �����, � ������� ��������� ������ ��������� ���� �� ���������
/// </summary>
string terminal_analysis_file_name;

/// <summary>
/// ��� ����� � ������� �������������� ����� ����������������� ����
/// </summary>
string output_file_name;

/// <summary>
/// �������� �� ���������������� ��� � ��������� ����
/// </summary>
bool out_file_declared = false;

/// <summary>
/// ��� ����� � �������� ����� ���������
/// </summary>
string input_file_name;

/// <summary>
/// �������� �� help
/// </summary>
bool out_help = false;

/// <summary>
/// ��������� ��� ����� �� ����������
/// </summary>
/// <param name="file_name">��� �����</param>
/// <returns>��������� ��������</returns>
bool _validate_filename(const char* file_name) {
	FILE* fdsc = fopen(file_name, "w");
	if (fdsc) {
		fclose(fdsc);
		return true;
	}
	return false;
}

/// <summary>
/// ������� ��������������� ����������� ���� ��� ������ � ����������� ��������� ������
/// </summary>
/// <param name="argc">���������� ����������</param>
/// <param name="argv">���������</param>
void parce_args(const int & argc, char * argv[])
{
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], ARG_OUTPUT_FILE) == 0) {
			out_file_declared = true;
			if (i + 1 >= argc)
				throw runtime_error((string)"Not found file name after " + ARG_OUTPUT_FILE);
			output_file_name = argv[++i];
			if (!_validate_filename(output_file_name.c_str()))
				throw runtime_error((string)"Can't create file: " + output_file_name);
			continue;
		}
		if (strcmp(argv[i], ARG_ANALYSIS) == 0) {
			out_analysis = true;
			if (i + 1 >= argc)
				throw runtime_error((string)"Not found file name after " + ARG_ANALYSIS);
			analysis_file_name = argv[++i];
			if (!_validate_filename(analysis_file_name.c_str()))
				throw runtime_error((string)"Can't create file: " + analysis_file_name);
			continue;
		}
		if (strcmp(argv[i], ARG_TERMINAL_ANALYSIS) == 0) {
			out_terminal_analysis = true;
			if (i + 1 >= argc)
				throw runtime_error((string)"Not found file name after " + ARG_ANALYSIS);
			terminal_analysis_file_name = argv[++i];
			if (!_validate_filename(terminal_analysis_file_name.c_str()))
				throw runtime_error((string)"Can't create file: " + terminal_analysis_file_name);
			continue;
		}
		if (strcmp(argv[i], ARG_HELP) == 0) {
			out_help = true;
			continue;
		}
		input_file_name = argv[i];
	}
}
