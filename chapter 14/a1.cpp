#include "a1.h"

bool compare_Core_handles(const Handle<Core> &h1, const Handle<Core> &h2)
{
    return  h1->name() < h2->name();
}

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

template<typename T>
Ref_handle<T>& Ref_handle<T>::operator=(const Ref_handle &rhs)
{
	(*rhs.refptr)++;

	if((--*refptr) == 0)
	{
		delete refptr;
		delete p;
	}

	refptr = rhs.refptr;
	p = rhs.p;
	return *this;
}

template<typename T>
Ref_handle<T>::~Ref_handle()
{
	if((--*refptr) == 0)
	{
		delete refptr;
		delete p;
	}
}
