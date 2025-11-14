#pragma once
#include <string>

enum class Mode { Vid = 1, Med = 2 };
enum class Strategija {S1 = 1, S2 = 2, S3 = 3};

class Student {
private:
    std::string pavarde_;
    std::string vardas_;
    double galVid_;
    double galMed_;
public:
    Student()
        : pavarde_(), vardas_(), galVid_(0.0), galMed(0.0) {}

    Student(const std::string& pav, const std::string& var, double vid, double med)
        : pavarde_(pav), vardas_(var), galVid_(vid), galMed(med) {}
};





