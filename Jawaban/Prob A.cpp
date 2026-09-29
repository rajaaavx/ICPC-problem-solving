#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char name[100][11];
    int score1;
    int time1;
    int score2;
    int time2;
    int totalScore[100];
    int totalTime[100];
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%s", name[i]);
        getchar();
        scanf("%d %d %d %d", &score1, &time1, &score2, &time2);
        totalScore[i] = score1 + score2;
        totalTime[i] = time1 +  time2;
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1; j++){
            int swap = 0;
            if (totalScore[j] < totalScore[j+1]) swap = 1;
            else if (totalScore[j] == totalScore[j+1] && totalTime[j] > totalTime[j+1]) swap = 1;
            
            if(swap){
                int temp = totalScore[j];
                totalScore[j] = totalScore[j+1];
                totalScore[j+1] = temp;
                temp = totalTime[j];
                totalTime[j] = totalTime[j+1];
                totalTime[j + 1] = temp;
                char tempName[100];
                strcpy(tempName, name[j]);
                strcpy(name[j], name[j+1]);
                strcpy(name[j+1], tempName);
            }
        }
    }
    for(int i = 0; i < n; i++){
        printf("%s\n", name[i]);
    }
}