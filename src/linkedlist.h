#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
typedef struct Node{
    char data;
    struct Node	*next;
}node;//データと次のノードへのポインタを持つ

typedef struct {
  node * head;
  int length;//linkedlistの長さ. ただし, 初期状態で追加される('\0', NULL)は数えない.
} list;//最初のノードheadへのポインタ. 「「headは0番目」」のデータと見る

node * make_new_node(char data, node * after);
list * make_new_list();
node * n_node(node * lookedNood, int n);
char n_data(list * linkedlist, int n);
list * joint_list_n(list * inserted, list * linkedlist, int n);
list * insert_data(list * inserted, char data[], int n);
list *  delete_data(list * linkedlist, int a, int b);
list * replace_data(list * linkedlist, char data[], int n);
void show(list * linkedlist);
#endif