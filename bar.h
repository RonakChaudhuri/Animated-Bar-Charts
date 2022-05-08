// barchartanimate.h
// Project: Animated Bar Chart
// Name: Ronak Chaudhuri
// Class Overview: This class is used to animate the bar chart. It consists of
// a C-style array of barcharts, and graphs each barchart to a specific
// iteration amount of times on top of each other with a small delay, creating
// the animated barchart.

#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "barchart.h"
#include "myrandom.h"  // used in autograder, do not remove

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    string title;
    string xlabel;
    string source;
    int index;

    // Updates color map, first checks to see if category is already in color
    // map, if not then adds that category to the color map with whatever the
    // next color is in the colors vector
    void updateColorMap(string category) {
        if (colorMap.count(category) == 0) {
            colorMap[category] = COLORS[index];
            index++;
            if (index == 7) {
                index = 0;
            }
        }
    }

    // Checks to see if array is full, and if full doubles the capacity of
    // the array.
    void doubleCapacity() {
        if (size == capacity) {
            int newCapacity = capacity * 2;
            BarChart* newBarCharts = new BarChart[newCapacity];
            for (int i = 0; i < size; ++i) {
                newBarCharts[i] = barcharts[i];
            }
            delete[] barcharts;
            barcharts = newBarCharts;
            capacity = newCapacity;
        }
    }

public:
    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    // Sets private variables to default values
    // Sets the matching private variables to parameter values
    BarChartAnimate(string title, string xlabel, string source) {
        barcharts = new BarChart[4];
        capacity = 4;
        size = 0;
        index = 0;
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        if (barcharts != nullptr) {  // then we have something to free:
            delete[] barcharts;        // since we new'd an array, we delete[]
        }
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    // First reads in whitespace, then reads in the number of records n
    // Loops through n times, storing the year, name, country, value, and
    // category to a Barchart, and adds that barchart to the barcharts array
    void addFrame(ifstream& file) {
        string whitespace, holder;
        int n = 0;
        string year, name, country, category;
        int value = 0;
        int counter = 0;
        getline(file, whitespace);
        getline(file, holder);
        if (holder == "") {
            n = 0;
        } else {
            n = stoi(holder);
            BarChart bc(n);
            while (counter < n) {
                getline(file, year, ',');
                getline(file, name, ',');
                getline(file, country, ',');
                getline(file, holder, ',');
                value = stoi(holder);
                getline(file, category);
                updateColorMap(category);
                bc.setFrame(year);
                bc.addBar(name, value, category);
                counter++;
            }
            doubleCapacity();
            barcharts[size] = bc;
            size++;
            bc.clear();
        }
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
    // Loops through the barcharts array until endIter parameter times
    // Outputs the title, source, graph, label and frame for each index
    // of barcharts.
    void animate(ostream& output, int top, int endIter) {
        unsigned int microsecond = 50000;

        if (endIter == -1 || endIter > size) {
            endIter = size;
        }
        for (int i = 0; i < endIter; i++) {
            usleep(3 * microsecond);
            output << CLEARCONSOLE;
            output << BLACK << title << endl;
            output << BLACK << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << BLACK << xlabel << endl;
            output << BLACK << "Frame: " << barcharts[i].getFrame() << endl;
        }
    }

    // second animate function for creative component
    // same as first animate function, but takes in extra timeScale
    // parameter to change the speed of the frames.
    void animate(ostream& output, int top, int endIter, int timeScale) {
        unsigned int microsecond = 50000;

        if (endIter == -1 || endIter > size) {
            endIter = size;
        }
        for (int i = 0; i < endIter; i++) {
            usleep(timeScale * microsecond);
            output << CLEARCONSOLE;
            output << BLACK << title << endl;
            output << BLACK << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << BLACK << xlabel << endl;
            output << BLACK << "Frame: " << barcharts[i].getFrame() << endl;
        }
    }

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize() { return size; }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i) {
        if (i < 0 || i >= size) {
            throw out_of_range("BarChartAnimate: i out of bounds");
        }

        return barcharts[i];
    }
};
