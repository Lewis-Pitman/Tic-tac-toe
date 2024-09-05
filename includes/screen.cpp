//this file contains all the logic needed to initialise and render the grid

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

char** spaces;

class Screen
{
    private:
    int width {};
    int height {};
    int spacing {};
    bool turn {false}; //false = X, true = O
    int count {0}; 
    int linePrintIterator {0};

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

            DrawLine(0); //seperate the previous grid
            std::cout << "\n";

            for(int i = 0; i < width; i++){
                std::cout << std::setw((spacing * 2) + 1) << i + 1; //number line across top
            }

            std::cout << "\n";
            DrawLine(1); //dividing line under the number line
            std::cout << "\n";

            linePrintIterator = 0;
            count = 0;
            
            for(int i = 0; i < height; i++){
                std::cout << i + 1 << std::setw(spacing);//so that we can print out the number of each line
                for(int j = 0; j < width; j++){
                    std::cout << "|" << std::setw(spacing) << spaces[i][j] << std::setw(spacing) << "|"; 
                }

            std::cout << "\n";
            DrawLine(1); //dividing line
            std::cout << "\n";

            count = 0;
    }
    }

    public:
    
    Screen(int _width, int _height, int _spacing){
        width = _width;
        height = _height;
        spacing = _spacing;

        spaces = new char*[_height];
        for(int i = 0; i < _height; i++){
            spaces[i] = new char[_width];
        } //2D array initialisation | "spaces" is a pointer to an array of pointers. Each pointer in this pointer array points to the memory address of another pointer.

        for(int i = 0; i < _height; i++){
            for(int j = 0; j < _width; j++){
                spaces[i][j] = ' '; //Initialise all elements in the 2D array to " " so that the grid displays properly
            }
        }

    }//constructor

    ~Screen(){
    }//deconstructor

    void Render(){
        DrawScreen();
    }
};