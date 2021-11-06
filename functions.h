//
// Created by zct85 on 2020/11/7.
//

#ifndef INC_2312_FINAL_FUNCTIONS_H
#define INC_2312_FINAL_FUNCTIONS_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <ctime>
using namespace std;

//class for single point
class grid{
    public:
    string Hori_p;
    string Vert_p;
    friend ostream & operator<<(ostream& os, const grid& gr);
    friend bool operator==(const grid& gr1,const grid& gr2);
};
//parent class for ship
class Ship{
public:
    string gettype(){return type;};
    void settype(string type_){type=type_;};
    grid getlocation(){return location;}
    string getVorH(){return VorH;}
    void setlocation(grid _location){location=_location;}
    void setVorH(string _VorH){VorH=_VorH;}
    bool getsink() const{return sink;}
    void setsink(bool _sink){sink=_sink;}
    //getters and setters for status
    grid getpos1(){return pos1;}
    grid getpos2(){return pos2;}
    grid getpos3() {return pos3;}
    grid getpos4() {return pos4;}
    grid getpos5() {return pos5;}

    void setpos1(grid _pos1){pos1=_pos1;}
    void setpos2(grid _pos2){pos2=_pos2;}
    void setpos3(grid _pos3){pos3=_pos3;}
    void setpos4(grid _pos4){pos4=_pos4;}
    void setpos5(grid _pos5){pos5=_pos5;}
    //getters and setters for positions
private:
    grid location;
    string VorH;
    string type;
    bool sink;
    grid pos1,pos2,pos3,pos4,pos5;
};
//not much to implement for inherited classes
class Carrier: public Ship{
private:

public:

};

class Battleship: public Ship{
private:

public:

};

class Cruiser: public Ship{
private:

public:

};

class Submarine: public Ship{
private:

public:

};

class Destroyer: public Ship{
private:

public:

};

void readingfiles(vector<Ship>&ship);
void compare(vector<Ship>&ship, grid input, int &count);
void AIships(vector<Ship>&ship);
void display(vector<Ship>&ship);
grid generate(grid &temp);
bool check(string s, int i);
//define functions here

#endif //INC_2312_FINAL_FUNCTIONS_H
