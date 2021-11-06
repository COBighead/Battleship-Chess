
#include "functions.h"
using namespace std;

int main() {
    vector <Ship> Player,AI;
    vector<grid> Playerhist,AIhist;//list to record history
    string inputs;
    grid input,AIinput;
    bool repeat=false;
    int Playercount=0,AIcount=0;


    readingfiles(Player);
    AIships(AI);//generate ships for each player

    while (Playercount<5 && AIcount<5)
    {
        bool valid;
        do {
            valid=true;
            cout<<"Enter the grid you want to try (ex.A5), enter Q to quit"<<endl;
            getline(cin,inputs);
            if (inputs=="Q")//Quit option
            {
                cout<<"Your ships: "<<endl;
                display(Player);
                cout<<endl;
                cout<<"Enemy ships: "<<endl;
                display(AI);
                //show ships and guesses
                cout<<"Your guesses: ";
                for (int i = 0; i < Playerhist.size(); ++i) {
                    cout<<Playerhist[i]<<" ";
                }
                cout<<endl;
                cout<<"Opponent guesses: ";
                for (int i = 0; i < AIhist.size(); ++i) {
                    cout<<AIhist[i]<<" ";
                }

                exit(0);
            }
            input.Hori_p=inputs.substr(0,1);
            input.Vert_p=inputs.substr(1);//convert input to grid type
            int v=atoi(input.Vert_p.c_str());

            if (!check(input.Hori_p,v))
            {
                valid= false;
                cout<<"Please enter valid position!"<<endl;
            }

        }while (!valid);//valid player input

        do {
            for (int i = 0; i < Playerhist.size(); ++i) {
                if(Playerhist[i]==input)
                {
                    repeat= true;
                    cout<<"Please try another unfired grid"<<endl;
                    getline(cin,inputs);
                    input.Hori_p=inputs.substr(0,1);
                    input.Vert_p=inputs.substr(1);
                }
                else
                    repeat= false;//when no repeat
            }
        }while (repeat);//check if input repeats previous inputs

        cout<<"You ";
        compare(AI,input,AIcount);//check if hits
        Playerhist.push_back(input);

        generate(AIinput);//generate a guess for AI

        do {
            for (int i = 0; i < AIhist.size(); ++i) {
                if(AIhist[i]==AIinput)
                {
                    repeat= true;
                    generate(AIinput);
                }
                else
                    repeat= false;
            }
        }while (repeat);//check if AI input repeats

        cout<<"Enemy fired at "<<AIinput<<endl;
        cout<<"Enemy ";
        compare(Player,AIinput,Playercount);//Computer player's turn
        AIhist.push_back(AIinput);

        //show status after each turn
        cout<<"Ships you sink: "<<AIcount<<endl;
        cout<<"Your sunk ships: "<<Playercount<<endl;

    }
    if (AIcount==5 && Playercount<5)//Computer player's 5 ships are sunk
    {
        cout<<endl;
        cout<<"==========You won!=========="<<endl;//show ships after game
        cout<<"Your ships: "<<endl;
        display(Player);
        cout<<endl;
        cout<<"Enemy ships: "<<endl;
        display(AI);
    }
    if (Playercount==5 && AIcount<5)//Player's 5 ships are sunk
    {
        cout<<endl;
        cout<<"==========You lost!=========="<<endl;//show ships after game
        cout<<"Your ships: "<<endl;
        display(Player);
        cout<<endl;
        cout<<"Enemy ships: "<<endl;
        display(AI);
    }
    if (Playercount==5 && AIcount==5)
    {
        cout<<"==========DRAW=========="<<endl;
        cout<<"Your ships: "<<endl;
        display(Player);
        cout<<endl;
        cout<<"Enemy ships: "<<endl;
        display(AI);
    }

    //show guesses after game
    cout<<"Your guesses: ";
    for (int i = 0; i < Playerhist.size(); ++i) {
        cout<<Playerhist[i]<<" ";
    }
    cout<<endl;
    cout<<"Opponent guesses: ";
    for (int i = 0; i < AIhist.size(); ++i) {
        cout<<AIhist[i]<<" ";
    }

    return 0;
}
