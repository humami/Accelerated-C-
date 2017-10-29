#ifndef HANDLE
#define HANDLE
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

template<typename T>
class Handle
{
    public:
        Handle(): p(nullptr) {}
        Handle(const Handle &s): p(nullptr) { if(s.p)p=s.p->clone(); } 
        Handle& operator=(const Handle&);
        ~Handle() { delete p; }
        Handle(T *t): p(t) {}
        operator bool() const { return p; }
        T& operator*() const;
        T* operator->() const;

    private: 
        T *p;
};

template<typename T>
Handle<T>& Handle<T>::operator=(const Handle&rhs)
{
    if(this != &rhs)
    {
        delete p;

        if(rhs.p)
            p = rhs.p->clone();
        else
            p = nullptr;
    }

    return *this;
}

template<typename T>
T& Handle<T>::operator*() const
{
    if(p)
        return *p;
    throw runtime_error("unbound Handle");
}

template<typename T>
T* Handle<T>::operator->() const
{
    if(p)
        return p;
    throw runtime_error("unbound Handle");
}

class Core
{
    public:
        Core(): midterm(0), final(0) {}
        Core(istream &is) { read(is); }
        virtual ~Core() {};
        string name() const;
        virtual istream& read(istream &);
        virtual double grade();
        virtual Core* clone() const { return new Core(*this); }

    protected:
        istream& read_common(istream &);
        double midterm, final;
        vector<double> homework;

        istream& read_hw(istream &, vector<double> &);
        double median(vector<double>);
        double grade(double, double, double);
        double grade(double, double, const vector<double> &);

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
        Grad* clone() const { return new Grad(*this); }

    private:
        double thesis;
};

bool compare_Core_handles(const Handle<Core> &, const Handle<Core> &);

template<typename T>
class Ref_handle
{
    public:
        void make_unique()
        {
            if(*refptr != 1)
            {
                --*refptr;
                refptr = new size_t(1);

                if(p)
                    p = p->clone();
                else
                    p = nullptr;
            }
        }

        Ref_handle():p(nullptr), refptr(nullptr){}
        Ref_handle(T *t):p(t), refptr(new size_t(1)){}
        Ref_handle(const Ref_handle &h):p(h.p), refptr(h.refptr)
        {
            (*refptr)++;
        }

        Ref_handle& operator=(const Ref_handle &);
        ~Ref_handle();

        operator bool() const { return p; }

        T& operator*() const
        {
            if(p)
                return *p;
            throw runtime_error("unbound Ref_Handle");
        }

        T& operator->() const
        {
            if(p)
                return p;
            throw runtime_error("unbound Ref_Handle");
        }

    private:
        T *p;
        size_t *refptr;
};

#endif