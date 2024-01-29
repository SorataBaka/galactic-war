#include "leaderboard.h"
void writeLeaderboard(Player * playerObject){
    FILE * leaderboardFile = fopen("./leaderboard.txt", "r");
    if(leaderboardFile == NULL){
        leaderboardFile = fopen("./leaderboard.txt", "w+");
        fclose(leaderboardFile);
        leaderboardFile = fopen("./leaderboard.txt", "r");
    }
    int score;
    char username[20];
    
    Entry * leaderboardEntry = (Entry *)malloc(sizeof(Entry) * 15);
    int index = 0;
    while(fscanf(leaderboardFile, " %d|%s", &score, username) == 2){
        leaderboardEntry[index].score = score;
        strcpy(leaderboardEntry[index].username, username);
        index++;
    }
    fclose(leaderboardFile);
    leaderboardEntry[index].score = playerObject->points;
    strcpy(leaderboardEntry[index].username, playerObject->username);
    index++;
    // Sort by highest score
    for(int i = 0; i <  index - 1; i++){
        for(int j = 0; j < index - i - 1; j++){
            if(leaderboardEntry[j].score < leaderboardEntry[j+1].score){
                Entry temp = leaderboardEntry[j];
                leaderboardEntry[j] = leaderboardEntry[j+1];
                leaderboardEntry[j+1] = temp;
            }
        }
    }
    leaderboardFile = fopen("./leaderboard.txt", "w");
    for(int i = 0; i < (index <= 10 ? index : 10); i++){
        fprintf(leaderboardFile, "%d|%s\n", leaderboardEntry[i].score, leaderboardEntry[i].username);
    }
    fclose(leaderboardFile);
    return;
}