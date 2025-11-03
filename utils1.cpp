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
        Student st;
        st.pav = "Pavarde" + std::to_string(i+1);
        st.var = "Vardas"  + std::to_string(i+1);
        st.galVid = d(rng);
        st.galMed = d(rng);
        v.push_back(st);
    }
    return v;
}
