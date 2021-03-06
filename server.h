/*
 * server.h: header for server.c 
 *
 * Written By Michael Sandrof
 *
 * Copyright(c) 1990 
 *
 * See the COPYRIGHT file, or do a HELP IRCII COPYRIGHT 
 *
 * @(#)$Id$
 */

#ifndef SERVER_H
#define SERVER_H

/* for struct channel */
#include "names.h"
#include "whois.h"
#include "sa.h"

#define SPLIT 1

#define SERVER_BUF_LEN BIG_BUFFER_SIZE

#define SERVER(i)	(server_list+i)

struct notify_stru;

/* Server: a structure for the server_list */
struct server {
    char *name;			/* the name of the server */
    char *itsname;		/* the server's idea of its name */
    char *password;		/* password for that server */
    int port;			/* port number on that server */

    char *nickname;		/* nickname for this server */
    char *s_nickname;		/* last NICK command sent */
    char *d_nickname;		/* Default nickname to use */
    int fudge_factor;		/* How much s_nickname's fudged */
    int nickname_pending;	/* Is a NICK command pending? */

    char *away;			/* away message for this server */
    time_t awaytime;
    int operator;		/* true if operator */
    char *version_string;	/* what is says */
    int whois;			/* true if server sends numeric 318 */
    int flags;			/* Various flags */
    char umode[80];		/* User Mode storage */
    int connected;		/* true if connection is assured */
    int eof;			/* eof flag for server */
    int motd;			/* motd flag (used in notice.c) */
    int lag;			/* indication of lag from server CDE */
    time_t lag_time;		/* time ping sent to server CDE */
    time_t last_msg;		/* last mesg recieved from the server CDE */
    WhoisQueue *WQ_head;	/* WHOIS Queue head */
    WhoisQueue *WQ_tail;	/* WHOIS Queue tail */
    WhoisStuff whois_stuff;	/* Whois Queue current collection buffer */
    int close_serv;		/* Server to close when we're LOGGED_IN */
    time_t ctcp_last_reply_time;	/* used to limit flooding */
    struct channel *chan_list;	/* list of channels for this server */
    int link_look;
    time_t link_look_time;
    int trace_flags;
    int stats_flags;
    struct notify_stru *notify_list;	/* Notify list */

    sa_addr_t *rem_addr;
    sa_addr_t *lcl_addr;
    sa_t *sock;

    char line[SERVER_BUF_LEN];
    int pos;
    int index;

#ifdef HAVE_SSL
    int enable_ssl;
    SSL_CTX* ctx;
    int ssl_error;
    SSL* ssl_fd;
#endif /* HAVE_SSL */
};

int find_server_group(char *, int);
char *find_server_group_name(int);
void add_to_server_list(char *, int, char *, char *, int);
void remove_from_server_list(int i);
void build_server_list(char *);
int connect_to_server(char *, int, int);
void get_connected(int);
int read_server_file(char *);
void display_server_list(void);
void do_server(fd_set *, fd_set *);
int connect_to_server_by_refnum(int, int);
int find_server_refnum(char *, char **);

int get_server_whois(int);

WhoisStuff *get_server_whois_stuff(int);
WhoisQueue *get_server_qhead(int);
WhoisQueue *get_server_qtail(int);

extern int save_chan_from;	/* to keep the channel list if all servers are lost */

/* for vhost stuff */
extern sa_addr_t *local_host_addr;
extern char *local_host_name;
extern char def_hostname[NAME_LEN + 1];

extern int number_of_servers;
extern int connected_to_server;
extern int never_connected;
extern int using_server_process;
extern int primary_server;
extern int from_server;
extern int last_server;
extern char *connect_next_nick;
extern char *connect_next_password;
extern int parsing_server_index;

void servercmd(char *, char *, char *, char *);
char *get_server_nickname(int);
char *get_server_name(int);
char *get_server_itsname(int);
void set_server_flag(int, int, int);
int find_in_server_list(char *, int);
char *create_server_list(void);
void set_server_motd(int, int);
int get_server_motd(int);
int get_server_operator(int);
void close_server(int, char *);
int is_server_connected(int);
void flush_server(void);
int get_server_flag(int, int);
void set_server_operator(int, int);
void server_is_connected(int, int);
int parse_server_index(char *);
void parse_server_info(char *, char **, char **, char **);
void set_server_bits(fd_set *, fd_set *);
void set_server_itsname(int, char *);
void set_server_version(int, int);

int is_server_open(int);
int get_server_port(int);

int get_server_lag(int);
int set_server_lag(int);

char *set_server_password(int, char *);
void set_server_nickname(int, char *);

void set_server_qhead(int, WhoisQueue *);
void set_server_qtail(int, WhoisQueue *);
void set_server_whois(int, int);
void close_all_server(void);
void disconnectcmd(char *, char *, char *, char *);
char *get_umode(int);
int server_list_size(void);
void set_server_away(int, char *);
char *get_server_away(int);

extern void register_server(int, char *);
extern char *get_pending_nickname(int);
extern void accept_server_nickname(int, char *);

/* XXXXX ick, gross, bad.  XXXXX */
void password_sendline(char *data, char *line);
extern int user_changing_nickname;

#ifdef HAVE_SSL
extern       void    set_server_ssl          (int idx, int val); 
extern       int     get_server_ssl          (int idx); 
#endif /* HAVE_SSL */


/* server_list: the list of servers that the user can connect to,etc */
extern struct server *server_list;

void send_to_server(struct server *s, const char *format, ...);
void reset_nickname(struct server *s);
void change_server_nickname(struct server *s, char *nick);
void fudge_nickname(struct server *s);
void init_hostname(void);

#define USER_MODE	0x0001
#define USER_MODE_A	USER_MODE << 0
#define USER_MODE_B	USER_MODE << 1
#define USER_MODE_C	USER_MODE << 2
#define USER_MODE_D	USER_MODE << 3
#define USER_MODE_E	USER_MODE << 4
#define USER_MODE_F	USER_MODE << 5
#define USER_MODE_G	USER_MODE << 6
#define USER_MODE_H	USER_MODE << 7
#define USER_MODE_I	USER_MODE << 8
#define USER_MODE_J	USER_MODE << 9
#define USER_MODE_K	USER_MODE << 10
#define USER_MODE_L	USER_MODE << 11
#define USER_MODE_M	USER_MODE << 12
#define USER_MODE_N	USER_MODE << 13
#define USER_MODE_O	USER_MODE << 14
#define USER_MODE_P	USER_MODE << 15
#define USER_MODE_Q	USER_MODE << 16
#define USER_MODE_R	USER_MODE << 17
#define USER_MODE_S	USER_MODE << 18
#define USER_MODE_T	USER_MODE << 19
#define USER_MODE_U	USER_MODE << 20
#define USER_MODE_V	USER_MODE << 21
#define USER_MODE_W	USER_MODE << 22
#define USER_MODE_X	USER_MODE << 23
#define USER_MODE_Y	USER_MODE << 24
#define USER_MODE_Z	USER_MODE << 25

#define LOGGED_IN	USER_MODE << 29
#define CLOSE_PENDING	USER_MODE << 30
#define CLOSING_SERVER  USER_MODE << 31
extern const char *umodes;

#endif				/* __server_h_ */
