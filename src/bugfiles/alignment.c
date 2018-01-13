#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "alignment.h"
typedef struct
{
    int score;
    char to;
} DP;

DP max(int a, int b, int c)
{
    DP a_d, b_d, c_d;

    a_d.score = a, b_d.score = b, c_d.score = c;
    a_d.to = 'd', b_d.to = 'l', c_d.to = 'u';

    return (b > c) ? ((a > b) ? a_d : b_d)
                   : ((a > c) ? a_d : c_d);
} //a斜め移動, b左移動, c上移動のうち最もスコアが高いものを返すと同時に移動法を設定

int DP_matrix(node *node1, node *node2, int len1, int len2, DP F[len1 + 1][len2 + 1], int p, int q, int (*score)(char, char), int gap)
{
    if (F[p][q].score != INT16_MIN)
    {
        return F[p][q].score; //メモ化
    }
    else if (p == 0 && q == 0)
    {
        return (F[p][q].score = 0);
    }
    else if (p == 0 && q > 0)
    {
        F[p][q].to = 'l';
        return (F[p][q].score = 0);
    } //oDP行列の上側
    else if (p > 0 && q == 0)
    {
        F[p][q].to = 'u';
        return (F[p][q].score = 0);
    } //DP行列の左端
    else
    {
        int a = DP_matrix(node1->next, node2->next, len1, len2, F, p - 1, q - 1, score, gap) + score(node1->data, node2->data); //斜めへの移動
        int b = DP_matrix(node1, node2->next, len1, len2, F, p, q - 1, score, gap) - gap;                                       //左への移動
        int c = DP_matrix(node1->next, node2, len1, len2, F, p - 1, q, score, gap) - gap;                                       //上への移動

        F[p][q] = max(a, b, c); //スコアが最大のものを選ぶ
        return F[p][q].score;
    }
}

void alignment(list *list1, list *list2, int len1, int len2, int (*score)(char, char), int gap)
{ //len1 > len2を前提
    DP F[len1 + 1][len2 + 1];
    int p, q;
    for (p = 0; p < len1 + 1; p++)
    {
        for (q = 0; q < len2 + 1; q++)
        {
            F[p][q].score = INT16_MIN;
            F[p][q].to = 'n';
        }
    } //初期化

    DP_matrix(list1->head, list2->head, len1, len2, F, len1, len2, score, gap); //アラインメント

    int min = INT32_MAX;
    int index = 0;
    q = len2;

    for (p = len2 + 1; p < len1 + 1; p++)
    {
        if (F[p][q].score < min)
        {
            min = F[p][q].score;
            index = p;
        }
    } //len2文字目以降でスコアが一番小さいところを探す

    p = index;
    node *node1 = list1->head, *node2 = list2->head;
    
    while (p != 0 || q != 0)
    {
        if (F[p][q].to == 'd')
        {                        //斜めの移動
            if(node1 != NULL && node2 != NULL){
                node1->abc_del[node2->data - 'a']++;
                node1 = node1->next; //更新
                node2 = node2->next; //更新
            }
            p--;
            q--; //更新
        }
        else if (F[p][q].to == 'l')
        {                        //左への移動
            if(node1 != NULL && node2 != NULL){
                node1->abc_del[node2->data - 'a' + 3]++;
                node2 = node2->next; //更新
            }
            q--; //更新
        }
        else if (F[p][q].to == 'u')
        {                        //上への移動
            if (node1 != NULL && q != 0)
            {
                node1->abc_del[6]++;
                node1 = node1->next; //更新
            }
            p--; //更新
        }

    }
}

void SW_alignment(list *list1, list *list2, int (*score)(char, char), int gap)
{
    int len1 = list1->length, len2 = list2->length;
    if (len1 > len2)
    {
        alignment(list1, list2, len1, len2, score, (gap > 0) ? gap : -gap);
    }
    else if (len2 > len1)
    {
        alignment(list2, list1, len2, len1, score, (gap > 0) ? gap : -gap);
    }
}

void bitap_main(list *list1, list *list2, int len1, int len2, int d, int ret[], int len)
{ //len1 > len2を前提
    unsigned long mask[3] = {};
    unsigned long state[d + 1], saved_state[d + 1];
    unsigned long finish = 1 << (len2 - 1);
    int a, b;

    for (a = 0; a < d + 1; a++)
    {
        state[a] = (1 << a) - 1;
        saved_state[d + 1] = 0;
    }

    node *current_node = list2->head;
    for (a = 0; a < len2; a++)
    {
        for (b = 0; b < 3; b++)
        {
            mask[b] >>= 1;
        }
        mask[current_node->data - 'a'] |= finish;
        current_node = current_node->next;
    }

    current_node = list1->head;
    int index = 0;

    for (a = 0; a < len1; a++)
    {
        for (b = 0; b < d + 1; b++)
        {
            state[b] = (state[b] << 1) | 1;
            saved_state[b] = state[b] | state[b] << 1 | state[b] >> 1;
            state[b] &= mask[current_node->data - 'a'];
        }

        for (b = 1; b < d + 1; b++)
        {
            state[b] |= saved_state[b - 1];
        }

        for (b = 0; b < d + 1; b++)
        {
            if (state[b] >= finish)
            {
                ret[index] = a - len2 + 1;
                index++;

                if (index >= len)
                {
                    break;
                }
            }
        }
        if (index >= len)
        {
            break;
        }
        current_node = current_node->next;
    }
}

void bitap(list *list1, list *list2, int d, int ret[], int len)
{
    int len1 = list1->length, len2 = list2->length;

    if (len1 > len2)
    {
        bitap_main(list1, list2, len1, len2, d, ret, len);
    }
    else if (len2 > len1)
    {
        bitap_main(list2, list1, len2, len1, d, ret, len);
    }
}