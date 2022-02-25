#include"TNodeListOnQueue.h"
int main()
{
	T_queue_list<int> q;

	cout << "Push check:\n" << q << endl;
	q.push(5);
	cout << q << endl;
	q.push(3);
	cout << q << endl;
	q.push(1);
	cout << q << endl;

	cout << "Assign check" << endl;
	T_queue_list<int> c = q;
	q.clear();
	cout << "q: " << q << endl;
	cout << "c: " << c << endl;

	cout << "Pop q?" << endl;
	//q.pop();
	cout << "Top q?" << endl;
	//q.top();

	while (c.is_not_empty()) {
		cout << "Pop:" << c.pop() << endl;
		cout << c << endl;
	}

	cout << "EQ check" << endl;
	q.push(5);
	cout << q << endl;
	q.push(3);
	cout << q << endl;
	q.push(1);
	cout << q << endl;
	cout << "q:\n" << q << endl;
	T_queue_list<int> c1(q);
	cout << "c1(q):\n" << c1 << endl;
	cout << "Before pop: (q == c1) = " << (q == c1) << endl;
	q.pop();
	cout << "After pop: (q == c1) = " << (q == c1) << endl;

}