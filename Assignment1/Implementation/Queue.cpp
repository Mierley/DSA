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

