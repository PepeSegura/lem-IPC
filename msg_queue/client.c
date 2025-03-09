// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[10];
    int x;
    int y;
} message;

int main()
{
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("progfile", 65);
    printf("key: %d\n", key);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666);
    if (msgid == -1)
    {
        printf("queue dont exists\n");
        exit(1);
    }

    // msgrcv to receive message
    // while (1)
    // {
    //     errno = 0;
    //     msgrcv(msgid, &message, sizeof(message) - sizeof(long), 1, IPC_NOWAIT);
    //     if (errno == ENOMSG)
    //     {
    //         sleep(1);
    //         perror("msgrcv");
    //     }
    //     else if (strcmp(message.mesg_text, "stop\n") == 0)
    //         break;
    //     else
    //     {

    //         printf("%s", message.mesg_text);
    //         // continue;
    //     }
    //     perror("msgrcv");
        
    // }
    // printf("errno: %d\n", errno);

    // display the message

    // // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
