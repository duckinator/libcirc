#ifndef CIRC_H
#define CIRC_H

#include <stdbool.h>
#include <string.h>

/* Start socket-related includes. */
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
/* End socket-related includes. */

// IRC message length + room for null byte.
#define MESSAGE_BUFFER_LENGTH (512 + 1)

// Maximum domain name length + room for null byte.
// See RFC 1034, section 3.1, page 8. https://tools.ietf.org/html/rfc1034
#define DOMAIN_BUFFER_LENGTH (255 + 1)

// Nick/handle length can vary by server, but can't be longer than a message.
#define NICK_BUFFER_LENGTH MESSAGE_BUFFER_LENGTH

// Channel length vary by server, but can't be longer than a message.
#define CHANNEL_BUFFER_LENGTH MESSAGE_BUFFER_LENGTH

#define MIN_PORT 1          // Smallest port we can use. (TCP reserves port 0.)
#define MAX_PORT 65535      // Highest port number we can use.
#define MAX_PORT_LENGTH 5   // Length of MAX_PORT.

typedef struct circ_channel_s {
    char name[CHANNEL_BUFFER_LENGTH];
} CIrcChannel;

typedef struct circ_server_s {
    char address[DOMAIN_BUFFER_LENGTH];
    uint16_t port;
} CIrcServer;

typedef struct circ_client_s {
    char nick[NICK_BUFFER_LENGTH];
    CIrcServer *server;
    int sock;
    char pending_nick[NICK_BUFFER_LENGTH];
} CIrcClient;

