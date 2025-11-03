#include "io1.h"
#include "student1.h"
#include "utils1.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cstdlib>

std::vector<Student> studentuSkaitymas(const std::string& path) {
    std::ifstream f(path);
    if (!f) { std::cerr << "Nepavyko atidaryti: " << path << "\n"; return {}; }

    std::vector<Student> out;

    for (std::string line; std::getline(f, line); ) {
        if (line.empty()) continue;
        for (char& c : line) if (c == ',') c = '.';

        std::istringstream is(line);
        std::vector<std::string> tok;
        std::string t;
        while (is >> t) tok.push_back(t);
        if (tok.size() < 3) continue;

        auto parse_d = [](const std::string& s, double& v)->bool{
            char* e = nullptr;
            v = std::strtod(s.c_str(), &e);
            return e && *e == '\0';
        };

        double g1 = 0, g2 = 0;
        bool have1 = parse_d(tok.back(), g1);
        bool have2 = (tok.size() >= 4) && parse_d(tok[tok.size()-2], g2);

        std::string pav, var;
        double vid = 0, med = 0;

        if (have1 && have2) {
            vid = g2; med = g1;
            tok.pop_back();
            tok.pop_back();
        } else if (have1) {
            vid = med = g1;
            tok.pop_back();
        } else {
            continue;
        }

        size_t start = 0;
        if (tok.size() - start < 2) continue;

        pav = tok[start];
        var = tok[start + 1];

        out.push_back(Student{pav, var, vid, med});
    }

    return out;
}

static void antrastesSpausdinimas(std::ostream& out, Mode m) {
    out << std::left << std::setw(12) << "Pavarde"
        << std::setw(12) << "Vardas";
    if (m == Mode::Vid) out << std::right << std::setw(14) << "Galutinis(Vid)\n";
    else                out << std::right << std::setw(14) << "Galutinis(Med)\n";
    out << std::string(38, '-') << "\n";
    out << std::fixed << std::setprecision(2);
}

void lentelesSpausdinimas(const std::vector<Student>& s, Mode m) {
    antrastesSpausdinimas(std::cout, m);
    for (const auto& st : s) {
        std::cout << std::left  << std::setw(12) << st.pav
                  << std::setw(12) << st.var
                  << std::right << std::setw(14)
                  << (m == Mode::Vid ? st.galVid : st.galMed) << "\n";
    }
}

void lentelesSpausdinimas(const std::list<Student>& s, Mode m) {
    antrastesSpausdinimas(std::cout, m);
    for (const auto& st : s) {
        std::cout << std::left  << std::setw(12) << st.pav
                  << std::setw(12) << st.var
                  << std::right << std::setw(14)
                  << (m == Mode::Vid ? st.galVid : st.galMed) << "\n";
    }
}

static void antrastesRasymas(std::ostream& out, Mod m) {
    out << std::left << std::stw(12) << "Pavarde"
        << std::setw(12) << "Vardas";
    if (m ==Mode::Vid) out << std::right << std::setw(14) << "Galutinis(Vid)\n";
    else               out << std::right << std::setw(14) << "Galutinis(Med)\n";
    out << std::string(38, '-') << "\n";
    out << std::fixed << std::setprecision(2);
}

void grupesIrasymas(const std::string& path, const std::vector<Student>& s, Mode m) {
    std::ofstream out(path);
    if (!out) return;
    antrastesRasymas(out, m);
    for (const auto& st : s) {
        out << std::left << std::stw(12) << st.pav
            << std::setw(12) << st.var
            << std::right << std::setw(14)
            << (m == Mode::Vid ? st.galVid : st.galMed) << "\n";
    }
}

void grupesIrasymas(const std::string& path, const std::list<Student>& s, Mode m) {
    std::ofstream out(path);
    if (!out) return;
    antrastesRasymas(out, m);
    for (const auto& st : s) {
        out << std::left << std::stw(12) << st.pav
            << std::setw(12) << st.var
            << std::right << std::setw(14)
            << (m == Mode::Vid ? st.galVid : st.galMed) << "\n";
    }
}

void padalinimasStrategija1(std::vector<Student> const& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet) {
    varg.clear(); kiet.clear();
    varg.resserve(s.size());
    kiet.reserve(s.size());
    for (const auto& st : s) {
        double v = (m == Mode::Vid ? st.galVid : st.galMed);
        (v < 5.0 ? varg : kiet).push_back(st);
    }
}

void padalinimasStrategija1(std::list<Student> const& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet) {
    varg.clear(); kiet.clear();
    for (const auto& st : s) {
        double v = (m == Mode::Vid ? st.galVid : st.galMed);
        (v < 5.0 ? varg : kiet).push_back(st);
    }
}

void padalinimasStrategija2(std::vector<Student> const& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet) {
    varg.clear(); kiet.clear();
    varg.resserve(s.size());
    kiet.reserve(s.size());
    for (const auto& st : s) {
        double v = (m == Mode::Vid ? st.galVid : st.galMed);
        (v < 5.0 ? varg : kiet).push_back(st);
    }
}

void padalinimasStrategija2(std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet) {
    varg.clear(); kiet.clear();
    varg.reserve(s.size());
    auto it = std::remove_if(s.begin(), s.end(), [&](Student& st){
        double v = (m == Mode::Vid ? st.galVid : st.galMed);
        if (v < 5.0) { varg.push_back(std::move(st)); return true; }
        return false;
    });
    s.erase(it, s.end());
    kiet.swap(s);
}

void padalinimasStrategija2(std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet) {
    varg.clear(); kiet.clear();
    for(auto it = s.begin(); it != s.end();){
        auto nxt = std::next(it);
        double v = (m == Mode::Vid ? it->galVid : it->galMed);
        if (v < 5.0) varg.splice(varg.end(), s, it);
        it = nxt;
    }
    kiet.swap(s);
}

void padalinimasStrategija3(std::vector<Student> const& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet) {
    std::vector<Student> tmp = s;
    auto pivot = std::partition(tmp.begin(), tmp.end(), [&](const Student& st){
        return (m == Mode::Vid ? st.galVid : st.galMed) < 5.0;
    });
    varg.assign(tmp.begin(), pivot);
    kiet.assign(pivot, tmp.end());
}

void padalinimasStrategija3(std::list<Student> const& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet) {
    varg,clear(); kiet.clear();
    for(auto it = s.begin(), it != s.end(); ) {
        auto nxt = std::next(it);
        double v = (m == Mode::Vid ? it->galVid : it->galMed);
        if (v < 5.0) varg.splice(varg.end(), s , it);
        it = nxt;
    }
    kiet.swap(s);
}



