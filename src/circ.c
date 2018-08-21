#include <circ.h>
#include <stdbool.h>

bool circ_recv_raw(CIrcClient *client, char *message)
{
    printf("[RECV] %s\n", message);
}

bool circ_recv(CIrcClient *client, char *sender, char *recipient,
        char *message)
{
    // TODO.
}

bool circ_register_recv_callback(CIrcClient *client,
        CIrcRecvCallback *callback)
{
    // TODO.
}

// Change your nickname to +new_nick+.
//
// TODO: Add corresponding code to change client->nick on successful change.
bool circ_change_nick(CIrcClient *client, char *new_nick)
{
    // Store new_nick. Use strncpy() to avoid buffer overflows.
    strncpy(client.pending_nick, new_nick, MAX_NICK_LENGTH);

    return _circ_send2(client, "NICK", new_nick);
}

// Join the channel specified with +channel+.
bool circ_join(CIrcClient *client, char *channel) {
    return _circ_send2(client, "JOIN", channel);
}

// Leave (part) the channel specified with +channel+.
bool circ_part(CIrcClient *client, char *channel, char *message) {
    return _circ_send3(client, "PART", channel, message);
}

// Send a message to +recipient+
bool circ_privmsg(CIrcClient *client, char *recipient, char *message) {
    return _circ_send3(client, "PRIVMSG", recipient, message);
}
