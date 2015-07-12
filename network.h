#include <sys/socket.h>
#include <arpa/inet.h>

#define SOCKET_ERROR -1
#define DEFAULT_LISTEN_BACKLOG 5 // listenする際の標準の受入数

typedef int SOCKET;
