#pragma once
#include "grammar.h"
#include <vector>
#include <string>

using namespace std;

/// <summary>
/// Детерминированный восходящий автомат
/// </summary>
extern vector<int>** automate;

/// <summary>
/// Инициализация автомата
/// </summary>
void initial_automate();

/// <summary>
/// Освобождение памяти
/// </summary>
void dispose_automate();