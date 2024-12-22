#include<iostream>
#include<fstream>
#include<ctime>
#include <locale.h>

#define SGN (rand() % 2 ? -1 : 1)

void rewrite(std::fstream& _in, int a, int b, int c) {
	if (!_in.is_open()) {
		std::cerr << "ERROR::failed to open file\n";
		return;
	}
	_in << a << "x^2";
	if (b > 0) {
		_in << " + " << b << "x";
	}
	else if(b < 0) {
		_in << " - " << -b << "x";
	}
	if (c > 0) {
		_in << " + " << c << " = 0";
	}
	else if (c < 0) {
		_in << " - " << -c << " = 0";
	}
	else { _in << " = 0"; }
}

void solve(std::fstream& _in, int a, int b, int c) {
	if (!a) { std::cerr << "FATAL_ERROR\n"; return; }
	if (!_in.is_open()) {
		std::cerr << "ERROR::failed to open file\n";
		return;
	}
	int64_t D = b * b - 4 * a * c;
	if (D == 0) {
		_in << -b << '/' << 2 << a;
	}
	else {
		if (D > 0) {
			_in << '(' << -b << " + root " << D << ")/" << 2
				<< '(' << a << ')';
			_in << "\t\t";
			_in << '(' << -b << " - root " << D << ")/" << 2 
				<< '(' << a << ')';
		}
		else {
			_in << "D < 0 " << '(' << "D = " << D << ')';
		}
	}
}

int main(int argc, char** argv) {

	std::srand(time(0));

	int count = 0;
	int greatest = 0;
	std::cout << "how many equations and high border: ";
	std::cin >> count >> greatest;

	if (count == 0 || greatest == 0) {
		std::cerr << "EMPTY_REQUEST\n";
		std::exit(EXIT_FAILURE);
	}

	std::fstream homework("homework.txt");
	std::fstream answers("answer.txt");

	if (!homework.is_open() || !answers.is_open()) {
		std::cerr << "ERROR::failed to open file\n";
		std::exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < count; i++) {
		int a = SGN * (1 + rand() % greatest);
		int b = SGN * rand() % greatest;
		int c = SGN * rand() % greatest;
		if (!a) { std::cerr << "FATAL_ERROR\n"; return -1; }
		rewrite(homework, a, b, c);
		homework << std::endl;
		answers << i + 1 << ") ";
		solve(answers, a, b, c);
		answers << std::endl;
	}

	answers.close();
	homework.close();

	return 0;
}