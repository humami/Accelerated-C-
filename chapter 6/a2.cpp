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

static bool pgrade(const Student_Info &s)
{
    return grade(s) >= 60;
}

static vector<Student_Info> extract_fails(vector<Student_Info> &students)
{
    vector<Student_Info> fail;
    auto iter = stable_partition(students.begin(), students.end(), pgrade);
    vector<Student_Info> fail(iter, students.end());
    students.erase(iter, students.end());

    return fail;
}

static double grade_aux(const Student_Info &s)
{
    try
    {
        return grade(s);
    }
    catch(domain_error)
    {
        return grade(s.midterm, s.final, 0);
    }
}

double median_analysis(const vector<Student_Info> &students)
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), grade_aux);

    return median(grades);
}

void write_analysis(ostream &out, const string &name, double (*analysis)(const vector<Student_Info> &),
    const vector<Student_Info> did, const vector<Student_Info> didnt)
    {
        cout << name << ": median(did) = " << analysis(did)
             << ", median(didnt) = " << analysis(didnt) << endl;
    }

static double average(const vector<double> &v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

static double average_grade(const Student_Info &s)
{
    return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<Student_Info> &students)
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), average_grade);

    return median(grades);
}

static double optimistic_median(const Student_Info &s)
{
    vector<double> nonzero;
    remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);

    if(nonzero.empty())
        return grade(s.midterm, s.final, 0);
    else
        return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis(const vector<Student_Info> &students)
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), optimistic_median);

    return median(grades);
}

