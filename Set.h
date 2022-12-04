#ifndef SET_H
#define SET_H
#include<iostream>
using namespace std;
template<typename T>
class Set
{
	T* data;
	int capacity;
	int noOfElements; 
	bool isFull()const;
	bool isEmpty()const;
	int searchElementPosition(int element)const;
public:
	Set(int cap = 0);
	~Set();
	Set(const Set<T>&);
	/*
	Set(Set<T>&&);
	Set<T>& operator = (const Set<T>&);
	Set<T>& operator = (Set<T>&);
	*/
	void insert(T element);
	void remove(T element);
	void print()const;
	int getCardinality() const;
	int getCapacity() const;
	int isMember(T val) const;
	int isSubset(const Set<T>& s2)const;
	void reSize(int newCap);
	Set<T> calcUnion(const Set<T>& s2) const;
	Set<T> calcIntersection(const Set<T>& s2) const;
	Set<T> calcDifference(const Set<T>& s2) const;
	Set<T> calcSymmetricDifference(const Set<T>& s2) const;
};

template<typename T>
bool Set<T>::isFull()const
{
	return (getCardinality() == getCapacity());
}
template<typename T>
bool Set<T>::isEmpty()const
{
	return (noOfElements == 0);
}
template<typename T>
int Set<T>::searchElementPosition(int element)const
{
	int index = 0;
	while (index < noOfElements)
	{
		if (element == data[index])
			return index;
		index++;
	}
	index = -1;
	return index;
}
template<typename T>
Set<T>::Set(int cap) :capacity(cap), noOfElements(0)
{
	data = new T[capacity];
}
template<typename T>
Set<T>::~Set()
{
	delete[] data;
	capacity = 0;
	noOfElements = 0;
}
template<typename T>
Set<T>::Set(const Set<T>& ref)
{
	this->~Set();
	if (!ref.data)
		return;
	capacity = ref.capacity;
	data = ref.data;
	for (int i = 0; i < ref.capacity; i++)
	{
		data[i] = ref.data[i];
	}
	noOfElements = ref.noOfElements;
}
/*
template<typename T>
Set<T>::Set(Set<T>&& ref)
{ }
template<typename T>
Set<T>& Set<T>::operator = (const Set<T>& ref)
{ }
template<typename T>
Set<T>& Set<T>::operator = (Set<T>& ref)
{ }
*/
template<typename T>
void Set<T>::insert(T element)
{
	if (isEmpty())
		reSize(20);
	if (isFull())
		reSize(2 * noOfElements);
	if (searchElementPosition(element) != -1)
		return;
	data[noOfElements] = element;
	noOfElements++;
}
template<typename T>
void Set<T>::remove(T element)
{
	if (isEmpty())
		return;
	int ind = searchElementPosition(element);
	if (ind == -1)
		return;
	noOfElements--;
	data[ind] = data[noOfElements];
}
template<typename T>
void Set<T>::print()const
{
	cout << "{ ";
	for (int i = 0; i < getCardinality(); i++)
		cout << data[i] << " , ";
	cout<<" }" << endl;
}
template<typename T>
int Set<T>::getCardinality() const
{
	return noOfElements;
}
template<typename T>
int Set<T>::getCapacity() const
{
	return capacity;
}
template<typename T>
int Set<T>::isMember(T val) const
{
	int index = 0;
	while (index < noOfElements)
	{
		if (val == data[index])
			return 1;
		index++;
	}
	return 0;
}
template<typename T>
int Set<T>::isSubset(const Set<T>& s2)const
{
	enum { S2_SUBSET = -1, NO_ONE_SUBSET = 0, CALLING_OBJECT_SUBSET = 1, IMPROPER_SUBSET = 2 };
	if (isEmpty() && s2.isEmpty())
		return IMPROPER_SUBSET;
	if (!isEmpty() && s2.isEmpty())
		return S2_SUBSET;
	if (isEmpty() && !s2.isEmpty())
		return CALLING_OBJECT_SUBSET;
	if (noOfElements < s2.noOfElements)
	{
		int i = 0;
		while ((i < noOfElements) && (s2.isMember(data[i])))
			i++;
		if (i == noOfElements)
			return CALLING_OBJECT_SUBSET;
		return NO_ONE_SUBSET;
	}
	else if (noOfElements > s2.noOfElements)
	{
		int i = 0;
		while ((i < s2.noOfElements) && (isMember(s2.data[i])))
			i++;
		if (i == s2.noOfElements)
			return S2_SUBSET;
		return NO_ONE_SUBSET;
	}
	else
	{
		int i = 0;
		while ((i < noOfElements) && (s2.isMember(data[i])))
			i++;
		return (i == noOfElements ? IMPROPER_SUBSET : NO_ONE_SUBSET);
	}
}
template<typename T>
void Set<T>::reSize(int newCap)
{
	if (newCap <= 0)
	{
		delete[] data;
		noOfElements = 0;
		capacity = 0;
	}
	T* temp = new T[newCap];
	capacity = (newCap > getCapacity() ? newCap : getCapacity());
	for (int i = 0; i < getCardinality(); i++)
		temp[i] = data[i];
	delete[] data;
	data = temp;
	temp = nullptr;
}
template<typename T>
Set<T> Set<T>::calcUnion(const Set<T>& s2) const
{
	if (s2.isEmpty())
	{
		Set<T> temp(* this );
		return temp;
	}
	else if (isEmpty())
	{
		Set<T> temp{ s2 };
		return temp;
	}
	Set<T> temp(* this );
	for (int i = 0; i < s2.noOfElements; i++)
		temp.insert(s2.data[i]);
	//temp.print();
	return temp;
	//cout << "here\n";
}
template<typename T>
Set<T> Set<T>::calcIntersection(const Set<T>& s2) const
{
	Set<T> temp;
	if (isEmpty() || s2.isEmpty())
		return temp;
	for (int i = 0; i < noOfElements; i++)
	{
		if (isMember(s2.data[i]))
			temp.insert(s2.data[i]);
	}
	return temp;
}
template<typename T>
Set<T> Set<T>::calcDifference(const Set<T>& s2) const
{
	if (s2.isEmpty())
	{
		Set<T> temp{ *this };
		return temp;
	}
	Set<T> temp;
	if (isEmpty())
		return temp;
	for (int i = 0; i < noOfElements; i++)
	{
		if (!s2.isMember(data[i]))
			temp.insert(data[i]);
	}
	return temp;
}
template<typename T>
Set<T> Set<T>::calcSymmetricDifference(const Set<T>& s2) const
{
	Set<T> tUnion = calcUnion(s2);
	Set<T> tIntersect = calcIntersection(s2);
	return tUnion.calcDifference(tIntersect);
}
#endif // !SET_H
