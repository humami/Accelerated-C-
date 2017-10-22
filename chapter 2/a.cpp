#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "please enter your first name: ";

    string name;
    cin >> name;

    string greeting = "Hello, " + name + "!";

    const int pad = 2;
    const int rows = pad * 2 + 3;

    const size_t cols = greeting.size() + pad * 2 + 2;

    int r = 0;
    while(r != rows)
    {
        size_t c=0;

        while(c != cols)
        {
            if(r == pad+1 && c == pad+1)
            {
                cout << greeting;
                c+=greeting.size();
            }
            else
            {
                if(r==0 || r==rows-1 || c==0 || c==cols-1)
                    cout << "*";
                else
                    cout << " ";

                ++c;
            }
        }
        cout << endl;

        r++;
    }

    return 0;
}
