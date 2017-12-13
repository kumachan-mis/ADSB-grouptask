#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

node * make_new_node(char data, node * after)
{
    node * newnode = malloc(sizeof(node));
    newnode -> data = data;
    newnode -> next = after;
    return newnode;
}//dataを情報としてもつnewnodeは次としてafterへのポインタを持つ. newnodeへのポインタを返す.

list * make_new_list()
{
    list * newlist = malloc(sizeof(list));
    newlist -> head = NULL;
    newlist -> length = 0;
    return newlist;
}//新しいリンクリストを作成し, length = 0を設定. 新しいリンクリストへのポインタを返す.

node * n_node(node * lookedNode, int n)
{
    if(lookedNode == NULL){
        return NULL;
    }
    else if(n == 0){
        return lookedNode;
    }
    else{
        return n_node(lookedNode -> next, n - 1);//１つ先のノードの n - 1番目になる.
    }
}//n番目のノードへのポインタを返す.

char n_data(list * linkedlist, int n)
{
    node * nth = n_node(linkedlist -> head, n);//n番目のノードへのポインタを探す.

    if(nth == NULL){
        return '\0';//n番目のノードがなければ例外的に終端文字を返す.
    }else{
        return nth -> data;
    }
}//n番目のノードに格納されたデータを返す.

list * joint_list_n(list * inserted, list * linkedlist, int n)
{
    if(linkedlist -> length != 0){
        if(n == -1){

             n_node(linkedlist -> head, linkedlist -> length - 1) -> next = inserted -> head;//挿入するものの次は挿入される方の先頭
             inserted -> head = linkedlist -> head;//先頭の書き換え

        }//先頭への挿入
        else{ 
            
            node * nth = n_node(inserted -> head, n);//n番目のノードへのポインタを探す.
            if(nth != NULL){

                node * np1th = nth ->next;//n + 1番目を見る
                nth ->next = linkedlist -> head;//n番目の次は挿入するもののはじめ
                n_node(linkedlist -> head, linkedlist -> length - 1) -> next = np1th;//挿入するもののの次はn + 1番目
            }
        }
    }
    inserted ->length += linkedlist ->length;
    return inserted;

}//insertedのn番目の後にlinkedlistをつなげ, linkedlistの続きからinsertedのn + 1番目を続ける. 先頭に結合したい場合は n = -1.

list * insert_data(list * inserted, char data[], int n)
{
    list * linkedlist = make_new_list();//data[]だけを要素にもつlinkedlist
    linkedlist -> length = strlen(data);
    node * temp = linkedlist -> head;
    int i = 0;

    for(i = linkedlist -> length - 1; i >= 0; i--){
        temp = make_new_node(data[i], temp);
    }//nodeたちをどんどんつなげていって

    linkedlist -> head = temp;//先頭をlinkedlistに
    return joint_list_n(inserted, linkedlist, n);
}//insertedのn番目とn+1番目の間にdata[]を要素に持つリンクリストを挿入

list *  delete_data(list * linkedlist, int a, int b)
{
    node * temp = n_node(linkedlist -> head, a) -> next;//a番目から先
    n_node(linkedlist -> head, a) -> next =  n_node(linkedlist -> head, b);//a番目のノードの次をb番目に
    free(temp);//元のa番目から先を削除
    linkedlist ->length -= (b - a - 1);
    return linkedlist;

}//a番目のノードの次をb番目にするように間を削除

list * replace_data(list * linkedlist, char data[], int n)
{
     node * temp = n_node(linkedlist -> head, n);
     int i = 0;
     for(i = 0; i < strlen(data); i++){
         temp -> data = data[i];
         temp = temp -> next;
     }
     return linkedlist;
}//linkedlistのn番目からn + strlen(data) - 1までをdataに置き換え

int check(node * a, node * b, int x, int y, int d)
{
    if(d == 0 || d - ((x - y) > 0 ? x - y : y - x) <= 0) return 0;

    node * temp1 = a, * temp2 = b;
    while(x > 0 && y > 0 && temp1 -> data == temp2 -> data) {
        temp1 = temp1 -> next; temp2 = temp2 -> next;
        x--; y--;
    }
    if(x == 0 || y == 0 
    || check(temp1 -> next, temp2 -> next, x - 1, y - 1, d - 1) 
    || check(temp1, temp2 -> next, x, y - 1, d - 1) 
    || check(temp1 -> next, temp2, x - 1, y, d - 1)) return 1;
    else return 0;
}//しらすくんの編集距離part2書き換え

int edit_distance(list * linkedlist1, list * linkedlist2, int d)
{
    return check(linkedlist1 -> head, linkedlist2 -> head,linkedlist1 -> length, linkedlist2 -> length, d);
}

void showR(node * showed){
    if(showed != NULL){
        printf("%c",showed -> data);
        showR(showed -> next);
    }
}//showed以降の表示

void show(list * linkedlist){
    showR(linkedlist -> head);
    printf("\n");
}//linkedlistのデータの表示
