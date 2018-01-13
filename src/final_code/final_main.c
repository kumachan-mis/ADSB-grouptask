#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "alignment.h"

#define maxTlen 105000
#define Snum 20000
#define Slen 25
#define BITAP_LEN 30
#define PART_LEN 50

#define BITAP_D 3
#define GAP 6

int score(char a, char b)
{
    return (a == b) ? 4 : -3;
}

int main()
{
    list *T = make_new_list();
    char Tstring[maxTlen + 1];
    list *S = make_new_list();
    char Sstring[Slen + 1];
    int bitap_ret[BITAP_LEN] = {};

    scanf("%s", Tstring);
    T = insert_data(T, Tstring, -1);
    int i;
    for (i = 0; i < Snum; i++)
    {
        scanf("%s", Sstring);

        if (i == 0)
        {
            S = insert_data(S, Sstring, -1);
            S->length = 20;
        }
        else
        {
            S = replace_data(S, Sstring, 0);
        }

        int j;
        for (j = 0; j < BITAP_LEN; j++)
        {
            bitap_ret[j] = -1;
        }

        bitap(S, T, BITAP_D, bitap_ret, BITAP_LEN);

        node *p = T->head;
        list *part = make_new_list();
        part->length = PART_LEN;

        for (j = 0; j < BITAP_LEN; j++)
        {
            if (p == NULL || n_node(p, PART_LEN) == NULL || bitap_ret[j] == -1)
            {
                break;
            }

            if (j == 0 && T->length - bitap_ret[j] > PART_LEN && bitap_ret[j] >= 0)
            {
                p = n_node(p, bitap_ret[j]);
                part->head = p;
                SW_alignment(S, part, score, GAP);
            }
            else if (bitap_ret[j] != bitap_ret[j - 1] && T->length - bitap_ret[j] > PART_LEN && bitap_ret[j] >= 0)
            {
                p = n_node(p, bitap_ret[j] - bitap_ret[j - 1]);
                part->head = p;
                SW_alignment(S, part, score, GAP);
            }
        }

        free(part);
    }

    node *p = T->head;
    list *part = make_new_list();

    for (i = 0; i < T->length; i++)
    {
        part->head = p;
        int j;

        /*
        for(j = 0; j < 7; j++){
            printf("%2d ",p ->abc_del[j]);
        }
         printf("\n");// 投票結果を表示
         */

        //最終的な編集(ここから)
        for (j = 0; j < 3; j++)
        {
            if (p->abc_del[j] > p->abc_del[(1 + j) % 3] + p->abc_del[(2 + j) % 3])
            {
                char c[] = {'a' + j};
                insert_data(part, c, 0);
            } //置換
            if (p->abc_del[j] > p->abc_del[(1 + j) % 3 + 3] + p->abc_del[(2 + j) % 3 + 3] + p->abc_del[6])
            {
                node *newnode = make_new_node('a' + j, p->next);
                p->next = newnode;
            } //挿入
        }

        if (p->abc_del[6] > p->abc_del[3] + p->abc_del[4] + p->abc_del[5])
        {
            delete_data(part, 0, 2);
        } //削除
        //最終的な編集(ここまで)

        p = p->next;
        if (p == NULL)
        {
            break;
        }
    }

    show(T);
    return 0;
}