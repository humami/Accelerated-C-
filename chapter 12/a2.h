#ifndef STR
#define STR
#include "a1.h"
#include <string.h>
using namespace std;

class Str
{
    public:
    	friend istream& operator >> (istream&, Str&);
        typedef Vec<char>::size_type size_type;

        Str(){}
        Str(size_type n, char c):data(n, c){}
        Str(const char *cp)
        {
        	copy(cp, cp+strlen(cp), back_inserter(data));
        }
        
        template<typename In>
        Str(In b, In e)
        {
        	copy(b, e, back_inserter(data));
        }

        char& operator [](size_type i) { return data[i]; }
        const char& operator [](size_type i) const { return data[i]; }
        Str& operator +=(const Str&s)
        {
        	copy(s.data.begin(), s.data.end(), back_inserter(data));

        	return *this;
        }

        size_type size() const { return data.size(); }

    private:
    	Vec<char> data;
};

ostream& operator << (ostream&, const Str&);
Str operator +(const Str&, const Str&);

#endif