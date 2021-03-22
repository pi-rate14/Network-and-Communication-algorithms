#include <iostream>
#include <cstdlib>
using namespace std;
void division(int temp[], int gen[], int n, int r)
{
    for (int i = 0; i < n; i++)
    {
        if (gen[0] == temp[i])
        {
            for (int j = 0, k = i; j < r + 1; j++, k++)
                if (!(temp[k] ^ gen[j]))
                    temp[k] = 0;
                else
                    temp[k] = 1;
        }
    }
}

void receiver(int message[], int n, int r, int gen[])
{
    int temp[50];
    cout << endl
         << endl
         << "At Receiver's End " << endl;
    cout << "The received message : ";
    for (int i = 0; i < n + r; i++)
        cout << message[i] << " ";
    for (int i = 0; i < n + r; i++)
        temp[i] = message[i];
    division(temp, gen, n, r);
    for (int i = 0; i < r; i++)
    {
        if (temp[n + i])
        {
            cout << "\nError detected in received message.";
            return;
        }
    }
    cout << "\nNo error in received Message.\nReceived Message : ";
    for (int i = 0; i < n; i++)
        cout << message[i] << " ";
}

int modify(int message[], int n, int r, int gen[])
{
    int rnd = (rand() % n);
    if (message[rnd] == 0)
    {
        message[rnd] = 1;
    }
    else
    {
        message[rnd] = 0;
    }
    receiver(message, n, r, gen);
}

void sender()
{
    int n, r, message[50], gen[50], temp[50], choice = 0;
    cout << "At Sender's End " << endl;
    cout << "Enter the number of message bits : ";
    cin >> n;
    cout << "Enter the number of generator bits : ";
    cin >> r;
    cout << "Enter the message : ";
    for (int i = 0; i < n; i++)
        cin >> message[i];
    cout << "Enter the generator : ";
    for (int i = 0; i < r; i++)
        cin >> gen[i];
    r--;
    for (int i = 0; i < r; i++)
        message[n + i] = 0;
    for (int i = 0; i < n + r; i++)
        temp[i] = message[i];
    division(temp, gen, n, r);
    cout << "CRC : ";
    for (int i = 0; i < r; i++)
    {
        cout << temp[n + i] << " ";
        message[n + i] = temp[n + i];
    }
    cout << endl
         << "Transmitted Message : ";
    for (int i = 0; i < n + r; i++)
        cout << message[i] << " ";
    cout << "\nDo you want to modify the message? enter 1 for yes, 0 for no. ";
    cin >> choice;
    if (choice)
    {
        modify(message, n, r, gen);
    }
    else
    {
        receiver(message, n, r, gen);
    }
}

int main()
{
    sender();
    return 0;
}