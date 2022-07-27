//
// Created by clinux01 on 26/07/22.
//


#include <iostream>
#include <random>
#include <vector>

#include <add_array.hh>
#include <CL/sycl.hpp>

using namespace add_array;

using namespace sycl;

int main() {

    std::vector<float> A, B, C(n, 0);

    A.reserve(n);
    B.reserve(n);
    C.reserve(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    float value = dis(gen);
    A.push_back(value);
    B.push_back(value - 1.0f);

    for (int i = 0; i < n - 1; ++i) {
        A.push_back(value += 3);
        B.push_back(value - 1.0f);
    }

    {
        buffer A_b {A}, B_b {B}, C_b {C};
        queue q(gpu_selector{});
        q.submit([&](handler &h) {
            auto A_a = A_b.get_access(h, read_only);
            auto B_a = B_b.get_access(h, read_only);
            auto C_a = C_b.get_access(h, write_only);
            h.parallel_for(1024, [=](auto i) {
                C_a[i] = A_a[i] + B_a[i];
            });
        });
    }

    for (int i = 0; i < 8; ++i) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;


}