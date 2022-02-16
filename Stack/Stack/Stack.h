#include <vector>
#include <iostream>

using namespace std;

template <class T> class Stack
{
    public:
        bool isEmpty();
        void push(T element);
        T pop();
        T top();

    private:
        int currentElementNumber = 0;
        vector<T> elements;
};

