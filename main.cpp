#include<winbgim.h>
#include<iostream>
#include<string>
#include<windows.h>
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
const int maxx = 1200, maxy = 800;
using namespace std;
//VE MAN HINH
struct Node{
	string name;
	int x, y;
};
typedef struct Node Node;
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
void CreateScreen(){
	char Menu[9][15] = {"    DFS", "    BFS", "    X->Y", "   TPLT", "Hamilton", "    Euler", "  Dinh tru", "Dinh that", "Canh cau"};
	char Toolbar[8][15] = {"      New", "     Open", "     Save", " AddVertex", "  AddEdge", "     Move", "   Rename", "      Delete"};
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
		outtextxy(10 + (i-1)*(maxx/8 - 5) + 10, 10 + 5, Toolbar[i-1]);
		if(i == 7){
			outtextxy(10 + (i)*(maxx/8-5) + 10, 10 + 5, Toolbar[i]);
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
	string s = "Nhap vao ";
	int x, y;
	if(name == "ten") s += name + "(01 -> 99): ";
	else s += name + "(0 -> 99): ";
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
bool CheckNode(int x, int y, int mx, int my){
	return ((mx - x)*(mx - x) + (my - y)*(my - y) <= 25*25);
}
//THEM NODE 
void AddNode(int &x, int &y, string &ten, bool flag){
	if(flag == true){
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(x > 440 && x < 1150 && y > 90 && y < 560){
			setlinestyle(0, 0, 2);
			circle(x, y, 25);
			ten = AddName_Weight("ten");
			CreateNode(x, y, (char*)ten.c_str(), BLUE);
		}
	}
	else{
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(x > 440 && x < 1150 && y > 90 && y < 560){
			setlinestyle(0, 0, 2);
			circle(x, y, 25);
			CreateNode(x, y, (char*)ten.c_str(), BLUE);
		}
	}	
}
//DOI TEN NODE
void Rename(int x, int y, string &ten){// x, y sau nay se truyen node[i].x, node[i].y
	fillellipse(x, y, 25, 25);
	setlinestyle(0, 0, 2);
	circle(x, y, 25);
	ten = AddName_Weight("ten");
	CreateNode(x, y, (char*)ten.c_str(), BLUE);
}
//KIEM TRA VI TRI
bool CheckPos(int mx, int my, Node *node[], int numberNode){
	int count = 0;
	if(mx > 440 && mx < 1150 && my > 90 && my < 560) return true;
	for (int i = 0; i < numberNode; ++i){
		if((mx - node[i]->x)*(mx - node[i]->x) + (my - node[i]->y)*(my - node[i]->y) >=  75*75){
			count++;
		}
	}
	if(count == numberNode) return true;
	else return false;
}

//Thong bao
void NotificationFull(string Noti){
	bar(maxx/3 + 10, 602, maxx - 11, maxy - 11);
	setcolor(RED);
	outtextxy(500, 680, (char *)Noti.c_str());
	setcolor(BLUE);
	//bar(maxx/3 + 10, 602, maxx - 11, maxy - 11);
}
void SubEffect(int x1, int y1, int x2, int y2, char a[], int color, bool flag){
	if(flag == true){
		setfillstyle(1, color); 
		bar(x1+2, y1+2, x2-2, y2-2);
		setbkcolor(color);
		outtextxy(x1 + 10, y1 + 5, a); 
		Sleep(1);
	}
	else{
		setfillstyle(1, color); 
		bar(x1+2, y1+2, x2-2, y2-2);
		setbkcolor(color);
		outtextxy(x1 + 14, y1 + 18, a); 
		Sleep(1);
	}
}
//Hieu ung cho dep 
void Effect(bool flag){
	char Menu[9][15] = {"    DFS", "    BFS", "    X->Y", "   TPLT", "Hamilton", "    Euler", "  Dinh tru", "Dinh that", "Canh cau"};
	char Toolbar[8][15] = {"      New", "     Open", "     Save", " AddVertex", "  AddEdge", "     Move", "   Rename", "      Delete"};
	if(flag == true){//flag == true : dang tao do thi moi
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 10 && mousex() < 155 && mousey() > 10 && mousey() < 52) SubEffect(10, 10, 155, 52, Toolbar[0], LIGHTGREEN, true);
		else SubEffect(10, 10, 155, 52, Toolbar[0], WHITE, true);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 155 && mousex() < 300 && mousey() > 10 && mousey() < 52) SubEffect(155, 10, 300, 52, Toolbar[1], LIGHTGREEN, true);
		else SubEffect(155, 10, 300, 52, Toolbar[1], WHITE, true);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 300 && mousex() < 445 && mousey() > 10 && mousey() < 52) SubEffect(300, 10, 445, 52, Toolbar[2], LIGHTGREEN, true);	
		else SubEffect(300, 10, 445, 52, Toolbar[2], WHITE, true);	
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 445 && mousex() < 590 && mousey() > 10 && mousey() < 52) SubEffect(445, 10, 590, 52, Toolbar[3], LIGHTGREEN, true);
		else SubEffect(445, 10, 590, 52, Toolbar[3], WHITE, true);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 590 && mousex() < 735 && mousey() > 10 && mousey() < 52) SubEffect(590, 10, 735, 52, Toolbar[4], LIGHTGREEN, true);
		else SubEffect(590, 10, 735, 52, Toolbar[4], WHITE, true);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 735 && mousex() < 880 && mousey() > 10 && mousey() < 52) SubEffect(735, 10, 880, 52, Toolbar[5], LIGHTGREEN, true);
		else SubEffect(735, 10, 880, 52, Toolbar[5], WHITE, true);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 880 && mousex() < 1025 && mousey() > 10 && mousey() < 52) SubEffect(880, 10, 1025, 52, Toolbar[6], LIGHTGREEN, true);
		else SubEffect(880, 10, 1025, 52, Toolbar[6], WHITE, true);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 1025 && mousex() < 1190 && mousey() > 10 && mousey() < 52) SubEffect(1025, 10, 1190, 52, Toolbar[7], LIGHTGREEN, true);
		else SubEffect(1025, 10, 1190, 52, Toolbar[7], WHITE, true);
	}
	else{
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 14 && mousex() < 139 && mousey() > 99 && mousey() < 168) SubEffect(14, 99, 139, 168, Menu[0], LIGHTGREEN, false);
		else SubEffect(14, 99, 139, 168, Menu[0], WHITE, false);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 143 && mousex() < 268 && mousey() > 99 && mousey() < 168) SubEffect(143, 99, 268, 168, Menu[1], LIGHTGREEN, false);
		else SubEffect(143, 99, 268, 168, Menu[1], WHITE, false);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 272 && mousex() < 397 && mousey() > 99 && mousey() < 168) SubEffect(272, 99, 397, 168, Menu[2], LIGHTGREEN, false);
		else SubEffect(272, 99, 397, 168, Menu[2], WHITE, false);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 14 && mousex() < 139 && mousey() > 172 && mousey() < 241) SubEffect(14, 172, 139, 241, Menu[3], LIGHTGREEN, false);
		else SubEffect(14, 172, 139, 241, Menu[3], WHITE, false);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 143 && mousex() < 268 && mousey() > 172 && mousey() < 241) SubEffect(143, 172, 268, 241, Menu[4], LIGHTGREEN, false);
		else SubEffect(143, 172, 268, 241, Menu[4], WHITE, false);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 272 && mousex() < 397 && mousey() > 172 && mousey() < 241) SubEffect(272, 172, 397, 241, Menu[5], LIGHTGREEN, false);
		else SubEffect(272, 172, 397, 241, Menu[5], WHITE, false);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 14 && mousex() < 139 && mousey() > 245 && mousey() < 314) SubEffect(14, 245, 139, 314, Menu[6], LIGHTGREEN, false);
		else SubEffect(14, 245, 139, 314, Menu[6], WHITE, false);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 143 && mousex() < 268 && mousey() > 245 && mousey() < 314) SubEffect(143, 245, 268, 314, Menu[7], LIGHTGREEN, false);
		else SubEffect(143, 245, 268, 314, Menu[7], WHITE, false);
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 272 && mousex() < 397 && mousey() > 245 && mousey() < 314) SubEffect(272, 245, 397, 314, Menu[8], LIGHTGREEN, false);
		else SubEffect(272, 245, 397, 314, Menu[8], WHITE, false);
		
		if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 15 && mousex() < 398 && mousey() > 318 && mousey() < 391){
			setfillstyle(1, LIGHTGREEN); 
			bar(17, 320, 396, 391);
			setbkcolor(LIGHTGREEN);
			outtextxy(155, 340, "Topo Sort");
			Sleep(1);
		} 
		else{
			setfillstyle(1, WHITE); 
			bar(17, 320, 396, 391);
			setbkcolor(WHITE);
			outtextxy(155, 340, "Topo Sort");
			Sleep(1);
		} 
	}
}
int main(){
	Node *node[15];
	int numberNode = 0;
	// createScreenWelcome();
	CreateScreen();

	int x, y;
	string ten;
	NotificationFull("HAY MO DO THI CO SAN HOAC TAO MOT DO THI MOI!");
	while(true){//Kiem tra khi mới vào. CHỉ được nhấn 1 trong 2 nút: New, Open
		cout<<mousex()<<' '<<mousey()<<"\n";
		if(kbhit()){
			char key = getch();
			if(key == 27){
				break;
			}
		}
		Effect(true);
		if(ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if(x > 10 && x < 155 && y > 10 && y < 52){//Nhat nut New
				NotificationFull("HAY NHAP DO THI MOI!");
				Sleep(1500);
				NotificationFull("CHON CHUC NANG HOAC NHAN ESC DE DUNG TAO DO THI!");
				label:
				while(true){
					if(kbhit()){
						char key = getch();
						if(key == 27){
							NotificationFull("BAN DA THOAT. NHAN SAVE DE LUU DO THI");
							break;
						}
					}
					Effect(false);
					if(ismouseclick(WM_LBUTTONDOWN)){
						getmouseclick(WM_LBUTTONDOWN, x, y);
						if(x < 590 && x > 445 && y > 10 && y < 52){//Nhan nut AddVerTex
							NotificationFull("HAY CLICK CHUOT TRAI VAO VUNG TRONG DE THEM DINH!");
							if(numberNode < 15){
								while(!kbhit()){
									if (numberNode >= 15) 
										break;
									AddNode(x, y, ten, true);
									if(x != -1 && y != -1){
										Node *n = new Node;
										n->name = ten;
										n->x = x;
										n->y = y;
										node[numberNode] = n;
										numberNode++;
										NotificationFull("CHON CHUC NANG HOAC NHAN ESC DE DUNG TAO DO THI!");
										break;
									}
								}	
							}
							else{
								NotificationFull("DO THI DA DAY, KHONG THE THEM DINH!");
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
						// else if(x < 735 && x > 590 && y > 10 && y < 52){//Nhan nut AddEdge

						// }
						else if(x < 880 && x > 735 && y > 10 && y < 52){//Nhan nut Move
							NotificationFull("HAY CLICK VAO DINH CAN DI CHUYEN!");
							while(!kbhit()){
								getmouseclick(WM_LBUTTONDOWN, x, y);
								if(x != -1 && y != -1){
									string tmp;
									for(int i=0; i<numberNode; i++){
										if(CheckNode(node[i]->x, node[i]->y, x, y)){
											NotificationFull("HAY CLICK VAO NOI CAN DI CHUYEN TOI!");
											tmp = node[i]->name;
											while(!kbhit()){
												AddNode(x, y, tmp, false);
												setcolor(WHITE);
												fillellipse(node[i]->x, node[i]->y, 30, 30);
												setcolor(BLUE);
												if(x != -1 && y != -1){
													node[i]->x = x;
													node[i]->y = y;
													NotificationFull("CHON CHUC NANG HOAC NHAN ESC DE DUNG TAO DO THI!");
													goto label;
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
											goto label;
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
	}
	return 0;
}
