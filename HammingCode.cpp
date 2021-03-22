#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace ::std;
int input[32];
int code[32];
int ham_calc(int, int);
void Receiver(int, int);
void sender()
{
    int n, i, pn = 0, cl, j, k;
    cout << "Enter the length of the Data: ";
    cin >> n;
    cout << "enter the Data:\n";
    for (i = 0; i < n; i++)
    {
        cin >> input[i];
    }

    i = 0;
    while (n > (int)pow(2, i) - (i + 1))
    {
        pn++;
        i++;
    }

    cl = pn + n;

    j = k = 0;
    for (i = 0; i < cl; i++)
    {

        if (i == ((int)pow(2, k) - 1))
        {
            code[i] = 0;
            k++;
        }
        else
        {
            code[i] = input[j];
            j++;
        }
    }
    for (i = 0; i < pn; i++)
    {
        int position = (int)pow(2, i);
        int value = ham_calc(position, cl);
        code[position - 1] = value;
    }
    cout << "\nThe calculated Code Word is: ";
    for (i = 0; i < cl; i++)
        cout << code[i];
    cout << endl;
    ;
    Receiver(cl, pn);
}
void Receiver(int cl, int pn)
{
    int i;
    cout << "Enter the received Code Word:\n";
    for (i = 0; i < cl; i++)
        cin >> code[i];

    int error_pos = 0;
    for (i = 0; i < pn; i++)
    {
        int position = (int)pow(2, i);
        int value = ham_calc(position, cl);
        if (value != 0)
            error_pos += position;
    }
    if (error_pos == 1)
        printf("The received Code Word is correct.\n");
    else
        printf("Error at bit position: %d\n", error_pos);
}
int ham_calc(int position, int cl)
{
    int count = 0, i, j;
    i = position - 1;
    while (i < cl)
    {
        for (j = i; j < i + position; j++)
        {
            if (code[j] == 1)
                count++;
        }
        i = i + 2 * position;
    }
    if (count % 2 == 0)
        return 0;
    else
        return 1;
}
int main()
{
    sender();
    return 0;
}