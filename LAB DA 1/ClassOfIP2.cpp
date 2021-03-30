#include <bits/stdc++.h>
using namespace ::std;

char findClass(int block)
{
    if (block >= 1 && block <= 126)
        return 'A';
    else if (block >= 128 && block <= 191)
        return 'B';
    else if (block >= 192 && block <= 223)
        return 'C';
    else if (block >= 224 && block <= 239)
        return 'D';
    else
        return 'E';
}

int main()
{
    string IP;
    cout << "enter IP address ";
    string block = "";
    cin >> IP;
    char result = 'A';
    int i = 0, ctr = 0, j = 0;
    while (i < IP.length())
    {
        if (IP[i] != '.')
        {
            block += IP[i];
            int b = atoi(block.c_str());
            result = findClass(b);
        }
        else
        {
            break;
        }
        i++;
    }
    cout << "Class of IP address is: " << result << endl;
}