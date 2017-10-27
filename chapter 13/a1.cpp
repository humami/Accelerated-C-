#include "a1.h"

istream& Core::read_hw(istream &in, vector<double> &hw)
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

double Core::median(vector<double> vec)
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

double Core::grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}


double Core::grade(double midterm, double final, const vector<double> &hw)
{
    if(hw.size() == 0)
        throw domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}

string Core::name() const
{
    return n;
}
        
double Core::grade()
{
    return grade(midterm, final, homework);
}

istream& Core::read_common(istream &is)
{
    is >> midterm >> final;

    return is;
}

istream& Core::read(istream &is)
{
    read_common(is);
    read_hw(is, homework);

    return is;
}

istream& Grad::read(istream &is)
{
    read_common(is);
    is >> thesis;
    read_hw(is, homework);

    return is;
}

double Grad::grade()
{
    return min(Core::grade(), thesis);
}

bool compare_core_ptrs(const Core *x, const Core *y)
{
    return compare(*x, *y);
}

bool compare(const Core &x, const Core &y)
{ 
    return x.name() < y.name();
}

istream& Student_info::read(istream &is)
{
    delete cp;

    char ch;
    is >> ch;

    if(ch == 'U')
        cp = new Core(is);
    else
        cp = new Grad(is);

    return is;
}

Student_info::Student_info(const Student_info &s)
{
    cp = nullptr;

    if(s.cp)
    {
        cp = s.cp->clone();
    }
}

Student_info& Student_info::operator=(const Student_info &s)
{
    if(&s != this)
    {
        delete cp;

        if(s.cp)
            cp = s.cp->clone();
        else
            cp = nullptr;
    }

    return *this;
}
