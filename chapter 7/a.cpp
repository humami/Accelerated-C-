#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
using namespace std;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

bool is_space(char c)
{
    return isspace(c);
}

bool not_space(char c)
{
    return !isspace(c);
}

vector<string> split(const string &ss)
{
    vector<string> ret;
    auto sit = ss.begin();

    while(sit != ss.end())
    {
        auto i = find_if(sit, ss.end(), not_space);
        auto j = find_if(i, ss.end(), is_space);

        if(i != j)
            ret.push_back(string(i, j));

        sit = j;
    }

    return ret;
}

map<string, vector<int> > xref(istream &in, 
    vector<string> (*find_words)(const string&) = split)
{
    map<string, vector<int> > ret;
    string ss;
    int line_num = 0;

    while(getline(in, ss))
    {
        line_num++;

        vector<string> words = find_words(ss);
        vector<int> v;

        for(auto wit = words.begin(); wit != words.end(); wit++)
            ret[*wit].push_back(line_num);
    }

    return ret;
}

int nrand(int n)
{
    if(n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");

    const int bucket_size = RAND_MAX / n;
    int r;

    do
    {
        r = rand() / bucket_size;
    }while(r >= n);

    return r;
}

Grammar read_grammer(istream &in)
{
    Grammar ret;
    string ss;

    while(getline(in, ss))
    {
        vector<string> entry = split(ss);

        if(!entry.empty())
        {
            ret[entry[0]].push_back(Rule(entry.begin()+1, entry.end()));
        }
    }

    return ret;
}

bool bracketed(const string &s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size()-1] == '>';
}

void gen_aux(const Grammar&g, const string word, vector<string> &ret)
{
    if(!bracketed(word))
        ret.push_back(word);
    else
    {
        auto it = g.find(word);
        
        if(it == g.end())
            throw logic_error("empty rule");

        const Rule_collection &rc = it->second;

        const Rule r = rc[nrand(rc.size())];

        for(auto rit = r.begin(); rit != r.end(); rit++)
            gen_aux(g, *rit, ret);        
    }
}

vector<string> gen_sentence(const Grammar &g)
{
    vector<string> ret;

    gen_aux(g, "<sentence>", ret);

    return ret;
}

int main()
{
    Grammar g;
    vector<string> sentence;

    g = read_grammer(cin);
    sentence = gen_sentence(g);

    for(auto it = sentence.begin(); it != sentence.end(); it++)
        cout << *it << " ";
    cout << endl;

    /*
    for(auto it = m.begin(); it != m.end(); it++)
    {
        cout << it->first << " occurs on line(s): ";
        
        auto line_it = it->second.begin();
        cout << *line_it;

        line_it++;
        while(line_it != it->second.end())
        {    
            cout <<  ", " << *line_it;
            ++line_it;
        }

        cout << endl;
    }
    */

    return 0;
}