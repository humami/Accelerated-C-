#include "a1.h"

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

Pic_base::wd_sz String_Pic::width() const
{
    Pic_base::wd_sz n = 0;

    for(Pic_base::ht_sz i=0; i < data.size(); i++)
        n = max(n, data[i].size());
    
    return n;
}

void String_Pic::display(ostream &os, ht_sz row, bool do_pat) const
{
    cout << endl;
}

void Frame_Pic::display(ostream &os, ht_sz row, bool do_pat) const
{
    cout << endl;
}

void Vcat_Pic::display(ostream &os, ht_sz row, bool do_pat) const
{
    wd_sz w = 0;

    if(row < top->height())
    {
        top->display(os, row, do_pat);
        w = bottom->width();
    }
    else if(row < height())
    {
        bottom->display(os, row, do_pat);
        w = bottom->width();
    }
}

void Hcat_Pic::display(ostream &os, ht_sz row, bool do_pat) const
{
    left->display(os, row, do_pat);
    right->display(os, row, do_pat);
}

Picture::Picture(const vector<string> &v):p(new String_Pic(v))
{
}

Picture frame(const Picture &pic)
{
    return new Frame_Pic(pic.p);
}

Picture hcat(const Picture &l, const Picture &r)
{
    return new Hcat_Pic(l.p, r.p);
}

Picture vcat(const Picture &t, const Picture &b)
{
    return new Vcat_Pic(t.p, b.p);
}

ostream& operator<< (ostream &os, const Picture &picture)
{
    const Pic_base::ht_sz ht = picture.p->height();

    for(Pic_base::ht_sz i=0; i < ht; i++)
    {
        picture.p->display(os, i, false);
        os << endl;
    }

    return os;
}