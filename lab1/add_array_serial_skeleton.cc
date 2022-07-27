#include <iostream>
#include <random>
#include <vector>

#include <add_array.hh>

using namespace add_array;

int main() {
	std::vector<float> A, B, C(n, 0);

  // ensure the vectors are contiguous
	A.reserve(n);
	B.reserve(n);
	C.reserve(n);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, 1.0f);

  // use a random value to initialize the first element to avoid compiler
  // optimizations
	float value = dis(gen);
	A.push_back(value);
	B.push_back(value - 1.0f);

  // initialize the array
    for (int i = 0; i < n - 1; ++i) {
        A.push_back(value += 3);
        B.push_back(value - 1.0f);
    }

	// add the two vectors
    for (int i = 0; i < n; ++i) {
        C[i] = A[i] + B[i];
    }

  // print the first 8 elements
    for (int i = 0; i < 8; ++i) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;
}
