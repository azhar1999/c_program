#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
    mqd_t mqdes;
    char *str1;
    struct mq_attr *attr;
    attr = malloc(sizeof(struct mq_attr));
    
    int p;

    mqdes = mq_open("/test3_q", O_RDWR);

    if (mqdes == -1)
    {
        printf("Error\n");
    }
    else
    {
    	str1 = malloc(10*sizeof(char));
 	mq_getattr(mqdes, attr);

        mq_getattr(mqdes, attr);
        mq_receive(mqdes, str1, attr->mq_msgsize, &p);
        printf("message -%s ,priority %d\n", str1, p);
        mq_receive(mqdes, str1, attr->mq_msgsize, &p);
        printf("message -%s ,priority %d\n", str1, p);
        mq_receive(mqdes, str1, attr->mq_msgsize, &p);
        printf("message -%s ,priority %d\n", str1, p);
    }
}
