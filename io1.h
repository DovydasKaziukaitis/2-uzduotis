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



