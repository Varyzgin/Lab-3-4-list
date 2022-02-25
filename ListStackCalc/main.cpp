#include <iostream>
#include <string>
#include "TNodeStackAndList.h"


using namespace std;

int main()
{
	T_stack_list<int> s;

	cout << "Push check:\n" << s << endl;
	s.push(5);
	cout << s << endl;
	s.push(3);
	cout << s << endl;
	s.push(1);
	cout << s << endl;

	cout << "Assign check" << endl;
	T_stack_list<int> c = s;
	s.clear();
	cout << "s: " << s << endl;
	cout << "c: " << c << endl;

	cout << "Pop s?" << endl;
	//s.pop();
	cout << "Top s?" << endl;
	//s.top();

	while (c.is_not_empty()) {
		cout << "Pop:" << c.pop() << endl;
		cout << c << endl;
	}

	cout << "EQ check" << endl;
	s.push(5);
	cout << s << endl;
	s.push(3);
	cout << s << endl;
	s.push(1);
	cout << s << endl;
	cout << "s:\n" << s << endl;
	T_stack_list<int> c1(s);
	cout << "c1(s):\n" << c1 << endl;
	cout << "Before pop: (s == c1) = " << (s == c1) << endl;
	s.pop();
	cout << "After pop: (s == c1) = " << (s == c1) << endl;
}