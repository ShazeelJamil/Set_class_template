#include"Set.h"
int main()
{
	Set<int> s(2),s1;
	s.insert(20);
	s.insert(21);
	//for (int i = 0; i < s.getCapacity(); i++)
		//s.insert(i);
	s.print();
	s1.insert(20);
	s1.insert(21);
	s1.insert(22);
	s1.insert(23);
	//s1.remove(23);
	s1.print();
	s.calcUnion(s1).print();
	//s.calcIntersection(s1).print();
	//s.calcDifference(s1).print();
	//s.calcSymmetricDifference(s1).print();
	//cout << "here";
	
	return 0;
}