#include <iostream>
#include <string>
#include <ios>
#include <iomanip>
#include <list>
#include <algorithm>
#include "a1.h"
#include "a2.h"
using namespace std; 

int main()
{
    list<Student_Info> students;
    Student_Info record;
    size_t maxlen = 0;

    vector<Student_Info> did, didnt;

    while(read(cin, record))
    {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    for(auto it = students.begin(); it != students.end(); it++)
    {
        if(did_all_hw(*it))
            did.push_back(*it);
        else
            didnt.push_back(*it);
    }

    if(did.empty())
    {
        cout << "No student did all the homework!" << endl;
        return 1;
    }
    if(didnt.empty())
    {
        cout << "Every student did all the homework" << endl;
        return 1;
    }

    write_analysis(cout, "median", median_analysis, did, didnt);
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "median of homework turned in", optimistic_median_analysis, did, didnt);

    return 0;
}