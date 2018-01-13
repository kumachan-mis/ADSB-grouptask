#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define maxTlen 105000
#define Snum    20000
#define Slen    25

int main()
{
    list * T = make_new_list();
    char Tstring[maxTlen + 1];
    list * S = make_new_list();
    char Sstring[Slen + 1];

    node * p;
    list * part = make_new_list();
    part -> length = 20;


    scanf("%s", Tstring);

    const int Tlen = strlen(Tstring);
    T = insert_data(T, Tstring, -1);
    p = T -> head;

    int i;
    int index = 0;
   
    for(i = 0; i < Snum/2; i++){
        scanf("%s", Sstring);
        Sstring[20] = '\0';

        if(i == 0){
            S = insert_data(S, Sstring, -1);
            S -> length = 20;
        }else{
            S = replace_data(S, Sstring, 0);
        }

        for(index = 0; index < Tlen - Slen + 1; index++){
            if(p == NULL) break;
            part -> head = p;

            if(edit_distance(part, S, 2)){
                replace_data(T, Sstring, index);
                break;
            }
            p = p -> next;
        }
         p = T -> head;
    }
    
    show(T);
    return 0;
}