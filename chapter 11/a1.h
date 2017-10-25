#ifndef VEC
#define VEC
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

template<typename T>
class Vec
{
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef size_t size_type;
        typedef T value_type;

        Vec() { create(); }
        ~Vec() { uncreate(); }
        Vec(const Vec &v) { create(v.begin(), v.end()); };
        explicit Vec(size_t n, const T &val=T()) { create(n, val); }
        
        size_type size() const { return limit - data; }
        T& operator [](size_type i) { return data[i]; }
        const  T& operator [](size_type i) const { return data[i]; }
        Vec& operator =(const Vec &);

        void push_back(const T &v)
        {
            if(avail == limit)
                grow();

            unchecked_append(v);
        }

        iterator begin() { return data; }
        const_iterator begin() const { return data; }
        iterator end() { return avail; }
        const_iterator end() const { return avail; }
 
    private:
        iterator data;      //vec begin
        iterator avail;     //vec avail
        iterator limit;     //vec end

        allocator<T> alloc;

        void create();
        void create(size_type, const T&);
        void create(const_iterator, const_iterator);

        void uncreate();
        
        void grow();
        void unchecked_append(const T &val);
};

template<typename T>
void Vec<T>::create()
{
    data = avail = limit = nullptr;
}

template<typename T>
void Vec<T>::create(size_type n, const T& v)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, v);
}

template<typename T>
void Vec<T>::create(const_iterator b, const_iterator e)
{
    data = alloc.allocate(e-b);
    limit = avail = uninitialized_copy(b, e, data);
}

template<typename T>
void Vec<T>::uncreate()
{
    if(data)
    {
        iterator it = avail;

        while(it != data)
        {
            alloc.destroy(--it);
        }

        alloc.deallocate(data, limit-data);
    }

    data = limit = avail = nullptr;
}

template<typename T>
void Vec<T>::grow()
{
    size_type new_size = max(2*(limit-data), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);

    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template<typename T>
void Vec<T>::unchecked_append(const T &val)
{
    alloc.construct(avail++, val);
}

template<typename T>
Vec<T>& Vec<T>::operator =(const Vec &rhs)
{
    if(*this != rhs)
    {
        uncreate();

        create(rhs.begin(), rhs.end());
    }

    return *this;
}


#endif