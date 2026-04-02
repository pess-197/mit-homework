#include <iostream>

int fib(int n) {
	if (n == 1) {
		return 0;
	}
	if (n == 2) {
		return 1;
	}
	if (n > 2) {
		return fib(n-1)+fib(n-2);
	}
}

int main() {
	int n;
	std::cout << "Enter n: ";
	std::cin >> n;
	std::cout << fib(n) << std::endl;
}
