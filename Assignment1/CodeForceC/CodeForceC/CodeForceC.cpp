#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename T> class ICircularBoundedQueue {
	virtual void offer(T value) = 0; //!!! insert an element to the rear of the queue
	// overwrite the oldest elements
	// when the queue is full
	virtual T poll() = 0; //!!! remove an element from the front of the queue
	virtual T peek() = 0; // look at the element at the front of the queue
	// (without removing it)
	virtual void flush() = 0; // remove all elements from the queue
	virtual bool isEmpty() = 0; // is the queue empty?
	virtual bool isFull() = 0; // is the queue full?
	virtual int size() = 0; // number of elements
	virtual int capacity() = 0; // maximum capacity
};


template <typename T>
class CircularBoundedQueue : ICircularBoundedQueue<T>
{
	int front;
	int rear;
	size_t CAPACITY;

	T* array;
	T custom_null_value;

public:
	CircularBoundedQueue(size_t CAPACITY, T custom_null_value) : custom_null_value(custom_null_value)
	{
		this->CAPACITY = CAPACITY;
		array = new T[CAPACITY];
		front = -1;
		rear = -1;
	}

	~CircularBoundedQueue()
	{
		delete[] array;
	}

	void offer(T value)
	{
		if (isEmpty())
		{
			rear = 0;
			array[rear] = value;
			front = 0;
		}

		else
		{
			rear = (rear + 1) % CAPACITY;
			array[rear] = value;
			if (rear == front)
			{
				front = (front + 1) % CAPACITY;
			}
		}
	}

	T poll()
	{
		if (isEmpty())
			return custom_null_value;

		int temp = front;

		if (front == rear)
			flush();
		else
			front = (front + 1) % CAPACITY;

		return array[temp];
	}

	T peek()
	{
		if (isEmpty())
			return custom_null_value;

		return array[front];
	}

	void flush()
	{
		front = -1;
		rear = -1;
	}

	bool isEmpty()
	{
		return (front == -1 && rear == -1);
	}

	bool isFull()
	{
		return ((front + CAPACITY) % CAPACITY == ((rear + 1 + CAPACITY) % CAPACITY));
	}

	int size()
	{
		if (isEmpty())
			return 0;
		if (isFull())
			return CAPACITY;
		else
			return (int)((rear - front + 1 + CAPACITY) % CAPACITY);
	}

	int capacity()
	{
		return CAPACITY;
	}
};

template <typename T>
class IBoundedStack
{
	virtual void push(T value) = 0; // push an element onto the stack
	// remove the oldest element5
		// when if stack is full
	virtual T pop() = 0; // remove an element from the top of the stack
	virtual T top() = 0; // look at the element at the top of the stack
	// (without removing it)
	virtual void flush() = 0; // remove all elements from the stack
	virtual bool isEmpty() = 0; // is the stack empty?
	virtual bool isFull() = 0; // is the stack full?
	virtual int size() = 0; // number of elements
	virtual int capacity() = 0; // maximum capacity
};

template <typename T>
class BoundedStack : IBoundedStack<T>
{
	size_t CAPACITY;
	T custom_null_value;
	CircularBoundedQueue<T>* inverseQ;
	CircularBoundedQueue<T>* tempQ;

public:
	BoundedStack(size_t CAPACITY, T custom_null_value) :
		CAPACITY(CAPACITY),
		custom_null_value(custom_null_value),
		inverseQ(new CircularBoundedQueue<T>(CAPACITY, custom_null_value)),
		tempQ(new CircularBoundedQueue<T>(CAPACITY, custom_null_value))
	{}

	~BoundedStack()
	{
		delete inverseQ;
		delete tempQ;
	}

	void push(T value)
	{
		inverseQ->offer(value);

		while (!tempQ->isEmpty() && (!inverseQ->isFull()))
		{
			inverseQ->offer(tempQ->poll());
		}

		tempQ->flush();
		CircularBoundedQueue<T>* t = inverseQ;
		inverseQ = tempQ;
		tempQ = t;
	}

	T pop()
	{
		if (tempQ->isEmpty())
			return custom_null_value;

		return tempQ->poll();
	}
	T top()
	{
		if (tempQ->isEmpty())
			return custom_null_value;

		return tempQ->peek();
	}

