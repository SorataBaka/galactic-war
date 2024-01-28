#include "mainscreen.h"
void mainScreen(Player * playerObject, Meteor * meteorArray, int maxHeight, int maxWidth){
	timeout(-1);
    //Basic settings
    int verticalOffset = -5;
    int horizontalOffset = 0;
    int currentChoice = 0;
    int yCenter = maxHeight/2 + verticalOffset;
    int xCenter = maxWidth/2 + horizontalOffset;

    //Make the prompt to input player name here.


    while(true){
        erase();
        //Display the main title
        mvaddstr(0, 0, "National Institute of Technology Kushiro Kosen - 3rd Year Programming Course - Christian Harjuno");
        mvaddstr((yCenter)-3, (xCenter)-44, "  _____          _               _____ _______ _____ _____  __          __     _____  \n");
        mvaddstr((yCenter)-2, (xCenter)-44, " / ____|   /\\   | |        /\\   / ____|__   __|_   _/ ____| \\ \\        / /\\   |  __ \\ \n");
        mvaddstr((yCenter)-1, (xCenter)-44, "| |  __   /  \\  | |       /  \\ | |       | |    | || |       \\ \\  /\\  / /  \\  | |__) |\n");
        mvaddstr((yCenter), (xCenter)-44, "| | |_ | / /\\ \\ | |      / /\\ \\| |       | |    | || |        \\ \\/  \\/ / /\\ \\ |  _  / \n");
        mvaddstr((yCenter)+1, (xCenter)-44, "| |__| |/ ____ \\ |____ / ____ \\ |____   | |   _| || |____     \\  /\\  / ____ \\| | \\ \\ \n");
        mvaddstr((yCenter)+2, (xCenter)-44, " \\_____/_/    \\_\\______/_/    \\_\\_____|  |_|  |_____\\_____\\     \\/  \\/_/    \\_\\_|  \\_\\ \n");

        mvaddstr(yCenter + 6, xCenter-21, "https://soratabaka.github.io/galactic-war/");

        mvaddstr(yCenter + 9, xCenter-7, "[1] Start Game");
        mvaddstr(yCenter + 10, xCenter-7, "[2] Leaderboard");
        mvaddstr(yCenter + 11, xCenter-7, "[3] Quit");
        
        char input = getch();
        switch(input-'0'){
            case(1):
                game(playerObject, meteorArray);
                endScreen(maxWidth, maxHeight, playerObject);
                //Make function to write name to leaderboard here
                break;
            case(2):
                break;
            case(3):
                return;
                break;
            default:
                continue;
        }
    }
}