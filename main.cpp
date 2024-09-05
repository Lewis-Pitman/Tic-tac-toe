#include <iostream>
#include "C:\Users\Lewis\Desktop\Code projects\Tic tac toe\includes\screen.cpp"

//screen:
int screenX {};
int screenY {};
int padding {};
Screen screen(screenX, screenY, padding);
//input
int chosenX {};
int chosenY {};
//decide which player
bool firstPlayer {true};
//arrays for checking winner
int checkCount {10};
char* rowArray = NULL;
char* ColumnArray = NULL;
//other checking variables
bool currentlyMatching {false}; //the functions below compare 2 numbers at a time. This value needs to remain true for the width of the grid in order for the player to win
int matchingCount {}; //In order for the player to be able to change how many tiles are needed to win, the function needs to keep track of how many tiles are matching
int playerMatching {}; //In order to determine which player is currently winning (We know that some tiles are matching, but we need to know which player they belong to)
bool gameActive {true};

void Initialise(){
    std::cout << "\nWelcome to Dynamic Tic Tac Toe.\nThis game allows you to change size of the play grid.\nThe padding option changes how stretched the grid looks.";
    std::cout << "\nIf there are a matching set of tiles for the whole width of the grid, that player wins.\nIf there are a matching set of tiles for the whole height of the grid, that player wins.\nA player can win with a diagonal if it is possible.";
    std::cout << "\n---------------------------------------------------";
    //setting up the screen
    std::cout << "\nEnter Grid size: ";
    std::cin >> screenX;
    screenY = screenX;//you used to be able to change the height and width seperately, however this was removed due to complexity. This is kept here so I can re-use screen.cpp in the future with other projects
    std::cout << "\nEnter padding of grid: ";
    std::cin >> padding;
}

void Hang(){//this is so the program doesn't exit straight away, the user has to enter -1 in order to close the program
    int response {};
    while(response != -1){
        std::cout << "\nEnter -1 to exit the program: ";
        std::cin >> response;
    }
}

int Horizontal() {

}

int Vertical() {

}//these kind of work but produce unexpected results sometimes

int CheckWinner(){
    if(Horizontal() == 1 || Vertical() == 1){
        return 1;// X wins
    } else if(Horizontal() == 2 || Vertical() == 2){
        return 2;//O wins
    } else{
        return -1;//nobody one (this value could be anything other than 1 or 2)
    }
}

void GameLogic(){
    if(firstPlayer){
            std::cout << "\nPLAYER X -> choose a number on the X axis to place your X: ";
            std::cin >> chosenX;
            std::cout << "\nPLAYER X -> choose a number on the Y axis to place your X: ";
            std::cin >> chosenY;

            spaces[chosenY - 1][chosenX - 1] = *"X";

            firstPlayer = false;
        } else{
            std::cout << "\nPLAYER O -> choose a number on the X axis to place your O: ";
            std::cin >> chosenX;
            std::cout << "\nPLAYER O -> choose a number on the Y axis to place your O: ";
            std::cin >> chosenY;

            spaces[chosenY - 1][chosenX - 1] = *"O";

            firstPlayer = true;
        }
        screen.Render();
        /*
        switch(CheckWinner()){
            case 1:
            std::cout << "\nPlayer X wins!\n";
            gameActive = false;
            break;
            case 2:
            std::cout << "\n\nPlayer O wins!\n";
            gameActive = false;
            break;
            default:
            std::cout << "\n\nNobody has won yet\n";
            break;
        }
        */
}

int main(){
    Initialise();
    Screen screen(screenX, screenY, padding);
    
    //game logic
    for(int i = 0; i < screenX * screenY; i++){//The maximum number of turns is the screen width multiplied by the screen height
        if(gameActive){
            screen.Render();
            GameLogic();
        }
    }

    Hang();
    return 0;
}