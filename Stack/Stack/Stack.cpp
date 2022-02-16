#include <vector>
#include <iostream>
#include "Stack.h"

using namespace std;

template <class T> bool Stack<T>::isEmpty()
{
    return (topNumber == 0);
}
template <class T> void Stack<T>::push(T element)
{
    currentElementNumber++;
    elements.push_back(element);
}

template <class T> T Stack<T>::pop()
{
    if (currentElementNumber == 0)
        return null;

    T t = elements[currentElementNumber - 1];
    elements.pop_back();
    currentElementNumber--;
    return t;
}

template <class T> T Stack<T>::top()
{
    if (currentElementNumber == 0)
        return null;

    return elements[currentElementNumber - 1];
}