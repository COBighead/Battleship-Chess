//
// Created by zct85 on 2020/11/7.
//

#include "functions.h"
bool check(string s, int i)//function to check if position is valid
{
    if (s!="A" && s!="B" && s!="C" && s!="D" && s!="E" && s!="F" && s!="G" && s!="H" && s!="I" && s!="J"||i>10||i==0)
        return false;
    else
        return true;
}
//function to read
void readingfiles(vector<Ship>&ship){
    cout<<"Battleship chess"<<endl;
    cout<<"******************************"<<endl;
    int count=0;
    ifstream infile;
    vector<grid> taken;
    infile.open("ship_placement.csv");
    //if can't open file
    if (!infile.is_open()){
        cerr<<"File not found!"<<endl;
        exit(1);
    }
    while (!infile.eof())//loop to read file
    {
        string type;
        string origin;
        string direction;
        grid location;
        getline(infile,type,',');
        if (type=="Carrier")
        {
            Carrier temp;
            temp.settype(type);//set ship type
            grid pos1,pos2,pos3,pos4,pos5;
            stringstream Vert_p;
            int vert;
            getline(infile,origin,',');
            location.Hori_p=origin.substr(0,1);
            location.Vert_p=origin.substr(1);
            temp.setlocation(location);//set up start point
            temp.setsink(false);// set ship not sink
            Vert_p<<location.Vert_p;
            Vert_p>>vert;//convert string to int
            if (!check(location.Hori_p,vert))//invalid starting coordinate from file
            {
                cerr<<"Invalid Carrier position! Check Input file"<<endl;
                exit(1);
            }
            getline(infile,direction);
            temp.setVorH(direction);//get and set V or H
            if (direction=="V")
            {
                stringstream V1,V2,V3,V4,V5;
                int v1,v2,v3,v4,v5;
                string V2S,V3S,V4S,V5S;
                V1<<location.Vert_p;
                V1>>v1;//convert string to int

                v2=v1+1;
                v3=v1+2;
                v4=v1+3;
                v5=v1+4;//use int to calculate for each position

                if (v5>10)//invalid vertical coordinate
                {
                    cerr<<"Carrier is outside border!"<<endl;
                    exit(1);
                }

                V2<<v2;
                V3<<v3;
                V4<<v4;
                V5<<v5;//convert int into stringstream

                V2>>V2S;
                V3>>V3S;
                V4>>V4S;
                V5>>V5S;//convert back to string

                pos1.Hori_p=location.Hori_p;
                pos2.Hori_p=location.Hori_p;
                pos3.Hori_p=location.Hori_p;
                pos4.Hori_p=location.Hori_p;
                pos5.Hori_p=location.Hori_p;
                pos1.Vert_p=location.Vert_p;
                pos2.Vert_p=V2S;
                pos3.Vert_p=V3S;
                pos4.Vert_p=V4S;
                pos5.Vert_p=V5S;
                //set coordinate for each temporary position
            }
            if (direction=="H")
            {
                char H1,H2,H3,H4,H5;
                H1=location.Hori_p[0];//convert to char to calculate following horizontal coordinates
                H2=H1+1;
                H3=H2+1;
                H4=H3+1;
                H5=H4+1;

                string H1S(1,H1);
                string H2S(1,H2);
                string H3S(1,H3);
                string H4S(1,H4);
                string H5S(1,H5);//convert to string from char

                if (H5S>"J")//invalid Horizontal position
                {
                    cerr<<"Carrier is outside border!"<<endl;
                    exit(1);
                }

                pos1.Vert_p=location.Vert_p;
                pos2.Vert_p=location.Vert_p;
                pos3.Vert_p=location.Vert_p;
                pos4.Vert_p=location.Vert_p;
                pos5.Vert_p=location.Vert_p;
                pos1.Hori_p=H1S;
                pos2.Hori_p=H2S;
                pos3.Hori_p=H3S;
                pos4.Hori_p=H4S;
                pos5.Hori_p=H5S;
                //set coordinate for each temporary position
            }
            taken.push_back(pos1);
            taken.push_back(pos2);
            taken.push_back(pos3);
            taken.push_back(pos4);
            taken.push_back(pos5);//record each taken point on grid

            temp.setpos1(pos1);
            temp.setpos2(pos2);
            temp.setpos3(pos3);
            temp.setpos4(pos4);
            temp.setpos5(pos5);//set positions for ship
            ship.push_back(temp);

            if (direction!="H" && direction!="V")//not V or H
            {
                cerr<<"Invalid Carrier direction! Check Input file"<<endl;
                exit(1);
            }
            count++;
        }

        if (type=="Battleship")
        {
            Battleship temp;
            temp.settype(type);//set ship type
            grid pos1,pos2,pos3,pos4;
            stringstream Vert_p;
            int vert;
            getline(infile,origin,',');
            location.Hori_p=origin.substr(0,1);
            location.Vert_p=origin.substr(1);
            temp.setlocation(location);//set up start point
            temp.setsink(false);//set ship not sink
            Vert_p<<location.Vert_p;
            Vert_p>>vert;//convert string to int

            if (!check(location.Hori_p,vert))//invalid starting coordinate from file
            {
                cerr<<"Invalid Battleship position! Check Input file"<<endl;
                exit(1);
            }
            getline(infile,direction);
            temp.setVorH(direction);//get and set V or H
            if (direction=="V")
            {
                stringstream V1,V2,V3,V4;
                int v1,v2,v3,v4;
                string V2S,V3S,V4S;
                V1<<location.Vert_p;
                V1>>v1;//convert string to int

                v2=v1+1;
                v3=v1+2;
                v4=v1+3;
                //calculate for each position

                if (v4>10)//invalid vertical coordinate
                {
                    cerr<<"Battleship is outside border!"<<endl;
                    exit(1);
                }

                V2<<v2;
                V3<<v3;
                V4<<v4;//convert into stringstream

                V2>>V2S;
                V3>>V3S;
                V4>>V4S;//convert back to string

                pos1.Hori_p=location.Hori_p;
                pos2.Hori_p=location.Hori_p;
                pos3.Hori_p=location.Hori_p;
                pos4.Hori_p=location.Hori_p;

                pos1.Vert_p=location.Vert_p;
                pos2.Vert_p=V2S;
                pos3.Vert_p=V3S;
                pos4.Vert_p=V4S;
                //set coordinate for each temporary position
            }
            if (direction=="H") {
                char H1, H2, H3, H4;
                H1 = location.Hori_p[0];
                H2 = H1 + 1;
                H3 = H2 + 1;
                H4 = H3 + 1;
                //convert to char to calculate following horizontal coordinates

                string H1S(1, H1);
                string H2S(1, H2);
                string H3S(1, H3);
                string H4S(1, H4);//convert to string from char

                if (H4S > "J") //invalid Horizontal position
                {
                    cerr << "Battleship is outside border!" << endl;
                    exit(1);
                }

                pos1.Vert_p = location.Vert_p;
                pos2.Vert_p = location.Vert_p;
                pos3.Vert_p = location.Vert_p;
                pos4.Vert_p = location.Vert_p;

                pos1.Hori_p = H1S;
                pos2.Hori_p = H2S;
                pos3.Hori_p = H3S;
                pos4.Hori_p = H4S;
                //set coordinate for each temporary position
            }
            temp.setpos1(pos1);
            temp.setpos2(pos2);
            temp.setpos3(pos3);
            temp.setpos4(pos4);
            //set positions for ship
            taken.push_back(pos1);
            taken.push_back(pos2);
            taken.push_back(pos3);
            taken.push_back(pos4);
            //record each taken point on grid
            ship.push_back(temp);

            if (direction!="H" && direction!="V")
            {
                cerr<<"Invalid Battleship direction! Check Input file"<<endl;
                exit(1);
            }
            count++;
        }
        if (type=="Cruiser")
        {
            Cruiser temp;
            temp.settype(type);//set ship type
            grid pos1,pos2,pos3;
            stringstream Vert_p;
            int vert;
            getline(infile,origin,',');
            location.Hori_p=origin.substr(0,1);
            location.Vert_p=origin.substr(1);
            temp.setlocation(location);//set up start point
            temp.setsink(false);//set ship not sink
            Vert_p<<location.Vert_p;
            Vert_p>>vert;//convert string to int
            if (!check(location.Hori_p,vert))//invalid starting coordinate from file
            {
                cerr<<"Invalid Cruiser position! Check Input file"<<endl;
                exit(1);
            }
            getline(infile,direction);
            temp.setVorH(direction);//get and set V or H
            if (direction=="V")
            {
                stringstream V1,V2,V3;
                int v1,v2,v3;
                string V2S,V3S;
                V1<<location.Vert_p;
                V1>>v1;//convert string to int

                v2=v1+1;
                v3=v1+2;
                //calculate for each position

                if (v3>10)//invalid vertical coordinate
                {
                    cerr<<"Cruiser is outside border!"<<endl;
                    exit(1);
                }

                V2<<v2;
                V3<<v3;//convert into stringstream

                V2>>V2S;
                V3>>V3S;//convert back to string

                pos1.Hori_p=location.Hori_p;
                pos2.Hori_p=location.Hori_p;
                pos3.Hori_p=location.Hori_p;

                pos1.Vert_p=location.Vert_p;
                pos2.Vert_p=V2S;
                pos3.Vert_p=V3S;
                //set coordinate for each temporary position
            }
            if (direction=="H") {
                char H1, H2, H3;
                H1 = location.Hori_p[0];
                H2 = H1 + 1;
                H3 = H2 + 1;
                //convert to char to calculate following horizontal coordinates
                string H1S(1, H1);
                string H2S(1, H2);
                string H3S(1, H3);
                //convert to string from char
                if (H3S > "J") //invalid Horizontal position
                {
                    cerr << "Cruiser is outside border!" << endl;
                    exit(1);
                }

                pos1.Vert_p = location.Vert_p;
                pos2.Vert_p = location.Vert_p;
                pos3.Vert_p = location.Vert_p;

                pos1.Hori_p = H1S;
                pos2.Hori_p = H2S;
                pos3.Hori_p = H3S;
                //set coordinate for each temporary position
            }

            taken.push_back(pos1);
            taken.push_back(pos2);
            taken.push_back(pos3);
            //record each taken point on grid
            temp.setpos1(pos1);
            temp.setpos2(pos2);
            temp.setpos3(pos3);
            //set positions for ship
            ship.push_back(temp);

            if (direction!="H" && direction!="V")
            {
                cerr<<"Invalid Cruiser direction! Check Input file"<<endl;
                exit(1);
            }
            count++;

        }

        if (type=="Submarine")
        {
            Submarine temp;
            temp.settype(type);//set ship type
            grid pos1,pos2,pos3;
            stringstream Vert_p;
            int vert;
            getline(infile,origin,',');
            location.Hori_p=origin.substr(0,1);
            location.Vert_p=origin.substr(1);
            temp.setlocation(location);//set up start point
            temp.setsink(false);//set ship not sink
            Vert_p<<location.Vert_p;
            Vert_p>>vert;//convert string to int
            if (!check(location.Hori_p,vert))//invalid starting coordinate from file
            {
                cerr<<"Invalid Submarine position! Check Input file"<<endl;
                exit(1);
            }
            getline(infile,direction);
            temp.setVorH(direction);//get and set V or H
            if (direction=="V")
            {
                stringstream V1,V2,V3;
                int v1,v2,v3;
                string V2S,V3S;
                V1<<location.Vert_p;
                V1>>v1;//convert string to int

                v2=v1+1;
                v3=v1+2;
                //calculate for each position

                if (v3>10)//invalid vertical coordinate
                {
                    cerr<<"Submarine is outside border!"<<endl;
                    exit(1);
                }

                V2<<v2;
                V3<<v3;//convert into stringstream

                V2>>V2S;
                V3>>V3S;//convert back to string

                pos1.Hori_p=location.Hori_p;
                pos2.Hori_p=location.Hori_p;
                pos3.Hori_p=location.Hori_p;

                pos1.Vert_p=location.Vert_p;
                pos2.Vert_p=V2S;
                pos3.Vert_p=V3S;
                //set coordinate for each temporary position
            }
            if (direction=="H") {
                char H1, H2, H3;
                H1 = location.Hori_p[0];
                H2 = H1 + 1;
                H3 = H2 + 1;
                //convert to char to calculate following horizontal coordinates
                string H1S(1, H1);
                string H2S(1, H2);
                string H3S(1, H3);
                //convert to string from char
                if (H3S > "J") //invalid Horizontal position
                {
                    cerr << "Submarine is outside border!" << endl;
                    exit(1);
                }

                pos1.Vert_p = location.Vert_p;
                pos2.Vert_p = location.Vert_p;
                pos3.Vert_p = location.Vert_p;

                pos1.Hori_p = H1S;
                pos2.Hori_p = H2S;
                pos3.Hori_p = H3S;
                //set coordinate for each temporary position
            }
            taken.push_back(pos1);
            taken.push_back(pos2);
            taken.push_back(pos3);
            //record each taken point on grid
            temp.setpos1(pos1);
            temp.setpos2(pos2);
            temp.setpos3(pos3);
            //set positions for ship
            ship.push_back(temp);

            if (direction!="H" && direction!="V")
            {
                cerr<<"Invalid Submarine direction! Check Input file"<<endl;
                exit(1);
            }
            count++;

        }

        if (type=="Destroyer")
        {
            Destroyer temp;
            temp.settype(type);//set ship type
            grid pos1,pos2;
            stringstream Vert_p;
            int vert;
            getline(infile,origin,',');
            location.Hori_p=origin.substr(0,1);
            location.Vert_p=origin.substr(1);
            temp.setlocation(location);//set up start point
            temp.setsink(false);//set ship not sink
            Vert_p<<location.Vert_p;
            Vert_p>>vert;//convert string to int
            if (!check(location.Hori_p,vert))//invalid starting coordinate from file
            {
                cerr<<"Invalid Destroyer position! Check Input file"<<endl;
                exit(1);
            }
            getline(infile,direction);
            temp.setVorH(direction);//get and set V or H
            if (direction=="V")
            {
                stringstream V1,V2;
                int v1,v2;
                string V2S;
                V1<<location.Vert_p;
                V1>>v1;//convert string to int
                v2=v1+1;//calculate for each position

                if (v2>10)//invalid vertical coordinate
                {
                    cerr<<"Destroyer is outside border!"<<endl;
                    exit(1);
                }

                V2<<v2;//convert into stringstream
                V2>>V2S;//convert back to string


                pos1.Hori_p=location.Hori_p;
                pos2.Hori_p=location.Hori_p;

                pos1.Vert_p=location.Vert_p;
                pos2.Vert_p=V2S;
                //set coordinate for each temporary position
            }
            if (direction=="H") {
                char H1, H2;
                H1 = location.Hori_p[0];
                H2 = H1 + 1;
                //convert to char to calculate following horizontal coordinates
                string H1S(1, H1);//convert char to string
                string H2S(1, H2);
                //convert to string from char
                if (H2S > "J") //invalid Horizontal position
                {
                    cerr << "Destroyer is outside border!" << endl;
                    exit(1);
                }
                pos1.Vert_p = location.Vert_p;
                pos2.Vert_p = location.Vert_p;
                pos1.Hori_p = H1S;
                pos2.Hori_p = H2S;
                //set coordinate for each temporary position
            }
            taken.push_back(pos1);
            taken.push_back(pos2);
            //record each taken point on grid
            temp.setpos1(pos1);
            temp.setpos2(pos2);
            //set positions for ship
            ship.push_back(temp);

            if (direction!="H" && direction!="V")//check if direction input is valid
            {
                cerr<<"Invalid Destroyer direction! Check Input file"<<endl;
                exit(1);
            }
            count++;
        }

        if (type!="Carrier" && type!="Battleship" && type!="Cruiser" && type!="Destroyer" && type!="Submarine")
        {
            cerr<<"input file invalid Ship type!"<<endl;//check if ship type is valid
            exit(1);
        }
    }
    if (count!=5)//check ship quantity
    {
        cerr<<"Wrong ship number!"<<endl;
        exit(1);
    }

    for(int i=0;i<taken.size();i++)//check if ship overlaps
    {
        for (int j=i+1;j<taken.size();j++)
        {
            if (taken[i].Vert_p==taken[j].Vert_p && taken[i].Hori_p==taken[j].Hori_p)
            {
                cerr<<"Ship overlaps! Check input file"<<endl;
                exit(1);
            }
        }
    }
    cout<<"// Your ships are ready to fight! //"<<endl;
}
//************************************************ AISships ***********************************************************
void AIships(vector<Ship>&ship){
    Carrier CV;
    Battleship BB;
    Cruiser CA;
    Submarine SS;
    Destroyer DD;
    vector<grid> Taken;
    CV.setsink(false);
    BB.setsink(false);
    CA.setsink(false);
    SS.setsink(false);
    DD.setsink(false);
    //make every ship alive!

    srand(time(nullptr));
    string HorV[5];
    int j=0;
    for (int i=0;i<5;i++)//generate random direction for each ship
    {
        int temp;
        temp=rand()% 2;
            if (temp==1)
                HorV[j]="H";
            else
                HorV[j]="V";
        j++;
    }
    grid CVstart,CVpos2,CVpos3,CVpos4,CVpos5;

    if (HorV[0]=="H")//Decide start point for Carrier
    {
        CV.setVorH("H");
        int Hori=rand()% 6+1;
        switch (Hori) {
            case 1: CVstart.Hori_p="A";
                break;
            case 2: CVstart.Hori_p="B";
                break;
            case 3: CVstart.Hori_p="C";
                break;
            case 4: CVstart.Hori_p="D";
                break;
            case 5: CVstart.Hori_p="E";
                break;
            case 6: CVstart.Hori_p="F";
                break;
        }//get start point Horizontal coordinates that not let carrier exceed border

        char H1=CVstart.Hori_p[0];
        char H2,H3,H4,H5;
        H2=H1+1;
        H3=H2+1;
        H4=H3+1;
        H5=H4+1;
        string H2S(1,H2);
        string H3S(1,H3);
        string H4S(1,H4);
        string H5S(1,H5);
        CVpos2.Hori_p=H2S;
        CVpos3.Hori_p=H3S;
        CVpos4.Hori_p=H4S;
        CVpos5.Hori_p=H5S;//get Horizontal coordinates for the rest of points

        int Vert=rand()% 10+1;
        stringstream Vert_;
        Vert_<<Vert;
        Vert_>>CVstart.Vert_p;//get start point Vertical coordinates
        CVpos2.Vert_p=CVstart.Vert_p;
        CVpos3.Vert_p=CVstart.Vert_p;
        CVpos4.Vert_p=CVstart.Vert_p;
        CVpos5.Vert_p=CVstart.Vert_p;//get Vertical coordinates for the rest of points

    }
    if (HorV[0]=="V")
    {
        CV.setVorH("V");
        int Vert1=rand()% 6+1;
        int Vert2,Vert3,Vert4,Vert5;
        Vert2=Vert1+1;
        Vert3=Vert2+1;
        Vert4=Vert3+1;
        Vert5=Vert4+1;
        stringstream Vert_1,Vert_2,Vert_3,Vert_4,Vert_5;
        Vert_1<<Vert1;
        Vert_1>>CVstart.Vert_p;

        Vert_2<<Vert2;
        Vert_2>>CVpos2.Vert_p;

        Vert_3<<Vert3;
        Vert_3>>CVpos3.Vert_p;

        Vert_4<<Vert4;
        Vert_4>>CVpos4.Vert_p;

        Vert_5<<Vert5;
        Vert_5>>CVpos5.Vert_p;//set vertical coordinates

        int Hori=rand()% 10+1;
        switch (Hori) {//assign each number to a letter
            case 1: CVstart.Hori_p="A";
                break;
            case 2: CVstart.Hori_p="B";
                break;
            case 3: CVstart.Hori_p="C";
                break;
            case 4: CVstart.Hori_p="D";
                break;
            case 5: CVstart.Hori_p="E";
                break;
            case 6: CVstart.Hori_p="F";
                break;
            case 7: CVstart.Hori_p="G";
                break;
            case 8: CVstart.Hori_p="H";
                break;
            case 9: CVstart.Hori_p="I";
                break;
            case 10: CVstart.Hori_p="J";
                break;
        }
        CVpos2.Hori_p=CVstart.Hori_p;
        CVpos3.Hori_p=CVstart.Hori_p;
        CVpos4.Hori_p=CVstart.Hori_p;
        CVpos5.Hori_p=CVstart.Hori_p;//set horizontal coordinates

    }
    CV.setpos1(CVstart);
    CV.setpos2(CVpos2);
    CV.setpos3(CVpos3);
    CV.setpos4(CVpos4);
    CV.setpos5(CVpos5);//set up coordinates
    CV.settype("Carrier");
    Taken.push_back(CVstart);
    Taken.push_back(CVpos2);
    Taken.push_back(CVpos3);
    Taken.push_back(CVpos4);
    Taken.push_back(CVpos5);//set up taken points

    ship.push_back(CV);

    srand(time(nullptr)+5);

    grid BBstart,BBpos2,BBpos3,BBpos4;
    bool nooverlap=true;

    do {
        nooverlap= true;
        if (HorV[1]=="H")
        {
            BB.setVorH("H");
            int Hori=rand()%7+1;

            switch (Hori) {//assign each letter for a number
                case 1: BBstart.Hori_p="A";
                    break;
                case 2: BBstart.Hori_p="B";
                    break;
                case 3: BBstart.Hori_p="C";
                    break;
                case 4: BBstart.Hori_p="D";
                    break;
                case 5: BBstart.Hori_p="E";
                    break;
                case 6: BBstart.Hori_p="F";
                    break;
                case 7: BBstart.Hori_p="G";
                    break;
            }
            char H1=BBstart.Hori_p[0];//string to char
            char H2,H3,H4;
            H2=H1+1;
            H3=H2+1;
            H4=H3+1;
            string H2S(1,H2);
            string H3S(1,H3);
            string H4S(1,H4);
            BBpos2.Hori_p=H2S;
            BBpos3.Hori_p=H3S;
            BBpos4.Hori_p=H4S;//char to string,set up horizontal

            int Vert=rand()% 10+1;
            stringstream Vert_;
            Vert_<<Vert;
            Vert_>>BBstart.Vert_p;
            BBpos2.Vert_p=BBstart.Vert_p;
            BBpos3.Vert_p=BBstart.Vert_p;
            BBpos4.Vert_p=BBstart.Vert_p;

        }
        if (HorV[1]=="V")
        {
            BB.setVorH("V");
            int Vert1=rand()% 7+1;
            int Vert2,Vert3,Vert4;
            Vert2=Vert1+1;
            Vert3=Vert2+1;
            Vert4=Vert3+1;
            stringstream Vert_1,Vert_2,Vert_3,Vert_4;

            Vert_1<<Vert1;
            Vert_1>>BBstart.Vert_p;

            Vert_2<<Vert2;
            Vert_2>>BBpos2.Vert_p;

            Vert_3<<Vert3;
            Vert_3>>BBpos3.Vert_p;

            Vert_4<<Vert4;
            Vert_4>>BBpos4.Vert_p;//convert to string and set vertical coordinate

            int Hori=rand()% 10+1;
            switch (Hori) {
                case 1: BBstart.Hori_p="A";
                    break;
                case 2: BBstart.Hori_p="B";
                    break;
                case 3: BBstart.Hori_p="C";
                    break;
                case 4: BBstart.Hori_p="D";
                    break;
                case 5: BBstart.Hori_p="E";
                    break;
                case 6: BBstart.Hori_p="F";
                    break;
                case 7: BBstart.Hori_p="G";
                    break;
                case 8: BBstart.Hori_p="H";
                    break;
                case 9: BBstart.Hori_p="I";
                    break;
                case 10: BBstart.Hori_p="J";
                    break;
            }
            BBpos2.Hori_p=BBstart.Hori_p;
            BBpos3.Hori_p=BBstart.Hori_p;
            BBpos4.Hori_p=BBstart.Hori_p;//set horizontal
        }
        BB.setpos1(BBstart);
        BB.setpos2(BBpos2);
        BB.setpos3(BBpos3);
        BB.setpos4(BBpos4);

        grid BBtaken[4];//use array to check if current ship position repeat previous ships
        BBtaken[0]=BBstart;
        BBtaken[1]=BBpos2;
        BBtaken[2]=BBpos3;
        BBtaken[3]=BBpos4;

        for (int i=0;i<Taken.size();i++)
        {
            for (int k=0;k<4;k++)
            {
                if (Taken[i].Hori_p==BBtaken[k].Hori_p && Taken[i].Vert_p==BBtaken[k].Vert_p)
                    nooverlap=false;
            }
        }
    }while (!nooverlap);//make sure no overlap ships are recorded
    BB.settype("Battleship");
    Taken.push_back(BBstart);
    Taken.push_back(BBpos2);
    Taken.push_back(BBpos3);
    Taken.push_back(BBpos4);//set taken points
    ship.push_back(BB);

//The rest generating process are quite similar

    grid CAstart,CApos2,CApos3;
    do {
        nooverlap= true;
        if (HorV[2]=="H")
        {
            CA.setVorH("H");
            int Hori=rand()%8+1;

            switch (Hori) {
                case 1: CAstart.Hori_p="A";
                    break;
                case 2: CAstart.Hori_p="B";
                    break;
                case 3: CAstart.Hori_p="C";
                    break;
                case 4: CAstart.Hori_p="D";
                    break;
                case 5: CAstart.Hori_p="E";
                    break;
                case 6: CAstart.Hori_p="F";
                    break;
                case 7: CAstart.Hori_p="G";
                    break;
                case 8: CAstart.Hori_p="H";
                    break;
            }
            char H1=CAstart.Hori_p[0];
            char H2,H3;
            H2=H1+1;
            H3=H2+1;

            string H2S(1,H2);
            string H3S(1,H3);

            CApos2.Hori_p=H2S;
            CApos3.Hori_p=H3S;

            int Vert=rand()% 10+1;
            stringstream Vert_;
            Vert_<<Vert;
            Vert_>>CAstart.Vert_p;
            CApos2.Vert_p=CAstart.Vert_p;
            CApos3.Vert_p=CAstart.Vert_p;
        }

        if (HorV[2]=="V")
        {
            CA.setVorH("V");
            int Vert1=rand()% 8+1;
            int Vert2,Vert3;
            Vert2=Vert1+1;
            Vert3=Vert2+1;

            stringstream Vert_1,Vert_2,Vert_3;

            Vert_1<<Vert1;
            Vert_1>>CAstart.Vert_p;

            Vert_2<<Vert2;
            Vert_2>>CApos2.Vert_p;

            Vert_3<<Vert3;
            Vert_3>>CApos3.Vert_p;

            int Hori=rand()% 10+1;
            switch (Hori) {
                case 1: CAstart.Hori_p="A";
                    break;
                case 2: CAstart.Hori_p="B";
                    break;
                case 3: CAstart.Hori_p="C";
                    break;
                case 4: CAstart.Hori_p="D";
                    break;
                case 5: CAstart.Hori_p="E";
                    break;
                case 6: CAstart.Hori_p="F";
                    break;
                case 7: CAstart.Hori_p="G";
                    break;
                case 8: CAstart.Hori_p="H";
                    break;
                case 9: CAstart.Hori_p="I";
                    break;
                case 10: CAstart.Hori_p="J";
                    break;
            }
            CApos2.Hori_p=CAstart.Hori_p;
            CApos3.Hori_p=CAstart.Hori_p;
        }
        CA.setpos1(CAstart);
        CA.setpos2(CApos2);
        CA.setpos3(CApos3);


        grid CAtaken[3];
        CAtaken[0]=CAstart;
        CAtaken[1]=CApos2;
        CAtaken[2]=CApos3;

        for (int i=0;i<Taken.size();i++)
        {
            for (int k=0;k<3;k++)
            {
                if (Taken[i].Hori_p==CAtaken[k].Hori_p && Taken[i].Vert_p==CAtaken[k].Vert_p)
                    nooverlap=false;
            }
        }
    }while (!nooverlap);
    CA.settype("Cruiser");
    Taken.push_back(CAstart);
    Taken.push_back(CApos2);
    Taken.push_back(CApos3);
    ship.push_back(CA);

    grid SSstart,SSpos2,SSpos3;

    do {
        nooverlap= true;
        if (HorV[3]=="H")
        {
            SS.setVorH("H");
            int Hori=rand()%8+1;

            switch (Hori) {
                case 1: SSstart.Hori_p="A";
                    break;
                case 2: SSstart.Hori_p="B";
                    break;
                case 3: SSstart.Hori_p="C";
                    break;
                case 4: SSstart.Hori_p="D";
                    break;
                case 5: SSstart.Hori_p="E";
                    break;
                case 6: SSstart.Hori_p="F";
                    break;
                case 7: SSstart.Hori_p="G";
                    break;
                case 8: SSstart.Hori_p="H";
                    break;
            }
            char H1=SSstart.Hori_p[0];
            char H2,H3;
            H2=H1+1;
            H3=H2+1;

            string H2S(1,H2);
            string H3S(1,H3);

            SSpos2.Hori_p=H2S;
            SSpos3.Hori_p=H3S;

            int Vert=rand()% 10+1;
            stringstream Vert_;
            Vert_<<Vert;
            Vert_>>SSstart.Vert_p;
            SSpos2.Vert_p=SSstart.Vert_p;
            SSpos3.Vert_p=SSstart.Vert_p;
        }

        if (HorV[3]=="V")
        {
            SS.setVorH("V");
            int Vert1=rand()% 8+1;
            int Vert2,Vert3;
            Vert2=Vert1+1;
            Vert3=Vert2+1;

            stringstream Vert_1,Vert_2,Vert_3;

            Vert_1<<Vert1;
            Vert_1>>SSstart.Vert_p;

            Vert_2<<Vert2;
            Vert_2>>SSpos2.Vert_p;

            Vert_3<<Vert3;
            Vert_3>>SSpos3.Vert_p;

            int Hori=rand()% 10+1;
            switch (Hori) {
                case 1: SSstart.Hori_p="A";
                    break;
                case 2: SSstart.Hori_p="B";
                    break;
                case 3: SSstart.Hori_p="C";
                    break;
                case 4: SSstart.Hori_p="D";
                    break;
                case 5: SSstart.Hori_p="E";
                    break;
                case 6: SSstart.Hori_p="F";
                    break;
                case 7: SSstart.Hori_p="G";
                    break;
                case 8: SSstart.Hori_p="H";
                    break;
                case 9: SSstart.Hori_p="I";
                    break;
                case 10: SSstart.Hori_p="J";
                    break;
            }
            SSpos2.Hori_p=SSstart.Hori_p;
            SSpos3.Hori_p=SSstart.Hori_p;
        }
        SS.setpos1(SSstart);
        SS.setpos2(SSpos2);
        SS.setpos3(SSpos3);


        grid SStaken[3];
        SStaken[0]=SSstart;
        SStaken[1]=SSpos2;
        SStaken[2]=SSpos3;

        for (int i=0;i<Taken.size();i++)
        {
            for (int k=0;k<3;k++)
            {
                if (Taken[i].Hori_p==SStaken[k].Hori_p && Taken[i].Vert_p==SStaken[k].Vert_p)
                    nooverlap=false;
            }
        }
    }while (!nooverlap);
    SS.settype("Submarine");
    Taken.push_back(SSstart);
    Taken.push_back(SSpos2);
    Taken.push_back(SSpos3);
    ship.push_back(SS);

    grid DDstart,DDpos2;

    do {
        nooverlap= true;
        if (HorV[4]=="H")
        {
            DD.setVorH("H");
            int Hori=rand()%9+1;

            switch (Hori) {
                case 1: DDstart.Hori_p="A";
                    break;
                case 2: DDstart.Hori_p="B";
                    break;
                case 3: DDstart.Hori_p="C";
                    break;
                case 4: DDstart.Hori_p="D";
                    break;
                case 5: DDstart.Hori_p="E";
                    break;
                case 6: DDstart.Hori_p="F";
                    break;
                case 7: DDstart.Hori_p="G";
                    break;
                case 8: DDstart.Hori_p="H";
                    break;
                case 9: DDstart.Hori_p="I";
            }
            char H1=DDstart.Hori_p[0];
            char H2;
            H2=H1+1;

            string H2S(1,H2);
            DDpos2.Hori_p=H2S;

            int Vert=rand()% 10+1;
            stringstream Vert_;
            Vert_<<Vert;
            Vert_>>DDstart.Vert_p;
            DDpos2.Vert_p=DDstart.Vert_p;
        }

        if (HorV[4]=="V")
        {
            DD.setVorH("V");
            int Vert1=rand()% 8+1;
            int Vert2;
            Vert2=Vert1+1;

            stringstream Vert_1,Vert_2;

            Vert_1<<Vert1;
            Vert_1>>DDstart.Vert_p;

            Vert_2<<Vert2;
            Vert_2>>DDpos2.Vert_p;

            int Hori=rand()% 10+1;
            switch (Hori) {
                case 1: DDstart.Hori_p="A";
                    break;
                case 2: DDstart.Hori_p="B";
                    break;
                case 3: DDstart.Hori_p="C";
                    break;
                case 4: DDstart.Hori_p="D";
                    break;
                case 5: DDstart.Hori_p="E";
                    break;
                case 6: DDstart.Hori_p="F";
                    break;
                case 7: DDstart.Hori_p="G";
                    break;
                case 8: DDstart.Hori_p="H";
                    break;
                case 9: DDstart.Hori_p="I";
                    break;
                case 10: DDstart.Hori_p="J";
                    break;
            }
            DDpos2.Hori_p=DDstart.Hori_p;
        }
        DD.setpos1(DDstart);
        DD.setpos2(DDpos2);

        grid DDtaken[2];
        DDtaken[0]=DDstart;
        DDtaken[1]=DDpos2;

        for (int i=0;i<Taken.size();i++)
        {
            for (int k=0;k<2;k++)
            {
                if (Taken[i].Hori_p==DDtaken[k].Hori_p && Taken[i].Vert_p==DDtaken[k].Vert_p)
                    nooverlap=false;
            }
        }
    }while (!nooverlap);
    DD.settype("Destroyer");
    Taken.push_back(DDstart);
    Taken.push_back(DDpos2);
    ship.push_back(DD);

    cout<<"// Enemy ships are in position! //"<<endl;
}

