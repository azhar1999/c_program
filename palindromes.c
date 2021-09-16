#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf
{
    long msgtype;
    char msgtxt[100];
};

int main()
{
    char str[20];
    key_t key;
    int msgid;
    struct msgbuf msg;

    msg.msgtype = 1;
    printf("enter string:");
    gets(str);
    strcpy(msg.msgtxt, str);

    key = ftok("palindrome.c", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgsnd(msgid, &msg, sizeof(msg), 0) == -1)
    {
        perror("msgsnd failed:");
    }
    else
    {
        printf("%s sent successfully\n", msg.msgtxt);
    }

    return 0;
}
