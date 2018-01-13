#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

node *make_new_node(char data, node *after)
{
    node *newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = after;
    return newnode;
} //dataを情報としてもつnewnodeは次としてafterへのポインタを持つ. newnodeへのポインタを返す.

list *make_new_list()
{
    list *newlist = malloc(sizeof(list));
    newlist->head = NULL;
    newlist->length = 0;
    return newlist;
} //新しいリンクリストを作成し, length = 0を設定. 新しいリンクリストへのポインタを返す.

node *n_node(node *lookedNode, int n)
{
    if (lookedNode == NULL)
    {
        return NULL;
    }
    else if (n == 0)
    {
        return lookedNode;
    }
    else
    {
        return n_node(lookedNode->next, n - 1); //１つ先のノードの n - 1番目になる.
    }
} //n番目のノードへのポインタを返す.

char n_data(list *linkedlist, int n)
{
    node *nth = n_node(linkedlist->head, n); //n番目のノードへのポインタを探す.

    if (nth == NULL)
    {
        return '\0'; //n番目のノードがなければ例外的に終端文字を返す.
    }
    else
    {
        return nth->data;
    }
} //n番目のノードに格納されたデータを返す.

list *joint_list_n(list *inserted, list *linkedlist, int n)
{
    if (linkedlist->length != 0)
    {
        if (n == -1)
        {

            n_node(linkedlist->head, linkedlist->length - 1)->next = inserted->head; //挿入するものの次は挿入される方の先頭
            inserted->head = linkedlist->head;                                       //先頭の書き換え

        } //先頭への挿入
        else
        {

            node *nth = n_node(inserted->head, n); //n番目のノードへのポインタを探す.
            if (nth != NULL)
            {

                node *np1th = nth->next;                                        //n + 1番目を見る
                nth->next = linkedlist->head;                                   //n番目の次は挿入するもののはじめ
                n_node(linkedlist->head, linkedlist->length - 1)->next = np1th; //挿入するもののの次はn + 1番目
            }
        }
    }
    inserted->length += linkedlist->length;
    return inserted;

} //insertedのn番目の後にlinkedlistをつなげ, linkedlistの続きからinsertedのn + 1番目を続ける. 先頭に結合したい場合は n = -1.

list *insert_data(list *inserted, char data[], int n)
{
    list *linkedlist = make_new_list(); //data[]だけを要素にもつlinkedlist
    linkedlist->length = strlen(data);
    node *temp = linkedlist->head;
    int i = 0;

    for (i = linkedlist->length - 1; i >= 0; i--)
    {
        temp = make_new_node(data[i], temp);
    } //nodeたちをどんどんつなげていって

    linkedlist->head = temp; //先頭をlinkedlistに
    return joint_list_n(inserted, linkedlist, n);
} //insertedのn番目とn+1番目の間にdata[]を要素に持つリンクリストを挿入

list *delete_data(list *linkedlist, int a, int b)
{
    node *temp = n_node(linkedlist->head, a)->next;                  //a番目から先
    n_node(linkedlist->head, a)->next = n_node(linkedlist->head, b); //a番目のノードの次をb番目に
    free(temp);                                                      //元のa番目から先を削除
    linkedlist->length -= (b - a - 1);
    return linkedlist;

} //a番目のノードの次をb番目にするように間を削除

list *replace_data(list *linkedlist, char data[], int n)
{
    node *temp = n_node(linkedlist->head, n);
    int i = 0;
    for (i = 0; i < strlen(data); i++)
    {
        temp->data = data[i];
        temp = temp->next;
    }
    return linkedlist;
} //linkedlistのn番目からn + strlen(data) - 1までをdataに置き換え

int check(node *a, node *b, int x, int y, int d)
{
    if (d == 0 || d - ((x - y) > 0 ? x - y : y - x) <= 0)
        return 0;

    node *temp1 = a, *temp2 = b;
    while (x > 0 && y > 0 && temp1->data == temp2->data)
    {
        temp1 = temp1->next;
        temp2 = temp2->next;
        x--;
        y--;
    }
    if (x == 0 || y == 0 || check(temp1->next, temp2->next, x - 1, y - 1, d - 1) || check(temp1, temp2->next, x, y - 1, d - 1) || check(temp1->next, temp2, x - 1, y, d - 1))
        return 1;
    else
        return 0;
} //しらすくんの編集距離part2書き換え

int edit_distance(list *linkedlist1, list *linkedlist2, int d)
{
    return check(linkedlist1->head, linkedlist2->head, linkedlist1->length, linkedlist2->length, d);
}

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

int DP_matrix(node *node1, node *node2, unsigned long len1, unsigned long len2, DP F[len1 + 1][len2 + 1], int p, int q, int (*score)(char, char), int gap)
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

list *alignment(list *list1, list *list2, unsigned long len1, unsigned long len2, int (*score)(char, char), int gap)
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
            node1 = node1->next; //更新
            node2 = node2->next; //更新
            p--;
            q--; //更新
        }
        else if (F[p][q].to == 'l')
        {                                                            //左への移動
            node *newnode = make_new_node(node2->data, node1->next); //ギャップ部を埋めるノードを作って
            node1->next = newnode;                                   //つなぎ合わせ
            node1 = node1->next;                                     //更新(newnodeを挿入した分移動しなければいけない)
            node2 = node2->next;                                     //更新
            q--;                                                     //更新
        }
        else if (F[p][q].to == 'u')
        {                        //上への移動
            node1 = node1->next; //更新
            p--;                 //更新
        }
    } //アラインメントに従ってgap部をつなぎ合わせ
    return list1;
}

list *SW_alignment(list *list1, list *list2, int (*score)(char, char), int gap)
{
    int len1 = list1->length, len2 = list2->length;

    if (len1 > len2)
    {
        return alignment(list1, list2, len1, len2, score, (gap > 0) ? gap : -gap);
    }
    else if (len2 > len1)
    {
        return alignment(list2, list1, len2, len1, score, (gap > 0) ? gap : -gap);
    }
    else
    {
        return NULL;
    } //call_alignmentではlen1 > len2かつgap > 0なるように
}

void showR(node *showed)
{
    if (showed != NULL)
    {
        printf("%c", showed->data);
        showR(showed->next);
    }
} //showed以降の表示

void show(list *linkedlist)
{
    showR(linkedlist->head);
    printf("\n");
} //linkedlistのデータの表示