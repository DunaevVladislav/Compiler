#include "grammar.h"
using namespace std;



/// <summary>
/// Терминальные символы
/// </summary>
vector<string> terminals = {
	"var",
	"begin",
	"end",
	"logical",
	"not",
	"and",
	"equ",
	"or",
	"read",
	"write",
	"if",
	"then",
	"else",
	"end_if",
	"0",
	"1",
	"ident",
	";",
	":",
	",",
	"=",
	"(",
	")",
	END_OF_TAPE,
};

/// <summary>
/// Нетерминальные символы
/// </summary>
vector<string> determinals = {
	"<Program>",
	"<Var_declare>",
	"<Var_list>",
	"<Prefix_var_declare>",
	"<Calculation_descr>",
	"<Function_list>",
	"<Assignment>",
	"<Function>",
	"<Expression>",
	"<Sub_expression>",
	"<Unary_op>",
	"<Binary_op>",
	"<Operand>",
	"<Const>",
	MAGAZINE_BOTTOM,
};

/// <summary>
/// Полный словарь грамматики
/// </summary>
vector<string> dictionary;

/// <summary>
/// map слово из словаря в его индекс
/// </summary>
unordered_map<string, int> _ind_term_dictionary;

/// <summary>
/// Символы являющиесями разделителями для данной грамматкии
/// </summary>
unordered_set<char> _separators = {
	';',
	':',
	',',
	'=',
	'(',
	')',
	' ',
	'\n',
	'\t',
};

/// <summary>
/// Инициализация словарей
/// </summary>
void initial() {
	for (string s : terminals) dictionary.emplace_back(s);
	for (string s : determinals) dictionary.emplace_back(s);
	for (int i = 0; i < dictionary.size(); ++i) {
		_ind_term_dictionary.insert({ dictionary[i], i });
	}
	initial_rules();
	initial_automate();
}

/// <summary>
/// Является ли строка идентификатором
/// </summary>
/// <param name="s">Проверяемая строка</param>
/// <returns>-1 - идентификатор, с длиной > 11; 0 - не идентификатор; 1 - идентификатор</returns>
int is_ident(string s) {
	bool ok = true;
	for (int i = 0; ok && i < s.length(); ++i) ok = isalpha(s[i]);
	if (s.length() > _MAX_IDENT_LENGTH) return -1;
	return (int)ok;
}

/// <summary>
/// Индекс слова из словаря
/// </summary>
/// <param name="s">Слово</param>
/// <returns>-1 - если слова нет в словаре, иначе индекс слова</returns>
int get_index(string s) {
	auto it = _ind_term_dictionary.find(s);
	return it == _ind_term_dictionary.end() ? -1 : it->second;
}

/// <summary>
/// Является ли слово термианльным символом
/// </summary>
/// <param name="s">Проверяемое слово</param>
/// <returns>Является ли слово терминальныи символом</returns>
bool is_terminal(string s) {
	auto it = _ind_term_dictionary.find(s);
	return it != _ind_term_dictionary.end() && it->second < terminals.size();
}

/// <summary>
/// Является ли слово с индексом index терминальным символом
/// </summary>
/// <param name="index">index проверяемого слова</param>
/// <returns>Является ли слово с индексом index терминальным символом</returns>
bool is_terminal(int index) {
	return index >= 0 && index < terminals.size();
}

/// <summary>
/// Является ли слово нетермианльным символом
/// </summary>
/// <param name="s">Проверяемое слово</param>
/// <returns>Является ли слово нетерминальным символом</returns>
bool is_determinal(string s) {
	auto it = _ind_term_dictionary.find(s);
	return it != _ind_term_dictionary.end() && it->second >= terminals.size();
}

/// <summary>
/// Является ли слово с индексом index нетерминальным символом
/// </summary>
/// <param name="index">index проверяемого слова</param>
/// <returns>Является ли слово с индексом index нетерминальным символом</returns>
bool is_determinal(int index) {
	return index >= terminals.size() && index <= dictionary.size();
}

/// <summary>
/// Разделить строки на терминальные символы
/// </summary>
/// <param name="lines">Строки</param>
/// <returns>Полученные терминалы</returns>
/// <exception cref="exception">Если слово не является терминалом</exception>
vector<term*> split_on_terminals(vector<string> & lines) {
	vector<term*> res;

	auto add_res = [&](string sterm, int i, int j) {
		if (sterm.empty()) return;
		if (!is_terminal(sterm)) {
			if (_separators.count(sterm[0])) return;
			int res = is_ident(sterm);
			string msg = "";
			if (res == -1) msg = "Identificator length exceeds 11 symbols: line " + to_string(i + 1) + " position " + to_string(j + 1);
			if (res == 0) 
				msg = "Unknown terminal: line " + to_string(i + 1) + " position " + to_string(j + 1);
			if (msg.empty()) sterm = "ident";
			else throw runtime_error(msg);
		}
		res.push_back(new term(get_index(sterm), i, j));
	};

	for (int i = 0; i < lines.size(); ++i) {
		int l = 0;
		for (int j = 0; j < lines[i].length(); ++j) {
			if (_separators.count(lines[i][j])) {
				add_res(lines[i].substr(l, j - l), i, l);
				add_res(lines[i].substr(l, 1), i, l = j);
				l++;
			}
		}
		add_res(lines[i].substr(l), i, l);
	}
	return res;
}

/// <summary>
/// Информация о терминале
/// </summary>
/// <param name="trm">Терминал</param>
/// <returns>Строку, предоставляющую информацию о терминале </returns>
string get_info(term* trm) {
	return terminals[trm->val] + "\t\t" + to_string(trm->val) + "\t\t" +
		to_string(trm->indLines) + "\t\t" + to_string(trm->indPos);
};