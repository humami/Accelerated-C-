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

bool space(char c)
{
    return isspace(c);
}

bool not_space(char c)
{
    return !isspace(c);
}

vector<string> split(const string &s)
{
    vector<string> ret;
    auto sit = s.begin();

    while(sit != s.end())
    {
        sit = find_if(sit, s.end(), not_space);

        auto j = find_if(sit, s.end(), space);

        if(sit != s.end())
            ret.push_back(string(sit, j));

        sit = j;
    }

    return ret;
}

bool is_palindrome(const string &s)
{
    return equal(s.begin(), s.end(), s.rbegin());
}

bool not_url_char(char c)
{
    static const string url_ch = "~;/?:@=&$-_.+!*'(),'";

    return !(isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e)
{
    static const string sep = "://";

    auto i = b;

    while((i = search(i, e, sep.begin(), sep.end())) != e)
    {
        if(i != b && i + sep.size() != e)
        {
            auto beg = i;
            while(beg != b && isalpha(beg[-1]))
                beg--;

            if(beg != i && i + sep.size() != e && !not_url_char(i[sep.size()]))
                return beg;
        }

        if(i != e)
            i += sep.size();
    }

    return e;
}

vector<string> find_urls(const string &s)
{
    vector<string> ret;
    auto b = s.begin();
    auto e = s.end();

    while(b != e)
    {
        b = url_beg(b, e);

        if(b != e)
        {
            auto after = url_end(b, e);

            ret.push_back(string(b, after));

            b = after;
        }
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
    vector<string> v;
    string ss;

    getline(cin, ss);

    v = find_urls(ss);

    for(auto it = v.begin(); it != v.end(); it++)
        cout << *it << endl;

    return 0;
}