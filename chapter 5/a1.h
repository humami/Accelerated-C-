#ifndef STU_INFO
#define STU_INFO
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Student_Info
{
    string name;
    double midterm, final;
    vector<double> homework;
};

bool compare(const Student_Info &, const Student_Info &);
istream& read(istream &, Student_Info &);
istream& read_hw(istream &, vector<double> &);

#endif