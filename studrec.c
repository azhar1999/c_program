#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

typedef struct student
{
    int roll;
    int marks;
} student;

int main()
{

    int i, j, min, tempm, tempr;
    int n = 0;

    key_t key = ftok("sharedmemory", 65);

    int shmid = shmget(key, 100, 0666 | IPC_CREAT);

    student *st = (student *)shmat(shmid, (void *)0, 0);
    printf("enter no . of students:");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
            if (st[j].marks > st[min].marks)
                min = j;

        tempm = st[i].marks;
        st[i].marks = st[min].marks;
        st[min].marks = tempm;

        tempr = st[i].roll;
        st[i].roll = st[min].roll;
        st[min].roll = tempr;
    }
    for (int i = 0; i < n; i++)
    {
        printf("Rank  %d Roll No : %d : Marks: %d  \n", i + 1, st[i].roll, st[i].marks);
    }

    shmdt(st);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
