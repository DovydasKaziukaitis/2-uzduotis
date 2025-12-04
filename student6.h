#pragma once
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

enum class Mode { Vid = 1, Med = 2 };
enum class Strategija { S1 = 1, S2 = 2, S3 = 3 };

class Student {
private:
    std::string pavarde_;
    std::string vardas_;

    std::vector<double> nd_;
    double egzaminas_;
    double galVid_;
    double galMed_;

    static double vidurkis(const std::vector<double>& v) {
        if (v.empty()) return 0.0;
        double sum = std::accumulate(v.begin(), v.end(), 0.0);
        return sum / static_cast<double>(v.size());
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
        galVid_ = 0.4 * vid + 0.6 * egzaminas_;
        galMed_ = 0.4 * med + 0.6 * egzaminas_;
    }

public:
    Student()
        : pavarde_(), vardas_(), nd_(), egzaminas_(0.0), galVid_(0.0), galMed_(0.0) {}

    Student(const std::string& pav, const std::string& var, double vid, double med)
        : pavarde_(pav), vardas_(var), nd_(), egzaminas_(0.0), galVid_(vid), galMed_(med) {}

    Student(const std::string& pav, const std::string& var,
            const std::vector<double>& nd, double egz)
        : pavarde_(pav), vardas_(var),
          nd_(nd), egzaminas_(egz) {
        perskaiciuotiIsPirminiu();
    }


    inline const std::string& getPavarde()  const { return pavarde_; }
    inline const std::string& getVardas()   const { return vardas_;  }
    inline double getGalVid()               const { return galVid_;  }
    inline double getGalMed()               const { return galMed_;  }

    inline const std::vector<double>& getNd() const { return nd_; }
    inline double getEgz() const { return egzaminas_; }

    inline void setPavarde(const std::string& pav) { pavarde_ = pav; }
    inline void setVardas(const std::string& var)  { vardas_  = var; }

    inline void setGalVid(double v) { galVid_ = v; }
    inline void setGalMed(double m) { galMed_ = m; }

    inline void setNd(const std::vector<double>& nd) {
        nd_ = nd;
        perskaiciuotiIsPirminiu();
    }
    inline void setEgz(double egz) {
        egzaminas_ = egz;
        perskaiciuotiIsPirminiu();
    }

    friend std::istream& operator>>(std::istream& is, Student& st);
    friend std::ostream& operator<<(std::ostream& os, const Student& st);
};








