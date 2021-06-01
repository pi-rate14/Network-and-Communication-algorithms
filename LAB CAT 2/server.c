#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

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
    }
    //debugged
    int messageBits = strlen(data);

    int r, gen[50];
    printf("Enter the number of generator bits : ");
    scanf("%d", &r);
    printf("\nEnter the generator : ");
    for (int i = 0; i < r; i++)
    {
        scanf("%d", &gen[i]);
    }

    r--;
    for (int i = 0; i < r; i++)
    {
        p[messageBits + i] = 0;
    }

    for (int i = 0; i < messageBits + r; i++)
        temp[i] = p[i];
    division(temp, gen, messageBits, r);
    printf("CRC successful ");
    for (int i = 0; i < r; i++)
    {

        printf(" ");
        p[messageBits + i] = temp[messageBits + i];
    }
    printf("\n");
    printf("Transmitted Message : ");
    for (int i = 0; i < messageBits + r; i++)
        printf("%c", p[i]);
}

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;)
    {
        bzero(buff, MAX);

        read(sockfd, buff, sizeof(buff));
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        char *binaryString = stringToBinary(buff);
        crc(binaryString);
        write(sockfd, buff, sizeof(buff));

        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");
    func(connfd);
    close(sockfd);
}
