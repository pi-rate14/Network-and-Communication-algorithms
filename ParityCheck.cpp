#include <iostream>
#include <cstdlib>
using namespace ::std;

int sender(int a[], int n)
{
    cout << "sent bits are: ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
    }
}

int modify(int a[], int n)
{
    int r = (rand() % n);
    if (a[r] == 0)
    {
        a[r] = 1;
    }
    else
    {
        a[r] = 0;
    }
}

int receiver(int a[], int n)
{
    cout << endl
         << "received bits are: ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
    }
}

int main()
{
    int n, choice = 0, a[20];
    cout << "enter number of digits in binary ";
    cin >> n;
    cout << "enter the binary number with digits separated by space ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sender(a, n);
    cout << endl
         << "do you want to modify? enter 1 for yes, 0 for no. ";
    cin >> choice;
    if (choice == 1)
    {
        modify(a, n);
    }
    receiver(a, n);
}
