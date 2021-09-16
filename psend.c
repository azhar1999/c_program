#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

void main()
{
    char m1[10];
    char m2[10];
    char m3[10];
    int p1, p2, p3;
    mqd_t mqdes;
    printf("enter first message:");
    gets(m1);
    printf("enter second message:");
    gets(m2);
    printf("enter third message:");
    gets(m3);

    printf("enter priority of 1st message:");
    scanf("%d", &p1);
    printf("enter priority of 2nd message:");
    scanf("%d", &p2);
    printf("enter priority of 3rd message:");
    scanf("%d", &p3);

    mqdes = mq_open("/test3_q", O_CREAT | O_RDWR, 0666, NULL);
    if (mqdes == -1)
    {
        printf("Error creating queue\n");
    }
    else
    {
       
        mq_send(mqdes, m1, 10, p1);
        mq_send(mqdes, m2, 10, p2);
        mq_send(mqdes, m3, 10, p3);
        printf("message has send\n");
    }
}
