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
void createScreenWelcome(){
	initwindow(1009, 713);
	settextstyle(1, HORIZ_DIR, 1);
	outtextxy(100, 100, "CHAO MUNG DEN VOI CHUONG TRINH DEMO DO THI");
	int mx=getmaxx()/2; int my=getmaxy()/2;
	setbkcolor(BLUE);
	setcolor(RED);
	setfillstyle(1,RED);
	bar(mx-150,my-100,mx+150,my+100);
	setcolor(YELLOW);
	setfillstyle(1,YELLOW);
	moveto(mx,my-70);
	lineto(mx+50,my+60);
	lineto(mx-70,my-25);
	lineto(mx+70,my-25);
	lineto(mx-50,my+60);
	lineto(mx,my-70);
	floodfill(mx,my,YELLOW);
	floodfill(mx,my-30,YELLOW);
	floodfill(mx+20,my+30,YELLOW);
	floodfill(mx-20,my+30,YELLOW);
	floodfill(mx-50,my-20,YELLOW);
	floodfill(mx+50,my-20,YELLOW);
	Sleep(3500);
	closegraph();
}
void CreateScreen(int maxx, int maxy){
	char Menu[9][5] = {"DFS", "BFS", "X->Y", "TPLT", "HMT", "EUL", "DTR", "DTH", "CCA"};
	char Toolbar[8][6] = {"New", "Open", "Save", "AddV", "AddE", "Move", "RName", "Del"};
	initwindow(1009, 713);
	setbkcolor(15);
	setcolor(BLUE);
	setlinestyle(0, 0, 10);
	cleardevice();
	//ve khung man hinh
	rectangle(0, 0, maxx, maxy);
	setlinestyle(0, 0, 2);
	settextstyle(4, HORIZ_DIR, 5);
	//ve thanh cong cu
	for(int i=1; i<8; i++){
		rectangle(10 + i*123, 10, 10 + (i-1)*123, 52);
		settextstyle(4, HORIZ_DIR, 1);
		outtextxy(10 + (i-1)*123 + 10, 10 + 10, Toolbar[i-1]);
		if(i == 7){
			outtextxy(10 + (i)*123 + 10, 10 + 10, Toolbar[i]);
		}
	}
	//ve khung thanh cong cu
	rectangle(10, 10, maxx - 10, 52);
	
	//ve khung menu
	rectangle(10, 58, 326, 366);
	//ve bang menu. co su support cua Hung
	int c = 0;// bien c la bien lay vi tri cua ten menu trong mang Menu
	for(int i = 1; i <= 3; i++){
		for(int j = 1; j <= 3; j++){
			rectangle(10 + j*100 + (j)*4, 62 + (i-1)*76, 10 + (j-1)*100 + j*4, 72+62 + (i-1)*76);
			//setbkcolor(14);
			outtextxy(10 + j*100 - 80 + j*4, 62 + (i-1)*76 + 25, Menu[c]);
			c++;
		}
	}
	//ve o Topo Sort
	rectangle(14, 290, 322, 362);
	//ghi chu Topo Sort
	setfillstyle(1, 7); bar(14, 290, 322, 362);
	setbkcolor(7);
	outtextxy(100, 315, "Topo Sort");
	
	
	//ve khung ma tran don vi
	rectangle(10, 372, 326, maxy - 10);
	
	//ve khung huong dan
	rectangle(332, 550, maxx - 10, maxy -10);
	
	//ve khung xu ly
	rectangle(332, 58, maxx - 10, 544);
	
	///////////////////////////////////////////////////
	//ghi chu MA TRAN TRONG SO
	setbkcolor(WHITE);
	outtextxy(18, 382, "MA TRAN TRONG SO");
	
}
//TAO NODE
void CreateNode(int x, int y, char name[], int color){
	setcolor(color);
	setlinestyle(0, 0, 3);//(kieu duong, ..., kich thuoc)
	settextstyle(4, HORIZ_DIR, 2);//(font, ngang doc, do dam)
	outtextxy(x-18, y-12, name);
	circle(x, y, 25);
}
//

int main(){
	createScreenWelcome();
	CreateScreen(1000, 700);
	char node1[] = "00";
	CreateNode(500, 500, node1, BLACK); 
	while(!kbhit());
	return 0;
}
