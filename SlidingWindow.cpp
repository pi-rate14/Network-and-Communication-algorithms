#include <bits/stdc++.h>

using namespace std;
int frames[50];

void receiver(int w, int f)
{
    int i = (rand() % f);
    for (i; i <= f; i++)
    {
        if (i % w == 0)
        {
            cout << frames[i] << "\n";
            cout << "Acknowledgement of above frames sent is received by sender\n\n";
        }
        else
        {
            cout << frames[i] << " ";
        }
    }

    if (f % w != 0)
        cout << "\nAcknowledgement of above frames sent is received by sender\n";
}

void sender(int w, int f, int i)
{
    cout << "\nEnter " << f << " frames: ";
    for (i = 1; i <= f; i++)
    {
        cin >> frames[i];
    }
    receiver(w, f);
}

int main()
{
    int w, i, f;

    cout << "Enter window size: ";
    cin >> w;

    cout << "\nEnter number of frames to transmit: ";
    cin >> f;

    sender(w, f, i);

    return 0;
}