#include "automate.h"
#include <vector>
#include <string>
#include <initializer_list>

using namespace std;

vector<int>** automate;

template<typename... T>
void _add_in_automate(string magazine_top, string terminal, const T&... transitions) {
	int term_ind = get_index(terminal);
	if (!is_terminal(term_ind)) throw runtime_error("Terminal dinctionary not include " + terminal);
	int mag_ind = get_index(magazine_top);
	if (mag_ind == -1) throw runtime_error("Dinctionary not include " + magazine_top);
	for (auto&& s : initializer_list<int>{ transitions... }) {
		automate[term_ind][mag_ind].push_back(s - 1);
	}
}

void initial_automate() {
	automate = new vector<int>*[terminals.size()];
	for (int i = 0; i < terminals.size(); ++i) {
		automate[i] = new vector<int>[dictionary.size()];
	}
	_add_in_automate("var", "ident", 0);
	_add_in_automate("begin", "read", 0);
	_add_in_automate("begin", "write", 0);
	_add_in_automate("begin", "if", 0);
	_add_in_automate("begin", "ident", 0);
	_add_in_automate("end", END_OF_TAPE, 7);
}