#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <iomanip>
using namespace std;
void menu();
void game();
void controls(char s[][22],int temp[][22],int eating);
void credits();
void table(char s[][22],int score);
bool checkFood(char s[][22],int fx,int fy);
void spawnFood(char s[][22],int & fx,int & fy);
bool gameover(char s[][22],int temp[][22]);
void endgame(int score,int highscore);
void help();
void options();
void difficulty();
void pause();

int lenght; 
char contr='n';
int chek[32][22];
double diff=0.5; 
int main()
{
    srand(time(0)); 
    int i;
    char sl; 
    for(i=0;i<9999;i++)
    {
        if(i>0)
        {
            cout<<""<<endl;
            cout<<"Do you want to play again ? [y/n]   ";
            cin>>sl;
            if(sl=='y')
            {
                system("cls"); //clearing screen
                goto start;
            }
            else goto quit;
        }
        start: 
        {
            menu(); 
        }
        cin>>sl; 
        if(sl=='1')
        {
            system("cls"); 
            game(); 
            i=1;
        }
        else if(sl=='2')
        {
            options();
            system("cls");
            goto start;
            i=1;
        }
        else if(sl=='3') goto quit;
        else
        {
            system("cls");
            i=1;
            goto start;
        }
    }
    quit: //quits program
        {
            system("exit");
        }

    return 0;
}


void table(char s[][22],int score)  //function for showing table (screen in which snake moves
{
    int x=32; //i am using coordinates for displaying the table
    int y=22;
    int i,j;
    for(i=0;i<y;i++)
    {
        for(j=0;j<x;j++)
        {
            if(j<(x-1)) cout<<s[j][i];
            if(j==(x-1)) cout<<s[j][i]<<endl;
        }
    }
    cout<<""<<endl;
    cout<<"Your score: "<<score;
}

