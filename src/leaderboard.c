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
void displayLeaderboard(int maxWidth, int maxHeight){
    FILE * leaderboardFile = fopen("./leaderboard.txt", "r");
    int yCenter = maxHeight/2;
    int xCenter = maxWidth/2;
    if(leaderboardFile == NULL){
        mvaddstr(yCenter, xCenter-12, "No leaderboard to show.");
        mvaddstr(yCenter, xCenter-13, "Press any key to continue.");
        getch();
        return;
    }
    Entry * leaderboard = (Entry * )malloc(sizeof(Entry) * 11);
    int score;
    char username[20];
    int index = 0;
    while(fscanf(leaderboardFile, "%d|%s", &score, username) == 2){
        leaderboard[index].score = score;
        strcpy(leaderboard[index++].username, username);
    }
    yCenter = yCenter - 5;
    erase();
    mvaddstr(yCenter-2, xCenter-6, "LEADERBOARD");
    timeout(-1);
    for(int i = 0; i < index; i++){
        char entryPrint[30];
        sprintf(entryPrint, "%2d. %5d %s", i+1, leaderboard[i].score, leaderboard[i].username);
        mvaddstr(yCenter+i, xCenter-10, entryPrint);
    }
    mvaddstr(yCenter+14, xCenter-14, "Press any key to continue.");
    getch();
    return;
}