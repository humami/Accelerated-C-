#include <iostream>
#include "a1.h"
using namespace std;

int main()
{
	vector<Handle<Core>> students;
	Handle<Core> record;
	char ch;
	size_t maxlen = 0;

	while(cin >> ch)
	{
		if(ch == 'U')
			record = new Core();
		else
			record = new Grad();

		record->read(cin);
		maxlen = max(maxlen, record->name().size());
		students.push_back(record);
	}

	sort(students.begin(), students.end(), compare_Core_handles);

	for(auto it = students.begin(); it != students.end(); it++)
	{
		cout << (*it)->name() << " ";

		try
		{
			double grade = (*it)->grade();
			cout << grade << endl;
		}
		catch(domain_error e)
		{
			cout << e.what() << endl;
		}
	}

	return 0;
}