bool operator==(const grid& gr1,const grid& gr2)//operator overloading for grid type
{
    if (gr1.Hori_p==gr2.Hori_p && gr1.Vert_p==gr2.Vert_p)
        return true;
    else
        return false;
}

void compare(vector<Ship>&ship, grid input,int &count){//function used to check if hits

    bool hit=false;

    for (int i = 0; i < ship.size(); ++i) {

        if (!ship[i].getsink())//only check surviving ships
        {
            if (ship[i].gettype()=="Carrier")//for carrier type
            {
                if (ship[i].getpos1()==input || ship[i].getpos2()==input || ship[i].getpos3()==input || ship[i].getpos4()==input || ship[i].getpos5()==input )
                {
                    ship[i].setsink(true);//set ship sunk
                    cout<<"sink Carrier!   Position: "<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<", "<<ship[i].getpos3()<<", "<<ship[i].getpos4()<<", "<<ship[i].getpos5()<<endl;
                    hit=true;// to not show missing message
                    count++;//sunk ship count
                    cout<<"sunk ship count: "<<count<<endl;
                }
            }
            if (ship[i].gettype()=="Battleship")
            {
                if (ship[i].getpos1()==input || ship[i].getpos2()==input || ship[i].getpos3()==input || ship[i].getpos4()==input )
                {
                    ship[i].setsink(true);//set ship sunk
                    cout<<"sink Battleship!   Position: "<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<", "<<ship[i].getpos3()<<", "<<ship[i].getpos4()<<endl;
                    hit=true;// to not show missing message
                    count++;
                    cout<<"sunk ship count: "<<count<<endl;
                }
            }
            if (ship[i].gettype()=="Cruiser")
            {
                if (ship[i].getpos1()==input || ship[i].getpos2()==input || ship[i].getpos3()==input)
                {
                    ship[i].setsink(true);//set ship sunk
                    cout<<"sink Cruiser!   Position: "<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<", "<<ship[i].getpos3()<<endl;
                    hit=true;// to not show missing message
                    count++;
                    cout<<"sunk ship count: "<<count<<endl;
                }
            }
            if (ship[i].gettype()=="Submarine")
            {
                if (ship[i].getpos1()==input || ship[i].getpos2()==input || ship[i].getpos3()==input)
                {
                    ship[i].setsink(true);//set ship sunk
                    cout<<"sink Submarine!   Position: "<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<", "<<ship[i].getpos3()<<endl;
                    hit=true;// to not show missing message
                    count++;
                    cout<<"sunk ship count: "<<count<<endl;
                }
            }
            if (ship[i].gettype()=="Destroyer")
            {
                if (ship[i].getpos1()==input || ship[i].getpos2()==input)
                {
                    ship[i].setsink(true);//set ship sunk
                    cout<<"sink Destroyer!   Position: "<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<endl;
                    hit=true;// to not show missing message
                    count++;
                    cout<<"sunk ship count: "<<count<<endl;
                }
            }
        }
    }
    if (!hit)
    {
        cout<<"Missed!"<<endl;
    }
}

