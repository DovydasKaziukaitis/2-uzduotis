#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include "student2.h"
#include "io2.h"
#include "utils2.h"
#include <iomanip>

using laikr_t = std::chrono::high_resolution_clock;

static void testasVector(const std::string& path, Mode m, Strategija s);
static void testasList(const std::string& path, Mode m, Strategija s);
static void RankinisIvedimasVector(Mode m);
static void RankinisIvedimasList(Mode m);

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

        if (mnu == 3) { RankinisIvedimasVector(mode); continue; }
        if (mnu == 4) { RankinisIvedimasList(mode); continue; }
        std::cout << "Blogas pasirinkimas\n";
    }
    return 0;
}

static void RankinisIvedimasVector(Mode m) {
    std::string pav, var;
    double vid, med;
    std::cout << "Iveskite: Pavarde Vardas Galutinis(Vid) [Galutinis(Med)]: ";
    if (!(std::cin >> pav >> var >> vid)) return;
    if (std::cin.peek() != '\n') {if(!(std::cin >> med)) med = vid; }
    else med = vid;
    
    Student st(pav, var, vid, med);
    std::vector<Student> v; v.push_back(st);
    std::cout << "Objekto adresas (vector): " << static_cast<const void*>(&v.back()) << "\n";
    lentelesSpausdinimas(v, m);
}

static void RankinisIvedimasList(Mode m) {
    std::string pav, var;
    double vid, med;
    std::cout << "Iveskite: Pavarde Vardas Galutinis(Vid) [Galutinis(Med)]: ";
    if (!(std::cin >> pav >> var >> vid)) return;
    if (std::cin.peek() != '\n') {if (!(std::cin >> med)) med = vid; }
    else med = vid;
    Student st(pav, var, vid, med);
    std::list<Student> s; s.push_back(st);
    std::cout << "Objekto adresas (list): " << static_cast<const void*>(&s.back()) << "\n";
    lentelesSpausdinimas(s, m);
}

static double to_ms(laikr_t::duration d) {
    using namespace std::chrono;
    return duration_cast<microseconds>(d).count()/1000.0;
}

static void testasVector(const std::string& path, Mode m, Strategija strat) {
    auto t_all0 = laikr_t::now();

    auto t0 = laikr_t::now();
    auto s = studentuSkaitymas(path);
    auto t_read = laikr_t::now() - t0;

    t0 = laikr_t::now();
    std::sort(s.begin(), s.end(), [](const Student& a, const Student& b){
        if (a.getPavarde() != b.getPavarde()) return a.getPavarde() < b.getPavarde();
        return a.getVardas() < b.getVardas();
    });
    auto t_sort = laikr_t::now() - t0;

    std::vector<Student> varg, kiet;

    t0 = laikr_t::now();
    if (strat == Strategija::S1) padalinimasStrategija1(s, m, varg, kiet);
    else if (strat == Strategija::S2) padalinimasStrategija2(s, m, varg, kiet);
    else padalinimasStrategija3(s, m, varg, kiet);
    auto t_split = laikr_t::now() - t0;

    t0 = laikr_t::now();
    grupesIrasymas("vargsiukai.txt", varg, m);
    auto t_w1 = laikr_t::now() - t0;

    t0 = laikr_t::now();
    grupesIrasymas("kietiakiai.txt",  kiet, m);
    auto t_w2 = laikr_t::now() - t0;

    auto t_all = laikr_t::now() - t_all0;

    std::cout << "Vector (strategija " << static_cast<int>(strat) << ")\n";
    std::cout << "Failo nuskaitymo laikas: " << std::fixed << std::setprecision(6) << to_ms(t_read) << "\n";
    std::cout << "Rusiavimo laikas: "        << to_ms(t_sort)  << "\n";
    std::cout << "Dalinimo laikas: "         << to_ms(t_split) << "\n";
    std::cout << "Israsymo (1) laikas: "     << to_ms(t_w1)    << "\n";
    std::cout << "Israsymo (2) laikas: "     << to_ms(t_w2)    << "\n";
    std::cout << "Viso: "                    << to_ms(t_all)   << "\n";
}

static void testasList(const std::string& path, Mode m, Strategija strat) {
    auto t_all0 = laikr_t::now();

    auto t0 = laikr_t::now();
    auto v = studentuSkaitymas(path);
    auto t_read = laikr_t::now() - t0;
    std::list<Student> s(v.begin(), v.end());

    t0 = laikr_t::now();
    s.sort([](const Student& a, const Student& b){
        if (a.getPavarde() != b.getPavarde()) return a.getPavarde() < b.getPavarde();
        return a.getVardas() < b.getVardas();
    });
    auto t_sort = laikr_t::now() - t0;

    std::list<Student> varg, kiet;

    t0 = laikr_t::now();
    if (strat == Strategija::S1) padalinimasStrategija1(s, m, varg, kiet);
    else if (strat == Strategija::S2) padalinimasStrategija2(s, m, varg, kiet);
    else padalinimasStrategija3(s, m, varg, kiet);
    auto t_split = laikr_t::now() - t0;

    t0 = laikr_t::now();
    grupesIrasymas("vargsiukai.txt", varg, m);
    auto t_w1 = laikr_t::now() - t0;

    t0 = laikr_t::now();
    grupesIrasymas("kietiakiai.txt",  kiet, m);
    auto t_w2 = laikr_t::now() - t0;

    auto t_all = laikr_t::now() - t_all0;


    std::cout << "List (strategija " << static_cast<int>(strat) << ")\n";
    std::cout << "Failo nuskaitymo laikas: " << std::fixed << std::setprecision(6) << to_ms(t_read) << "\n";
    std::cout << "Rusiavimo laikas: "        << to_ms(t_sort)  << "\n";
    std::cout << "Dalinimo laikas: "         << to_ms(t_split) << "\n";
    std::cout << "Israsymo (1) laikas: "     << to_ms(t_w1)    << "\n";
    std::cout << "Israsymo (2) laikas: "     << to_ms(t_w2)    << "\n";
    std::cout << "Viso: "                    << to_ms(t_all)   << "\n";
}


