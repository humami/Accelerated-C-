#include "a2.h"

double median(vector<double> vec)
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

bool fgrade(const Student_Info &s)
{
    return grade(s) < 60;
}

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}


double grade(double midterm, double final, const vector<double> &hw)
{
    if(hw.size() == 0)
        throw domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}

double grade(const Student_Info &s)
{
    return grade(s.midterm, s.final, s.homework);
}


list<Student_Info> extract_fails(list<Student_Info> &students) 
{
    list<Student_Info> fail;
    auto it = students.begin();

    while(it != students.end())
    {
        if(fgrade(*it))
        {
            fail.push_back(*it);
            it = students.erase(it);
        }
        else
            it++;
    }

    return fail;
}
