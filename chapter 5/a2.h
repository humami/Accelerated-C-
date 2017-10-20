#ifndef GRADE
#define GRADE
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <list>
#include "a1.h"

double median(vector<double>);
bool fgrade(const Student_Info&);
double grade(double, double, double);
double grade(double, double, const vector<double> &);
double grade(const Student_Info &);

list<Student_Info> extract_fails(list<Student_Info> &);

#endif