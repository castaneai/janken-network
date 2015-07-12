#include <stdio.h>

#include "network.h"

typedef enum
{
    GOO = 1,
    CHOKI,
    PAA
} HAND;

/**
 * 自分のターン
 */
HAND choose_hand(SOCKET sock)
{
    int my_hand;

    printf("あなたの出す手は？\n");
    printf("1: グー\n2: チョキ\n3: パー\n");
    scanf("%d", &my_hand);
    send(sock, (char*)&my_hand, sizeof(my_hand), 0);
    return (HAND)my_hand;
}

/**
 * 相手のターンが終わるのを待つ
 */
HAND wait_enemy_hand(SOCKET sock)
{
    int enemy_hand;

    printf("相手側の入力を待っています\n");
    recv(sock, (char*)&enemy_hand, sizeof(enemy_hand), 0);
    printf("相手は%dでした\n", enemy_hand);
    return (HAND)enemy_hand;
}

/**
 * 勝敗判定
 * 返り値: 1 なら自分の勝ち，0ならあいこ, -1 なら負け
 */
int judge(HAND my_hand, HAND enemy_hand)
{
    if (my_hand == enemy_hand) {
        return 0;
    }

    if (my_hand == GOO && enemy_hand == CHOKI ||
        my_hand == CHOKI && enemy_hand == PAA ||
        my_hand == PAA && enemy_hand == GOO) {
        return 1;
    }
    return -1;
}


void janken(SOCKET sock, int is_my_turn_first)
{
    HAND my_hand, enemy_hand;
    int result;

    printf("じゃんけんスタート！！\n");

    while (1) {
        my_hand = choose_hand(sock);
        enemy_hand = wait_enemy_hand(sock);
        result = judge(my_hand, enemy_hand);
        if (result == 1) {
            printf("あなたの勝ち！\n");
        } else if (result == -1) {
            printf("あなたの負け・・・\n");
        } else {
            printf("あいこです\n");
        }
    }
}
