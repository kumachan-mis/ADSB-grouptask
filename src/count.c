#include <stdio.h>
#define N 100000
int main(){
    char data[N];
    char filename[30];
    printf("filename : ");
    scanf("%s", filename);
    FILE * fl = fopen(filename, "r");
    FILE * out = fopen("CountOut.txt", "a");
    fscanf(fl, "%s", data);
    int i = 0;
    int num[4][3] = {};
    for(i = 0; i < N-1; i++){
        num[0][data[i] - 'a']++;
        num[data[i + 1] - 'a' + 1][data[i] - 'a']++;
    }
    num[0][data[N - 1] - 'a']++;
    fprintf(out, "%s\n", filename);
    fprintf(out, "a: %d, b: %d, c:%d\n", num[0][0], num[0][1], num[0][2]);
    fprintf(out, "aa: %d, ba: %d, ca:%d\n", num[1][0], num[1][1], num[1][2]);
    fprintf(out, "ab: %d, bb: %d, cb:%d\n", num[2][0], num[2][1], num[2][2]);
    fprintf(out, "ac: %d, bc: %d, cc:%d\n", num[3][0], num[3][1], num[3][2]);
    
}
