#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

size_t width(const vector<string> &v)
{   
    size_t max_width = 0;

    for(auto vit = v.begin(); vit != v.end(); vit++)
        max_width = max(max_width, vit->size());

    return max_width;
}

vector<string> split(const string &s)
{
    vector<string> ret;
    size_t i = 0;

    while(i != s.size())
    {
        while(i != s.size() && isspace(s[i]))
            ++i;

        size_t j = i+1;
        while(j != s.size() && !isspace(s[j]))
            ++j;

        ret.push_back(s.substr(i, j-i));
        i = j;
    }

    return ret;
}

vector<string> frame(const vector<string> &v)
{
    vector<string> ret;
    size_t w = width(v);
    string border(w + 4, '*');

    ret.push_back(border);
    for(auto vit = v.begin(); vit != v.end(); vit++)
        ret.push_back("* "+ *vit + string(w-vit->size(), ' ') + " *");
    ret.push_back(border);

    return ret;
}

vector<string> vcat(const vector<string> &top, const vector<string> &bottom)
{
    vector<string> ret = top;

    for(auto it = bottom.begin(); it != bottom.end(); it++)
        ret.push_back(*it);

    return ret;
}

vector<string> hcat(const vector<string> &left, const vector<string> &right)
{
    vector<string> ret;

    size_t w1 = width(left)+1;

    auto l = left.begin();
    auto r = right.begin();

    while(l != left.end() || r != right.end())
    {
        string s;

        if(l != left.end())
        {
            s = *l;
            l++;
        }

        s += string(w1 - s.size(), ' ');

        if(r != right.end())
        {
            s += *r;
            r++;
        }

        ret.push_back(s);
    }

    return ret;
}


int main()
{
    vector<string> v1;
    vector<string> v2;
    vector<string> v;
    string ss;

    while(getline(cin, ss))
        v1.push_back(ss);

    v1 = frame(v1);
    v2 = v1;

    v = hcat(v1, v2);

    cout << endl;
    for(auto vit = v.begin(); vit != v.end(); vit++)
        cout << *vit << endl;

    return 0;
}