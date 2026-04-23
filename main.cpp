#include <iostream>

void fib(int n) {
	int* fibarr = new int[n];
	fibarr[0] = 0;
	fibarr[1] = 1;
	std::cout << 0 << '\n' << 1 << '\n';
	for (int i = 2; i < n; i++) {
		fibarr[i] = fibarr[i-1]+fibarr[i-2];
		std::cout << fibarr[i] << '\n';
	}
	delete[] fibarr;
}

int main() {
	int n;
	std::cout << "Enter N: ";
	std::cin >> n;
	fib(n);
	std::cout << "hello world again";
}
