#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int nf, N, x = 0;
int no_tr = 0;

void receiver(int i, int x)
{
    for (int j = i; j < i + N && j <= nf; j++)
    {
        int flag = rand() % 2;
        if (!flag)
        {
            cout << "Acknowledgment for Frame " << j << endl;
            x++;
        }
        else
        {
            cout << "Frame " << j << " Not Received" << endl;
            cout << "Retransmitting Window" << endl;
            break;
        }
    }
}

void sender(int i)
{
    for (int j = i; j < i + N && j <= nf; j++)
    {
        cout << "Sent Frame " << j << endl;
        no_tr++;
    }
}

int main()
{

    srand(time(NULL));
    cout << "Enter the number of frames : ";
    cin >> nf;
    cout << "Enter the Window Size : ";
    cin >> N;
    int i = 1;
    while (i <= nf)
    {

        sender(i);

        for (int j = i; j < i + N && j <= nf; j++)
        {
            int flag = rand() % 2;
            if (!flag)
            {
                cout << "Acknowledgment for Frame " << j << endl;
                x++;
            }
            else
            {
                cout << "Frame " << j << " Not Received" << endl;
                cout << "Retransmitting Window" << endl;
                break;
            }
        }

        cout << endl;
        i += x;
    }
    cout << "Total number of transmissions : " << no_tr << endl;
    return 0;
}