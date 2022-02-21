#include <iostream>

using namespace std;

template <typename T> class ICircularBoundedQueue {
	virtual void offer(T value) = 0; // insert an element to the rear of the queue
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
	int front; // index of the queue first element  
	int rear; // index of the queue last element
	size_t CAPACITY; // max size of queue

	T* array; // base of queue 
	T custom_null_value; // I use this value in method peek and poll, in queue is empty

public:
	CircularBoundedQueue(size_t CAPACITY, T custom_null_value)
	{
		//origin state
		front = -1;
		rear = -1;
		this->CAPACITY = CAPACITY;
		array = new T[CAPACITY];
		this->custom_null_value = custom_null_value;
	}

	~CircularBoundedQueue()
	{
		delete[] array;
	}

	void offer(T value) //O(1)
	{
		if (isEmpty())
		{
			// put both indexes to the beginning of array
			front = 0;
			rear = 0;
			array[rear] = value;
		}

		//я двигаю поинтер rear и записываю value, если массив переполнился и значение перезаписалось в конец, то двигаю front
		// move index rear and put value, but if array became full and value overwritten front element, I need to move index front
		else
		{
			rear = (rear + 1) % CAPACITY; // to move index circularly 
			array[rear] = value;
			if (rear == front)
			{
				front = (front + 1) % CAPACITY;// to move index circularly 
			}
		}
	}

	T poll()//O(1)
	{
		if (isEmpty())
			return custom_null_value;

		// take first element in queue
		T temp = array[front];

		//if queue had only one element, I flush it
		if (front == rear)
			flush();
		// move index front circularly
		else
			front = (front + 1) % CAPACITY;

		return temp;
	}

	T peek()//O(1)
	{
		if (isEmpty())
			return custom_null_value;

		//show the first element of queue
		return array[front];
	}

	void flush()//O(1)
	{
		// move indexes to the origin state
		front = -1;
		rear = -1;
	}

	bool isEmpty()//O(1)
	{
		// check to the origin state
		return (front == -1 && rear == -1);
	}

	bool isFull()//O(1)
	{
		//if queue is full, between front and rear should be CAPACITY - 1 elements
		return ((front + CAPACITY) % CAPACITY == ((rear + 1 + CAPACITY) % CAPACITY));
	}

	int size()//O(1)
	{
		if (isEmpty())
			return 0;
		if (isFull())
			return CAPACITY;
		else
			// calculate how many elements between front and rear
			return (int)((rear - front + 1 + CAPACITY) % CAPACITY);
	}

	int capacity()//O(1)
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
	CircularBoundedQueue<T>* temp_Q;// help inverse_Q to change the order of items
	CircularBoundedQueue<T>* inverse_Q;// keep items in order like stack usually do
	T custom_null_value;// return this value in top and pop if stack is empty
	size_t CAPACITY; //max size of stack
public:
	BoundedStack(size_t CAPACITY, T custom_null_value)
	{
		this->CAPACITY = CAPACITY;
		this->custom_null_value = custom_null_value;
		temp_Q = new CircularBoundedQueue<T>(CAPACITY, -1);
		inverse_Q = new CircularBoundedQueue<T>(CAPACITY, -1);
	}
	~BoundedStack()
	{
		delete temp_Q;
		delete inverse_Q;
	}

	void push(T value)//O(n) - we need inverse all elements in queue size n
	{
		temp_Q->offer(value);//O(1) put it in empty queue to make this element first

		while (!inverse_Q->isEmpty() && (!temp_Q->isFull()))// put other element that stack have after first element while we have places
		{
			temp_Q->offer(inverse_Q->poll());//O(1)
		}

		inverse_Q->flush();//O(1) delete elements which didn 't fit

		// swap this queue, because all elements in temp queue should keep in inverse_Q
		CircularBoundedQueue<T>* t = temp_Q;
		temp_Q = inverse_Q;
		inverse_Q = t;
	}

	T pop()//O(1)
	{
		if (inverse_Q->isEmpty())//O(1)
			return custom_null_value;
		//return first element in inverse_Q and delete it
		return inverse_Q->poll();//O(1)
	}
	T top()//O(1)
	{
		if (inverse_Q->isEmpty())//O(1)
			return custom_null_value;
		//return first element in inverse_Q
		return inverse_Q->peek();
	}

	void flush()//O(1) 
	{
		// remove all elements from the inverse queue
		inverse_Q->flush();//O(1)
	}
	
	bool isEmpty()//O(1)
	{
		return (size() == 0);
	}
	bool isFull()//O(1)
	{
		return (size() == CAPACITY);
	}
	int size()//O(1)
	{
		return inverse_Q->size();
	}
	int capacity()//O(1)
	{
		return CAPACITY;
	}
};

int main()
{
}