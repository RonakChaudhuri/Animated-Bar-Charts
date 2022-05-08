#include <iostream>
#include "barchartanimate.h"
#include <sstream>
using namespace std;


bool testBarDefaultConstructor() {
    Bar b;
    if (b.getName() != "") {
        cout << "testBarDefaultConstructor: getName failed" << endl;
        return false;
    } else if (b.getValue() != 0) {
        cout << "testBarDefaultConstructor: getValue failed" << endl;
        return false;
    } else if (b.getCategory() != "") {
        cout << "testBarDefaultConstructor: getCategory failed" << endl;
        return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
    Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
        cout << "testBarParamConstructor: getName failed" << endl;
        return false;
    } else if (b.getValue() != 9234324) {
        cout << "testBarParamConstructor: getValue failed" << endl;
        return false;
    } else if (b.getCategory() != "US") {
        cout << "testBarParamConstructor: getCategory failed" << endl;
        return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

bool testBarOperators() {
    Bar b("Chicago", 95671, "US");
    Bar b2("Beijing", 8455, "China");
    Bar b3("Tokyo", 8455, "Japan");
    if (b < b2) {
        cout << "testBarOperators: operator< failed" << endl;
        return false;
    } else if (b <= b2) {
        cout << "testBarOperators: operator<= failed" << endl;
        return false;
    } else if (b2 > b) {
        cout << "testBarOperators: operator> failed" << endl;
        return false;
    } else if (b2 >= b) {
        cout << "testBarOperators: operator>= failed" << endl;
        return false;
    } else if(b2 > b3) {
        cout << "testBarOperators: operator> failed" << endl;
        return false;
    } else if(!(b3 >= b2)) {
        cout << "testBarOperators: operator>= failed" << endl;
        return false;
    } else if(!(b3 <= b2)) {
        cout << "testBarOperators: operator<= failed" << endl;
        return false;
    } else if(b3 < b2) {
        cout << "testBarOperators: operator< failed" << endl;
        return false;
    }
    cout << "testBarOperators: all passed!" << endl;
    return true;
}

bool testBarChartDefaultConstructor() {
    BarChart bc;
    if (bc.getSize() != 0) {
        cout << "testBarChartDefaultConstructor: getSize failed" << endl;
        return false;
    } else if (bc.getFrame() != "") {
        cout << "testBarChartDefaultConstructor: getFrame failed" << endl;
        return false;
    }
    cout << "testBarChartDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarChartParamConstructor() {
    BarChart bc(10);
    if (bc.getSize() != 0) {
        cout << "testBarChartParamConstructor: getSize failed" << endl;
        return false;
    } else if (bc.getFrame() != "") {
        cout << "testBarChartParamConstructor: getFrame failed" << endl;
        return false;
    }
    bc.addBar("Chicago", 1020, "US");
    bc.setFrame("2018");
    if (bc.getSize() != 1) {
        cout << "testBarChartParamConstructor: getSize failed" << endl;
        return false;
    } else if (bc.getFrame() != "2018") {
        cout << "testBarChartParamConstructor: getFrame failed" << endl;
        return false;
    }
    cout << "testBarChartParamConstructor: all passed!" << endl;
    return true;
}

bool testBarChartCopyConstructor() {
    BarChart bc(10);
    BarChart bcCopy(bc);
    if (bc.getSize() != 0) {
        cout << "testBarChartCopyConstructor: getSize failed" << endl;
        return false;
    } else if (bc.getFrame() != "") {
        cout << "testBarChartCopyConstructor: getFrame failed" << endl;
        return false;
    }
    cout << "testBarChartCopyConstructor: all passed!" << endl;
    return true;

}

bool testBarChartAddBar() {
    BarChart bc1;
    BarChart bc2(3);
    bc2.setFrame("1950");
    bc2.addBar("Chicago", 1020, "US");
    bc2.addBar("NYC", 1300, "US");
    bc2.addBar("Paris", 1200, "France");
    bc1 = bc2;
    if (bc2.getSize() != 3) {
        cout << "testBarChartAddBar: addBar failed" << endl;
        return false;
    } else if (bc2.getFrame() != "1950") {
        cout << "testBarChartAddBar: getFrame failed" << endl;
        return false;
    } else if (bc1.getSize() != 3) {
        cout << "testBarChartAddBar: operator= failed" << endl;
        return false;
    } else if (bc1.getFrame() != "1950") {
        cout << "testBarChartAddBar: operator= failed" << endl;
        return false;
    } else if (bc1[0].getName() != "Chicago" || bc1[1].getName() != "NYC" || bc1[2].getName() != "Paris") {
        cout << "testBarChartAddBar: operator[] failed" << endl;
        return false;
    }
    cout << "testBarChartAddBar: all passed!" << endl;
    return true;
}

bool testBarChartClear() {
    BarChart bc1;
    bc1.addBar("Chicago", 1020, "US");
    bc1.clear();
    if(bc1.getSize() != 0) {
        cout << "testBarChartClear: clear failed" << endl;
        return false;
    } else if(bc1.getFrame() != "") {
        cout << "testBarChartClear: clear failed" << endl;
        return false;
    }
    cout << "testBarChartClear: all passed!" << endl;
    return true;
}


bool testBarChartDump() {
    stringstream ss;
    string line;
    BarChart bc(3);
    bc.setFrame("1950");
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    bc.dump(ss);
    getline(ss,line);
    if(line != "frame: 1950"){
        cout << "testBarChartDump: failed" << endl;
        return false;
    }
    getline(ss,line);
    if(line != "NYC 1300 US") {
        cout << "testBarChartDump: failed" << endl;
        return false;
    }
    getline(ss,line);
    if(line != "Paris 1200 France") {
        cout << "testBarChartDump: failed" << endl;
        return false;
    }
    getline(ss,line);
    if(line != "Chicago 1020 US") {
        cout << "testBarChartDump: failed" << endl;
        return false;
    }
    cout << "testBarChartDump: all passed!" << endl;
    return true;
}

void testsBarChartGraph() {
    cout << "\nTesting Graph One... " << endl;
    BarChart bc(4);
    bc.setFrame("1950");
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    bc.addBar("Tokyo", 800, "Japan");
    string red("\033[1;36m");
    string blue("\033[1;33m");
    map<string, string> colorMap;
    colorMap["US"] = red;
    colorMap["France"] = blue;
    bc.graph(cout, colorMap, 4);
}

void testsBarChartGraph2() {
    cout << "\nTesting Graph Two... " << endl;
    BarChart bc(5);
    bc.setFrame("1950");
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    bc.addBar("Tokyo", 800, "Japan");
    bc.addBar("Beijing", 1200, "China");
    string red("\033[1;36m");
    string blue("\033[1;33m");
    string gold("\033[1;34m");
    map<string, string> colorMap;
    colorMap["US"] = red;
    colorMap["France"] = blue;
    colorMap["China"] = gold;
    bc.graph(cout, colorMap, 4);
}

bool testBarChartAnimate() {
    string filename = "cities.txt";
    ifstream inFile(filename);
    string title;
    getline(inFile, title);
    string xlabel;
    getline(inFile, xlabel);
    string source;
    getline(inFile, source);
    BarChartAnimate bca(title, xlabel, source);
    if(bca.getSize() != 0) {
        cout << "testBarChartAnimate: getSize failed" << endl;
        return false;
    }
    while (!inFile.eof()) {
        bca.addFrame(inFile);
    }
    if(bca.getSize() != 519) {
        cout << "testBarChartAnimate: addFrame failed" << endl;
        return false;
    } else if(bca[0].getSize() != 12) {
        cout << "testBarChartAnimate: operator[] failed" << endl;
        return false;
    }
    cout << "testBarChartAnimate: all passed!" << endl;
    return true;
}

bool testBarChartAnimate2() {
    string filename = "brands.txt";
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
    if(bca.getSize() != 217) {
        cout << "testBarChartAnimate2: getSize failed" << endl;
        return false;
    } else if(bca[0].getSize() != 75) {
        cout << "testBarChartAnimate: operator[] failed" << endl;
        return false;
    }
    cout << "testBarChartAnimate2: all passed!" << endl;
    return true;
}

int main() {
    testBarDefaultConstructor();
    testBarParamConstructor();
    testBarOperators();
    testBarChartDefaultConstructor();
    testBarChartParamConstructor();
    testBarChartCopyConstructor();
    testBarChartAddBar();
    testBarChartClear();
    testBarChartDump();
    testBarChartAnimate();
    testBarChartAnimate2();
    testsBarChartGraph();
    testsBarChartGraph2();


    return 0;
}