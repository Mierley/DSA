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
	CircularBoundedQueue(size_t CAPACITY, T custom_null_value)
	{
		this->CAPACITY = CAPACITY;
		array = new T[CAPACITY];
		front = -1;
		rear = -1;
		this->custom_null_value = custom_null_value;
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

		//я двигаю поинтер rear и записываю value, если массив переполнился и значение перезаписалось в конец, то двигаю front

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
	CircularBoundedQueue<T>* inverseQ;
	CircularBoundedQueue<T>* tempQ;
	T custom_null_value;
	size_t CAPACITY;
public:
	BoundedStack(size_t CAPACITY, T custom_null_value)
	{
		this->CAPACITY = CAPACITY;
		this->custom_null_value = custom_null_value;
		inverseQ = new CircularBoundedQueue<T>(CAPACITY, -1);
		tempQ = new CircularBoundedQueue<T>(CAPACITY, -1);
	}
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
		inverseQ->flush();
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
		return inverseQ->size();
	}// number of elements
	int capacity()
	{
		return CAPACITY;
	}// maximum capacity
};



void printErrorMessage(const string& command, const string& name)
{
	cout << "ERROR: cannot execute " << command << " " << name << "\n";
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

	for (int i = 0; i < n; i++)
	{
		cin >> command;

		if (command == "LIST")
		{
			cout << myset.ToString() << "\n";
			continue;
		}

		else
		{
			cin >> myobject;

			if (command == "NEW")
			{
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

	//SOLUTION A
	//int k, n;
	//cin >> n >> k;
	//string s;
	//CircularBoundedQueue<string> myqueue(k, "");
	//getline(cin, s);
	//for (int i = 0; i < n; i++)
	//{
	//	getline(cin, s);
	//	myqueue.offer(s);
	//}

	//
	//while (!myqueue.isEmpty())
	//	cout << myqueue.poll() << endl;
}
