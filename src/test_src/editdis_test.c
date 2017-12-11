#include <stdio.h>
#include "linkedlist.h"
int main()
{
    int i, j, n, cnt = 0;
    char str[100][1001];
    scanf("%d", &n);
    for(i = 0; i < n; i++) scanf("%s", str[i]);
    //全組み合わせを網羅
    for(i = 0; i < n - 1; i++) 
    {
        for(j = i + 1; j < n; j++)
        {
            list * linkedlist1 = make_new_list();
            list * linkedlist2 = make_new_list();
            linkedlist1 = insert_data(linkedlist1, str[i], -1);
            linkedlist2 = insert_data(linkedlist2, str[j], -1);
            if(edit_distance(linkedlist1, linkedlist2, 10)) cnt++; 
        }
    }
    printf("%d\n", cnt);
}