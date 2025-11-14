#pragma once
#include <string>

enum class Mode { Vid = 1, Med = 2 };
enum class Strategija {S1 = 1, S2 = 2, S3 = 3};

class Student {
private:
    std::string pavarde_;
    std::string vardas_;

    std::vector<double> nd_;
    double egzaminas_ = 0.0;
    double galVid_;
    double galMed_;

    static double vidurkis(const std::vector<double>& v) {
        if (v.empty()) return 0.0;
        double sum = std::accumulate(v.begin(), v.end(), 0.0);
        return sum / v.size():
    }

    static double mediana(std::vector<double> v) {
        if (v.empty()) return 0.0;
        std::sort(v.begin(), v.end());
        size_t n = v.size();
        if (n % 2 == 1) return v[n / 2];
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    }

    void perskaiciuotiIsPirminiu() {
        double vid = vidurkis(nd_);
        double med = mediana(nd_);
        GalVid_ = 0.4 * egzaminas_ + 0.6 * vid;
        GalMed_ = 0.4 * egzaminas_ + 0.6 * med;

public:
    Student()
        : pavarde_(), vardas_(), galVid_(0.0), nd_(), egzaminas_(0.0), galMed(0.0) {}

    Student(const std::string& pav, const std::string& var, double vid, double med)
        : pavarde_(pav), vardas_(var), galVid_(vid), galMed(med) {}
};





