#include <stdio.h>
#include <string.h>

#define Tlength 105000
#define sizeofS 20000
#define slength 25

int main(){
    char infile[50], orgfile[50];
    char T[Tlength + 1], s[slength + 1];
    FILE * in, * org;
    FILE * out;
    int i; int n;
    int count = 0;
    out = fopen("searchSinT.txt", "w");
    for(i = 0; i < 5; i++){

        sprintf(infile, "dat%d_in", i);
        sprintf(orgfile, "dat%d_org", i);
        fprintf(out, "dat%d: ", i);

        in = fopen(infile, "r");
        org = fopen(orgfile, "r");

        fscanf(in, "%s", T);
        fscanf(org, "%s", T);
        
        for(n = 0; n < sizeofS; n++){
            fscanf(in, "%s", s);
            if(strstr(T, s) != NULL){
                count++;
            }
        }
        fprintf(out, "%d\n", count);
        count = 0;
        fclose(in);
        fclose(org);
    }
    fclose(out);
    return 0;
}