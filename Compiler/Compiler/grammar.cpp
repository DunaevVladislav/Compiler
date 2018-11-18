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
	"<Prefix_io>",
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
const unordered_set<char> _separators = {
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
	for (string &s : terminals) dictionary.emplace_back(s);
	for (string &s : determinals) dictionary.emplace_back(s);
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
int is_ident(const string& s)
{
	bool ok = true;
	for (int i = 0; ok && i < s.length(); ++i) ok = isalpha(s[i]);
	if (s.length() > _MAX_IDENT_LENGTH) return LONG_IDENT;
	if (!ok) return NOT_IDENT;
	return IS_IDENT;
}

/// <summary>
/// Индекс слова из словаря
/// </summary>
/// <param name="s">Слово</param>
/// <returns>-1 - если слова нет в словаре, иначе индекс слова</returns>
int get_index(const string& s) {
	auto it = _ind_term_dictionary.find(s);
	return it == _ind_term_dictionary.end() ? -1 : it->second;
}

/// <summary>
/// Является ли слово термианльным символом
/// </summary>
/// <param name="s">Проверяемое слово</param>
/// <returns>Является ли слово терминальныи символом</returns>
bool is_terminal(const string& s) {
	auto it = _ind_term_dictionary.find(s);
	return it != _ind_term_dictionary.end() && it->second < terminals.size();
}

/// <summary>
/// Является ли слово с индексом index терминальным символом
/// </summary>
/// <param name="index">index проверяемого слова</param>
/// <returns>Является ли слово с индексом index терминальным символом</returns>
bool is_terminal(const int& index) {
	return index >= 0 && index < terminals.size();
}

/// <summary>
/// Является ли слово нетермианльным символом
/// </summary>
/// <param name="s">Проверяемое слово</param>
/// <returns>Является ли слово нетерминальным символом</returns>
bool is_determinal(const string& s) {
	auto it = _ind_term_dictionary.find(s);
	return it != _ind_term_dictionary.end() && it->second >= terminals.size();
}

/// <summary>
/// Является ли слово с индексом index нетерминальным символом
/// </summary>
/// <param name="index">index проверяемого слова</param>
/// <returns>Является ли слово с индексом index нетерминальным символом</returns>
bool is_determinal(const int& index) {
	return index >= terminals.size() && index <= dictionary.size();
}

/// <summary>
/// Разделить строки на терминальные символы
/// </summary>
/// <param name="lines">Строки</param>
/// <returns>Полученные терминалы</returns>
/// <exception cref="exception">Если слово не является терминалом</exception>
vector<term*> split_on_terminals(const vector<string> & lines) {
	vector<term*> res;

	auto add_res = [&](string sterm, const int& i, const int& j) {
		if (sterm.empty()) return;
		if (!is_terminal(sterm)) {
			if (_separators.count(sterm[0])) return;
			int res = is_ident(sterm);
			string msg = "";
			if (res == LONG_IDENT) msg = "Identificator length exceeds 11 symbols: line " + to_string(i + 1) + " position " + to_string(j + 1);
			if (res == NOT_IDENT)
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
string get_info(const term* trm) {
	return terminals[trm->val] + "\t\t" + to_string(trm->val) + "\t\t" +
		to_string(trm->ind_lines) + "\t\t" + to_string(trm->ind_pos);
};

/// <summary>
/// Восходящий анализ по заданным правилам
/// </summary>
/// <param name="input_line">Терминалы на входной ленте</param>
/// <returns>Последовательность номером правил, которые приведут к получению исходной ленты</returns>
vector<int> upstream_analysis(const vector<term*>& input_line) {
	vector<int> magazine, form_rules;
	magazine.emplace_back(get_index(MAGAZINE_BOTTOM));
	int ptr_input_line = 0;
	while (true) {
		bool ok = false;
		for (int& ind_rules : automate[input_line[ptr_input_line]->val][magazine.back()]) {
			if (ind_rules == SUCCESS) {
				reverse(form_rules.begin(), form_rules.end());
				return form_rules;
			}
			if (ind_rules == -1) {
				cout << "adding: " << dictionary[input_line[ptr_input_line]->val] << endl;
				magazine.emplace_back(input_line[ptr_input_line]->val);
				ptr_input_line++;
				ok = true;
				break;
			}
			if (magazine.size() < rules[ind_rules].right.size()) continue;
			if (equal(rules[ind_rules].right.rbegin(), rules[ind_rules].right.rend(), magazine.rbegin())) {
				magazine.erase(magazine.begin() + (magazine.size() - rules[ind_rules].right.size()), magazine.end());
				form_rules.emplace_back(ind_rules);
				for (int i : rules[ind_rules].right) cout << dictionary[i] << ' ';
				cout << " => " << dictionary[rules[ind_rules].left] << endl;
				magazine.emplace_back(rules[ind_rules].left);
				ok = true;
				break;
			}
		}
		if (!ok) {
			string error = "Invalid sequence: line " +
				to_string(input_line[ptr_input_line]->ind_lines + 1) +
				" pos " + to_string(input_line[ptr_input_line]->ind_pos + 1);
			throw runtime_error(error);
		}
	}

}

/// <summary>
/// Возвращает идентификатор из входной ленты
/// </summary>
/// <param name="lines">Входная лента</param>
/// <param name="ind_lines">Индекс строки</param>
/// <param name="ind_pos">Индекс позиции начала идентификатора</param>
/// <returns>Идентификатор</returns>
string get_real_ident(const vector<string>& lines, const int & ind_lines, const int & ind_start_pos)
{
	int ind_pos = ind_start_pos;
	while (ind_pos < lines[ind_lines].length() &&
		isalpha(lines[ind_lines][ind_pos])) ind_pos++;
	return lines[ind_lines].substr(ind_start_pos, ind_pos - ind_start_pos);
}

/// <summary>
/// Проверка кода на неизвестные идентификаторы или повторное объявление
/// </summary>
/// <param name="lines">Исходный код</param>
/// <param name="terms">Терминалы</param>
/// <param name="error_pos">Позиция найденного ошибочного идентификатора</param>
/// <returns>-1 - не найден ошибочный идентификатор, 0 - повтороное объявление, 1 - неизвестный идентификатор</returns>
int check_error_ident(const vector<string>& lines, const vector<term*>& terms, pair<int, int>& error_pos)
{
	int ind_begin = get_index(_BEGIN);
	int ind_ident = get_index(_IDENT);
	unordered_set<string> declared_idents;
	bool after_begin = false;
	for (const auto& trm : terms) {
		if (trm->val == ind_begin) after_begin = true;
		if (trm->val == ind_ident) {
			auto ident = get_real_ident(lines, trm->ind_lines, trm->ind_pos);
			auto iter = declared_idents.find(ident);
			if (after_begin) {
				if (iter == declared_idents.end()) {
					error_pos = make_pair(trm->ind_lines, trm->ind_pos);
					return UNKNOWN_IDENT;
				}
			}
			else {
				if (iter != declared_idents.end()) {
					error_pos = make_pair(trm->ind_lines, trm->ind_pos);
					return REDCLARED_IDENT;
				}
				declared_idents.insert(ident);
			}
		}
	}
	return NO_ERROR_IN_DECLARE_IDENT;
}
