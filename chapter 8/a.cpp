#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

bool space(char c)
{
    return isspace(c);
}

bool not_space(char c)
{
    return !isspace(c);
}

template<typename Out>
void split(const string &s, Out os)
{
    auto sit = s.begin();

    while(sit != s.end())
    {
        sit = find_if(sit, s.end(), not_space);

        auto j = find_if(sit, s.end(), space);

        if(sit != s.end())
            *os++ = string(sit, j);

        sit = j;
    }
}

template<typename Ran, typename X>
bool binary_search(Ran begin, Ran end, const X &x)
{
    while(begin < end)
    {
        Ran mid = begin + (end - begin) / 2;

        if(x < *mid)
            end = mid;
        else if(x > *mid)
            begin = mid + 1;
        else
            return true;
    }
}

template<typename Bi>
void reserve(Bi begin, Bi end)
{
    while(begin != end)
    {
        --end;
        if(begin != end)
            swap(*begin++, end);
    }
}

template<typename For, typename X>
void replace(For beg, For end, const X &x, const X &y)
{
    while(beg != end)
    {
        if(*beg == x)
            *beg = y;
        ++beg;
    }
}

template<typename In, typename Out>
Out copy(In begin, In end, Out dest)
{
    while(begin != end)
        *dest++ = *begin++;

    return dest;
}

template <typename In, typename X>
In find(In begin, In end, const X &x)
{
    while(begin != end && *begin != x)
        ++begin;

    return begin;
}

template <typename T>
T median(vector<T> v)
{
    T ret;

    auto v_size = v.size();

    if(v_size == 0)
        throw domain_error("median of an empty vector");

    sort(v.begin(), v.end());

    auto mid = v_size / 2;

    if(v_size % 2 == 0)
        return (v[mid] + v[mid-1]) / 2;
    else
        return v[mid];
}

int main()
{
    string ss;

    while(getline(cin, ss))
        split(ss, ostream_iterator<string>(cout, "\n"));

    return 0;
}
