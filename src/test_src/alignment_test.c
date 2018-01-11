#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

int score(char a, char b);

int main(){
    list * list1 = make_new_list(), * list2 = make_new_list();;
    list1 = insert_data(list1, "bbaabcb", -1);
    list2 = insert_data(list2, "bcbcbbabcbaabb", -1);
    show(list1);
    show(list2);
    list1= SW_alignment(list1, list2, score, -2);
    show(list1);
}

int score(char a, char b){
    return (a == b) ? 5 : -5;
}