enum CIrcMessageType {
    // https://defs.ircdocs.horse/defs/numerics.html
    //
    // We currently only include ones defined by RFCs.
    // If ones _not_ listed in RFCs are ever added, add a comment of the
    // form "// NONSTANDARD: Origin: <origin as mentioned in above link>".
    //
    // E.g.,
    //      CIRC_RPL_BOUNCE = 410, // NONSTANDARD: Unknown origin.
    CIRC_RPL_WELCOME           =   1,
    CIRC_RPL_YOURHOST          =   2,
    CIRC_RPL_CREATED           =   3,
    CIRC_RPL_MYINFO            =   4,
    CIRC_RPL_ISUPPORT          =   5,
    // 006-199 not defined by RFC.
    CIRC_RPL_TRACELINK         = 200,
    CIRC_RPL_TRACECONNECTING   = 201,
    CIRC_RPL_TRACEHANDSHAKE    = 202,
    CIRC_RPL_TRACEUNKNOWN      = 203,
    CIRC_RPL_TRACEOPERATOR     = 204,
    CIRC_RPL_TRACEUSER         = 205,
    CIRC_RPL_TRACESERVER       = 206,
    CIRC_RPL_TRACESERVICE      = 207,
    CIRC_RPL_TRACENEWTYPE      = 208,
    CIRC_RPL_TRACECLASS        = 209,
    CIRC_RPL_TRACERECONNECT    = 210,
    CIRC_RPL_STATSLINKINFO     = 211,
    CIRC_RPL_STATSCOMMANDS     = 212,
    CIRC_RPL_STATSCLINE        = 213,
    CIRC_RPL_STATSNLINE        = 214,
    CIRC_RPL_STATSILINE        = 215,
    CIRC_RPL_STATSKLINE        = 216,
    CIRC_RPL_STATSQLINE        = 217,
    CIRC_RPL_STATSYLINE        = 218,
    CIRC_RPL_ENDOFSTATS        = 219,
    // 220 not defined by RFC.
    CIRC_RPL_UMODEIS           = 221,
    // 222-230 not defined by RFC.
    CIRC_RPL_SERVICEINFO       = 231,
    CIRC_RPL_ENDOFSERVICES     = 232,
    CIRC_RPL_SERVLIST          = 234,
    CIRC_RPL_SERVLISTEND       = 235,
    // 236-239 not defined by RFC.
    CIRC_RPL_STATSVLINE        = 240,
    CIRC_RPL_STATSLLINE        = 241,
    CIRC_RPL_STATSUPTIME       = 242,
    CIRC_RPL_STATSOLINE        = 243,
    CIRC_RPL_STATSHLINE        = 244,
    // 245 not defined by RFC.
    CIRC_RPL_STATSPING         = 246,
    CIRC_RPL_STATSBLINE        = 247,
    // 248-249 not defined by RFC.
    CIRC_RPL_STATSDLINE        = 250,
    CIRC_RPL_LUSERCLIENT       = 251,
    CIRC_RPL_LUSEROP           = 252,
    CIRC_RPL_LUSERUNKNOWN      = 253,
    CIRC_RPL_LUSERCHANNELS     = 254,
    CIRC_RPL_LUSERME           = 255,
    CIRC_RPL_ADMINME           = 256,
    CIRC_RPL_ADMINLOC1         = 257,
    CIRC_RPL_ADMINLOC2         = 258,
    CIRC_RPL_ADMINEMAIL        = 259,
    // 260 not defined by RFC.
    CIRC_RPL_TRACELOG          = 261,
    CIRC_RPL_TRACEEND          = 262,
    CIRC_RPL_TRYAGAIN          = 263,
    // 264-299 not defined by RFC.
    CIRC_RPL_NONE              = 300,
    CIRC_RPL_AWAY              = 301,
    CIRC_RPL_USERHOST          = 302,
    CIRC_RPL_ISON              = 303,
    CIRC_RPL_UNAWAY            = 305,
    CIRC_RPL_NOWAWAY           = 306,
    // 307-310 not defined by RFC.
    CIRC_RPL_WHOISUSER         = 311,
    CIRC_RPL_WHOISSERVER       = 312,
    CIRC_RPL_WHOISOPERATOR     = 313,
    CIRC_RPL_WHOWASUSER        = 314,
    CIRC_RPL_ENDOFWHO          = 315,
    CIRC_RPL_WHOISCHANOP       = 316,
    CIRC_RPL_WHOISIDLE         = 317,
    CIRC_RPL_ENDOFWHOIS        = 318,
    CIRC_RPL_WHOISCHANNELS     = 319,
    // 320 not defined by RFC.
    CIRC_RPL_LISTSTART         = 321,
    CIRC_RPL_LIST              = 322,
    CIRC_RPL_LISTEND           = 323,
    CIRC_RPL_CHANNELMODEIS     = 324,
    // 325-330 not defined by RFC.
    CIRC_RPL_NOTOPIC           = 331,
    CIRC_RPL_TOPIC             = 332,
    // 333-340 not defined by RFC.
    CIRC_RPL_INVITING          = 341,
    CIRC_RPL_SUMMONING         = 342,
    // 343-345 not defined by RFC.
    CIRC_RPL_INVITELIST        = 346,
    CIRC_RPL_ENDOFINVITELIST   = 347,
    CIRC_RPL_EXCEPTLIST        = 348,
    CIRC_RPL_ENDOFEXCEPTLIST   = 349,
    // 350 not defined by RFC.
    CIRC_RPL_VERSION           = 351,
    CIRC_RPL_WHOREPLY          = 352,
    CIRC_RPL_NAMEREPLY         = 353,
    // 354-360 not defined by RFC.
    CIRC_RPL_KILLDONE          = 361,
    CIRC_RPL_CLOSING           = 362,
    CIRC_RPL_CLOSEEND          = 363,
    CIRC_RPL_LINKS             = 364,
    CIRC_RPL_ENDOFLINKS        = 365,
    CIRC_RPL_ENDOFNAMES        = 366,
    CIRC_RPL_BANLIST           = 367,
    CIRC_RPL_ENDOFBANLIS       = 368,
    CIRC_RPL_ENDOFWHOWAS       = 369,
    // 370 not defined by RFC.
    CIRC_RPL_INFO              = 371,
    CIRC_RPL_MOTD              = 372,
    CIRC_RPL_INFOSTART         = 373,
    CIRC_RPL_ENDOFINFO         = 374,
    CIRC_RPL_MOTDSTART         = 375,
    CIRC_RPL_ENDOFMOTD         = 376,
    // 377-380 not defined by RFC.
    CIRC_RPL_YOUREOPER         = 381,
    CIRC_RPL_REHASHING         = 382,
    CIRC_RPL_YOURESERVICE      = 383,
    CIRC_RPL_MYPORTIS          = 384,
    // 385-390 not defined by RFC.
    CIRC_RPL_TIME              = 391,
    CIRC_RPL_USERSTART         = 392,
    CIRC_RPL_USERS             = 393,
    CIRC_RPL_ENDOFUSERS        = 394,
    CIRC_RPL_NOUSERS           = 395,
    // 396-400 not defined by RFC.
    CIRC_ERR_NOSUCHNICK        = 401,
    CIRC_ERR_NOSUCHSERVER      = 402,
    CIRC_ERR_NOSUCHCHANNEL     = 403,
    CIRC_ERR_CANNOTSENDTOCHANNEL   = 404,
    CIRC_ERR_TOOMANCHANNELS    = 405,
    CIRC_ERR_WASNOSUCHNICK     = 406,
    CIRC_ERR_TOOMANYTARGETS    = 407,
    CIRC_ERR_NOSUCHSERVICE     = 408,
    CIRC_ERR_NOORIGIN          = 409,
    // 410 not defined by RFC.
    CIRC_ERR_NORECIPIENT       = 411,
    CIRC_ERR_NOTEXTTOSEND      = 412,
    CIRC_ERR_NOTOPLEVEL        = 413,
    CIRC_ERR_WILDTOPLEVEL      = 414,
    CIRC_ERR_BADMASK           = 415,
    // 416-421 not defined by RFC.
    CIRC_ERR_UNKNOWNCOMMAND    = 421,
    CIRC_ERR_NOMOTD            = 422,
    CIRC_ERR_NOADMININFO       = 423,
    CIRC_ERR_FILEERROR         = 424,
    CIRC_ERR_NOOPERMOTD        = 425,
    // 426-430 not defined by RFC.
    CIRC_ERR_NONICKNAMEGIVEN   = 431,
    CIRC_ERR_ERRONEOUSNICKNAME = 432,
    CIRC_ERR_NICKNAMEINUSE     = 433,
    // 434-435 not defined by RFC.
    CIRC_ERR_NICKCOLLISION     = 436,
    CIRC_ERR_UNAVAILRESOURCE   = 437,
    // 438-440 not defined by RFC.
    CIRC_ERR_USERNOTINCHANNEL  = 441,
    CIRC_ERR_NOTONCHANNEL      = 442,
    CIRC_ERR_USERONCHANNEL     = 443,
    CIRC_ERR_NOLOGIN           = 444,
    CIRC_ERR_SUMMONDISABLED    = 445,
    CIRC_ERR_USERDISABLED      = 446,
    // 447-450 not defined by RFC.
    CIRC_ERR_NOTREGISTERED     = 451,
    // 452-460 not defined by RFC.
    CIRC_ERR_NEEDMOREPARAMS    = 461,
    CIRC_ERR_ALREADYREGISTERED = 462,
    CIRC_ERR_NOPERMFORHOST     = 463,
    CIRC_ERR_PASSWDMISMATCH    = 464,
    CIRC_ERR_YOUREBANNEDCREEP  = 465, // This name is actually from the RFC.
    CIRC_ERR_YOUWILLBEBANNED   = 466,
    CIRC_ERR_KEYSET            = 467,
    // 468-470 not defined by RFC.
    CIRC_ERR_CHANNELISFULL     = 471,
    CIRC_ERR_UNKNOWNMODE       = 472,
    CIRC_ERR_INVITEONLYCHAN    = 473,
    CIRC_ERR_BANNEDFROMCHAN    = 474,
    CIRC_ERR_BADCHANNELKEY     = 475,
    CIRC_ERR_BADCHANMASK       = 476,
    CIRC_ERR_NOCHANMODES       = 477,
    CIRC_ERR_BANLISTFULL       = 478,
    // 479-480 not defined by RFC.
    CIRC_ERR_NOPRIVILEGES      = 481,
    CIRC_ERR_CHANOPRIVSNEEDED  = 482,
    CIRC_ERR_CANTKILLSERVER    = 483,
    CIRC_ERR_RESTRICTED        = 484,
    CIRC_ERR_UNIQOPRIVSNEEDED  = 485,
    // 486-490 not defined by RFC.
    CIRC_ERR_NOOPER_HOSTED     = 491,
    // 492-501 not defined by RFC.
    CIRC_ERR_USERSDONTMATCH    = 502,
    // 503-669 not defined by RFC.

