#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

struct msgbuf
{
    long msgtype;
    char msgtxt[100];
} msg;

int main()
{
    struct msgbuf msg;
    char str[100];
    key_t key;
    int msgid, i, k = 0, n;
    msg.msgtype = 1;
    key = ftok("palindrome.c", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgrcv(msgid, &msg, sizeof(msg), 1, 0) == -1)
    {
        printf("error\n");
    }
    strcpy(str, msg.msgtxt);
    n = strlen(str);
    printf("%s\n", str);
    for (i = 0; i < n / 2; i++)
    {
        if (str[i] == str[n - i - 1])
        {
            k++;
        }
    }
    if (k == i)
        printf("string is palindrome\n");
    else
        printf("string is not palindrome\n");
}
