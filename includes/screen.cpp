//this file contains all the logic needed to render the grid in the terminal

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

char* spaces = NULL;

class Screen
{
    private:
    int width {};
    int height {};
    int spacing {};
    bool turn {false}; //false = X, true = O
    int count {-1}; //this is in order to draw the screen correctly (correct number of lines)
    int linePrintCount {0}; //this is to properly print the lines with the array
    int linePrintIterator {0}; // for the for loop that uses the value above

    void DrawLine(int type){
        switch(type){
            case 0://separating line after each turn is taken, appears above the horizontal number line. Starts at the leftmost side of screen.
            for(int j = 0; j < width * ((spacing * 3)+1); j++){
                std::cout << "-";
            }
            break;
            case 1://seperating line on the grid itself, seperating each line. Starts above the first "|" in each line
            std::cout << std::setw(spacing + 1); //starting point (above first space in the grid)
            for(int j = 0; j < width * ((spacing * 2)+1); j++){
                std::cout << "-";
            }
            break;
        }
    }

    void DrawScreen(){//contains the logic for drawing screen
        if(count == height){//finished (break out of recursion)
            count = -1; //reset the count so we can call drawScreen() again
        } 
        else if(count == -1){//initialising the screen (so it looks pretty with a divider and a top row of numbers)

            DrawLine(0); //seperate the previous grid
            std::cout << "\n";

            for(int i = 0; i < width; i++){
                std::cout << std::setw((spacing * 2) + 1) << i + 1; //number line across top
            }

            std::cout << "\n";
            DrawLine(1); //dividing line under the number line
            std::cout << "\n";

            linePrintCount = width;
            linePrintIterator = 0;
            count = 0;
            DrawScreen();
        } 
        else{
            std::cout << count + 1 << std::setw(spacing);//so that we can print out the number of each line
            for(; linePrintIterator < linePrintCount; linePrintIterator++){//printing each line

                std::cout << "|" << std::setw(spacing) << spaces[linePrintIterator] << std::setw(spacing) << "|"; 
            }

            std::cout << "\n";
            DrawLine(1); //dividing line
            std::cout << "\n";

            linePrintCount = linePrintCount + width;
            count++;
            DrawScreen();
            }   
    }

    public:
    
    Screen(int _width, int _height, int _spacing){
        width = _width;
        height = _height;
        spacing = _spacing;

        spaces = new char[_width *_height];
        for(int i = 0; i < _width * _height; i++){
            strcpy(&spaces[i], " ");//make sure all elements in the array "spaces" are initialised to "X"
        }
    }//constructor

    ~Screen(){
    }//deconstructor

    void Render(){
        DrawScreen();
    }
};