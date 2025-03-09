// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MAX 10

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
    msgid = msgget(key, 0666 | IPC_CREAT);
    while (1)
    {
    
        message.mesg_type = 1;

        // printf("Write Data : ");
        fgets(message.mesg_text,MAX,stdin);

        message.x = 4;
        message.y = 2;


        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0);

        // display the message
        // printf("Data send is : %s \n", message.mesg_text);
        if (strcmp(message.mesg_text, "stop\n") == 0)
            break;
    }

    return 0;
}
