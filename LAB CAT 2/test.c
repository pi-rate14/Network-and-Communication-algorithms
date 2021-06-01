#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned long binaryToDecimal(char *binary, int length)
{
    unsigned long decimal = 0;
    int i;
    unsigned long weight = 1;
    binary += length - 1;
    weight = 1;
    for (i = 0; i < length; ++i, --binary)
    {
        if (*binary == '1')
            decimal += weight;
        weight *= 2;
    }
    return decimal;
}

char *stringToBinary(char *s)
{
    if (s == NULL)
        return 0; /* no input string */
    char *binary = malloc(sizeof(s) * 8);
    strcpy(binary, "");
    char *ptr = s;
    int i;

    for (; *ptr != 0; ++ptr)
    {

        /* perform bitwise AND for every bit of the character */
        for (i = 7; i >= 0; --i)
        {
            (*ptr & 1 << i) ? strcat(binary, "1") : strcat(binary, "0");
        }
    }

    return binary;
}

//binary to string
char *binaryToString(char *data)
{
    char *text;
    int binaryLength, symbolCount;
    binaryLength = strlen(data);
    symbolCount = binaryLength / 8 + 1;
    text = malloc(symbolCount + 1);
    int i;
    for (i = 0; i < binaryLength; i += 8, data += 8)
    {
        char *byte = data;
        byte[8] = '\0';
        *text++ = binaryToDecimal(byte, 8);
    }
    text -= symbolCount;
    //printf("The result text is: %s\n", text);
    return text;
}

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

void crc(char *data)
{

    int p[strlen(data)];
    int i, temp[50];
    for (i = 0; i < strlen(data); i++)
    {
        p[i] = data[i] - '0';
        printf("%d", p[i]);
    }
    //debugged
    int messageBits = strlen(data);

    int r, gen[50];
    printf("Enter the number of generator bits : ");
    scanf("%d", r);
    printf("\nEnter the generator : ");
    for (int i = 0; i < r; i++)
    {
        scanf("%d", gen[i]);
    }

    r--;
    for (int i = 0; i < r; i++)
    {
        p[messageBits + i] = 0;
    }

    for (int i = 0; i < messageBits + r; i++)
        temp[i] = p[i];
    division(temp, gen, messageBits, r);
    printf("CRC : ");
    for (int i = 0; i < r; i++)
    {
        printf("%d", temp[messageBits + i]);
        printf(" ");
        p[messageBits + i] = temp[messageBits + i];
    }
    printf("%c", "\n");
    printf("Transmitted Message : ");
    for (int i = 0; i < messageBits + r; i++)
        printf("%d", p[i]);
}

void main()
{
    char *data = "Hello";
    char *binaryString = stringToBinary(data);
    crc(binaryString);
    // printf("\n");
    // printf(binaryString);
    // printf("\n");
    // char *stringBinary = binaryToString(binaryString);
    // printf(stringBinary);
    // printf("\n");
}