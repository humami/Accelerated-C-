#include "a1.h"

bool did_all_hw(const Student_Info &s)
{
    return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end());
}

istream& read(istream &in, Student_Info &s)
{
    in >> s.name >> s.midterm >> s.final;

    read_hw(in, s.homework);

    return in;
}

istream& read_hw(istream &in, vector<double> &hw)
{
    if(in)
    {
        hw.clear();

        double x;

        while(in >> x)
            hw.push_back(x);

        in.clear();
    }

    return in;
}

bool compare(const Student_Info &s1, const Student_Info &s2)
{
    return s1.name < s2.name;
}