grid generate(grid &temp)//function that generate guess for AI
{
    srand(time(nullptr));// reset seed

    int Hori=rand()% 10+1;//generate horizontal coordinate
    switch (Hori) {
        case 1: temp.Hori_p="A";
            break;
        case 2: temp.Hori_p="B";
            break;
        case 3: temp.Hori_p="C";
            break;
        case 4: temp.Hori_p="D";
            break;
        case 5: temp.Hori_p="E";
            break;
        case 6: temp.Hori_p="F";
            break;
        case 7: temp.Hori_p="G";
            break;
        case 8: temp.Hori_p="H";
            break;
        case 9: temp.Hori_p="I";
            break;
        case 10: temp.Hori_p="J";
            break;
    }

    int Vert=rand()% 10+1;//generate vertical coordinate
    stringstream Vert_;
    string Verts;
    Vert_<<Vert;
    Vert_>>Verts;
    temp.Vert_p=Verts;
    return temp;
}


ostream & operator<<(ostream& os, const grid& gr ){//operator overloading for grid type
    os<<gr.Hori_p<<gr.Vert_p;
    return os;
}


void display(vector<Ship>&ship){//function that showing ship information in parameter vector
    for(int i=0;i<ship.size();i++)
    {
        cout<<ship[i].gettype()<<", ";
        if (ship[i].gettype()=="Carrier")
            cout<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<", "<<ship[i].getpos3()<<", "<<ship[i].getpos4()<<", "<<ship[i].getpos5()<<endl;
        if (ship[i].gettype()=="Battleship")
            cout<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<", "<<ship[i].getpos3()<<", "<<ship[i].getpos4()<<endl;
        if (ship[i].gettype()=="Cruiser")
            cout<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<", "<<ship[i].getpos3()<<endl;
        if (ship[i].gettype()=="Submarine")
            cout<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<", "<<ship[i].getpos3()<<endl;
        if (ship[i].gettype()=="Destroyer")
            cout<<ship[i].getpos1()<<", "<<ship[i].getpos2()<<endl;
        //show positions

        if (ship[i].getsink())
            cout<<"sunk"<<endl;
        if (!ship[i].getsink())
            cout<<"survive"<<endl;
        //show status

    }
}



