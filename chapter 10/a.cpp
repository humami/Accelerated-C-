#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
using namespace std;

char *duplicate_chars(const char *p)
{
	size_t length = strlen(p) + 1;
	char *result = new char[length];

	copy(p, p+length, result);

	return result;
} 

string letter_grade(double grade)
{
	static const double numbers[] = {
		97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
	};

	static const char* const letter[] = {
		"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
	};

	static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

	for(size_t i = 0; i < ngrades; i++)
	{
		if(grade >= numbers[i])
			return letter[i];
	}

	return "?\?\?";
}

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		int fail_count;
		int i;

		for(i = 1; i < argc; i++)
		{
			ifstream fin(argv[i]);

			if(fin)
			{
				string s;

				while(getline(fin, s))
					cout << s << endl;
			}
			else
			{
				cerr << "cannot open the file" << argv[i] << endl;
				++fail_count;
			}
		}

		return fail_count;
	}

	return 0;
}
