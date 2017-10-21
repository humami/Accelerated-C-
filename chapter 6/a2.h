#ifndef GRADE
#define GRADE
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <list>
#include <cctype>
#include <numeric>
#include "a1.h"

double median(vector<double>);
bool fgrade(const Student_Info&);
double grade(double, double, double);
double grade(double, double, const vector<double> &);
double grade(const Student_Info &);

list<Student_Info> extract_fails(list<Student_Info> &);
double median_analysis(const vector<Student_Info> &);
double average_analysis(const vector<Student_Info> &);
double optimistic_median_analysis(const vector<Student_Info> &);
void write_analysis(ostream &out, const string &name, double (*analysis)(const vector<Student_Info> &),
	const vector<Student_Info> did, const vector<Student_Info> didnt);

#endif