#include <circ.h>
#include "send.h"
#include <stdio.h>

bool circ_send_raw(CIrcClient *client, char *message)
{
    (void)client;
    (void)message;

    printf("[SEND] %s\n", message);

    return true;
}

bool circ_send(CIrcClient *client, char *recipient, char *message)
{
    // TODO.
    (void)client;
    (void)recipient;
    (void)message;

    return true;
}

bool _circ_send2(CIrcClient *client, char *chunk1, char *chunk2)
{
    // Create a fixed-size buffer for the message, initialized to null bytes.
    char buffer[MESSAGE_BUFFER_LENGTH] = {0,};

    // Attempt to write the message to the buffer.
    int bytes_written = snprintf(buffer, MESSAGE_BUFFER_LENGTH, "%s %s\r\n",
            chunk1, chunk2);

    if (bytes_written >= MESSAGE_BUFFER_LENGTH || bytes_written < 0) {
        return false;
    }

    // Send the message.
    circ_send_raw(client, buffer);

    return true;
}

bool _circ_send3(CIrcClient *client, char *chunk1, char *chunk2, char *chunk3)
{
    // Create a fixed-size buffer for the message, initialized to null bytes.
    char buffer[MESSAGE_BUFFER_LENGTH] = {0,};

    // Attempt to write the message to the buffer.
    int bytes_written = snprintf(buffer, MESSAGE_BUFFER_LENGTH, "%s %s :%s\r\n",
            chunk1, chunk2, chunk3);

    if (bytes_written >= MESSAGE_BUFFER_LENGTH || bytes_written < 0) {
        return false;
    }

    // Send the message.
    circ_send_raw(client, buffer);

    return true;
}
