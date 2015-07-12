#include <stdio.h>
#include <stdlib.h>

#include "network.h"
#include "janken.h"

/**
 * サーバーに接続する
 */
SOCKET connect_server(const char* ip_addr, unsigned short server_port)
{
    int result;
    struct sockaddr_in addr;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(server_port);
    addr.sin_addr.s_addr = inet_addr(ip_addr);

    // サーバーに接続
    result = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (result == SOCKET_ERROR) {
        perror("connect");
        exit(1);
    }
    return sock;
}

/**
 * ゲーム番号を選ぶ
 */
void choose_game(SOCKET sock)
{
    int game_number;

    printf("ゲーム番号を入力: ");
    scanf("%d", &game_number);
    send(sock, (char*)&game_number, sizeof(game_number), 0);
}

int main(void)
{
    SOCKET sock;

    // 相手につなぐ
    sock = connect_server("127.0.0.1", 10800);

    // ゲームを選ぶ
    // choose_game(sock);

    // じゃんけん開始
    janken(sock);

    // おわり．
    return 0;
}
