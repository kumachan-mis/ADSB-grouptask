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

#define BITAP_D 4
int MATCH, MISS, GAP;

int score(char a, char b)
{
    return (a == b) ? MATCH : -MISS;
}

int max_int2(int a, int b){
    return (a > b) ? a : b;
}

int max_int3(int a, int b, int c){
    return (b > c) ? ((a > b) ? a : b)
                   : ((a > c) ? a : c);
}

int main(int argc, char *argv[])
{
    list *T = make_new_list();
    char Tstring[maxTlen + 1];
    list *S = make_new_list();
    char Sstring[Slen + 1];
    int bitap_ret[BITAP_LEN] = {};
    if (argc != 4) {
      fprintf(stderr, "Usage: ./a.out (MATCH) (MISS) (GAP) < dat*_in > dat*_out\nAll of 3 numbers are zero or more, integer.\n");
      exit(EXIT_FAILURE);
    }
    MATCH = atoi(argv[1]), MISS = atoi(argv[2]), GAP = atoi(argv[3]);
    
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
                alignment(S, part, score, GAP);
            }
            else if (bitap_ret[j] != bitap_ret[j - 1] && T->length - bitap_ret[j] > PART_LEN && bitap_ret[j] >= 0)
            {
                p = n_node(p, bitap_ret[j] - bitap_ret[j - 1]);
                part->head = p;
                alignment(S, part, score, GAP);
            }
        }

        free(part);
    }

    node *p = T->head;
    node *pre = NULL;
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
            if (p->abc_del[j] > max_int2(p->abc_del[(1 + j) % 3], p->abc_del[(2 + j) % 3]))
            {
                char c[] = {'a' + j};
                replace_data(part, c, 0);
            } //置換
            if (p->abc_del[j % 3 + 3] > max_int2(p->abc_del[(1 + j) % 3 + 3], p->abc_del[(2 + j) % 3 + 3])
            && p->abc_del[j % 3 + 3] > max_int3(p->abc_del[0], p->abc_del[1], p->abc_del[2]))
            {
                char c[] = {'a' + j};
                insert_data(part, c, 0);
                p = p->next;
            } //挿入
        }

        if (p->abc_del[6] > max_int3(p->abc_del[0], p->abc_del[1], p->abc_del[2]))
        {
            if(pre == NULL)
            {
                T->head = T->head->next;
            }
            else{
                pre->next = p->next;
            }

            T->length--;
        } //削除
        //最終的な編集(ここまで)
        pre = p;
        p = p->next;
        if (p == NULL)
        {
            break;
        }
    }

    show(T);
    printf("%d\n", T->length);
    return 0;
}
