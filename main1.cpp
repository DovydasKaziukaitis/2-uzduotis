#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include "student1.h"
#include "io1.h"
#include "utils1.h"
#include <iomanip>

static void vektoriausSpartosTestas(const std::string& path, Mode m);
static void sarasoSpartosTestas    (const std::string& path, Mode m);

int main(int argc, char** argv) {
    Mode mode = Mode::Vid;
    std::string dump;

    while (true) {
        std::cout << "\n=== MENIU ===\n"
                  << "1) Testas: Vector \n"
                  << "2) Testas List\n"
                  << "3) Rankinis ivedimas(vector)\n"
                  << "4) Rankinis ivedimas(list)\n"
                  << "5) Keisti rezima (1-Vid, 2-Med; dabar: " << (mode==Mode::Vid?"Vid":"Med") << ")\n"
                  << "0) Baigti\n"
                  << "Pasirinkite: ";

        int mnu;
        if (!(std::cin >> mnu)) return 0;
        std::getline(std::cin, dump);
        if (mnu == 0) break;

        if (mnu == 5) {
            std::cout << "Naujas rezimas (1-Vid, 2-Med): ";
            int x; if (!(std::cin >> x)) return 0;
            std::getline(std::cin, dump);
            mode = (x == 2 ? Mode::Med : Mode::Vid);
            continue;
        }

        if (mnu == 1 || mnu == 2) {
            int s; std::cout << "Strategija (1-kopijavimas, 2-perkelimas, 3-partition/splice): ";
            if (!(std::cin >> s) || s < 1 || s > 3) { std::getline(std::cin, dump); continue; }
            std::getline(std::cin, dump);
            std::string path = (argc >= 2 ? argv[1] : "");
            if (path.empty()) { std::cout << "Failo kelias: "; std::getline(std::cin, path); }
            if (mnu == 1) testasVector(path, mode, static_cast<Strategija>(s));
            else          testasList  (path, mode, static_cast<Strategija>(s));
            continue;
        }

        if (mnu == 3) {
        }

        if (mnu == 4) {
        }


        std::cout << "Blogas pasirinkimas\n";
    }
    return 0;
}

static void rankinisIvedimasVector(Mode m) {
    Student st;
    std::cout << "Iveskite: Pavarde Vardas Galutinis(Vid) [Galutinis(Med)]: ";
    if (!(std::cin >> st.pav >> st.var >> st.galVid)) return;
    if (std::cin.peek() != '\n') { double med; if (std::cin >> med) st.galMed = med; else st.galMed = st.galVid; }
    else st.galMed = st.galVid;

    std::vector<Student> v; v.push_back(st);
    std::cout << "Objekto adresas (vector): " << static_cast<const void*>(&v.back()) << "\n";
    lentelesSpausdinimas(v, m);
}

static void rankinisIvedimasList(Mode m) {
    Student st;
    std::cout << "Iveskite: Pavarde Vardas Galutinis(Vid) [Galutinis(Med)]: ";
    if (!(std::cin >> st.pav >> st.var >> st.galVid)) return;
    if (std::cin.peek() != '\n') { double med; if (std::cin >> med) st.galMed = med; else st.galMed = st.galVid; }
    else st.galMed = st.galVid;

    std::list<Student> s; s.push_back(st);
    std::cout << "Objekto adresas (list): " << static_cast<const void*>(&s.back()) << "\n";
    lentelesSpausdinimas(s, m);
}

static void vektoriausSpartosTestas(const std::string& path, Mode m) {
    using clock = std::chrono::high_resolution_clock;
    auto now = []{ return clock::now(); };
    auto ms  = [](auto d){ using namespace std::chrono;
                           return duration_cast<microseconds>(d).count()/1000.0; };

    auto t_all0 = now();

    auto t0 = now();
    auto s = studentuSkaitymas(path);
    auto t_read = now() - t0;

    t0 = now();
    std::sort(s.begin(), s.end(), [](const Student& a, const Student& b){
        if (a.pav != b.pav) return a.pav < b.pav;
        return a.var < b.var;
    });
    auto t_sort = now() - t0;

    t0 = now();
    std::vector<Student> varg; varg.reserve(s.size());
    std::vector<Student> kiet; kiet.reserve(s.size());
    for (const auto& st : s) {
        double v = (m == Mode::Vid ? st.galVid : st.galMed);
        (v < 5.0 ? varg : kiet).push_back(st);
    }
    auto t_split = now() - t0;

    t0 = now();
    grupesIrasymas("vargsiukai.txt", varg, m);
    auto t_w1 = now() - t0;

    t0 = now();
    grupesIrasymas("kietiakiai.txt",  kiet, m);
    auto t_w2 = now() - t0;

    auto t_all = now() - t_all0;

    std::cout << "Vector\n";
    std::cout << "Failo nuskaitymo laikas: " << std::fixed << std::setprecision(6) << ms(t_read) << "\n";
    std::cout << "Rusiavimo laikas: "        << ms(t_sort)  << "\n";
    std::cout << "Dalinimo laikas: "         << ms(t_split) << "\n";
    std::cout << "Israsymo (1) laikas: "     << ms(t_w1)    << "\n";
    std::cout << "Israsymo (2) laikas: "     << ms(t_w2)    << "\n";
    std::cout << "Viso: "                    << ms(t_all)   << "\n";
}

static void sarasoSpartosTestas(const std::string& path, Mode m) {
    using clock = std::chrono::high_resolution_clock;
    auto now = []{ return clock::now(); };
    auto ms  = [](auto d){ using namespace std::chrono;
                           return duration_cast<microseconds>(d).count()/1000.0; };

    auto t_all0 = now();

    auto t0 = now();
    auto v = studentuSkaitymas(path);
    auto t_read = now() - t0;

    std::list<Student> s(v.begin(), v.end());

    t0 = now();
    s.sort([](const Student& a, const Student& b){
        if (a.pav != b.pav) return a.pav < b.pav;
        return a.var < b.var;
    });
    auto t_sort = now() - t0;

    t0 = now();
    std::list<Student> varg, kiet;
    for (const auto& st : s) {
        double vbal = (m == Mode::Vid ? st.galVid : st.galMed);
        (vbal < 5.0 ? varg : kiet).push_back(st);
    }
    auto t_split = now() - t0;

    t0 = now();
    grupesIrasymas("vargsiukai.txt", varg, m);
    auto t_w1 = now() - t0;

    t0 = now();
    grupesIrasymas("kietiakiai.txt",  kiet, m);
    auto t_w2 = now() - t0;

    auto t_all = now() - t_all0;

    std::cout << "List\n";
    std::cout << "Failo nuskaitymo laikas: " << std::fixed << std::setprecision(6) << ms(t_read) << "\n";
    std::cout << "Rusiavimo laikas: "        << ms(t_sort)  << "\n";
    std::cout << "Dalinimo laikas: "         << ms(t_split) << "\n";
    std::cout << "Israsymo (1) laikas: "     << ms(t_w1)    << "\n";
    std::cout << "Israsymo (2) laikas: "     << ms(t_w2)    << "\n";
    std::cout << "Viso: "                    << ms(t_all)   << "\n";
}


