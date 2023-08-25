#include<stdio.h>
#include<stdlib.h>

void generateRandom(int n) {
    int i,j,k;
    FILE *fp;
    fp = fopen("input.txt", "w+");
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            if(i==j)
                fprintf(fp, "%d   ", 0);
            else if(i%10 == j%10){
                k=rand()%10;
                //k=k>5?0:k;
                fprintf(fp, "%d   ", k);
            }
            else {
                fprintf(fp, "%d   ", 0);
            }
            
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

int main() {
    generateRandom(100);
    return 0;
}