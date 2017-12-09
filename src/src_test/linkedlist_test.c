#include "linkedlist.h"
#include <stdio.h>
int main(){
    list * linkedlist = make_new_list();

    linkedlist = insert_data(linkedlist, "F**kin'da", -1);//cleared
    printf("%c\n", n_data(linkedlist, 3));//cleared
    show(linkedlist);
    printf("%d\n", linkedlist -> length);

    linkedlist = replace_data(linkedlist, "u", 1);//cleared
    printf("%c\n", n_data(linkedlist, 3));//cleared
    show(linkedlist);
    printf("%d\n", linkedlist -> length);

    linkedlist = insert_data(linkedlist, "Wase", 6);//cleared
    printf("%c\n", n_data(linkedlist, 3));//cleared
    show(linkedlist);
    printf("%d\n", linkedlist -> length);

    linkedlist = delete_data(linkedlist, 1, 5);//cleared
    printf("%c\n", n_data(linkedlist, 3));//cleared
    show(linkedlist);
    printf("%d\n", linkedlist -> length);

    linkedlist = insert_data(linkedlist, "Univ. ", 3);//cleared
    printf("%c\n", n_data(linkedlist, 3));//cleared
    show(linkedlist);
    printf("%d\n", linkedlist -> length);
    return 0;
}