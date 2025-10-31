#pragma once
#include <vector>
#include <list>
#include <string>
#include "student1.h"

std::vector<Student> studentuGeneravimas(int m);

void grupesIrasymas(const std::string& path, const std::vector<Student>& s, Mode m);
void grupesIrasymas(const std::string& path, const std::list<Student>&    s, Mode m);