void game()
{   char s[32][22]; 
    int temp[32][22]; 
    int i,j,fx,fy,x,y,score=0,highscore=score; 
    double k;
    int eating; //if snake eats food, this becomes 1, and snake gains lenght
    //preparations for game: setting table borders
    for(i=0;i<22;i++)
    {
        for(j=0;j<32;j++)
        {
            if(i==0 || i==21) s[j][i]='-';
            if(i>0 && i<21) s[j][i]=' ';
            if(j==0 || j==31) s[j][i]='|';
        }
    }
    spawnFood(s,fx,fy); //calling food spawn function
    for(y=1;y<21;y++)
    {
        for(x=1;x<31;x++)
        {
            temp[x][y]=0; //setting all the temp values to 0,
        }                 //to see where snake parts are, and where nothing (0);
    }
    s[17][10]='o'; //finally, sets primary snake position. o is head.
    s[16][10]='*';
    s[15][10]='*';

    temp[15][10]=3; //numbering snake parts
    temp[16][10]=2;
    temp[17][10]=1;

    system("cls");
    table(s,score); //calling table function to show a table
    lenght=3; //snake primary lenght

    while(true) //game starts
    {
        eating=0; //setting value to 0, because snake hasnt eaten anything
        Sleep(diff*1000); //delaying some time, how fast snake moves depends on difficulty
        if(kbhit()) //checking if some key is pressed
        {
            contr=getch(); //if pressed, getting info about that key. this is needed for snake controls
            if(contr=='s') pause(); //if 0, pauses game
            goto movemake; //starts making snake moves
        }
        else
        {
            goto movemake; //if no key is pressed, snake just moves
        }
        movemake:
        {
            for(x=1;x<31;x++) //a loop for checking where are snake parts
            {
                for(y=1;y<21;y++)
                {
                    if(s[x][y]=='*')
                    {
                        chek[x][y]=1; //this is needed for checking if snake hits its tail or borders
                    }
                    else chek[x][y]=0;
                }
            }
            if(checkFood(s,fx,fy)==true) //if snake eats something, some info needs to be sent for snake to gain lenght
            {
                eating=1;
                score=score+1;
                controls(s,temp,eating); //calling snake control and movement function
                spawnFood(s,fx,fy);
            }
            else
            {
                controls(s,temp,eating); //snake only moves
            }

            if(gameover(s,temp)==true) goto gameEnd; //if snake has hit something, game terminates
            else
            {
                goto LoopEnd;
            }
        }

        LoopEnd: //when loop ends, screen clears, updated table and score shows
        {
            system("cls");
            table(s,score);
            if(score>highscore) highscore=score;
        }
    }
    gameEnd:
    {
        endgame(score,highscore); //calls endgame screen
        return; //returns to int main
    }
}
void controls(char s[][22],int temp[][22],int eating) //finally, the coolest part :)
{
    int i,x,y;
    for(i=lenght;i>0;i--) //snake starts moving from tail to head
    {
        if(i==lenght) //when i equals to the number of snakes last part
        {
            for(x=1;x<31;x++)
            {
                for(y=1;y<21;y++)
                {
                    if(temp[x][y]==i && s[x][y]=='*')
                    {
                        if(eating==0) //if snake doesnt eat anything, the last part just disappears
                        {
                            s[x][y]=' '; temp[x][y]=0;
                            x=30;
                            y=20;
                        }
                        else if(eating==1) //if snake eats food, it moves, but the last part stays there,
                        {                  //giving snake 1 more part
                            s[x][y]='*'; temp[x][y]=lenght+1;
                            lenght++; //this new part number will be new length
                            x=30;
                            y=20;
                        }
                    }
                }
            }
        }
        else if(i>1 && i<lenght) // all other snake parts stays where they are, but
        {                        // their values (temp) will increase by 1
            for(x=1;x<31;x++)
            {
                for(y=1;y<21;y++)
                {
                    if(temp[x][y]==i && s[x][y]=='*')
                    {
                        temp[x][y]=i+1;
                        x=30;
                        y=20;
                    }
                }
            }
        }
        else if(i==1) //the hardest part, when i is equal to snake's head value.
        {
            for(x=1;x<31;x++)
            {
                for(y=1;y<21;y++)
                {
                    if(temp[x][y]==i && s[x][y]=='o')
                    {
                        movecheck:
                        if(contr!='z' && contr!='w' && contr!='a' && contr!='d') //if no control button is pressed,
                        {                                                       //snake just moves in its direction forward
                        s[x][y]='*'; temp[x][y]=i+1;
                        if(temp[x-1][y]==i+2) //several situations
                        {
                            s[x+1][y]='o'; temp[x+1][y]=1;
                            return; //when snake moves its head, loop ends, we return to void game
                        }
                        else if(temp[x+1][y]==i+2)
                        {
                            s[x-1][y]='o'; temp[x-1][y]=1;
                            return;
                        }
                        else if(temp[x][y+1]==i+2)
                        {
                            s[x][y-1]='o'; temp[x][y-1]=1;
                            return;
                        }
                        else if(temp[x][y-1]==i+2)
                        {
                            s[x][y+1]='o'; temp[x][y+1]=1;
                            return;
                        }
                        }
                        else if(contr=='w') //if control buttons are pressed, snake moves to that direction
                        {
                            if(temp[x][y-1]==0) //if the value of the square in front of snake's head equals 0
                            {                   //snake can move to it
                            s[x][y]='*'; temp[x][y]=i+1;
                            s[x][y-1]='o'; temp[x][y-1]=1;
                            return;
                            }
                            else //if not, we return to checking if control button is pressed
                            {    //the new contr value will not be control button
                                contr='n';
                                goto movecheck;
                            }
                        }
                        else if(contr=='z')
                        {
                            if(temp[x][y+1]==0)
                            {
                            s[x][y]='*'; temp[x][y]=i+1;
                            s[x][y+1]='o'; temp[x][y+1]=1;
                            return;
                            }
                            else
                            {
                                contr='n';
                                goto movecheck;
                            }
                        }
                        else if(contr=='a')
                        {
                            if(temp[x-1][y]==0)
                            {
                            s[x][y]='*'; temp[x][y]=i+1;
                            s[x-1][y]='o'; temp[x-1][y]=1;
                            return;
                            }
                            else
                            {
                                contr='n';
                                goto movecheck;
                            }
                        }
                        else if(contr=='d')
                        {
                            if(temp[x+1][y]==0)
                            {
                            s[x][y]='*'; temp[x][y]=i+1;
                            s[x+1][y]='o'; temp[x+1][y]=1;
                            return;
                            }
                            else
                            {
                                contr='n';
                                goto movecheck;
                            }
                        }
                    }
                }
            }
        }
    }
} //finally, the snake moves :)

bool checkFood(char s[][22],int fx,int fy) //function for checking if snake has eaten the food
{
    int x,y,c=0;
    for(x=1;x<31;x++)
    {
        for(y=1;y<21;y++)
        {
            if(s[x][y]=='o' && x==fx && y==fy)
            {
                c=1;
            }
        }
    }
    if(c==1) return true;
    else return false;
}

void spawnFood(char s[][22],int & fx,int & fy) //function for spawning new food
{
    //food spawning
        int i,j;
        fx=(rand()%30)+1; //generates random value
        fy=(rand()%20)+1;
        for(j=1;j<31;j++)
        {
            for(i=1;i<21;i++)
            {
                if(s[j][i]!='*' && s[j][i]!='o') //checks if there is something in generated value square
                {
                    s[fx][fy]='+';
                    return;
                }
                else //if there is something, generates again, and checks
                {
                    fx=(rand()%30)+1;
                    fy=(rand()%20)+1;
                    i=1;
                    j=1;
                }
            }
        }
}

bool gameover(char s[][22],int temp[][22]) //checking if snake has hit its tail or borders,
{
    int x,y,c=0;

    for(x=0;x<32;x++)
    {
        for(y=0;y<22;y++)
        {
            if((x==0 || x==31 || y==0 || y==21) && s[x][y]=='o')
            {
                c=1;
            }
            if(chek[x][y]==1 && s[x][y]=='o')
            {
                c=1;
            }
        }
    }
    if(c==1) return true; //if yes, game ends
    if(c==0) return false;
}

