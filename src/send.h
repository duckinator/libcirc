#ifndef CIRC_SEND_H
#define CIRC_SEND_H

#include <stdbool.h>

bool _circ_send2(CIrcClient *client, char *chunk1, char *chunk2);
bool _circ_send3(CIrcClient *client, char *chunk1, char *chunk2, char *chunk3);

#endif
