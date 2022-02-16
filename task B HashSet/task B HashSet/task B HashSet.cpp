#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

template <typename T>
class ISet
{
	virtual void add(T item) = 0; // add item in the set
	virtual void remove(T item) = 0; // remove an item from a set
	virtual bool contains(T item) = 0; // check if a item belongs to a set
	virtual int size() = 0; // number of elements in a set
	virtual bool isEmpty() = 0; // check if the set is empty
};


template <typename T>
class Node


template <typename T>
class HashSet : ISet<T>
{
private:
	// pointer to array of T pointers 
	T** array;
	size_t sizeS;
	size_t CAPACITY = 2027;
	size_t Q = 13;

	int hashCode1(T key) {

		auto hashfunc = hash<T>();

		int hashcode = hashfunc(key);

		return abs(hashcode) % CAPACITY;
	}

	int hashCode2(T key) {

		auto hashfunc = hash<T>();

		int hashcode = hashfunc(key);

		return Q - (abs(hashcode) % Q);
	}

public:
	HashSet()
	{
		array = new T * [CAPACITY];
		for (int i = 0; i < CAPACITY; i++)
		{
			*T = new T[2];
			array[1] = 0;
		}
		this->sizeS = 0;
	}
	~HashSet()
	{
		for (int i = 0; i < CAPACITY; i++)
			delete[] array[i];
		delete[] array;
	}

	void add(T item)
	{
		add(item, false);
	}


	virtual void remove(T item)
	{
		int index = 0;
		if (contains(item, index))
		{
			array[index][1] = 0;
			sizeS--;
		}
	}

	virtual bool contains(T item)
	{
		for (int i = 0; i < CAPACITY; i++)
		{
			if (array[i][1] == 1 && array[i][0] == item)
					return true;
		}
		return false;
	}

	int size()
	{
		return this->sizeS;
	}

	bool isEmpty()
	{
		return (this->sizeS == 0);
	}

	string ToString()
	{
		ostringstream answer;
		for (int i = 0; i < CAPACITY - 1; i++)
			if (array[i][1] != 0)
				answer << array[i][0] << " ";

		if (array[CAPACITY - 1][1] != 0)
			answer << array[CAPACITY - 1][0];
		return answer.str();
	}

private:
	void add(T item, bool is_contain)
	{
		if (!is_contain)
		{
			int i = 0;
			while (array[(hashCode1(item) + i * hashCode2(item)) % CAPACITY][1] != 0 && i < CAPACITY)
				i++;

			array[(hashCode1(item) + i * hashCode2(item)) % CAPACITY][0] = item;
			sizeS++;
		}
	}

	virtual bool contains(T item, int& outindex)
	{
		for (int i = 0; i < CAPACITY; i++)
		{
			if (array[i][1] == 1 && array[i][0] == item)
			{
				outindex = i;
				return true;
			}
		}
		return false;
	}

	
};

void printErrorMessage(ostringstream& answer, const string& command, const string& name)
{
	answer << "ERROR: cannot execute " << command << " " << name << "\n";
}

string makeSecondObject(string myobject)
{
	string optionalObject;
	if (myobject[myobject.length() - 1] == '/')
		optionalObject = myobject.substr(0, myobject.length() - 1);
	else
		optionalObject = myobject + '/';
	return optionalObject;
}

int main()
{

	//проверка

		//

		//HashSet<int> s;
		//cout << s.myfunc();


	///*	 SOLUTION B*/
	int n;
	cin >> n;

	HashSet<string> myset;

	string myobject, command, q;
	ostringstream answer;

	for (int i = 0; i < n; i++)
	{
		cin >> command;

		if (command == "LIST")
		{
			answer << myset.ToString() << "\n";
			continue;
		}

		else
		{
			cin >> myobject;

			if (command == "NEW")
			{
				string optionalObject = makeSecondObject(myobject);
				string temp = answer.str();
				if (myset.contains(myobject) || myset.contains(optionalObject))
					printErrorMessage(answer, command, myobject);

				else
					myset.add(myobject);
			}

			else if (command == "REMOVE")
			{
				int prevsize = myset.size();
				myset.remove(myobject);

				// if size of hashset did not change -> hashset did not contain this element(this way is faster then by checking iscontain())

				if (prevsize == myset.size())
				{
					string temp = answer.str();
					printErrorMessage(answer, command, myobject);
				}
			}
		}
	}
	cout << answer.str();
}