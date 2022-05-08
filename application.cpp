// Bar Chart Animation
//
// This application uses BarChartAnimate (which uses BarChart, which uses Bar)
// to produce an animated bar chart.
//
// Once your three class/abstraction files are completed and tested, run with
// this application to see your final creation.
//
// Project: Animated Bar chart
// Name: Ronak Chaudhuri
// Creative Component: For my creative component, my user interface first prints
// out the all the avaialable file options to choose from, and then allows the
// user to input a number to choose which option. Then it will prompt the user
// to choose number of frames to be displayed, and the speed of the animation.
// Using all the inputs, it will create an animated bar chart based on what the
// user selected. Edge cases are put in place, so user can only input valid
// numbers(0-11 for file options, >0 for frames, 1-10 for speed). If the user
// inputs a frame number that is greater than the total number of frames, then
// it will just display the total number of frames.
//
// Shanon Reckinger
// U. of Illinois, Chicago
// CS 251: Fall 2021
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include "barchartanimate.h"
using namespace std;

/* Prints all file options to use */
void printFileOptions() {
    cout << "\nFile Options: " << endl;
    cout << "1. baby-names.txt" << endl;
    cout << "2. brands.txt" << endl;
    cout << "3. cities-usa.txt" << endl;
    cout << "4. cities.txt" << endl;
    cout << "5. countries.txt" << endl;
    cout << "6. endgame.txt" << endl;
    cout << "7. football.txt" << endl;
    cout << "8. game-of-thrones.txt" << endl;
    cout << "9. infinity-war.txt" << endl;
    cout << "10. movies.txt" << endl;
    cout << "11. patents.txt" << endl;
    cout << "0. QUIT" << endl;
}

/* Depending on user input loads the file that matches user input */
void loadFiles(int option, string &filename) {
    if(option == 1) {
        filename = "baby-names.txt";
    } else if(option == 2) {
        filename = "brands.txt";
    } else if(option == 3) {
        filename = "cities-usa.txt";
    } else if(option == 4) {
        filename = "cities.txt";
    } else if(option == 5) {
        filename = "countries.txt";
    } else if(option == 6) {
        filename = "endgame.txt";
    } else if(option == 7) {
        filename = "football.txt";
    } else if(option == 8) {
        filename = "game-of-thrones.txt";
    } else if(option == 9) {
        filename = "infinity-war.txt";
    } else if(option == 10) {
        filename = "movies.txt";
    } else if(option == 11) {
        filename = "patents.txt";
    }

}

/* Function used to make sure valid numbers are being inputed for each input */
void edgeCases(int &option, int &iterations, int &speed, string &filename) {
    while(option < 0 || option > 11) {
        cout << "Invalid Number. Must be between 0-11." << endl;
        cout << "Enter number: " << endl;
        cin >> option;
    }
    loadFiles(option, filename);
    cout << "Enter number of frames(Any number > 0): " << endl;
    cin >> iterations;
    while(iterations < 0) {
        cout << "Invalid Number. Must be > 0" << endl;
        cout << "Enter number of frames(Any number > 0): " << endl;
        cin >> iterations;
    }
    cout << "Enter speed of animation(Integer from 1-10): " << endl;
    cin >> speed;
    while(speed > 10 || speed < 1) {
        cout << "Invalid Number. Must be between 1-10." << endl;
        cout << "Enter speed of animation(Integer from 1-10): " << endl;
        cin >> speed;
    }
}

/* Function call that takes info from filles and creates barchartanimate object,
   then calls creative component animate function in barchartanimate class
   using user input values as parameters */
void animate(string filename, int iterations, int timeScale) {
    ifstream inFile(filename);
    string title;
    getline(inFile, title);
    string xlabel;
    getline(inFile, xlabel);
    string source;
    getline(inFile, source);

    BarChartAnimate bca(title, xlabel, source);

    while (!inFile.eof()) {
        bca.addFrame(inFile);
    }
    timeScale = 11 - timeScale;
    bca.animate(cout, 12, iterations, timeScale);
}

int main() {
    int option = 0;
    int iterations = 0;
    int speed = 0;
    string filename;
    cout << "Welcome to Animated Bar Chart" << endl;
    while(true) {
        printFileOptions();
        cout << "Enter number: " << endl;
        cin >> option;
        if(option == 0) {
            return 0;
        }
        edgeCases(option, iterations, speed, filename);
        animate(filename, iterations, speed);
    }
}
