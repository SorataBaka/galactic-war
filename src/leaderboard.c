#include "leaderboard.h"
void writeLeaderboard(Player * playerObject){
    FILE * leaderboardFile = fopen("./leaderboard.txt", "w+");
    int score;
    char username[20];
    
    Entry * leaderboardEntry = (Entry *)malloc(sizeof(Entry) * 15);
    int index = 0;
    while(fscanf(leaderboardFile, " %d %s\n", &score, username) == 1){
        leaderboardEntry[index].score = score;
        strcpy(leaderboardEntry[index].username, username);
        index++;
    }
    leaderboardEntry[index].score = playerObject->points;
    strcpy(leaderboardEntry[index].username, playerObject->username);
    index++;
    //Sort by highest score
    // for(int i = 0; i <  index - 1; i++){
    //     for(int ii = 0; ii < index - i - 1; ii++){
    //         if(leaderboardEntry[ii].score < leaderboardEntry[i].score){
    //             Entry temp;
    //             temp.score = leaderboardEntry[i].score;
    //             strcpy(temp.username, leaderboardEntry[i].username);
    //             leaderboardEntry[i] = leaderboardEntry[ii];
    //             leaderboardEntry[ii].score = temp.score;
    //             strcpy(leaderboardEntry[ii].username, temp.username);
    //         }
    //     }
    // }
    for(int i = 0; i < index; i++){
        fprintf(leaderboardFile, "%d %s\n", leaderboardEntry[i].score, leaderboardEntry[i].username);
    }
    fclose(leaderboardFile);
    return;
}