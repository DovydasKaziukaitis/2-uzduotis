#include "utils1.h"
#include <fstream>
#include <iomanip>
#include <random>

std::vector<Student> studentuGeneravimas(int m) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> d(2.0, 9.9);

    std::vector<Student> v;
    v.reserve(m);
    for (int i = 0; i < m; ++i) {
        std::string pav = "Pavarde" + std::to_string(i+1);
        std::string var = "Vardas"  + std::to_string(i+1);

        std::vector<double> nd;
        nd.reserve(5);
        for (int j = 0; j < 5; ++j)
            nd.push_back(d(rng));
        double egz = d(rng);
        v.emplace_back(pav, var, nd, egz);
    }
    return v;
}


