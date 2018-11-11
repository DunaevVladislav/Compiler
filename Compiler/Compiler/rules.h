#pragma once
#include "grammar.h"
#include <vector>
#include <string>

using namespace std;

struct rule {
	int left;
	vector<int> right;
	template<typename... T>
	rule(string left_str, const T&... rights);
};

extern vector<rule> rules;

void initial_rules();