    /*   ==== Start IRCv3 ==== */

    CIRC_RPL_STARTTLS          = 670, // IRCv3.
    // 671-690 not defined by RFC.
    CIRC_ERR_STARTTLS          = 691, // IRCv3.
    // 692-759 not defined by RFC.
    CIRC_RPL_WHOISKEYVALUE     = 760,
    CIRC_RPL_KEYVALUE          = 761,
    CIRC_RPL_METADATAEND       = 762,
    // 763 not defined by RFC.
    CIRC_ERR_METADATALIMIT     = 764,
    CIRC_ERR_TARGETINVALID     = 765,
    CIRC_ERR_NOMATCHINGKEY     = 766,
    CIRC_ERR_KEYINVALID        = 767,
    CIRC_ERR_KEYNOTSET         = 768,
    CIRC_ERR_KEYNOPERMISSION   = 769,

    /* ==== End   IRCv3 ==== */

    // 770-999 not defined by RFC.

    // These aren't actual numerics, so add 0xF000 to avoid conflicts.
    CIRC_UNKNOWN    = 0xF000,
    CIRC_CAP        = 0xF001,
    CIRC_CAP_END    = 0xF002,
    CIRC_INVITE     = 0xF003,
    CIRC_JOIN       = 0xF004,
    CIRC_KICK       = 0xF005,
    CIRC_LUSERS     = 0xF006,
    CIRC_MODE       = 0xF007,
    CIRC_NICK       = 0xF008,
    CIRC_PART       = 0xF009,
    CIRC_PING       = 0xF00A,
    CIRC_PONG       = 0xF00B,
    CIRC_PRIVMSG    = 0xF00C,
    CIRC_QUIT       = 0xF00D,
    CIRC_SASL       = 0xF00E,
    CIRC_TOPIC      = 0xF00F,
    CIRC_USER       = 0xF010,
};

typedef bool (CIrcRecvCallback)(CIrcClient *client, char *recipient,
        char *sender, char *message);

bool circ_send_raw(CIrcClient *client, char *message);
bool circ_send(CIrcClient *client, char *recipient, char *message);
bool circ_recv_raw(CIrcClient *client, char *message);
bool circ_recv(CIrcClient *client, char *sender, char *recipient,
        char *message);

bool circ_register_recv_callback(CIrcClient *client,
        CIrcRecvCallback *callback);


bool circ_connect(CIrcClient *client);
bool circ_change_nick(CIrcClient *client, char *new_nick);
bool circ_join(CIrcClient *client, char *channel);
bool circ_part(CIrcClient *client, char *channel, char *message);
bool circ_privmsg(CIrcClient *client, char *recipient, char *message);

#endif
