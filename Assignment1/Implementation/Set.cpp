#include <iostream>

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
int hashCode1(T key)//O(1)
{
	// calculate hash_code for any object key

	auto hashfunc = hash<T>();

	int hashcode = hashfunc(key);

	return abs(hashcode);
}

template <typename T>
int hashCode2(T key)//O(1)
{
	//calculate hash_code for any object key using hash1

	string s;

	s = (string)key;

	return (s[0] + s[s.size() - 1]);
}

template <typename T>
class HashSet : ISet<T>
{
private:
	// pointer to array of T pointers 
	T** array;
	int sizeS;
	int CAPACITY = 797;
	int PRIME_NUMBER = 37;

public:
	HashSet()
	{
		// initialize the array and fill it with nullptr
		array = new T * [CAPACITY];
		for (int i = 0; i < CAPACITY; i++)
			array[i] = nullptr;

		this->sizeS = 0;
	}

	HashSet(const HashSet& copy)
	{
		this->sizeS = copy.sizeS;
		//initialize the array and fill it with copy_set's elements
		this->array = new T * [CAPACITY];
		std::copy(copy.array, copy.array + copy.CAPACITY, this->array);
	}

	HashSet& operator= (const HashSet& set)
	{
		if (this == &set)
			return *this;
		delete[] this->array;

		//initialize the array and fill it with copy_set's elements
		this->sizeS = set.sizeS;
		this->array = new T * [CAPACITY];
		std::copy(set.array, set.array + set.CAPACITY, this->array);

		return *this;
	}

	~HashSet()
	{
		delete[] array;
	}

	void add(T item)//O(n)
	{
		if (!contains(item))
		{
			int i = 0, h1, h2;
			h1 = hashCode1(item) % CAPACITY;
			h2 = hashCode2(item) % CAPACITY;
			//  iterate through the hash index until find an empty space or until go through the entire array
			while (array[(h1 + i * h2) % CAPACITY] != nullptr && i < CAPACITY)
				i++;
			// put to the first suitable place 
			int index = (h1 + i * h2) % CAPACITY;
			array[index] = new T;
			array[index][0] = item;
			sizeS++;
		}
	}

	/**
	 * \remove element in array[index] if it exists
	}
	 * \param element
	 */

	virtual void remove(T item)//O(n)
	{
		int index = 0;
		if (contains(item, index))
		{
			array[index] = nullptr;
			sizeS--;
		}
	}

	virtual bool contains(T item)//O(n)
	{
		int i = 0, h1, h2;
		h1 = hashCode1(item) % CAPACITY;
		h2 = hashCode2(item) % CAPACITY;

		while (i < CAPACITY)
		{
			//iterate through the hash index until find pointer to this element
			int index = (h1 + i * h2) % CAPACITY;

			if (array[index] != nullptr)
				if (array[index][0] == item)
					return true;
			i++;
		}
		return false;
	}

	int size()//O(1)
	{
		return this->sizeS;
	}

	bool isEmpty()//O(1)
	{
		return (this->sizeS == 0);
	}
	/**
	 * \print all element that HashSet contains
	 * \return line with all elements
	 */
	string ToString()//O(n)
	{
		ostringstream answer;
		for (int i = 0; i < CAPACITY - 1; i++)
			if (array[i] != nullptr)
				answer << array[i][0] << " ";

		if (array[CAPACITY - 1] != nullptr)
			answer << array[CAPACITY - 1][0];
		return answer.str();

	}

	//private:



	virtual bool contains(T item, int& out_index)//O(n)
	// method overload that return index if contains
	{
		int i = 0, h1, h2;
		h1 = hashCode1(item) % CAPACITY;
		h2 = hashCode2(item) % CAPACITY;
		while (i < CAPACITY)
		{
			int index = (h1 + i * h2) % CAPACITY;

			if (array[index] != nullptr)
				if (array[index][0] == item)
				{
					out_index = index;
					return true;
				}
			i++;
		}

		return false;
	}
};

int main()
{
}