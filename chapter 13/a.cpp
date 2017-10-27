#include "a1.h"
using namespace std;

int main()
{
	vector<Student_info> students;
	Student_info record;
	char ch;
	size_t maxlen = 0;

	while(record.read(cin))
	{
		maxlen = max(maxlen, record.name().size());
		students.push_back(record);
	}

	sort(students.begin(), students.end(), Student_info::compare);

	for(auto it = students.begin(); it != students.end(); it++)
	{
		cout << it->name() << " ";

		try
		{
			double final_grade = it->grade();
			cout << final_grade << endl;
		}
		catch(domain_error e)
		{
		    cout << e.what() << endl;
		}
	}

    return 0;
}