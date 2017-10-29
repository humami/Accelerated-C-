#ifndef HANDLE
#define HANDLE
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class Picture;

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

        T* operator->() const
        {
            if(p)
                return p;
            throw runtime_error("unbound Ref_Handle");
        }

    private:
        T *p;
        size_t *refptr;
};

class Pic_base
{
    friend ostream& operator<< (ostream&, const Picture&);
    friend class String_Pic;
    friend class Frame_Pic;
    friend class Hcat_Pic;
    friend class Vcat_Pic;

    typedef vector<string>::size_type ht_sz;
    typedef string::size_type wd_sz;

    public:
        virtual wd_sz width() const = 0;
        virtual ht_sz height() const = 0;
        virtual void display(ostream&, ht_sz, bool) const = 0;
};

class String_Pic: public Pic_base
{
    friend Picture;

    vector<string> data;
    String_Pic(const vector<string> &v):data(v) {}
    wd_sz width() const;
    ht_sz height() const { return data.size(); }
    void display(ostream&, ht_sz, bool) const;
};

class Frame_Pic: public Pic_base
{
    friend Picture frame(const Picture&);

    Ref_handle<Pic_base> p;
    Frame_Pic(const Ref_handle<Pic_base> &pic):p(pic){};
    wd_sz width() const { return p->width()+4; }
    ht_sz height() const { return p->height()+4; }
    void display(ostream &, ht_sz, bool) const;
};

class Vcat_Pic: public Pic_base
{
    friend Picture vcat(const Picture&, const Picture&);

    Ref_handle<Pic_base> top, bottom;
    Vcat_Pic(const Ref_handle<Pic_base> &t, const Ref_handle<Pic_base> &b):
        top(t), bottom(b) {}
    wd_sz width() const { return max(top->width(), bottom->width()); }
    ht_sz height() const { return top->height() + bottom->height(); }
    void display(ostream&, ht_sz, bool) const;
};

class Hcat_Pic: public Pic_base
{
    friend Picture hcat(const Picture&, const Picture&);
    Ref_handle<Pic_base> left, right;
    Hcat_Pic(const Ref_handle<Pic_base> &l, const Ref_handle<Pic_base> &r):
        left(l), right(r) {}
    wd_sz width() const { return left->width() + right->width(); }
    ht_sz height() const { return max(left->height(), right->height()); }
    void display(ostream &, ht_sz, bool) const;
};

class Picture
{
    public:
        friend Picture frame(const Picture&);
        friend Picture hcat(const Picture&, const Picture&);
        friend Picture vcat(const Picture&, const Picture&);
        friend ostream& operator<< (ostream&, const Picture&); 
        
        Picture(const vector<string>& = vector<string>());

    private:
        Picture(Pic_base *ptr):p(ptr) {}
        Ref_handle<Pic_base> p;
};

Picture frame(const Picture&);
Picture hcat(const Picture&, const Picture&);
Picture vcat(const Picture&, const Picture&);
ostream& operator<< (ostream&, const Picture&); 

#endif