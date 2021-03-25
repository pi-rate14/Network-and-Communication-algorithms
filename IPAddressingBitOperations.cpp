#include <bits/stdc++.h>
using namespace ::std;

string binDec = "";
string decBin = "";
string maskString = "";

int convertMask(int n)
{
    int num = n;
    int dec_value = 0;
    int base = 1;

    int temp = num;
    while (temp)
    {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }

    return dec_value;
}

string complement(string bits)
{
    for (int i = 0; i < bits.length(); i++)
    {
        if (bits[i] == '1')
        {
            bits[i] = '0';
        }
        else
        {
            bits[i] = '1';
        }
    }
    return bits;
}

void binToDecimal(string n)
{
    string num = n;
    int dec_value = 0;
    int base = 1;
    int len = num.length();
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    stringstream ss;
    ss << dec_value;
    string s;
    ss >> s;
    binDec = binDec + s + '.';
}

void FirstAddress(string bits, string mask)
{
    for (int i = 0; i < 32; i++)
    {
        if (bits[i] != mask[i])
        {
            bits[i] = '0';
        }
    }
    int j = 0;
    string block = "";
    for (int i = 0; i <= 31; i++)
    {
        block += bits[i];
        if ((i + 1) % 8 == 0)
        {
            binToDecimal(block);
            block = "";
        }
    }
    binDec[binDec.length() - 1] = ' ';
    cout << "First Address : " << binDec << endl;
    binDec = "";
}
void LastAddress(string bits, string mask)
{
    mask = complement(mask);
    for (int i = 0; i < 32; i++)
    {
        if (bits[i] == '0' && mask[i] == '1')
        {
            bits[i] = '1';
        }
    }
    int j = 0;
    string block = "";
    for (int i = 0; i <= 31; i++)
    {
        block += bits[i];
        if ((i + 1) % 8 == 0)
        {
            binToDecimal(block);
            block = "";
        }
    }
    binDec[binDec.length() - 1] = ' ';
    cout << "Last Address : " << binDec << endl;
    binDec = "";
}
void NoOfAddress(string bits, string mask)
{
    mask = complement(mask);
    int maskNum = atoi(mask.c_str());
    maskNum = convertMask(maskNum);
    cout << "Number of addresses: " << maskNum + 1 << endl;
}

int decToBinary(int n)
{
    for (int i = 7; i >= 0; i--)
    {
        int k = n >> i;
        if (k & 1)
            decBin += "1";
        else
            decBin += "0";
    }
}

int main()
{
    string IP;
    cout << "enter IP address ";
    string block = "";
    cin >> IP;
    string maskBits = "";
    maskBits = maskBits + IP[IP.length() - 2] + IP[IP.length() - 1];
    int mask = atoi(maskBits.c_str());
    for (int x = 0; x < mask; x++)
    {
        maskString += '1';
    }
    int remBits = 32 - mask;
    while (remBits)
    {
        maskString += '0';
        remBits--;
    }
    int i = 0, ctr = 0, j = 0;
    while (i < IP.length() - 3)
    {
        if (IP[i] != '.')
        {
            block += IP[i];
        }
        if (IP[i] == '.' || IP[i] == IP[IP.length() - 4])
        {
            int b = atoi(block.c_str());
            decToBinary(b);
            block = " ";
        }

        i++;
    }
    int choice;
    do
    {
        cout << "1. Press 1 for First Address\n2. Press 2 for second address\n2. Press 3 for number of addresses\nPress 0 to exit.\n";

        cin >> choice;
        switch (choice)
        {
        case 1:
            FirstAddress(decBin, maskString);
            break;
        case 2:
            LastAddress(decBin, maskString);
            break;
        case 3:
            NoOfAddress(decBin, maskString);
            break;
        default:
            cout << "Thanks for choosing ";
        }
    } while (choice != 0);
}