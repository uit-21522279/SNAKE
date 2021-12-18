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
            cout<<"Bạn có muốn tiếp tục chơi ? [y/n]   ";
            cin>>sl;
            if(sl=='y')
            {
                system("cls");
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
    quit:
        {
            system("exit");
        }

    return 0;
}

void table(char s[][22],int score)
{
    int x=32;
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
    int eating;
    for(i=0;i<22;i++)
    {
        for(j=0;j<32;j++)
        {
            if(i==0 || i==21) s[j][i]='-';
            if(i>0 && i<21) s[j][i]=' ';
            if(j==0 || j==31) s[j][i]='|';
        }
    }
    spawnFood(s,fx,fy);
    for(y=1;y<21;y++)
    {
        for(x=1;x<31;x++)
        {
            temp[x][y]=0;
        }
    }
    s[17][10]='o';
    s[16][10]=(char)219;
    s[15][10]=(char)219;

    temp[15][10]=3;
    temp[16][10]=2;
    temp[17][10]=1;

    system("cls");
    table(s,score);
    lenght=3;
    while(true)
    {
        eating=0;
        Sleep(diff*1000);
        if(kbhit())
        {
            contr=getch();
            if(contr=='s') pause();
            goto movemake;
        }
        else
        {
            goto movemake;
        }
        movemake:
        {
            for(x=1;x<31;x++)
            {
                for(y=1;y<21;y++)
                {
                    if(s[x][y]=='*')
                    {
                        chek[x][y]=1;
                    }
                    else chek[x][y]=0;
                }
            }
            if(checkFood(s,fx,fy)==true)
            {
                eating=1;
                score=score+1;
                controls(s,temp,eating);
                spawnFood(s,fx,fy);
            }
            else
            {
                controls(s,temp,eating);
            }

            if(gameover(s,temp)==true) goto gameEnd;
            else
            {
                goto LoopEnd;
            }
        }

        LoopEnd:
        {
            system("cls");
            table(s,score);
            if(score>highscore) highscore=score;
        }
    }
    gameEnd:
    {
        endgame(score,highscore);
        return;
    }
}
void controls(char s[][22],int temp[][22],int eating)
{
    int i,x,y;
    for(i=lenght;i>0;i--)
    {
        if(i==lenght)
        {
            for(x=1;x<31;x++)
            {
                for(y=1;y<21;y++)
                {
                    if(temp[x][y]==i && s[x][y]==(char)219)
                    {
                        if(eating==0)
                        {
                            s[x][y]=' '; temp[x][y]=0;
                            x=30;
                            y=20;
                        }
                        else if(eating==1)
                        {
                            s[x][y]=(char)219; temp[x][y]=lenght+1;
                            lenght++;
                            x=30;
                            y=20;
                        }
                    }
                }
            }
        }
        else if(i>1 && i<lenght)
        {
            for(x=1;x<31;x++)
            {
                for(y=1;y<21;y++)
                {
                    if(temp[x][y]==i && s[x][y]==(char)219)
                    {
                        temp[x][y]=i+1;
                        x=30;
                        y=20;
                    }
                }
            }
        }
        else if(i==1)
        {
            for(x=1;x<31;x++)
            {
                for(y=1;y<21;y++)
                {
                    if(temp[x][y]==i && s[x][y]=='o')
                    {
                        movecheck:
                        if(contr!='z' && contr!='w' && contr!='a' && contr!='d')
                        {
                        s[x][y]=(char)219; temp[x][y]=i+1;
                        if(temp[x-1][y]==i+2)
                        {
                            s[x+1][y]='o'; temp[x+1][y]=1;
                            return;
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
                        else if(contr=='w')
                        {
                            if(temp[x][y-1]==0)
                            {
                            s[x][y]=(char)219; temp[x][y]=i+1;
                            s[x][y-1]='o'; temp[x][y-1]=1;
                            return;
                            }
                            else 
                            {    
                                contr='n';
                                goto movecheck;
                            }
                        }
                        else if(contr=='z')
                        {
                            if(temp[x][y+1]==0)
                            {
                            s[x][y]=(char)219; temp[x][y]=i+1;
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
                            s[x][y]=(char)219; temp[x][y]=i+1;
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
                            s[x][y]=(char)219; temp[x][y]=i+1;
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
} //finally, the snake moves 🙂

bool checkFood(char s[][22],int fx,int fy)
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

void spawnFood(char s[][22],int & fx,int & fy)
{
    //food spawning
        int i,j;
        fx=(rand()%30)+1; //generates random value
        fy=(rand()%20)+1;
        for(j=1;j<31;j++)
        {
            for(i=1;i<21;i++)
            {
                if(s[j][i]!=(char)219 && s[j][i]!='o')
                {
                    s[fx][fy]=(char)219;
                    return;
                }
                else
                {
                    fx=(rand()%30)+1;
                    fy=(rand()%20)+1;
                    i=1;
                    j=1;
                }
            }
        }
}

bool gameover(char s[][22],int temp[][22])
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

void endgame(int score,int highscore)
{actions
    cout<<""<<endl<<endl;
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<"|    *****      *     *       * ******       ****  *       ****** ****    |"<<endl;
    cout<<"|   *          * *    * *   * * *           *    *  *     * *     *   *   |"<<endl;
    cout<<"|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |"<<endl;
    cout<<"|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |"<<endl;
    cout<<"|    *****  *       * *       * ******       ****      *    ***** *   *   |"<<endl;
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<""<<endl<<endl;
    cout<<"                        Đ I Ể M  C Ủ A  B Ạ N :   "<<score<<endl<<endl;
    cout<<"                        Đ I Ể M  C A O  N H Ấ T : "<<highscore<<endl;
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
    cout<<"                  1: Bắt Đầu     "<<endl<<endl;
    cout<<"                  2: Tuỳ Chọn    "<<endl<<endl;
    cout<<"                  3: Thoát       "<<endl<<endl;
}

void help()
{
    char sel;
    system("cls");
    while(true)
    {
    cout<<" ----------------------------------------------"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                     w - Lên                  |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|            a - Qua trái        d - Qua phải  |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                    z - Xuống                 |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                    s - Dừng                  |"<<endl;
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
    cout<<"                          T U Ỳ C H Ọ N :      "<<endl<<endl;
    cout<<"                       1: Chọn Độ Khó          "<<endl<<endl;
    cout<<"                       2: Bảng Điều Khiển      "<<endl<<endl;
    cout<<"                       3: Quay lại             "<<endl<<endl;
    cin>>sel;
    if(sel=='1') difficulty();
    else if(sel=='2') help();
    else if(sel=='3') return;
    else system("cls");
    }
}

void difficulty()
{
    char sel;
    system("cls");
    while(true)
    {
    cout<<"                   C H Ọ N Đ Ộ K H Ó :"<<endl<<endl;
    cout<<"                       1: Dễ          "<<endl<<endl;
    cout<<"                       2: Bình Thường "<<endl<<endl;
    cout<<"                       3: Khó         "<<endl<<endl;
    cout<<"                       4: Quay Lại    "<<endl<<endl;
    cin>>sel;
     if(sel=='1')
    {
        diff=0.5;
        system("cls");
         cout<<"Done";return;
    }
    else if(sel=='2')
    {
        diff=0.1;
        system("cls");
        cout<<"Done";return;
    }
    else if(sel=='3')
    {
        diff=0.05;
        system("cls");
        cout<<"Done";return;
    }
    else if(sel=='4') return;
    else system("cls");
    }
}

void pause()
{
    char c;
    cout<<""<<endl<<endl;
    cout<<"Kết thúc trò chơi. Bạn có muốn tiếp tục? [y/n]  ";
    ooo:
    cin>>c;
    if(c=='y') return;
    else goto ooo;
}
