/* Insertion sort
  We sequentially go through the array and for every element we should find the place to put it. This place is allocated somewhere between beginning of array and previous place of our element.
 We will use loops to realise Insertion sort. The first one to go through array from 0 to n and take key element. And the second one to find the place for this key element(we will go from index of key element - 1 to 0 and if key element is smaller than element[j] - we will move all elements from j to index of key element).
*/ 

#include <vector>
#include <iostream>
using namespace std;


int main()
{  
    // read input
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    
    // Insertion sort
    int key;
    //take key element 
    for (int i = 1, j; i < n; i++)
    {
        key = a[i];
        j = i - 1;

        // move elements
        while (j >= 0 && a[j] > key) 
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }

    // write output
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}
