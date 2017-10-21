#ifndef STU_INFO
#define STU_INFO
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct Student_Info
{
    string name;
    double midterm, final;
    vector<double> homework;
};

bool did_all_hw(const Student_Info &);
bool compare(const Student_Info &, const Student_Info &);
istream& read(istream &, Student_Info &);
istream& read_hw(istream &, vector<double> &);

#endif