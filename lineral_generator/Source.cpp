#include<iostream>
#include<fstream>
#include<ctime>

#define NP (negative ? (rand() % 2 ? -1 : 1) : 1) /* n - negative, p - positive */
#define ACCURACY 10

int main(int argc, char** argv) {

	srand(time(0));
	int count;
	int maxn;
	bool negative = false;
	std::cout << "Do You want to include negative solution? (0/1):";
	std::cin >> negative;

	std::cout << "How many do You want? How large nums?: ";
	std::cin >> count >> maxn;

	std::fstream homework("homework.txt");
	std::fstream answers("answer.txt");

	if (!answers.is_open() || !homework.is_open()) {
		std::cerr << "ERROR::failed to open file\n";
		std::exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < count; i++) {	// kx + b = 0
		int k = (1 + rand() % maxn) * NP;
		int b = (1 + rand() % maxn) * -NP;
		homework << k << " * x " << (b > 0 ? " + " : " - ")
			<< (b > 0 ? b : -b) << " = 0\n";
		answers << i + 1 << ") " << -b << " / " << k << "\t\t("
				<< static_cast<float>(-b) / k << ")\n";
	}

	std::cout << "How many float-point equations do You want?: ";
	std::cin >> count;

	if (count == 0) {
		answers.close();
		homework.close();
		return 0;
	}

	std::cout << "Greatest num:";
	std::cin >> maxn;

	homework << "\n\n";
	answers << "\n\n";
	for (size_t i = 0; i < count; i++) {
		float k = (2.f + (float)(rand() % maxn)) * NP
			+ std::floor(1.0f / (1.f + (float)(rand() % ACCURACY)) * ACCURACY) / ACCURACY;
		float b = 1.f + (float)(rand() % maxn) * -NP
			+ std::floor(1.0f / (1.f + (float)(rand() % ACCURACY)) * ACCURACY) / ACCURACY;
		homework << k << " * x " << (b > 0 ? " + " : " - ") 
								 << (b > 0 ? b : -b) << " = 0\n";
		answers << i + 1 << ") " << -b << " / " << k << "\t\t(" << -b / k << ")\n";
	}

	answers.close();
	homework.close();

	return 0;
}