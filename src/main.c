#include <circ.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
    CIrcServer server = {"irc.freenode.net", 6667};
    CIrcClient client = {.nick="test", .server=&server, 0, {0}};

    if (!circ_connect(&client)) {
        fprintf(stderr, "error: Failed to connect to server.");
        return 1;
    }

    (void)server;
    (void)client;

    printf("TODO.");

    return 0;
}
