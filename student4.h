#pragma once
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

enum class Mode { Vid = 1, Med = 2 };
enum class Strategija { S1 = 1, S2 = 2, S3 = 3 };

class Zmogus {
protected:
    std::string pavarde_;
    std::string vardas_;
public:
    Zmogus() : pavarde_(), vardas_() {}
    Zmogus(const std::string& pav, const std::string& var)
        : pavarde_(pav), vardas_(var) {}
    Zmogus(const Zmogus&) = default;
    Zmogus& operator=(const Zmogus&) = default;
    virtual ~Zmogus() = 0;

    const std::string& getPavarde() const { return pavarde_; }
    const std::string& getVardas()  const { return vardas_;  }
    void setPavarde(const std::string& pav) { pavarde_ = pav; }
    void setVardas(const std::string& var)  { vardas_  = var; }
};

inline Zmogus::~Zmogus() {}

class Studentas : public Zmogus {
private:
    std::vector<double> nd_;
    double egzaminas_;
    double galVid_;
    double galMed_;

    static double vidurkis(const std::vector<double>& v) {
        if (v.empty()) return 0.0;
        double sum = std::accumulate(v.begin(), v.end(), 0.0);
        return sum / v.size();
    }

    static double mediana(std::vector<double> v) {
        if (v.empty()) return 0.0;
        std::sort(v.begin(), v.end());
        size_t n = v.size();
        if (n % 2 == 1) return v[n/2];
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    }

    void perskaiciuotiIsPirminiu() {
        galVid_ = 0.4 * egzaminas_ + 0.6 * vidurkis(nd_);
        galMed_ = 0.4 * egzaminas_ + 0.6 * mediana(nd_);
    }

public:

    Studentas()
        : Zmogus(), nd_(), egzaminas_(0.0), galVid_(0.0), galMed_(0.0) {}

    Studentas(const std::string& pav, const std::string& var, double vid, double med)
        : Zmogus(pav, var), nd_(), egzaminas_(0.0), galVid_(vid), galMed_(med) {}

    Studentas(const std::string& pav, const std::string& var,
              const std::vector<double>& nd, double egz)
        : Zmogus(pav, var), nd_(nd), egzaminas_(egz) {
        perskaiciuotiIsPirminiu();
    }


    Studentas(const Studentas& kitas)
        : Zmogus(kitas),  
          nd_(kitas.nd_), 
          egzaminas_(kitas.egzaminas_), 
          galVid_(kitas.galVid_),
          galMed_(kitas.galMed_)
    {
    }

    Studentas& operator=(const Studentas& kitas) {
        if (this != &kitas) {    
            Zmogus::operator=(kitas);  
            nd_        = kitas.nd_;
            egzaminas_ = kitas.egzaminas_;
            galVid_    = kitas.galVid_;
            galMed_    = kitas.galMed_;
        }
        return *this;
    }

    ~Studentas() override { }


    double getGalVid() const { return galVid_; }
    double getGalMed() const { return galMed_; }
    const std::vector<double>& getNd() const { return nd_; }
    double getEgz() const { return egzaminas_; }


    void setNd(const std::vector<double>& nd) {
        nd_ = nd;
        perskaiciuotiIsPirminiu();
    }
    void setEgz(double egz) {
        egzaminas_ = egz;
        perskaiciuotiIsPirminiu();
    }

    friend std::istream& operator>>(std::istream&, Studentas&);
    friend std::ostream& operator<<(std::ostream&, const Studentas&);
};

inline std::istream& operator>>(std::istream& is, Studentas& st) {
    double nd;
    while (is >> nd) st.nd_.push_back(nd);
    is >> st.egzaminas_;
    st.perskaiciuotiIsPirminiu();
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Studentas& st) {
    os << st.getPavarde() << " " << st.getVardas() << " "
       << st.getGalVid() << " " << st.getGalMed();
    return os;
}

using Student = Studentas;
