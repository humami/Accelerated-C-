#ifndef GRADE
#define GRADE
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "a1.h"

double median(vector<double>);
double grade(double, double, double);
double grade(double, double, const vector<double> &);
double grade(const Student_Info &);

#endif