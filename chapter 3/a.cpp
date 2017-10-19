#include <iostream>
#include <string>
#include <ios>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    cout << "please enter your first name: ";
    
    string name;
    cin >> name;

    cout << "Hello, " << name << "!" << endl;

    cout << "please enter your midterm and final exam grades: ";
    double midterm, final;
    cin >> midterm >> final;

    cout << "Enter your all homework grads, follow by end-of-file: ";

    vector<double> homework;
    double x;

    while(cin >> x)
        homework.push_back(x);

    auto vec_sz = homework.size();

    if(vec_sz == 0)
        cout << "You must enter your grades, please try it again!" << endl;

    sort(homework.begin(), homework.end());

    auto mid = vec_sz / 2;
    double median;
    if(vec_sz % 2 != 0)
        median = homework[mid];
    else
        median = (homework[mid] + homework[mid-1]) / 2;

    streamsize prec = cout.precision();
    cout << "Your final grade is " << setprecision(3) 
         << 0.2 * midterm + 0.4 * final + 0.4 * median
         << setprecision(prec) << endl;

    return 0;
}