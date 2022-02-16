#include <iostream>
#include <vector>
using namespace std;

int main()
{
   /* int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int i, minindex, j;
    for (i = 0; i < n - 1; i++)
    {
        minindex = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[minindex])
                minindex = j;
        }

        if (a[minindex] != a[i])
        {
            a[minindex] = a[minindex] + a[i];
            a[i] = a[minindex] - a[i];
            a[minindex] = a[minindex] - a[i];
        }
    }
    
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";*/

    int n, res;

    for (n = 1; n <= 20; n++)
    {
        res = 0;
        for (int I = 1; I <= n - 1; I++)
            for (int j = I + 1; j <= n; j++)
                res++;
        cout << "for n = " << n << " result is " << res << endl;
        cout << "      but also = " << n*(n-1)*0.5 << endl << endl;
    }
}