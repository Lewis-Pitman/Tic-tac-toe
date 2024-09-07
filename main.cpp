#include <iostream>
#include "includes\screen.cpp"

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
int playerMatching {}; //In order to determine which player is currently winning (We know that some tiles are matching, but we need to know which player they belong to)
bool gameActive {true};
bool validMove {false}; //input validation
int winnerLR {-1}; //used in diagonal()
int winnerRL {-1}; //used in diagonal()
int element {0}; //used in diagonalLR() and diagonalRL()

//general functions ---------------------------------------------------------------------
void Initialise(){
    std::cout << "\nWelcome to Dynamic Tic Tac Toe.\nThis game allows you to change size of the play grid.\nThe padding option changes how stretched the grid looks.";
    std::cout << "\nIn order to win you need to get your tiles to cover an entire row or column, or diagonally across the grid.";
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

//winner checking functions -------------------------------------------------------------

int Horizontal(){
    currentlyMatching = true;
    //first [] = row, second = column
    for(int i = 0; i < screenY; i++){ //loop through rows
            for(int j = 1; j < screenX; j++){ //loop through columns
                if(spaces[i][j] != spaces[i][j-1] || spaces[i][j] == ' '){ //loops through a row and checks each element to the previous in the row
                    currentlyMatching = false;
                } else if(spaces[i][j] != ' '){
                    playerMatching = (spaces[i][j] == 'X') ? 1 : 2;
                }
            }
            if(currentlyMatching){//if all elements in a row have been checked and are matching, we can determine the winner
                return playerMatching;
            }
            currentlyMatching = true;//initialise for the next row
        }
    return -1; //if we have searched all rows and still not found a winner, we return a value other than 1 and 2 to indicate there is no winner
}

int Vertical(){
    currentlyMatching = true;
    for(int i = 0; i < screenX; i++){//loop through columns
        for(int j = 0; j < screenY; j++){//loop through rows
            if(spaces[j][i] != spaces[0][i] || spaces[j][i] == ' '){
                currentlyMatching = false;
            } else if(spaces[j][i] != ' '){
                playerMatching = (spaces[j][i] == 'X') ? 1 : 2;
            }
        }
        if(currentlyMatching){
            return playerMatching;
        }
        currentlyMatching = true;
    }
    return -1;
}

//finding a diagonal from top left to bottom right and from top right to bottom left
int DiagonalLR(){
    currentlyMatching = true;
    for(element = 0; element < screenX - 1; element++){
        if(spaces[element][element] != spaces[element + 1][element + 1] || spaces[element][element] == ' '){ //for example, we need to check the elements with coordinates (0,0), (1, 1) and (2, 2) in a 3x3 grid
            currentlyMatching = false;
        } else if(spaces[element][element] != ' '){
            playerMatching = (spaces[element][element] == 'X') ? 1 : 2;
        }
    }

    if(currentlyMatching){
        return playerMatching;
    } else{
        return -1;
    }
}

int DiagonalRL(){
    //for example (2, 0), (1, 1), (0, 2)
    //decreasing x value by 1, increasing y value by 1

    currentlyMatching = true;
    int count = screenX - 1;
    for(int i = 0; i < screenY - 1; i++){
        if(spaces[i][count] != spaces[i + 1][count - 1] || spaces[i][count] == ' '){
            currentlyMatching = false;
        } else if(spaces[i][count] != ' '){
            playerMatching = (spaces[i][count] == 'X') ? 1 : 2;
        }
        count--;
    }

    if(currentlyMatching){
        return playerMatching;
    } else{
        return -1;
    }
}

int Diagonal(){
    winnerLR = DiagonalLR();
    winnerRL = DiagonalRL();

    if(winnerLR == 1 || winnerRL == 1){
        return 1;
    } else if(winnerLR == 2 || winnerRL == 2){
        return 2;
    } else{
        return -1;
    }
}

int CheckWinner(){
    if(Horizontal() == 1 || Vertical() == 1 || Diagonal() == 1){
        return 1;// X wins
    } else if(Horizontal() == 2 || Vertical() == 2 || Diagonal() == 2){
        return 2;//O wins
    } else{
        return -1;//nobody won (this value could be anything other than 1 or 2, but I'm using -1 to be on the safe side and to keep everything consistant)
    }
}

//game functions ---------------------------------------------------------------------

void GameLogic(){
    if(firstPlayer){
        while(!validMove){
            std::cout << "\nPLAYER X -> choose a number on the X axis to place your X: ";
            std::cin >> chosenX;
            std::cout << "\nPLAYER X -> choose a number on the Y axis to place your X: ";
            std::cin >> chosenY;

            if(chosenX <= screenX && chosenY <= screenY){
                if(spaces[chosenY - 1][chosenX - 1] == ' '){
                    validMove = true;
                } else{
                std::cout << "\nPLAYER X -> this space has already been taken";
                }
            }
        }
            spaces[chosenY - 1][chosenX - 1] = 'X';
            validMove = false;
            firstPlayer = false;
        } else{
            while(!validMove){
            std::cout << "\nPLAYER O -> choose a number on the X axis to place your O: ";
            std::cin >> chosenX;
            std::cout << "\nPLAYER O -> choose a number on the Y axis to place your O: ";
            std::cin >> chosenY;

            if(chosenX <= screenX && chosenY <= screenY){
                if(spaces[chosenY - 1][chosenX - 1] == ' '){
                    validMove = true;
                } else{
                std::cout << "\nPLAYER O -> this space has already been taken";
                }
            }
        }
            spaces[chosenY - 1][chosenX - 1] = 'O';
            validMove = false;
            firstPlayer = true;
        }
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
    
    screen.Render(); // render final grid

    if(gameActive){ //if all moves have been exhausted and a winner hasn't stopped the game yet
        std::cout << "\n\nThis game is a tie\n";
    }

    Hang();
    return 0;
}