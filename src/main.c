#include <circ.h>
#include <stdio.h>
#include <stdbool.h>

CIrcRecvCallback *circ_new(char *nick, char *server, CIrcRecvCallback *recv_callback)
{
    CIrcClient *client = malloc(sizeof(CIrcClient));
    client->recv = recv_callback;

    return client;
}

bool circ_close(CIrcClient *client)
{
    // TODO.
    return false;
}

bool circ_register_recv_callback(CIrcClient *client,
        CIrcRecvCallback *callback)
{
    circ_recv
    return true;
}


int main()
{
    printf("TODO.");

    return 0;
}
