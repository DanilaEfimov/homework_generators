#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include<string>

#define ALPHABEET_SIZE 27
#define OP_COUNT 3 /* not, and, or */

enum {
	NOT = 1, AND, OR
};

static bool ans = false;

int getPos(char ch) {
	return (int)(ch - 'a');
}

std::string expression(size_t op, size_t argc, bool* argv) {
	char first = char('a' + rand() % argc);
	std::string res = "";
	res += first;
	ans = argv[getPos(first)];
	int last_code = 0;	// start flag = 0
	bool last_ans = false;
	for (size_t i = 0; i < op; i++) {
		last_ans = ans;
		int code = 1 + rand() % OP_COUNT;
		std::string::iterator it = res.end();
		switch (code) {
		case NOT:
			if (last_code != 0) {
				switch (last_code) {
				case NOT: continue;  break;
				case AND: ans = last_ans && !argv[getPos('a' + (i-1) % argc)]; break;
				case OR: ans = last_ans || !argv[getPos('a' + (i-1) % argc)]; break;
				default:
					std::cerr << "WARNING::EXPRESSION::UNDEFINED_COMMAND_CODE\n";
					return res;
				}
			}
			else { 
				ans = !ans;
			}
			res.erase(--it);
			res += '!'; 
			break;
		case AND: 
			res += " & ";
			ans &= argv[getPos('a' + i % argc)];
			break;
		case OR: 
			res += " | ";
			ans |= argv[getPos('a' + i % argc)];
			break;
		default:
			std::cerr << "WARNING::EXPRESSION::UNDEFINED_COMMAND_CODE\n";
			return res;
		}
		res += char('a' + i % argc);
		last_code = code;
	}
	return res;
}

int main(int argc, char* argv[]) {

	std::setlocale(LC_ALL, "ru");
	std::srand(time(0));
	int count = 0;
	int expressions = 0;
	std::cout << "how many values:\n";
	std::cin >> count;
	std::cout << "how many expressions:\n";
	std::cin >> expressions;

	if (count >= ALPHABEET_SIZE) {
		std::cerr << "WRNING, count was resized to ALPHABEET_SIZE\n";
		count %= ALPHABEET_SIZE;
	}
	if (expressions == 0) {
		std::cerr << "EMPTY REQUEST\n";
		std::exit(EXIT_FAILURE);
	}

	std::fstream homework("homework.txt");
	std::fstream answers("answer.txt");
	if (!homework.is_open() || !answers.is_open()) {
		std::cerr << "ERROR::failed to open file\n";
		std::exit(EXIT_FAILURE);
	}

	homework << "логические переменные (как в алгебре, но только 'истина' или  'ложь'):\n\n";
	bool* values = new bool[count];
	for (size_t i = 0; i < count; i++) {
		values[i] = rand() % 2;
		homework << (char)('a' + i) << " = "
		<< std::boolalpha << values[i] << ' ';	// value[i] ? "true" : false" << ' ';
	}
	homework << "\n\n";

	homework << "у логических операций так же есть приоритет действий\n";
	homework << "так же как умножение выполняется раньше сложения, так же\n";
	homework << "и логическое 'НЕ' выполняется раньше 'И', а 'И' раньше 'ИЛИ'.\n";
	homework << "ВНИМАНИЕ, в этих примерах прошу выполнять действия строго слева-направо\n";
	homework << "Удачи!\n\n";
	homework << " | - ИЛИ;\t & - И;\t\t ! - НЕ\n\n";
	homework << "найдите значение логических выражений:\n";

	answers << "Ответы:\n";
	for (size_t i = 0; i < expressions; i++) {
		size_t hard = 1 + rand() % count;
		homework << expression(hard, count, values) << std::endl;
		answers << i + 1 << ") " << std::boolalpha << ans << std::endl;;
	}

	delete[] values;

	homework.close();
	answers.close();

	return 0;
}