	void flush()
	{
		tempQ->flush();
	}
	// remove all elements from the stack
	bool isEmpty()
	{
		return (size() == 0);
	}// is the stack empty?
	bool isFull()
	{
		return (size() == CAPACITY);
	}// is the stack full?
	int size()
	{
		return tempQ->size();
	}// number of elements
	int capacity()
	{
		return CAPACITY;
	}// maximum capacity
};

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
	int sizeS;
	int CAPACITY = 797;
	int PRIME_NUMBER = 37;

public:
	HashSet()
	{
		array = new T * [CAPACITY];
		for (int i = 0; i < CAPACITY; i++)
			array[i] = nullptr;
		this->sizeS = 0;
	}

	HashSet(const HashSet& copy)
	{
		this->sizeS = copy.sizeS;
		this->array = new T * [CAPACITY];
		std::copy(copy.array, copy.array + copy.CAPACITY, this->array);
	}

	HashSet& operator= (const HashSet& set)
	{
		if (this == &set)
			return *this;

		delete[] this->array;

		this->sizeS = set.sizeS;
		this->array = new T * [CAPACITY];
		std::copy(set.array, set.array + set.CAPACITY, this->array);

		return *this;
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

	int hashCode1(T key) {

		auto hashfunc = hash<T>();

		int hashcode = hashfunc(key);

		return abs(hashcode) % CAPACITY;
	}

	int hashCode2(T key, int hash1) {

		return (PRIME_NUMBER - (abs(hash1) % PRIME_NUMBER));
	}

	virtual bool contains(T item, int& out_index)
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
					out_index = index;
					return true;
				}
			i++;
		}

		return false;
	}
};

void printErrorMessage(const string& command, const string& name)
{
	cout << "ERROR: cannot execute " << command << " " << name << "\n";
}
void printErrorMessage(const string& command, const int& num, bool is_num)
{
	if (is_num)
		cout << "ERROR: cannot execute " << command << " " << num << "\n";
	else
		cout << "ERROR: cannot execute " << command << "\n";
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
	int n, history_depth, num_undo, space_place, input_text_size;
	string input_text, myobject, command;
	cin >> n >> history_depth;
	getline(cin, input_text);
	HashSet<string> myset;

	HashSet<string> nullSet;
	// in stack I store the value of hashset using copy constructor
	BoundedStack<HashSet<string>>* mystack = new BoundedStack<HashSet<string>>(history_depth, nullSet);

	/// flag become false if stack at list one time become full, is_num is useful for comand UNDO and UNDO num
	bool flag = true, is_num;
	for (int i = 0; i < n; i++)
	{
		is_num = true;
		num_undo = 1;
		getline(cin, input_text);

		space_place = input_text.find(' ');
		input_text_size = input_text.size();

		if (space_place == string::npos)
		{
			//that means we have command without parameters
			command = input_text;
			is_num = false;
		}

		else
		{
			/// we take parameters
			command = input_text.substr(0, space_place);
			if (command == "UNDO")
				// param is number
				num_undo = stoi(input_text.substr(space_place + 1), nullptr, 10);
			else
				// param is string
				myobject = input_text.substr(space_place + 1);
		}

		if (command == "LIST")
		{
			// print all element in set
			cout << myset.ToString() << "\n";
			continue;
		}

		if (command == "UNDO")
		{
			// check validations 
			if ((!flag && (num_undo == mystack->size())) || (num_undo >= history_depth) || (num_undo > mystack->size()))
				printErrorMessage(command, num_undo, is_num);

			else
			{
				// clear the stack 
				while (num_undo--)
				{
					mystack->pop();
				}
				// now by set take value from one of the previous stages
				myset = mystack->top();
			}
		}

		else
		{
			if (command == "NEW")
			{
				// put or delete '/' to check the file or directory with the same name
				string optionalObject = makeSecondObject(myobject);

				if (myset.contains(myobject) || myset.contains(optionalObject))
					printErrorMessage(command, myobject);

				else
				{
					myset.add(myobject);
					mystack->push(myset);
				}
			}

			else if (command == "REMOVE")
			{
				int prevsize = myset.size();
				myset.remove(myobject);

				// if size of hashset did not change -> hashset did not contain this element(this way is faster then by checking iscontain())

				if (prevsize == myset.size())
					printErrorMessage(command, myobject);

				else
					mystack->push(myset);
			}

			if (flag == true)
				flag = !mystack->isFull();
		}
	}
	return 0;
}
