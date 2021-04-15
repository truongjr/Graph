#include<winbgim.h>
#include<iostream>
#include<string>
#include<windows.h>
#include<algorithm>
#include<cmath>
#include"Effect.h"
#include"lib.h"
#include"draw_line_and_curved.h"
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
#define M_PI 3.14159265358979323846
const int maxx = 1200, maxy = 800;
using namespace std;
struct Node{
	string name;
	int x, y;
};
typedef struct Node Node;
int main(){
	Node *node[15];
	int numberNode = 0;
	// createScreenWelcome();
	CreateScreen();
	int x, y;
	string ten;
	NotificationFull("HAY MO DO THI CO SAN HOAC TAO MOT DO THI MOI!");
	while(!kbhit()){//Kiem tra khi mới vào. CHỉ được nhấn 1 trong 2 nút: New, Open
		EffectFile();
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(x != -1 && y != -1){
			if(x > 1140 && x < 1190 && y > 10 && y < 52){
				break;
				closegraph();
				// setbkcolor(BLACK);
				// createScreenWelcome("VIET NAM VO DOI");
			}
			else{
				if(x > 10 && x < 155 && y > 10 && y < 52){//Nhat nut New
					NotificationFull("HAY NHAP DO THI MOI!");
					gtnew:
					while(!kbhit()){
						EffectToolbar();
						getmouseclick(WM_LBUTTONDOWN, x, y);
						if(x != -1 && y != -1){
							if(x < 590 && x > 445 && y > 10 && y < 52){//Nhan nut AddVerTex
								addV:
								if(numberNode < 14){
									NotificationFull("CLICK CHUOT VAO VUNG TRONG DE THEM DINH HOAC NHAN ESC DE THOAT!");
									while(!kbhit()){
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x > 1140 && x < 1190 && y > 10 && y < 52){
												NotificationFull("BAN DA THOAT CHUC NANG NHAP DINH");
												goto gtnew;
											}
											else{
												if(CheckPos(node, numberNode, x, y)){
														AddNode(node, numberNode, x, y, ten, true);
													if(x != -1 && y != -1){
														Node *n = new Node;
														n->name = ten;
														n->x = x;
														n->y = y;
														node[numberNode] = n;
														numberNode++;
														goto addV;
													}
												}
												else{
													goto addV;
												}
											}
										}
									}	
								}
								else{
									NotificationFull("DO THI DA DAY, KHONG THE THEM DINH!");
									goto gtnew;
								}
							}
							else if(x < 735 && x > 590 && y > 10 && y < 52){//Nhan nut AddEdge
								addE:
								NotificationFull("CLICK VAO DINH DAU!");
								if(numberNode < 2){
									NotificationFull("SO LUONG DINH CHUA DU. MOI NHAP THEM DINH");
									goto addV;
								}
								else{
									while(!kbhit()){
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x < 590 && x > 445 && y > 10 && y < 52){
												NotificationFull("BAN DA THOAT CHUC NANG NHAP CANH");
												goto gtnew;
											}
											else{
												bool flag = true;
												int x1, y1, x2, y2;
												for(int i=0; i<numberNode; i++){
													if(CheckNode(node[i]->x, node[i]->y, x, y)){
														x1 = node[i]->x;
														y1 = node[i]->y;
													}
												}
												NotificationFull("CLICK VAO DINH CUOI HOAC NHAN ESC DE NHAP LAI DINH DAU");
												while(!kbhit()){
													if(x < 590 && x > 445 && y > 10 && y < 52){
														goto addE;
													}
													else{
														getmouseclick(WM_LBUTTONDOWN, x, y);
														if(x != -1 && y != -1){
															for(int i = 0; i<numberNode; i++){
																if(CheckNode(node[i]->x, node[i]->y, x, y)){
																	x2 = node[i]->x;
																	y2 = node[i]->y;
																	clearmouseclick(WM_LBUTTONDOWN);
																	Create_curved(x1, y1, x2, y2, (char*)AddName_Weight("trong so").c_str());
																	setfillstyle(1, WHITE);
																	goto addE;
																}
															}
														}
													}
												}
											}
											////////////////////
										}
									}
								}																			
							}
							else if(x < 1025 && x > 880 && y > 10 && y < 52){//Nhan nut Rename
								NotificationFull("HAY CLICK VAO DINH CAN DOI TEN!");
								while(!kbhit()){
									getmouseclick(WM_LBUTTONDOWN, x, y);
									if(x != -1 && y != -1){
										bool flag = false;
										for(int i=0; i < numberNode; i++){
											if(CheckNode(node[i]->x, node[i]->y, x, y)){
												Rename(node[i]->x, node[i]->y , node[i]->name);
												flag = true;
												break;
											}
										}
										if(flag == false) NotificationFull("HAY CLICK VAO DINH CAN DOI TEN!");
										else {
											NotificationFull("CHON CHUC NANG HOAC NHAN ESC DE DUNG TAO DO THI!");
											break;
										}
									}
								}	
							}
							
							else if(x < 880 && x > 735 && y > 10 && y < 52){//Nhan nut Move
								move:
								NotificationFull("CLICK VAO DINH CAN DI CHUYEN HOAC NHAN ESC DE THOAT!");
								while(true){
									if(kbhit()){
										char key = getch();
										if(key == 27){
											NotificationFull("BAN DA THOAT CHUC NANG DI CHUYEN DINH");
											goto gtnew;
										}
									}
									getmouseclick(WM_LBUTTONDOWN, x, y);
									if(x != -1 && y != -1){
										string tmp;
										for(int i=0; i<numberNode; i++){
											if(CheckNode(node[i]->x, node[i]->y, x, y)){
												NotificationFull("HAY CLICK VAO VI TRI CAN DI CHUYEN TOI!");
												tmp = node[i]->name;
												setcolor(RED);
												circle(node[i]->x, node[i]->y, 25);
												while(!kbhit()){
													getmouseclick(WM_LBUTTONDOWN, x, y);
													if(x != -1 && y != -1){
														if(CheckPos(node, numberNode, x, y)){
															AddNode(node, numberNode, x, y, tmp, false);
															setcolor(BLUE);
															setcolor(WHITE);
															fillellipse(node[i]->x, node[i]->y, 30, 30);
															setcolor(BLUE);
															node[i]->x = x;
															node[i]->y = y;
															goto move;
														}
														else{
															NotificationFull("HAY NHAP LAI VI TRI CAN DI CHUYEN TOI");
														}	
													}	
												}
											}
										}
									}
								}
							}

							else if(x < 1170 && x > 1025 && y > 10 && y < 52){//Nhan nut Delete
								NotificationFull("HAY CLICK VAO DINH CAN XOA!");
								while(!kbhit()){
									getmouseclick(WM_LBUTTONDOWN, x, y);
									if(x != -1 && y != -1){
										string tmp;
										for(int i=0; i<numberNode; i++){
											if(CheckNode(node[i]->x, node[i]->y, x, y)){
												setcolor(WHITE);
												fillellipse(node[i]->x, node[i]->y, 30, 30);
												setcolor(BLUE);
												delete node[i];
												NotificationFull("CHON CHUC NANG HOAC NHAN ESC DE DUNG TAO DO THI!");
												goto gtnew;
											}
										}
									}
								}
							}
						}	
					}
				}
			}
		}
		// else if(x > 155 && x < 300 && y > 10 && y < 52){//Nhan nut Save

		// }
		// else if(x > 300 && x < 445 && y > 10 && y < 52){//Nhan nut Open

		// }
	}
	return 0;
}
//TAO MAN HINH CHAO MUNG
void createScreenWelcome(string s){
	initwindow(1209, 813);
	settextstyle(1, HORIZ_DIR, 1);
	outtextxy(100, 100, (char*)s.c_str());
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
//VE MAN HINH
void CreateScreen(){
	char Menu[9][15] = {"    DFS", "    BFS", "    X->Y", "   TPLT", "Hamilton", "    Euler", "  Dinh tru", "Dinh that", "Canh cau"};
	char Toolbar[8][15] = {"      New", "     Open", "     Save", " AddVertex", "  AddEdge", "     Move", "   Rename", "  Delete"};
	initwindow(1209, 813);
	setbkcolor(15);
	setcolor(BLUE);
	setlinestyle(0, 0, 10);
	cleardevice();
	//ve khung man hinh
	rectangle(0, 0, maxx, maxy);
	setlinestyle(0, 0, 2);
	settextstyle(3, HORIZ_DIR, 3);
	//ve khung thanh cong cu
	rectangle(10, 10, maxx - 10, 52);
	//ve thanh cong cu
	for(int i=1; i<8; i++){
		rectangle(10 + i*(maxx/8-5), 10, 10 + (i-1)*(maxx/8-5), 52);
		settextstyle(3, HORIZ_DIR, 3);
		outtextxy(10 + (i-1)*(maxx/8 - 5) + 10, 10 + 5, Toolbar[i-1]);
		if(i == 7){
			//xuat ra chu
			outtextxy(10 + (i)*(maxx/8-5) + 10, 10 + 5, Toolbar[i]);
			//tao nut thoat
			setfillstyle(1, RED);
			bar(1142, 12, 1188, 50);
			setbkcolor(RED);
			rectangle(1140, 10, 1190, 52);
			setcolor(YELLOW);
			outtextxy(1157, 15, "X" );
		}
	}
	setfillstyle(1, WHITE);
	setbkcolor(WHITE);
	setcolor(BLUE);
	//ve khung menu
	rectangle(10, 58, maxx/3 + 2, maxy/2-5);
	rectangle(10, 58, maxx/3 + 2, 95);
	outtextxy(150, 65, "ALGORITHM");
	//ve bang menu. co su support cua Hung
	int c = 0;// bien c la bien lay vi tri cua ten menu trong mang Menu
	for(int i = 1; i <= 3; i++){
		for(int j = 1; j <= 3; j++){
			rectangle(10 + j*125 + j*4, 95 + (i-1)*69 + (i)*4, 10 + (j-1)*125 + j*4, 69 + 95 + (i-1)*69 + i*4);
			//123 la chieu dai cua tung o trong menu; 10, 95 lan luot la vi tri bat dau cua x, y; 65 la do rong cua o
			//setbkcolor(14);
			outtextxy(10 + (j-1)*125 + j*4 + 14, 95 + (i-1)*69 + (i)*4 + 18, Menu[c]);
			c++;
		}
	}
	//ve o Topo Sort
	rectangle(15, 318, maxx/3 - 2, maxy/2 - 9);
	//ghi chu Topo Sort
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
	outtextxy(x-13, y-13, name);
	circle(x, y, 25);
	
}
//TAO BAN PHIM SO
void CreatePhim(int x, int y, char name[]){
	setcolor(BLUE);
	setlinestyle(0, 0, 3);//(kieu duong, ..., kich thuoc)
	settextstyle(3, HORIZ_DIR, 3);//(font, ngang doc, do dam)
	outtextxy(x - 8, y-12, name);
	circle(x, y, 35);
}
//NHAP TRONG SO && NHAP TEN
string AddName_Weight(string name){
	label1:
	bar(maxx/3 + 10, 602, maxx - 11, maxy - 11);
	string s = "Nhap ";
	int x, y;
	if(name == "ten") s += name + "(01 -> 99): ";
	else s += name + "(01->99): ";
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
				if(s.size() == 2 && s == "00") goto label1;
				if(x > 410 && x < 578 && y < maxy - 10 && y > 690){
					goto label2;
				}
				else if(x > 578 && x < 735  && y < maxy - 10 && y > 690){
					c = 0;
					s = "";
					goto label1;
				}
			}
		}
		if((x - 785)*(x - 785) + (y - 650)*(y-650) <= 35*35){
			s += "0";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 875)*(x - 875) + (y - 650)*(y-650) <= 35*35){
			s += "1";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 965)*(x - 965) + (y - 650)*(y-650) <= 35*35){
			s += "2";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 1055)*(x - 1055) + (y - 650)*(y-650) <= 35*35){
			s += "3";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 1145)*(x - 1145) + (y - 650)*(y-650) <= 35*35){
			s += "4";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 785)*(x - 785) + (y - 740)*(y-740) <= 35*35){
			s += "5";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 875)*(x - 875) + (y - 740)*(y-740) <= 35*35){
			s += "6";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 965)*(x - 965) + (y - 740)*(y-740) <= 35*35){
			s += "7";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 1055)*(x - 1055) + (y - 740)*(y-740) <= 35*35){
			s += "8";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 1145)*(x - 1145) + (y - 740)*(y-740) <= 35*35){
			s += "9";
			c++;
			outtextxy(690, 610, (char*)s.c_str());
		}
	}
	label2:
	bar(maxx/3 + 10, 602, maxx - 11, maxy - 11);
	return s;
}
/////////////////////////////////////////////////Tao Dinh///////////////////////////////////////
//Kiem tra vi tri click chuot co o ben trong Node hay khong
bool CheckNode(int x, int y, int mx, int my){
	return ((mx - x)*(mx - x) + (my - y)*(my - y) <= 25*25);
}
//KIEM TRA VI TRI
bool CheckPos(Node *node[], int numberNode, int mx, int my){
	if(numberNode == 0){
		if(mx > 440 && mx < 1150 && my > 90 && my < 560) return true;
		else return false;
	}
	else {
		int count = 0;
		if(mx > 440 && mx < 1150 && my > 90 && my < 560){ //return true;
			for (int i = 0; i < numberNode; ++i){
				if((mx - node[i]->x)*(mx - node[i]->x) + (my - node[i]->y)*(my - node[i]->y) <  75*75){
					return false;
				}
			}
			return true;
		} 
		else return false;
	}		
}
//THEM NODE 
bool AddNode(Node *node[], int numberNode, int &x, int &y, string &ten, bool flag){
	if(CheckPos(node, numberNode, x, y)){
		if(flag == true){//tao moi dinh
			// getmouseclick(WM_LBUTTONDOWN, x, y);
			// if(x > 440 && x < 1150 && y > 90 && y < 560){
				setlinestyle(0, 0, 2);
				circle(x, y, 25);
				ten = AddName_Weight("ten");
				CreateNode(x, y, (char*)ten.c_str(), BLUE);
			// }
		}
		else{//di chuyen dinh
			// getmouseclick(WM_LBUTTONDOWN, x, y);
			// if(x > 440 && x < 1150 && y > 90 && y < 560){
				setlinestyle(0, 0, 2);
				circle(x, y, 25);
				CreateNode(x, y, (char*)ten.c_str(), BLUE);
			// }
		}
		return true;	
	}
	else return false;
}
//DOI TEN NODE
void Rename(int x, int y, string &ten){// x, y sau nay se truyen node[i].x, node[i].y
	fillellipse(x, y, 25, 25);
	setlinestyle(0, 0, 2);
	circle(x, y, 25);
	ten = AddName_Weight("ten");
	CreateNode(x, y, (char*)ten.c_str(), BLUE);
}

////////////////////////////////////////////////Thong bao///////////////////////////////////////
void NotificationFull(string Noti){
	settextstyle(3, HORIZ_DIR, 2);
	bar(maxx/3 + 10, 602, maxx - 11, maxy - 11);
	setcolor(RED);
	outtextxy(maxx/3 + 20, 620, (char *)Noti.c_str());
	setcolor(BLUE);
	settextstyle(3, HORIZ_DIR, 3);
	//bar(maxx/3 + 10, 602, maxx - 11, maxy - 11);
}


///////////////////////////////////////////thuat toan/////////////////////////////////////////////////
