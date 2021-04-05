#include<winbgim.h>
#include<iostream>
#define BLACK 0
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4
#define MAGENTA 5 
#define BROWN 6 
#define LIHGTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15
using namespace std;
//VE MAN HINH
void CreateScreen(int maxx, int maxy){
	setcolor(RED);
	setlinestyle(0, 4, 9);
	rectangle(0, 0, maxx, maxy);// ve hinh chu nhat
}
//TAO NODE
void CreateNode(int x, int y, char name[], int thinkness, int color){
	setcolor(color);
	settextstyle(4, HORIZ_DIR, 2);
	outtextxy(x-13, y-12, name);
	circle(x, y, 25);
}
//
int main(){
	initwindow(1009, 713);
	char node1[] = "00", node2[] = "fi";
	CreateNode(500, 500, node1, 0, WHITE);
	CreateNode(250, 500, node2, 0, WHITE);
	CreateScreen(1000, 700);
	
	while(!kbhit());
	return 0;
}
