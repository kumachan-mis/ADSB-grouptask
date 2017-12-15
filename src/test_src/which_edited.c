#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

#define edTlen 105000
#define Tlen 100000
#define Snum 20000
#define Slen 25
#define cases 5

int func(list * Tlist, list * Slist, int d);

int main(int argc, char * argv[]){
    int d = atoi(argv[1]);
    char inname[20], orgname[20];
    char outname[20];

    sprintf(outname, "which_edited%d.txt", d);
    FILE * out =fopen(outname, "w");
    
    char T[edTlen], S[Slen];
    list * Tlist = make_new_list();

    int p;
    for(p = 0; p < cases; p++){

        int cnt[Slen] = {};
        sprintf(inname, "dat%d_in", p);
        sprintf(orgname, "dat%d_org", p);
        FILE * in = fopen(inname, "r");
        FILE * org = fopen(orgname, "r");
        fscanf(in, "%s", T);
        fscanf(org, "%s", T);

        if(p == 0){
            Tlist = insert_data(Tlist, T, -1);
        }else{
            Tlist = replace_data(Tlist, T, 0);
        }

        list * Slist = make_new_list();
        int q;
        for(q = 0; q < Snum; q++){
             fscanf(in, "%s", S);
             if(q == 0){
                 Slist = insert_data(Slist,S, -1);
             }else{
                 Slist = replace_data(Slist, S, 0);
             }

             int index = func(Tlist, Slist, d);
             if(index != -1){
                 cnt[index]++;
             }

        }//各Sの要素
        fprintf(out, "dat%d\n", p);
        for(q = 0; q <Slen; q++){
            fprintf(out, "%02d : %d\n", q, cnt[q]);
        }
    }//各データセット
    return 0;
}

int func(list * Tlist, list * Slist, int d){
    list * part = make_new_list();
    node * p = Tlist -> head;
    part -> length = Slen;

    int i;
    for(i= 0; i <= Tlen - Slen; i++){
        part -> head = p;
        if(edit_distance(part, Slist, d)){
            node * temp1 = Slist -> head;
            node * temp2 = p;

            int j;
            for(j=0; j < Slen; j++){
                if(temp1 -> data != temp2 -> data){
                    return j;
                }
                temp1 = temp1 -> next;
                temp2 = temp2 -> next;
            }//どこが編集されているかを見る
            return -1;
        }//編集距離が1以内なら
         p = p -> next;
    }//Tの各開始点
    return -1;
}
