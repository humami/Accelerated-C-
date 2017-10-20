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

    while(read(cin, record))
    {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    students.sort(compare);

    for(auto it=students.begin(); it != students.end(); it++)
    {
        cout << it->name << " ";
        
        try
        {
            double final_grade = grade(*it);
            
            streamsize prec = cout.precision();
            cout << "Your final grade is " << setprecision(3) 
                 << final_grade << setprecision(prec) << endl;
        }
        catch(domain_error e)
        {
            cout << e.what();
        }

        cout << endl;
    }

    return 0;
}