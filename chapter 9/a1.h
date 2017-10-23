#ifndef STU_INFO
#define STU_INFO
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Student_Info
{
    string name;
    double midterm, final;
    vector<double> homework;

    istream& read_hw(istream &, vector<double> &);
    double median(vector<double> vec);
    double grade(double midterm, double final, double homework);
    double grade(double midterm, double final, const vector<double> &);

    public:
    	Student_Info(): midterm(0), final(0) {}
    	Student_Info(istream &in) { read(in); }
        istream& read(istream &);
        double grade();
        string get_name() const { return name; }
        bool valid() const { return !homework.empty(); }
};

bool compare(const Student_Info &, const Student_Info &);

#endif