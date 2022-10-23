#include <iostream>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <conio.h>
using namespace std;


int szerokosc;
int wysokosc;
char pole[100][100];  //new int zainicjowac pamiec pozniej
int punkty=0;
void gotoxy(int x,int y)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(h,c);
}

int funkcja_wysokosc(int &y)
{
    cout<<"podaj wysokosc: ";
    cin >>y;
    return y;
}
int funkcja_szerokosc(int &x)
{
    cout<<"podaj szerokosc: ";
    cin >>x;
    return x;
}


void gra()
{
    system("CLS");
    int x_weza=1,y_weza=1;
    int kierunek =1;
    int ile=0;
    int dlugosc=4;
    int hist_x[1000];
    int hist_y[1000];
    int x_jedz,y_jedz;
    x_jedz=rand()%szerokosc+1;
    y_jedz=rand()%wysokosc+1;
    pole[x_jedz][y_jedz]='j';
    bool koniec=false;
    ///WYSWIETLANIE RAMKI
    gotoxy(0,0);
    for(int i=0; i<=szerokosc+1; i++)
    {
        cout<<char(219);
    }
    cout<<endl;

    for(int i=1; i<=wysokosc; i++)
    {
        cout<<char(219);
        gotoxy(szerokosc+1,i);
        cout<<char(219)<<endl;
    }

    for(int i=0; i<=szerokosc+1; i++)
    {
        cout<<char(219);
    }
    ///KONIEC WYSWIATLANIE RAMKI
    for(;;)  ///PIERWSZA PETLA FOR DO ZMIANY KLAWISZY
    {
        ///Po nicisnieciu przycisku, zmiana kierunku
        int znak;
        int kierunek_2=kierunek;
        if(kbhit())
        {
            znak=getch();
            if(znak==224) znak+=getch();
            if(znak==301) kierunek=1;
            if(znak==304) kierunek=2;
            if(znak==299) kierunek=3;
            if(znak==296) kierunek=4;
            if((kierunek==1)&&(kierunek_2==3)) kierunek=3;
            if((kierunek==2)&&(kierunek_2==4)) kierunek=4;
            if((kierunek==3)&&(kierunek_2==1)) kierunek=1;
            if((kierunek==4)&&(kierunek_2==2)) kierunek=2;
        } ///KONIEC Po nicisnieciu przycisku, zmiana kierunku

        for(;;) ///DRUGA PETLA FOR DO WYSWIETLANIA
        {
            ///INKREMENTACJA WARTOSCI X,Y WEZA
            ile++;
            if(kierunek==1) x_weza++;
            if(kierunek==2) y_weza++;
            if(kierunek==3) x_weza--;
            if(kierunek==4) y_weza--;
            if(x_weza<1) x_weza=szerokosc;
            if(y_weza<1) y_weza=wysokosc;
            if(x_weza>szerokosc) x_weza=1;
            if(y_weza>wysokosc) y_weza=1;
            ///KONIEC INKREMENTACJA WARTOSCI X,Y WEZA
            ///SPRAWDZANIE CZY NIE MA SKUCHY
            if(pole[x_weza][y_weza]=='w')
            {
                koniec=true;
                break;
            }
            ///ZAPISANIE W TABLICY WARTOSCI 'W'-WAZ,'P'-PUSTE POLE
            pole[x_weza][y_weza]='w';
            hist_x[ile]=x_weza;
            hist_y[ile]=y_weza;
            ///CZY WAZ ZJADL JEDZENIE?
            if((x_weza==x_jedz)&&(y_weza==y_jedz))
            {
                punkty++;
                dlugosc++;
                x_jedz=rand()%szerokosc+1;
                y_jedz=rand()%wysokosc+1;
                pole[x_jedz][y_jedz]='j';
            }
            ///PRZYPISANIE DO TABLICY - UKRYWANIE OGONA WEZA W ZALEZNOSCI OD DLUGOSCI
            if(ile>dlugosc) pole[hist_x[ile-dlugosc]][hist_y[ile-dlugosc]]='p';

            ///WYSWIETLANIE NA EKRANIE WEZA, JEDZENIA I PUSTYCH PÓL
            //odswierzanie tylko zmieniajacych sie pól a nie calej planszy,dziala szybciej
            gotoxy(x_weza,y_weza);
            cout<<char(219)<<endl;
            if(ile>dlugosc)
            {
            gotoxy(hist_x[ile-dlugosc],hist_y[ile-dlugosc]);
            cout<<" "<<endl;
            }
            gotoxy(x_jedz,y_jedz);
            cout<<char(219)<<endl;

            //odswierzanie calej planszy, dziala wolniej
            /*for(int i=1; i<=wysokosc; i++)
            {
                for(int j=1; j<=szerokosc; j++)
                {
                    if (pole[i][j]=='w')
                    {
                        gotoxy(i,j);
                        cout<<char(219)<<endl;
                    }
                    if (pole[i][j]=='p')
                    {
                        gotoxy(i,j);
                        cout<<" "<<endl;
                    }
                    if (pole[i][j]=='j')
                    {
                        gotoxy(i,j);
                        cout<<char(219)<<endl;
                    }
                }
            }*/
            Sleep(100);
            ///ZERWANIE DRUGIEJ PETLI FOR PRZY NASICNIECIU KLAWISZA
            if(kbhit()) break;
        }
        if(koniec==true) break;
    }
}
void koniec()
{
    system("CLS");
    cout<<"koniec, zdobyles: "<<punkty<<" punktow";
}


int main()
{
    srand(time(NULL));
    funkcja_szerokosc(szerokosc);
    funkcja_wysokosc(wysokosc);


    gra();
    koniec();

    return 0;
}
