#include <stdio.h>

#include "network.h"
#include "janken.h"

/**
 * ソケットに指定されたポート番号をBINDする
 */
void bind_socket(int socket, unsigned short port)
{
    int result;
    struct sockaddr_in server_address;
    int server_address_length;
    int socket_option_flag = 1;

    // BINDする受け入れアドレスを設定する
    server_address.sin_family = AF_INET;
    // INADDR_ANY はすべての外部接続を受け入れるアドレス指定
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);
    server_address_length = sizeof(server_address);

    // サーバーをすぐに再起動してもポート番号を再利用可能にする
    result = setsockopt(
            socket,
            SOL_SOCKET,
            SO_REUSEADDR,
            &socket_option_flag,
            sizeof(socket_option_flag));
    if (result == SOCKET_ERROR) {
        error("setsockopt");
    }

    // bindを実行
    result = bind(socket, (struct sockaddr*)&server_address, server_address_length);
    if (result == SOCKET_ERROR) {
        error("bind");
    }
}

SOCKET start_server(port){
    SOCKET server_socket;
    int result;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    bind_socket(server_socket, port);
    printf("bind to port: %d ok.\n", port);

    result = listen(server_socket, DEFAULT_LISTEN_BACKLOG);
    if (result == SOCKET_ERROR) {
        close(server_socket);
        error("listen");
    };
    return server_socket;
}

SOCKET accept_enemy(SOCKET server_sock)
{
    struct sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);
    return accept(server_sock, (struct sockaddr*)&addr, &addr_len);
}

int main(void)
{
    SOCKET server_sock = start_server(10800);
    SOCKET sock = accept_enemy(server_sock);
    close(server_sock);

    // じゃんけん開始
    janken(sock);
}
