#include<winbgim.h>
#include<iostream>
#include<string>
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
	initwindow(1209, 813);
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
	Sleep(3000);
	closegraph();
}
void CreateScreen(int maxx, int maxy){
	char Menu[9][10] = {"DFS", "BFS", "X->Y", "TPLT", "Hamilton", "Euler", "Dinh tru", "Dinh that", "Canh cau"};
	char Toolbar[8][10] = {"New", "Open", "Save", "AddVertex", "AddEdge", "Move", "Rename", "Delete"};
	initwindow(1209, 813);
	setbkcolor(15);
	setcolor(BLUE);
	setlinestyle(0, 0, 10);
	cleardevice();
	//ve khung man hinh
	rectangle(0, 0, maxx, maxy);
	setlinestyle(0, 0, 2);
	settextstyle(3, HORIZ_DIR, 3);
	//ve thanh cong cu
	for(int i=1; i<8; i++){
		rectangle(10 + i*(maxx/8-5), 10, 10 + (i-1)*(maxx/8-5), 52);
		settextstyle(3, HORIZ_DIR, 3);
		outtextxy(10 + (i-1)*(maxx/8 - 5) + 10, 10 + 10, Toolbar[i-1]);
		if(i == 7){
			outtextxy(10 + (i)*(maxx/8-5) + 10, 10 + 10, Toolbar[i]);
		}
	}
	//ve khung thanh cong cu
	rectangle(10, 10, maxx - 10, 52);
	
	//ve khung menu
	rectangle(10, 58, maxx/3 + 2, maxy/2-5);
	rectangle(10, 58, maxx/3 + 2, 95);
	outtextxy(150, 65, "ALGORITHM");
	//ve bang menu. co su support cua Hung
	int c = 0;// bien c la bien lay vi tri cua ten menu trong mang Menu
	for(int i = 1; i <= 3; i++){
		for(int j = 1; j <= 3; j++){
			rectangle(10 + j*125 + (j)*4, 95 + (i-1)*69 + (i)*4, 10 + (j-1)*125 + j*4, 69 + 95 + (i-1)*69 + i*4);
			//123 la chieu dai cua tung o trong menu; 10, 95 lan luot la vi tri bat dau cua x, y; 65 la do rong cua o
			//setbkcolor(14);
			outtextxy(10 + (j-1)*123 + j*4 + 20, 80 + (i-1)*76 + 35, Menu[c]);
			c++;
		}
	}
	//ve o Topo Sort
	rectangle(15, 318, maxx/3 - 2, maxy/2-5-4);
	//ghi chu Topo Sort
	//setfillstyle(1, 7); bar(10, 320, 322, 362);
	//setbkcolor(7);
	outtextxy(155, 340, "Topo Sort");
	
	//ve khung huong dan
	rectangle(maxx/3 + 9, 601, maxx - 10, maxy -10);
	
	//ve khung xu ly
	rectangle(maxx/3 + 9, 58, maxx - 10, 595);
	
	//ve khung ma tran don vi
	rectangle(10, maxy/2, maxx/3 + 2, maxy - 10);
	//ghi chu MA TRAN TRONG SO
	rectangle(10, maxy/2, maxx/3 + 2, maxy/2 + 40);
	//setbkcolor(WHITE);
	outtextxy(100, 410, "MA TRAN TRONG SO");
	for(int j=0; j<14; j++){
		for(int i=0; i<14; i++){
			rectangle(10 + i*28, maxy/2+40 + j*25, 10 + i*28 + 28, maxy/2 + 40 + 25 + j*25);
		}
	}
		
	
}
//TAO NODE
void CreateNode(int x, int y, char name[], int color){
	setcolor(color);
	setlinestyle(0, 0, 3);//(kieu duong, ..., kich thuoc)
	settextstyle(3, HORIZ_DIR, 3);//(font, ngang doc, do dam)
	outtextxy(x-18, y-12, name);
	circle(x, y, 25);
}
//TAO BAN PHIM SO
void CreatePhim(int x, int y, char name[]){
	setcolor(BLUE);
	setlinestyle(0, 0, 2);//(kieu duong, ..., kich thuoc)
	settextstyle(3, HORIZ_DIR, 3);//(font, ngang doc, do dam)
	outtextxy(x - 8, y-12, name);
	circle(x, y, 35);
}
void Notification(int maxx, int maxy, string name){
	label1:
	bar(maxx/3 + 10, 602, maxx - 11, maxy - 11);
	string s = "Nhap vao ";
	int x, y;
	s += name + ": ";
	char *n= (char*)s.c_str();
	outtextxy(maxx/3 + 20, 610, n);
	char a[10][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	int c=0;
	rectangle(maxx/3 + 9, 601, 735, maxy - 10);
	for(int i=0; i<2; i++){
		for(int j=0; j<5; j++){
			CreatePhim(785 + j*90, 650 + i*90, a[c]);
			c++;
		}
	}
	c = 0;
	s = "";
	while(!kbhit()){
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(c >= 2){
			while(!kbhit()){
				rectangle(maxx/3 + 9, 640, 735, 787);
				rectangle(410, 690, 578, maxy - 10);
				rectangle(578, 690, 735, maxy - 10);
				outtextxy(maxx/3 + 9 + 85, 650, "Thong bao");
				outtextxy(435, 723, "Tiep tuc");
				outtextxy(582, 723, "Chinh sua");
				getmouseclick(WM_LBUTTONDOWN, x, y);
				if(x > 410 && x < 578 && y < maxy - 10 && y > 690){
					goto label2;
					break;
				}
				else if(x > 578 && x < 735  && y < maxy - 10 && y > 690){
					c = 0;
					s = "";
					goto label1;
				}
			}
		}
		if((x - 785)*(x - 785) + (y - 640)*(y-640) <= 35*35){
			s += "0";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
		else if((x - 875)*(x - 875) + (y - 640)*(y-640) <= 35*35){
			s += "1";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
		else if((x - 965)*(x - 965) + (y - 640)*(y-640) <= 35*35){
			s += "2";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
		else if((x - 1055)*(x - 1055) + (y - 640)*(y-640) <= 35*35){
			s += "3";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
		else if((x - 1145)*(x - 1145) + (y - 640)*(y-640) <= 35*35){
			s += "4";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
		else if((x - 785)*(x - 785) + (y - 740)*(y-740) <= 35*35){
			s += "5";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
		else if((x - 875)*(x - 875) + (y - 740)*(y-740) <= 35*35){
			s += "6";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
		else if((x - 965)*(x - 965) + (y - 740)*(y-740) <= 35*35){
			s += "7";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
		else if((x - 1055)*(x - 1055) + (y - 740)*(y-740) <= 35*35){
			s += "8";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
		else if((x - 1145)*(x - 1145) + (y - 740)*(y-740) <= 35*35){
			s += "9";
			c++;
			outtextxy(640, 610, (char*)s.c_str());
		}
	}
	label2:
	bar(maxx/3 + 10, 602, maxx - 11, maxy - 11);
}

void AddNode(){
	int x, y;
	getmouseclick(WM_LBUTTONDOWN, x, y);
	if(x > 440 && x < 1150 && y > 90 && y < 560){
		CreateNode(x, y, "09", 0);
	}
}

int main(){
	//createScreenWelcome();
	CreateScreen(1200, 800);
//	char node1[] = "00";
//	CreateNode(500, 500, node1, BLACK); 
	Notification(1200, 800, "trong so");
	while(!kbhit()){
//		AddNode();
		
//		cout<<mousex()<<' '<<mousey()<<'\n';
	}
	return 0;
}
