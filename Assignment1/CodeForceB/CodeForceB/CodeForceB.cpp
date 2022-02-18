#include <iostream>
#include <string>
#include <sstream>

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
class HashSet : ISet<T>
{
private:
	// pointer to array of T pointers 
	T** array;
	size_t sizeS;
	size_t CAPACITY = 379;
	size_t PRIMENUMBER = 37;

	int hashCode1(T key) {

		auto hashfunc = hash<T>();

		int hashcode = hashfunc(key);

		return abs(hashcode) % CAPACITY;
	}

	int hashCode2(T key, int hash1) {

		return PRIMENUMBER - (abs(hash1) % PRIMENUMBER);
	}

public:
	HashSet()
	{
		array = new T * [CAPACITY];
		for (int i = 0; i < CAPACITY; i++)
			array[i] = nullptr;
		this->sizeS = 0;
	}
	~HashSet()
	{
		delete[] array;
	}

	void add(T item)
	{
		if (!contains(item))
		{
			int i = 0, h1, h2;
			h1 = hashCode1(item);
			h2 = hashCode2(item, h1);
			while (array[(h1 + i * h2) % CAPACITY] != nullptr && i < CAPACITY)
				i++;

			int index = (h1 + i * h2) % CAPACITY;
			array[index] = new T;
			array[index][0] = item;
			sizeS++;
		}
		//add(item, false);
		// overload add(T, bool) is used, because I call method in main only if my item is not  exist, so is_contain is always false 
	}

	/**
	 * \remove element in array[index] if it exists
	}
	 * \param element
	 */
	virtual void remove(T item)
	{
		int index = 0;
		if (contains(item, index))
		{
			array[index] = nullptr;
			sizeS--;
		}
	}


	virtual bool contains(T item)
	{
		int i = 0, h1, h2;
		h1 = hashCode1(item);
		h2 = hashCode2(item, h1);
		while (i < CAPACITY)
		{
			int index = (h1 + i * h2) % CAPACITY;

			if (array[index] != nullptr)
				if (array[index][0] == item)
					return true;
			i++;
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


	/**
	 * \print all element that HashSet contains
	 * \return line with all elements
	 */
	string ToString()
	{
		ostringstream answer;
		for (int i = 0; i < CAPACITY - 1; i++)
			if (array[i] != nullptr)
				answer << array[i][0] << " ";

		if (array[CAPACITY - 1] != nullptr)
			answer << array[CAPACITY - 1][0];
		return answer.str();

	}

private:

	void add(T item, bool is_contain)
	{
		if (!is_contain)
		{
			int i = 0, h1, h2;
			h1 = hashCode1(item);
			h2 = hashCode2(item, h1);
			while (array[(h1 + i * h2) % CAPACITY] != nullptr && i < CAPACITY)
				i++;

			int index = (h1 + i * h2) % CAPACITY;
			array[index] = new T;
			array[index][0] = item;
			sizeS++;
		}
	}

	virtual bool contains(T item, int& outindex)
	{
		int i = 0, h1, h2;
		h1 = hashCode1(item);
		h2 = hashCode2(item, h1);
		while (i < CAPACITY)
		{
			int index = (h1 + i * h2) % CAPACITY;

			if (array[index] != nullptr)
				if (array[index][0] == item)
				{
					outindex = index;
					return true;
				}
			i++;
		}

		return false;
	}
};

/**
 * \brief print error message
 * \param command - command line that can not be execute
 * \param name - name of file or directory
 */
void printErrorMessage(const string& command, const string& name)
{
	cout << "ERROR: cannot execute " << command << " " << name << "\n";
}


/**
 * \brief make name directory/directory with the same name as myobject
 * \param myobject - name of file/directory
 * \return directory/directory with the same name as myobject
 */
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
	int n;
	cin >> n;

	HashSet<string> myset;

	string myobject, command;

	for (int i = 0; i < n; i++)
	{
		cin >> command;

		if (command == "LIST")
		{
			// ptint all element in set
			cout << myset.ToString() << "\n";
			continue;
		}

		else
		{
			cin >> myobject;

			if (command == "NEW")
			{
				// put or delete '/' to check the file or directory with the same name
				string optionalObject = makeSecondObject(myobject);

				if (myset.contains(myobject) || myset.contains(optionalObject))
					printErrorMessage(command, myobject);

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
					printErrorMessage(command, myobject);
				}
			}
		}
	}
}
