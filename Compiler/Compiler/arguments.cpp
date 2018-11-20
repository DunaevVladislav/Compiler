#include "arguments.h"

/// <summary>
/// Выводить ли восходящий разбор
/// </summary>
bool out_analysis = false;

/// <summary>
/// Функция устанавливающие необходимые флаг для работы с аргументами командной строки
/// </summary>
/// <param name="argc">Количество аргументов</param>
/// <param name="argv">Аргументы</param>
void parce_args(const int & argc, char * argv[])
{
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], ARG_ANALYSIS) == 0) {
			out_analysis = true;
		}
	}
}
