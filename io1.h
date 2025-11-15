#pragma once
#include <string>
#include <vector>
#include <list>
#include "student1.h"

std::vector<Student> studentuSkaitymas(const std::string& path);
void lentelesSpausdinimas(const std::vector<Student>& s, Mode m);
void lentelesSpausdinimas(const std::list<Student>&    s, Mode m);

void grupesIrasymas(const std::string& path, const std::vector<Student>& s, Mode m);
void grupesIrasymas(const std::string& path, const std::list<Student>& s, Mode m);

void padalinimasStrategija1(const std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet);
void padalinimasStrategija1(const std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet);

void padalinimasStrategija2(const std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet);
void padalinimasStrategija2(std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet);

void padalinimasStrategija3(const std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet);
void padalinimasStrategija3(std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet);




