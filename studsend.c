#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct student
{
    int rollno;
    int mark;

} student;

int main()
{
    int i, no;

    key_t key = ftok("sharedmemory", 65);

    int shmid = shmget(key, 100, 0666 | IPC_CREAT);

    student *st = (student *)shmat(shmid, (void *)0, 0);

    printf("enter the no of student :");
    scanf("%d", &no);

    for (i = 0; i < no; i++)

    {
        printf("enter roll no:");
        scanf("%d", &st[i].rollno);

        printf("enter the mark of student: ");
        scanf("%d", &st[i].mark);
        printf("\n");
    }

    shmdt(st);

    return 0;
}
