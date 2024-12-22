#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>

#define ACCURACY 100

int main(int argc, char** argv) {
	std::setlocale(LC_ALL, "ru");

	std::srand(time(0));
	int count = 0;
	int littlest = 0;
	int greatest = 0;

	std::cout << "input, please, count of exp-s, littlest & greatest value:\n";
	std::cin >> count >> littlest >> greatest;

	if (!count) {
		std::cout << "EMPTY REQUEST\n";
		return 0;
	}

	int delta = greatest - littlest;
	std::fstream file("homework.txt");
	std::fstream answers("answer.txt");
	if (!file.is_open() || !answers.is_open()) {
		std::cerr << "ERROR::failed to open file\n";
		std::exit(EXIT_FAILURE);
	}

	file << "выполните умножение столбиком: \n";
	answers << "умножение столбиком: \n";
	for (size_t i = 0; i < count; i++) {
		int _left = littlest + rand() % delta + 1;
		int _right = littlest + rand() % delta + 1;
		file << _left << " * " << _right << " = ?\n";
		answers << i + 1 << ") " << _left * _right << std::endl;
	}

	int f_count;
	std::cout << "input, please, count of exp-s, littlest & greatest value:\n";
	std::cin >> f_count >> littlest >> greatest;

	if (!f_count) {
		std::cout << "EMPTY REQUEST\n";
		return 0;
	}

	file << "\n\nвыполните умножение десятичных дробей:\n";
	answers << "\n\nдесятичные дроби: \n";
	delta = greatest - littlest;
	float f_littlest = static_cast<float>(littlest);
	for (size_t i = 0; i < f_count; i++) {
		float _left = f_littlest + (float)(rand() % delta)
			+ std::floor(1.0f / (1.f + (float)(rand() % ACCURACY)) * ACCURACY) / ACCURACY;
		float _right = f_littlest + (float)(rand() % delta)
			+ std::floor(1.0f / (1.f + (float)(rand() % ACCURACY)) * ACCURACY) / ACCURACY;
		file << _left << " * " << _right << " = ?\n";
		answers << i + 1 << ") " << _left * _right << std::endl;
	}

	file.close();
	answers.close();

	return 0;
}