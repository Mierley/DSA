
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

template<class T>
class ISet {
public:
    virtual void add(T item) = 0; // add item in the set
    virtual void remove(T item) = 0; // remove an item from a set
    virtual bool contains(T item) = 0; // check if a item belongs to a set
    virtual int size() = 0; // number of elements in a set
    virtual bool isEmpty() = 0; // check if the set is empty
};


template<class T>
class DoubleHashSet : public virtual ISet<T>
{
private:
    T* arr_;
    bool* arr_exist_;
    int size_{ 0 };
    const int CAPACITY = 529;
    const int prime_num = 37;

    void get_hashes(const T& item, long long& hash1, long long& hash2)
    {
        auto hash_ = hash<T>();

        const string string_item = (string)item;

        hash1 = abs((int)(hash_(item))) % CAPACITY;
        hash2 = abs(prime_num - hash1 % prime_num) % (CAPACITY - 2);
    }

    bool findIndex(T item, int* index = nullptr)
    {
        long long hash1;
        long long hash2;;
        int hash_code;

        get_hashes(item, hash1, hash2);

        for (int j = 0; j < CAPACITY; j++)
        {
            hash_code = (hash1 + j * hash2) % CAPACITY;
            if (arr_exist_[hash_code] != false && arr_[hash_code] == item)
            {
                if (index != nullptr)
                    *index = hash_code;
                return true;
            }
        }
        return false;
    }
public:
    DoubleHashSet()
    {
        arr_ = new T[CAPACITY];
        arr_exist_ = new bool[CAPACITY];

        for (int i = 0; i < CAPACITY; i++)
            arr_exist_[i] = false;
    }

    DoubleHashSet(const DoubleHashSet& set)
    {
        this->size_ = set.size_;
        this->arr_ = new T[CAPACITY];
        this->arr_exist_ = new bool[CAPACITY];
        std::copy(set.arr_, set.arr_ + set.CAPACITY, this->arr_);
        std::copy(set.arr_exist_, set.arr_exist_ + set.CAPACITY, this->arr_exist_);
    }

    ~DoubleHashSet()
    {
        delete[] arr_;
        delete[] arr_exist_;
    }

    void add(T item) 
    {
        if (size() == CAPACITY)
            throw overflow_error("Set is full");

        long long hash1;
        long long hash2;
        int hash_code;

        get_hashes(item, hash1, hash2);

        int i = 0;
        while (arr_exist_[(hash1 + i * hash2) % CAPACITY] != false && i < CAPACITY)
            i++;

        size_++;
        arr_[(hash1 + i * hash2) % CAPACITY] = item;
        arr_exist_[(hash1 + i * hash2) % CAPACITY] = true;
    }
     
    void remove(T item) 
    {
        long long hash1;
        long long hash2;
        int hash_code;

        get_hashes(item, hash1, hash2);

        int i = 0;
        while (arr_[(hash1 + i * hash2) % CAPACITY] != item && i < CAPACITY)
            i++;

        if (i != CAPACITY)
        {
            size_--;
            arr_exist_[(hash1 + i * hash2) % CAPACITY] = false;
        }
        
    }
    virtual bool contains(T item)
    {
        int i = 0;
    	long long  hash1, hash2;

        get_hashes(item, hash1, hash2);

        while (i < CAPACITY)
        {
            int hash_code = (hash1 + i * hash2) % CAPACITY;

            if (arr_exist_[hash_code] != false)
                if (arr_[hash_code] == item)
                    return true;
            i++;
        }
        return false;
    }
    int size()
    {
        return size_;
    }
    bool isEmpty()
    {
        return size_ == 0;
    }

    operator string() const
    {
        ostringstream ans;
        for (int i = 0; i < CAPACITY; i++)
            if (arr_exist_[i] != false)
                ans << arr_[i] << " ";
        return ans.str();
    }

    DoubleHashSet& operator= (const DoubleHashSet& set)
    {
        if (this == &set)
            return *this;

        delete[] arr_;
        delete[]arr_exist_;

        this->size_ = set.size_;
        this->arr_ = new T[CAPACITY];
        this->arr_exist_ = new bool[CAPACITY];

        std::copy(set.arr_, set.arr_ + set.CAPACITY, this->arr_);
        std::copy(set.arr_exist_, set.arr_exist_ + set.CAPACITY, this->arr_exist_);

        return *this;
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

void parse_line(string& line, string& command, string& parameter)
{
    const size_t space_index = line.find(' ');

    if (space_index != string::npos)
    {
        command = line.substr(0, space_index);
        parameter = line.substr(space_index + 1);
    }
    else
    {
        command = line.substr(0);
        parameter = "";
    }
}

int main()
{
    int n, k;
    cin >> n >> k;

    DoubleHashSet<string> Set;
    BoundedStack<DoubleHashSet<string>> StatusSet(k, DoubleHashSet<string>());
    bool flag = true;

    string line, command, parameter;
    getline(cin, line);

    for (int i = 0; i < n; i++)
    {
        getline(cin, line);

        parse_line(line, command, parameter);

        if (command == "NEW")
        {
            string second_name = parameter;

            if (second_name[second_name.size() - 1] == '/')
                second_name = second_name.substr(0, second_name.size() - 1);
            else second_name = second_name.append("/");

            if (!(Set.contains(second_name) || Set.contains(parameter)))
            {
                Set.add(parameter);
                StatusSet.push(Set);
            }
            else cout << "ERROR: cannot execute " << command.append(" ").append(parameter).append("\n");
        }

        if (command == "REMOVE")
        {
            if (Set.contains(parameter))
            {
                Set.remove(parameter);
                StatusSet.push(Set);
            }
            else cout << "ERROR: cannot execute " << command.append(" ").append(parameter).append("\n");
        }

        if (command == "UNDO")
        {
            int undo_parameter = 1;
            if (!parameter.empty())
                undo_parameter = stoi(parameter, nullptr, 10);

            if ((!flag && (undo_parameter == StatusSet.size())) || (undo_parameter >= k) || undo_parameter > StatusSet.size())
            {
                cout << "ERROR: cannot execute " << command.append(" ").append(parameter).append("\n");
            }
            else
            {
                while (undo_parameter--)
                {
                    StatusSet.pop();
                }
                Set = StatusSet.top();
            }
        }

        if (command == "LIST")
        {
            cout << static_cast<string>(Set) << endl;
        }

        if (flag)
            flag = !StatusSet.isFull();
    }
}