void endgame(int score,int highscore) //just some screens for certain actions
{
    cout<<""<<endl<<endl;
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<"|    *****      *     *       * ******       ****  *       ****** ****    |"<<endl;
    cout<<"|   *          * *    * *   * * *           *    *  *     * *     *   *   |"<<endl;
    cout<<"|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |"<<endl;
    cout<<"|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |"<<endl;
    cout<<"|    *****  *       * *       * ******       ****      *    ***** *   *   |"<<endl;
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<""<<endl<<endl;
    cout<<"                        Y O U R   S C O R E : "<<score<<endl<<endl;
    cout<<"                        H I G H   S C O R E : "<<highscore<<endl;
    cout<<""<<endl<<endl;
}

void menu()
{
    cout<<"                                                                                                                                                      "<<endl;
    cout<<" ---------------------------------------------------------------------------------------------------------------------------------------------------- | "<<endl;
    cout<<"|                                                                                                                                                     | "<<endl;
    cout<<"|  *         * ****** *      ****   ****  **   ** *****   ***** ****    *****  **    *     **     *  * *****    ****       **     **   ** *****       | "<<endl;
    cout<<"|   *       *  *      *     *      *    * * * * * *         *  *    *  *       * *   *    *  *    * *  *       *          *  *    * * * * *           | "<<endl;
    cout<<"|    *  *  *   ****   *     *      *    * *  *  * ****      *  *    *   *****  *  *  *   *    *   **   ****    *   ***   *    *   *  *  * ****        | "<<endl;
    cout<<"|     * * *    *      *     *      *    * *     * *         *  *    *        * *   * *  ********  * *  *       *   * *  ********  *     * *           | "<<endl;
    cout<<"|      * *     ****** *****  ****   ****  *     * *****     *   ****    *****  *    ** *        * *  * *****     ****  *        * *     * *****       | "<<endl;
    cout<<"|                                                                                                                                                     | "<<endl;
    cout<<" ------------------------------------------------------------------------------------------------------------------------------------------------------  "<<endl;
    cout<<""<<endl<<endl;
    cout<<"                     M E N U:    "<<endl<<endl;
    cout<<"                  1: Start Game  "<<endl<<endl;
    cout<<"                  2: Options    "<<endl<<endl;
    cout<<"                  3: Exit     "<<endl<<endl;
}

void help()
{
    char sel;
    system("cls");
    while(true)
    {
    cout<<" ----------------------------------------------"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                     w - up                   |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|            a - left        d - right         |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                    z - down                  |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                    s - Pause                 |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<" ---------------------------------------------- "<<endl<<endl<<endl;
    cout<<"Go back? [y/n]  ";
    cin>>sel;
    if(sel=='y') return;
    else system("cls");
    }
}
void options()
{
    char sel;
    system("cls");
    while(true)
    {
    system("cls");
    cout<<""<<endl<<endl;
    cout<<"                          O P T I O N S:      "<<endl<<endl;
    cout<<"                       1: Choose Difficulty   "<<endl<<endl;
    cout<<"                       2: Controls            "<<endl<<endl;
    cout<<"                       3: Go Back             "<<endl<<endl;
    cin>>sel;
    if(sel=='1') difficulty();
    else if(sel=='2') help();
    else if(sel=='3') return;
    else system("cls");
    }
}

void difficulty() //function for setting difficulty (how fast snake moves
{
    char sel;
    system("cls");
    while(true)
    {
    cout<<""<<endl<<endl;
    cout<<"          C U R R E N T   D I F F I C U L T Y:"<<endl<<endl;
    if(diff==1) cout<<"                         E A S Y"<<endl<<endl;
    else if(diff==0.5) cout<<"                       N O R M A L"<<endl<<endl;
    else if(diff==0.2) cout<<"                         H A R D"<<endl<<endl;
    else if(diff==0.1) cout<<"                 S U P E R   H A R D"<<endl<<endl;
    else if(diff==0.03) cout<<"                 I M P O S S I B L E"<<endl<<endl;
    cout<<"          C H O O S E   D I F F I C U L T Y :"<<endl<<endl;
    cout<<"                       1: Easy        "<<endl<<endl;
    cout<<"                       2: Normal      "<<endl<<endl;
    cout<<"                       3: Hard        "<<endl<<endl;
    cout<<"                       4: Super Hard  "<<endl<<endl;
    cout<<"                       5: Impossible  "<<endl<<endl<<endl<<endl;
    cout<<"                       6: Go Back     "<<endl<<endl;
    cin>>sel;
    if(sel=='1')  //there are 5 ready difficulties
    {
        diff=1;
        system("cls");
    }
    else if(sel=='2')
    {
        diff=0.5;
        system("cls");
    }
    else if(sel=='3')
    {
        diff=0.2;
        system("cls");
    }
    else if(sel=='4')
    {
        diff=0.1;
        system("cls");
    }
    else if(sel=='5')
    {
        diff=0.03;
        system("cls");
    }
    else if(sel=='6') return;
    else system("cls");
    }
}

void pause() //pauses game
{
    char c;
    cout<<""<<endl<<endl;
    cout<<"Game paused. Do you want to continue? [y/n]  ";
    ooo:
    cin>>c;
    if(c=='y') return;
    else goto ooo;
}
