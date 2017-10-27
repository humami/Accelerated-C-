#ifndef CORE
#define CORE
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Core
{
    public:
        friend class Student_info;

        Core(): midterm(0), final(0) {}
        Core(istream &is) { read(is); }
        virtual ~Core() {};
        string name() const;
        virtual istream& read(istream &);
        virtual double grade();

    protected:
        istream& read_common(istream &);
        double midterm, final;
        vector<double> homework;

        istream& read_hw(istream &, vector<double> &);
        double median(vector<double>);
        double grade(double, double, double);
        double grade(double, double, const vector<double> &);

        virtual Core* clone() const { return new Core(*this); }

    private:
        string n;
};

class Grad: public Core
{
    public:
        Grad(): thesis(0) {}
        Grad(istream &is) { read(is); }
        istream& read(istream &); 
        double grade() override;
    protected:
        Grad* clone() const { return new Grad(*this); }

    private:
        double thesis;
};

class Student_info
{
    public:
        Student_info(): cp(nullptr) {}
        Student_info(istream &is): cp(nullptr) { read(is); }
        Student_info(const Student_info&);
        Student_info& operator=(const Student_info&);
        ~Student_info() { delete cp; }

        istream& read(istream&);

        string name() const
        {
            if(cp)
                return cp->name();
            else
                throw runtime_error("uninitialized Student");
        }

        double grade()
        {
            if(cp)
                return cp->grade();
            else
                throw runtime_error("uninitialized Student");
        }

        static bool compare(const Student_info &s1, const Student_info &s2)
        {
            return s1.name() < s2.name();
        }

    private:
        Core *cp;
};

bool compare_core_ptrs(const Core*, const Core*);
bool compare(const Core&, const Core&);

#endif