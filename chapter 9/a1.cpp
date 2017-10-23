#include "a1.h"

istream& Student_Info::read_hw(istream &in, vector<double> &hw)
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

istream& Student_Info::read(istream &in)
{
    in >> name >> midterm >> final;

    read_hw(in, homework);

    return in;
}

bool compare(const Student_Info &x, const Student_Info &y)
{
    return x.get_name() < y.get_name();
}

double Student_Info::Student_Info::grade()
{
    return grade(midterm, final, homework);
}

double Student_Info::median(vector<double> vec)
{
    auto vec_sz = vec.size();

    sort(vec.begin(), vec.end());

    auto mid = vec_sz / 2;
    
    double median;

    if(vec_sz % 2 != 0)
        median = vec[mid];
    else
        median = (vec[mid] + vec[mid-1]) / 2;

    return median;
}

double Student_Info::grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}


double Student_Info::grade(double midterm, double final, const vector<double> &hw)
{
    if(hw.size() == 0)
        throw domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}
