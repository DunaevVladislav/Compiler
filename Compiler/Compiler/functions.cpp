#include "functions.h"
using namespace std;

/// <summary>
/// Выходить из программы с выводом информации об ошибке
/// </summary>
/// <param name="message">Сообщение, выводимое на экран</param>
void exit_error(const char* message) {
	puts(message);
/*#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ || __CYGWIN__ )
    system("pause");
#endif*/
	exit(0);
}

/// <summary>
/// функция считывания файла
/// </summary>
/// <param name="file_name">имя файла</param>
/// <param name="data">считанные данные</param>
/// <returns>-1 если файл не найден, иначе количество считанных байт</returns>
int read_file(const char* file_name, char*& data) {
	FILE* source = fopen(file_name, "r");
	if (!source) return -1;
	size_t source_size = 0;
	while (~getc(source)) source_size++;
	fseek(source, 0L, SEEK_SET);
	data = new char[source_size + 1];
	for (size_t i = 0; i < source_size; ++i) data[i] = getc(source);
	data[source_size] = '\0';
	fclose(source);
	return static_cast<int>(source_size);
}

/// <summary>
/// Разделяет строку на линни(split by '\n')
/// </summary>
/// <param name="data">Строка</param>
/// <returns>Полученные линии</returns>
vector<string> split_lines(char*& data) {
	vector<string> lines;
	int ind = 0;
	for (int i = 0; data[i] != '\0'; ++i) {
		if (lines.size() == ind) lines.emplace_back("");
		if (data[i] == '\n') ind++;
		else lines[ind].push_back(data[i]);
	}
	return lines;
}

/// <summary>
/// функция, убирающая лишнии раздилители
/// </summary>
/// <param name="source">исходный код программы</param>
/// <param name="source_size">размер исходного кода</param>
/// <returns>результат обработки</returns>
char* parce_code(const char* source, size_t source_size) {
	if (!source_size) source_size = strlen(source);
	char* code = new char[source_size];
	int ptr = -1;
	for (size_t i = 0; i < source_size; ++i) {
		if (!isspace(source[i])) code[++ptr] = source[i];
		else if (ptr != -1 && code[ptr] != ' ') code[++ptr] = ' ';
	};
	if (ptr == -1 || code[ptr] != ' ') ptr++;
	code[ptr] = '\0';
	return code;
}

/// <summary>
/// Выводит информацию о разборе исходного кода на терминалы (если установлен соотвествующий аргумент)
/// </summary>
/// <param name="terms">Терминалы</param>
void output_terminal_analysis(const vector<term*>& terms)
{
	if (!out_terminal_analysis) return;	
	ofstream out(terminal_analysis_file_name);
	out << "terminals\tindex\t\tlines\t\tposition\n";
	for (auto& t : terms) {
		out << get_info(t) << endl;
	}
	out.close();
}

/// <summary>
/// Проверяет необходимость вывода help
/// Выводит его при необходимости
/// </summary>
void check_help() {
	if (!out_help) return;
	cout << "bool-lang [SOURCE_FILE] [-o COMPILED_FILE] [-oa ANALYSIS_FILE] [-ota TERMINAL_ANALYSIS_FILE]" << endl << endl;
	cout << "-o (optional) compile the program into the specified file" << endl;
	cout << "-oa (optional) output ascending analysis to the specified file" << endl;
	cout << "-ota (optional) output terminal analysis to the specified file" << endl;
	exit(0);
}

/// <summary>
/// Считывает исходный код из файла и вызывает функции для разбивание его на терминалы
/// </summary>
/// <param name="terms">Терминалы</param>
/// <param name="lines">Исходный код, построчно</param>
void get_terminals(vector<term*>& terms, vector<string>& lines) {
	if (input_file_name.empty()) {
		out_help = true;
		check_help();
	}
	thread initial_thread(initial);
	char* source;
	if (!~read_file(input_file_name.c_str(), source)) {
		initial_thread.join();
		throw runtime_error("File " + input_file_name + " not found");
	}
	initial_thread.join();
	lines = split_lines(source);
	terms = split_on_terminals(lines);
	terms.emplace_back(new term(get_index(END_OF_TAPE), -1, -1));
	output_terminal_analysis(terms);
}

/// <summary>
/// Вызывает восходящее распознование и проверку идентификаторов
/// </summary>
/// <param name="terms">Терминалы</param>
/// <param name="lines">Исходный код, построчно</param>
void analysis_grammar(const vector<term*>& terms, const vector<string>& lines) {
	upstream_analysis(terms);
	pair<int, int> error_pos;
	int check_ident_res = check_error_ident(lines, terms, error_pos);
	if (check_ident_res != NO_ERROR_IN_DECLARE_IDENT) {
		string message;
		if (check_ident_res == UNKNOWN_IDENT) message = "Unknown identifier: ";
		if (check_ident_res == REDECLARED_IDENT) message = "Redclared identifier: ";
		message.append("line " + to_string(error_pos.first + 1) + " position " + to_string(error_pos.second + 1));
		throw runtime_error(message);
	}
}

/// <summary>
/// Выводит информацию об успешной компиляции
/// </summary>
void ouput_success_result() {
	cout << "Successful build" << endl;
	cout << "Compiled file: " << output_file_name << endl;
}

/// <summary>
/// Освобождение ресурсов
/// </summary
/// <param name="terms">Терминалы</param>
void dispose(const vector<term*>& terms) {
	dispose_automate();
	for (auto& trm : terms) {
		delete trm;
	}
}