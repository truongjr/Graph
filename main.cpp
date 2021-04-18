#include<winbgim.h>
#include<iostream>
#include<string>
#include<windows.h>
#include<algorithm>
#include<cmath>
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

void createScreenWelcome(string s);
void CreateScreen();
void CreateNode(int x, int y, char name[], int color);
void CreateKeyboardNumber();
void CreateNotificationDel();
string AddName_Weight(string name);
bool CheckNode(int x, int y, int mx, int my);
bool CheckName(Node *node[], int numberNode, string name);
bool CheckPos(Node *node[], int numberNode, int mx, int my);
bool AddNode(Node *node[], int numberNode, int &x, int &y, string &ten, bool flag);
void Rename(int x, int y, string &ten);
void NotificationFull(string Noti);
void SubEffectFile(int x1, int y1, int x2, int y2, char a[], int color);
void SubEffectToolbar(int x1, int y1, int x2, int y2, char a[], int color);
void SubEffectMenu(int x1, int y1, int x2, int y2, char a[], int color);
void SubEffectNumber(int x, int y, string number, int color);
void EffectToolbar();
void EffectFile();
void EffectMenu();
void EffectDel();
void EffectNumber();
void DrawTriangle(int x1, int y1, int x2, int y2, int color);
void DrawCurved1(Node *node1, Node *node2, char *tt, int color);
void CreateCurved(Node *node1, Node *node2, char *tt, int color);
void CreateLine(Node *node1, Node *node2, char *tt, int color);
void DrawGraph(Node *node[], int numberNode, int adj[14][14], int type[14][14]);
void DeleteEdge(Node *node[], int &numberNode, int adj[14][14], int type[14][14], int x1, int y1, int x2, int y2, int index1, int index2);
void DeleteVertex(Node *node[], int &numberNode, int adj[14][14], int type[14][14], int x, int y, int index);
void Move(Node *node[], int &numberNode, int adj[14][14], int type[14][14], int x1, int y1, int x2, int y2, int index);

int main(){
	Node *node[14];
	int adj[14][14], type[14][14];
	int numberNode = 0;
	
	//loai dinh: 0 la dinh
	for(int i=0; i<14; i++){
		for(int j=0; j<14; j++){
			adj[i][j] = 0;
			type[i][j] = 0;
		}
	}
	// createScreenWelcome();
	CreateScreen();
	int x, y;
	string ten;
	lable:
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
							if(x > 1140 && x < 1190 && y > 10 && y < 52){
								goto lable;
							}
							else if(x < 590 && x > 445 && y > 10 && y < 52){//Nhan nut AddVerTex
								addV:
								if(numberNode < 14){
									NotificationFull("CLICK CHUOT VAO VUNG TRONG DE THEM DINH HOAC NHAN THOAT!");
									while(!kbhit()){
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x > 1140 && x < 1190 && y > 10 && y < 52){
												NotificationFull("BAN DA THOAT CHUC NANG!");
												goto gtnew;
											}
											else if(x > 440 && x < 1150 && y > 90 && y < 560){
												if(CheckPos(node, numberNode, x, y)){
													AddNode(node, numberNode, x, y, ten, true);
													while(CheckName(node, numberNode, ten) == false){
														ten = AddName_Weight("ten");
														Rename(x, y, ten);
													}
													Node *n = new Node;
													n->name = ten;
													n->x = x;
													n->y = y;
													node[numberNode] = n;
													numberNode++;
													goto addV;

												}
												else{
													goto addV;
												}
											}
											else{
												goto addV;
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
								if(numberNode < 2){
									NotificationFull("SO LUONG DINH CHUA DU. MOI NHAP THEM DINH!");
								}
								else{
									addE:
									NotificationFull("CLICK VAO DINH DAU HOAC NHAN X DE THOAT!");
									while(!kbhit()){
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x < 1190 && x > 1140 && y > 10 && y < 52){
												NotificationFull("BAN DA THOAT CHUC NANG!");
												goto gtnew;
											}
											else if(x > 440 && x < 1150 && y > 90 && y < 560){
												bool flag = true;	
												int x1 = 0, y1 = 0, x2 = 0, y2 = 0, idx1 = -1, idx2 = -1;
												string value = "";
												for(int i=0; i<numberNode; i++){
													if(CheckNode(node[i]->x, node[i]->y, x, y)){
														idx1 = i;
														x1 = node[i]->x;
														y1 = node[i]->y;
														flag = false;
													}
												}
												if(flag == true){
													goto addE;
												}
												else{
													NotificationFull("CLICK VAO DINH CUOI!");
													addEE:
													while(!kbhit()){
														getmouseclick(WM_LBUTTONDOWN, x, y);
														if(x != -1 && y != -1){
															bool flag = true;
															for(int i = 0; i<numberNode; i++){
																if(CheckNode(node[i]->x, node[i]->y, x, y)){
																	idx2 = i; 
																	x2 = node[i]->x;
																	y2 = node[i]->y;
																	flag = false;
																}
															}
															if(flag == true){
																goto addEE;
															}
															else{
																break;
															}
														}
													}
													value = AddName_Weight("trong so");
													if(adj[idx1][idx2] == 0 && adj[idx2][idx1] != 0) {
														CreateCurved(node[idx1], node[idx2], (char*)value.c_str(), BLUE);
														type[idx1][idx2] = 2;
													}
													else if(adj[idx1][idx2] == 0 && adj[idx2][idx1] == 0){
														CreateLine(node[idx1], node[idx2], (char*)value.c_str(), BLUE);
														type[idx1][idx2] = 1;
													}
													else if(adj[idx1][idx2] != 0){
														//value = AddName_Weight("trong so");
														CreateLine(node[idx1], node[idx2], (char*)value.c_str(), BLUE);
														type[idx1][idx2] = 1;
													}
													//DrawGraph(node, numberNode, adj, type);
													adj[idx1][idx2] = (value[0]-'0')*10+(value[1]-'0');
													setfillstyle(1, WHITE);
													goto addE;
												}
											}
											else{
												goto addE;
											}
										}
									}
								}																			
							}
							else if(x < 1025 && x > 880 && y > 10 && y < 52){//Nhan nut Rename
								if(numberNode < 1){
									NotificationFull("DO THI RONG. HAY THEM DINH!");
								}
								else{
									reN:
									NotificationFull("HAY CLICK VAO DINH CAN DOI TEN HOAC NHAN X DE THOAT!");
									while(!kbhit()){
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x < 1190 && x > 1140 && y > 10 && y < 52){
												NotificationFull("BAN DA THOAT CHUC NANG!");
												goto gtnew;
											}
											else if(x > 440 && x < 1150 && y > 90 && y < 560){
												bool flag = false;
												string nameNode = "";
												for(int i=0; i < numberNode; i++){
													if(CheckNode(node[i]->x, node[i]->y, x, y)){
														setcolor(RED);
														setlinestyle(0, 0, 3);
														circle(node[i]->x, node[i]->y, 25);
														setcolor(BLUE);
														setlinestyle(0, 0, 2);
														nameNode = AddName_Weight("trong so");
														Rename(node[i]->x, node[i]->y, nameNode);
														while(CheckName(node, numberNode, nameNode) == false){
															nameNode = AddName_Weight("trong so");
														}
														Rename(node[i]->x, node[i]->y, nameNode);
														node[i]->name = nameNode;
														flag = true;
														break;
													}
												}
												if(flag == false){
													NotificationFull("HAY CLICK VAO DINH CAN DOI TEN!");
												} 
												goto reN;	
											}
											else{
												goto reN;
											}
										}
									}	
								}
							}
							
							else if(x < 880 && x > 735 && y > 10 && y < 52){//Nhan nut Move
								if(numberNode < 1){
									NotificationFull("DO THI RONG. HAY THEM DINH");
								}
								else{
									move:
									NotificationFull("CLICK VAO DINH CAN DI CHUYEN HOAC NHAN X DE THOAT!");
									int x1 = 0, y1 = 0, x2 = 0, y2 = 0, idx = -1;
									while(!kbhit()){//Bat phim dau
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x < 1190 && x > 1140 && y > 10 && y < 52){
												NotificationFull("BAN DA THOAT CHUC NANG!");
												goto gtnew;
											}
											else if(x > 440 && x < 1150 && y > 90 && y < 560){
												string nameNode="";
												bool flag = true;
												for(int i=0; i<numberNode; i++){
													if(CheckNode(node[i]->x, node[i]->y, x, y)){
														x1 = node[i]->x;
														y1 = node[i]->y;
														idx = i;
														nameNode = node[i]->name;
														setcolor(RED);
														setlinestyle(0, 0, 3);
														circle(node[i]->x, node[i]->y, 25);
														flag = false;
														break;
													}
												}
												if(flag == true) goto move;
												else{
													movee:
													NotificationFull("HAY CLICK VAO VI TRI CAN DI CHUYEN TOI!");
													while(!kbhit()){
														getmouseclick(WM_LBUTTONDOWN, x, y);
														if(x != -1 && y != -1){
															if(CheckPos(node, numberNode, x, y)){
																x2 = x;
																y2 = y;
																break;
															}
															else{
																goto movee;//nhap lai noi can den 
															}	
														}	
													}
													Move(node, numberNode, adj, type, x1, y1, x2, y2, idx);
												}
											}
											else{
												goto move;
											}
										}
									}
								}
							}

							else if(x < 1140 && x > 1025 && y > 10 && y < 52){//Nhan nut Delete
								del:
								if(numberNode < 1){
									NotificationFull("DO THI RONG. HAY THEM DINH!");
								}
								else{
									CreateNotificationDel();
									while(!kbhit()){
										EffectDel();
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if((x - 1025)*(x - 1025) + (y - 102)*(y-102) <= 40*40){// xoa dinh
												bar(maxx/3 + 12, 61, maxx - 13, 592);
												DrawGraph(node, numberNode, adj, type);
												delV:
												NotificationFull("HAY CLICK VAO DINH CAN XOA!");
												int x, y, idx;
												bool flag = true;
												while(!kbhit()){
													getmouseclick(WM_LBUTTONDOWN, x, y);
													if(x != -1 && y != -1){
														if((x - 1025)*(x - 1025) + (y - 102)*(y-102) <= 40*40){
															NotificationFull("BAN DA THOAT CHUC NANG!");
															goto gtnew;
														}
														else if (x > 440 && x < 1150 && y > 90 && y < 560){
															for(int i=0; i<numberNode; i++){
																if(CheckNode(node[i]->x, node[i]->y, x, y)){
																	setcolor(RED);
																	setlinestyle(0, 0, 3);
																	circle(node[i]->x, node[i]->y, 25);
																	x = node[i]->x;
																	y = node[i]->y;
																	idx = i;
																	flag = false;
																	break;
																}
															}
															if(flag == true){
																goto delV;
															}
															else{
																DeleteVertex(node, numberNode, adj, type, x, y, idx);
																goto del;
															}
														}
														else {
															goto delV;
														}
													}
												}
											}
											else if((x - 1140)*(x - 1140) + (y - 102)*(y-102) <= 40*40){//xoa canh
												bar(maxx/3 + 12, 61, maxx - 13, 592);
												DrawGraph(node, numberNode, adj, type);
												delE:
												NotificationFull("HAY CLICK VAO DINH CAN XOA!");
												int x1, y1, x2, y2, idx1, idx2;
												while(!kbhit()){//Bat phim dau
													getmouseclick(WM_LBUTTONDOWN, x, y);
													if(x != -1 && y != -1){
														if(x < 1190 && x > 1140 && y > 10 && y < 52){
															NotificationFull("BAN DA THOAT CHUC NANG!");
															goto gtnew;
														}
														else if(x > 440 && x < 1150 && y > 90 && y < 560){
															bool flag = true;
															for(int i=0; i<numberNode; i++){
																if(CheckNode(node[i]->x, node[i]->y, x, y)){
																	x1 = node[i]->x;
																	y1 = node[i]->y;
																	idx1 = i;
																	setcolor(RED);
																	setlinestyle(0, 0, 3);
																	circle(node[i]->x, node[i]->y, 25);
																	flag = false;
																	break;
																}
															}
															if(flag == true) goto delE;
															else{
																delEE:
																NotificationFull("HAY CLICK VAO VI TRI CAN DI CHUYEN TOI!");
																while(!kbhit()){
																	getmouseclick(WM_LBUTTONDOWN, x, y);
																	if(x != -1 && y != -1){
																		bool flag = true;
																		for(int i=0; i<numberNode; i++){
																			if(CheckNode(node[i]->x, node[i]->y, x, y) && node[i]->x != x1 && node[i]->y != y1){
																				x2 = node[i]->x;
																				y2 = node[i]->y;
																				idx2 = i;
																				setcolor(RED);
																				setlinestyle(0, 0, 3);
																				circle(node[i]->x, node[i]->y, 25);
																				flag = false;
																				break;
																			}
																		}	
																		if(flag == true){
																			goto delEE;
																		}
																		else{
																			DeleteEdge(node, numberNode, adj, type, x1, y1, x2, y2, idx1, idx2);
																			goto del;
																		}
																	}	
																}
															}
														}
														else{
															goto delE;
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
	int mx = getmaxx() / 2; int my = getmaxy() / 2;
	setbkcolor(BLUE);
	setcolor(RED);
	setfillstyle(1, RED);
	bar(mx - 150, my - 100, mx + 150, my + 100);
	setcolor(YELLOW);
	setfillstyle(1, YELLOW);
	moveto(mx, my - 70);
	lineto(mx + 50, my + 60);
	lineto(mx - 70, my - 25);
	lineto(mx + 70, my - 25);
	lineto(mx - 50, my + 60);
	lineto(mx, my - 70);
	floodfill(mx, my, YELLOW);
	floodfill(mx, my - 30, YELLOW);
	floodfill(mx + 20, my + 30, YELLOW);
	floodfill(mx - 20, my + 30, YELLOW);
	floodfill(mx - 50, my - 20, YELLOW);
	floodfill(mx + 50, my - 20, YELLOW);
	Sleep(2000);
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
	for(int i = 1; i < 8; i++){
		rectangle(10 + i * (maxx / 8 - 5), 10, 10 + (i - 1)*(maxx / 8 - 5), 52);
		settextstyle(3, HORIZ_DIR, 3);
		outtextxy(10 + (i - 1) * (maxx / 8 - 5) + 10, 10 + 5, Toolbar[i - 1]);
		if(i == 7){
			//xuat ra chu
			outtextxy(10 + i * (maxx / 8 - 5) + 10, 10 + 5, Toolbar[i]);
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
	rectangle(10, 58, maxx / 3 + 2, maxy / 2 - 5);
	rectangle(10, 58, maxx / 3 + 2, 95);
	outtextxy(150, 65, "ALGORITHM");
	//ve bang menu. co su support cua Hung
	int c = 0;// bien c la bien lay vi tri cua ten menu trong mang Menu
	for(int i = 1; i <= 3; i++){
		for(int j = 1; j <= 3; j++){
			rectangle(10 + j * 125 + j * 4, 95 + (i - 1) * 69 + i * 4, 10 + (j - 1) * 125 + j * 4, 69 + 95 + (i - 1) * 69 + i * 4);
			//123 la chieu dai cua tung o trong menu; 10, 95 lan luot la vi tri bat dau cua x, y; 65 la do rong cua o
			outtextxy(10 + (j - 1) * 125 + j * 4 + 14, 95 + (i - 1) * 69 + i * 4 + 18, Menu[c]);
			c++;
		}
	}
	//ve o Topo Sort
	rectangle(15, 318, maxx / 3 - 2, maxy / 2 - 9);
	//ghi chu Topo Sort
	outtextxy(155, 340, "Topo Sort");
	//ve khung huong dan
	rectangle(maxx / 3 + 9, 601, maxx - 10, maxy - 10);
	//ve khung xu ly
	rectangle(maxx / 3 + 9, 58, maxx - 10, 595);
	//ve khung ma tran don vi
	rectangle(10, maxy / 2, maxx / 3 + 2, maxy - 10);
	//ghi chu MA TRAN TRONG SO
	rectangle(10, maxy / 2, maxx / 3 + 2, maxy / 2 + 40);
	//setbkcolor(WHITE);
	outtextxy(100, 410, "MA TRAN TRONG SO");
	for(int j = 0; j < 14; j++){
		for(int i = 0; i < 14; i++){
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
void CreateKeyboardNumber(){
	setfillstyle(1, WHITE);
	setcolor(BLUE);
	setlinestyle(0, 0, 2);//(kieu duong, ..., kich thuoc)
	settextstyle(3, HORIZ_DIR, 3);//(font, ngang doc, do dam)
	char a[10][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	int c = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 5; j++){
			fillellipse(785 + j*90, 650 + i*90, 35, 35);
			outtextxy(785 + j*90 - 8, 650 + i*90 - 12, a[c]);
			c++;
		}
	}
	// Sleep(50);
}
//Tao lua chon cho nut Delete
void CreateNotificationDel(){
	setlinestyle(0, 0, 3);
	settextstyle(3, HORIZ_DIR, 2);
	outtextxy(995, 90, "Vertex");
	outtextxy(1118, 90, "Edge");
	circle(1025, 102, 40);
	circle(1140, 102, 40);
	setlinestyle(0, 0, 2);
}

//NHAP TRONG SO && NHAP TEN
string AddName_Weight(string name){
	setfillstyle(1, WHITE);
	bar(maxx / 3 + 10, 602, maxx - 11, maxy - 11);
	label1:
	string s = "Nhap ";
	int x, y;
	if(name == "ten") s += name + "(01->99): ";
	else s += name + "(01->99): ";
	outtextxy(maxx/3 + 20, 610, (char*)s.c_str());
	rectangle(maxx/3 + 9, 601, 735, maxy - 10);
	CreateKeyboardNumber();
	s = "";
	while(!kbhit()){
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(s.size() >= 2){
			CreateKeyboardNumber();
			while(!kbhit()){
				setlinestyle(0, 0, 2);
				rectangle(maxx/3 + 9, 640, 735, maxy - 10);
				rectangle(409, 690, 578, maxy - 10);
				rectangle(578, 690, 735, maxy - 10);
				outtextxy(maxx/3 + 9 + 85, 650, "Thong bao");
				outtextxy(435, 723, "Tiep tuc");
				outtextxy(582, 723, "Chinh sua");
				getmouseclick(WM_LBUTTONDOWN, x, y);
				if(s.size() == 2 && s == "00") goto label1;
				else if(s.size() == 2 && s != "00"){
					if(x > 410 && x < 578 && y < maxy - 10 && y > 690){
						goto label2;
					}
					else if(x > 578 && x < 735  && y < maxy - 10 && y > 690){
						s = "";
						goto label1;
					}
				}
			}
		}
		EffectNumber();
		if((x - 785)*(x - 785) + (y - 650)*(y-650) <= 35*35){
			s += "0";
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 875)*(x - 875) + (y - 650)*(y-650) <= 35*35){
			s += "1";
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 965)*(x - 965) + (y - 650)*(y-650) <= 35*35){
			s += "2";
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 1055)*(x - 1055) + (y - 650)*(y-650) <= 35*35){
			s += "3";
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 1145)*(x - 1145) + (y - 650)*(y-650) <= 35*35){
			s += "4";
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 785)*(x - 785) + (y - 740)*(y-740) <= 35*35){
			s += "5";
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 875)*(x - 875) + (y - 740)*(y-740) <= 35*35){
			s += "6";
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 965)*(x - 965) + (y - 740)*(y-740) <= 35*35){
			s += "7";
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 1055)*(x - 1055) + (y - 740)*(y-740) <= 35*35){
			s += "8";
			outtextxy(690, 610, (char*)s.c_str());
		}
		else if((x - 1145)*(x - 1145) + (y - 740)*(y-740) <= 35*35){
			s += "9";
			outtextxy(690, 610, (char*)s.c_str());
		}
	}
	label2:
	setfillstyle(0, WHITE);
	bar(maxx / 3 + 10, 602, maxx - 11, maxy - 11);
	return s;
}

/////////////////////////////////////////////////Tao Dinh///////////////////////////////////////
//Kiem tra vi tri click chuot co o ben trong Node hay khong
bool CheckNode(int x, int y, int mx, int my){
	return (((mx - x)*(mx - x) + (my - y)*(my - y) <= 25*25)&&((mx > 440 && mx < 1150 && my > 90 && my < 560)));
}
//KIEM TRA VI TRI
bool CheckPos(Node *node[], int numberNode, int mx, int my){
	if(numberNode == 0){
		if(mx > 440 && mx < 1150 && my > 90 && my < 560) return true;
		else return false;
	}
	else {
		if(mx > 440 && mx < 1150 && my > 90 && my < 560){ //return true;
			for (int i = 0; i < numberNode; ++i){
				if((mx - node[i]->x)*(mx - node[i]->x) + (my - node[i]->y)*(my - node[i]->y) <  75 * 75){
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
			setlinestyle(0, 0, 2);
			circle(x, y, 25);
			ten = AddName_Weight("ten");
			CreateNode(x, y, (char*)ten.c_str(), BLUE);
		}
		else{//di chuyen dinh
			setlinestyle(0, 0, 2);
			circle(x, y, 25);
			CreateNode(x, y, (char*)ten.c_str(), BLUE);
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
	//ten = AddName_Weight("ten");
	CreateNode(x, y, (char*)ten.c_str(), BLUE);
}
//KIEM TRA TEN NODE 
bool CheckName(Node *node[], int numberNode, string nameNode){
	if(numberNode == 0) return true;
	else{
		for(int i = 0; i < numberNode; i++){
			if(node[i]->name == nameNode){
				return false;
			}
		}
		return true;
	}
}
////////////////////////////////////////////////Thong bao///////////////////////////////////////
void NotificationFull(string Noti){
	setfillstyle(1, WHITE);
	settextstyle(3, HORIZ_DIR, 2);
	bar(maxx/3 + 10, 602, maxx - 11, maxy - 11);
	setcolor(RED);
	outtextxy(maxx/3 + 20, 620, (char *)Noti.c_str());
	setcolor(BLUE);
	settextstyle(3, HORIZ_DIR, 3);
}

/////////////////////////////////////////////////Hieu ung con///////////////////////////////////////
void SubEffectNumber(int x, int y, string number, int color){
	if(color != WHITE){
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		circle(x, y, 35);
		setcolor(BLUE);
		setfillstyle(1, color);
		fillellipse(x, y, 35, 35);
		setbkcolor(color);
		outtextxy(x - 8, y - 12, (char*)number.c_str());
		setlinestyle(0, 0, 3);
	}
	else{
		setcolor(BLUE);
		setlinestyle(0, 0, 3);
		circle(x, y, 35);
		setfillstyle(1, color);
		fillellipse(x, y, 35, 35);
		setcolor(BLUE);	
		setbkcolor(color);
		outtextxy(x - 8, y - 12, (char*)number.c_str());
		setlinestyle(0, 0, 3);
	}
	setcolor(BLUE);
	setbkcolor(WHITE);
}
//Hieu ung cho 3 nut: New, Open, Save
void SubEffectFile(int x1, int y1, int x2, int y2, char a[], int color){
	if(color != WHITE){
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
		setcolor(BLUE);
		setfillstyle(1, color); 
		bar(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
		setbkcolor(color);
		outtextxy(x1 + 10, y1 + 5, a); 
		setlinestyle(0, 0, 2);
	}
	else{
		setcolor(WHITE);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		setfillstyle(1, color); 
		bar(x1+2, y1+2, x2-2, y2-2);
		setbkcolor(color);
		outtextxy(x1 + 10, y1 + 5, a); 
		setlinestyle(0, 0, 2);
	}
}
//Hieu ung cho 5 nut con lai tren thanh Toolbar
void SubEffectToolbar(int x1, int y1, int x2, int y2, char a[], int color){
	if(color != WHITE){
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		setfillstyle(1, color); 
		bar(x1+3, y1+3, x2-3, y2-3);
		setbkcolor(color);
		outtextxy(x1 + 10, y1 + 5, a); 
		setlinestyle(0, 0, 2);
	}
	else{
		setcolor(WHITE);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		setfillstyle(1, color); 
		bar(x1+2, y1+2, x2-2, y2-2);
		setbkcolor(color);
		outtextxy(x1 + 10, y1 + 5, a); 
		setlinestyle(0, 0, 2);
	}
}
//Hieu ung cho bang menu
void SubEffectMenu(int x1, int y1, int x2, int y2, char a[], int color){
	if(color != WHITE){
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		setfillstyle(1, color); 
		bar(x1+3, y1+3, x2-3, y2-3);
		setbkcolor(color);
		outtextxy(x1 + 14, y1 + 18, a); 
		setlinestyle(0, 0, 2);
	}
	else{
		setcolor(WHITE);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		setfillstyle(1, color); 
		bar(x1+2, y1+2, x2-2, y2-2);
		setbkcolor(color);
		outtextxy(x1 + 14, y1 + 18, a); 
		setlinestyle(0, 0, 2);
	}
}
//Hieu ung cho dep 
void EffectNumber(){
	if((mousex() - 785) * (mousex() - 785) + (mousey() - 650) * (mousey() - 650) <= 35*35) SubEffectNumber(785, 650, "0", LIGHTGREEN);
	else SubEffectNumber(785, 650, "0", WHITE);
	if((mousex() - 875) * (mousex() - 875) + (mousey() - 650) * (mousey() - 650) <= 35*35) SubEffectNumber(875, 650, "1", LIGHTGREEN);
	else SubEffectNumber(875, 650, "1", WHITE);
	if((mousex() - 965) * (mousex() - 965) + (mousey() - 650)*(mousey() - 650) <= 35*35) SubEffectNumber(965, 650, "2", LIGHTGREEN);
	else SubEffectNumber(965, 650, "2", WHITE);
	if((mousex() - 1055) * (mousex() - 1055) + (mousey() - 650) * (mousey() - 650) <= 35*35) SubEffectNumber(1055, 650, "3", LIGHTGREEN);
	else SubEffectNumber(1055, 650, "3", WHITE);
	if((mousex() - 1145) * (mousex() - 1145) + (mousey() - 650) * (mousey() - 650) <= 35*35) SubEffectNumber(1145, 650, "4", LIGHTGREEN);
	else SubEffectNumber(1145, 650, "4", WHITE);
	if((mousex() - 785) * (mousex() - 785) + (mousey() - 740) * (mousey() - 740) <= 35*35) SubEffectNumber(785, 740, "5", LIGHTGREEN);
	else SubEffectNumber(785, 740, "5", WHITE);
	if((mousex() - 875) * (mousex() - 875) + (mousey() - 740) * (mousey() - 740) <= 35*35) SubEffectNumber(875, 740, "6", LIGHTGREEN);
	else SubEffectNumber(875, 740, "6", WHITE);
	if((mousex() - 965) * (mousex() - 965) + (mousey() - 740) * (mousey() - 740) <= 35*35) SubEffectNumber(965, 740, "7", LIGHTGREEN);
	else SubEffectNumber(965, 740, "7", WHITE);
	if((mousex() - 1055) * (mousex() - 1055) + (mousey() - 740) * (mousey() - 740) <= 35*35) SubEffectNumber(1055, 740, "8", LIGHTGREEN);
	else SubEffectNumber(1055, 740, "8", WHITE);
	if((mousex() - 1145) * (mousex() - 1145) + (mousey() - 740) * (mousey() - 740) <= 35*35) SubEffectNumber(1145, 740, "9", LIGHTGREEN);
	else SubEffectNumber(1145, 740, "9", WHITE);
	Sleep(50);
}
void EffectDel(){//Hieu ung cho lua chon cua Delete
	if(ismouseclick(WM_LBUTTONDOWN) == false && (mousex() - 1025) * (mousex() - 1025) + (mousey() - 102) * (mousey() - 102) <= 40 * 40){
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		circle(1025, 102, 40);
		setfillstyle(1, LIGHTGREEN);
		fillellipse(1025, 102, 40, 40);
		setbkcolor(LIGHTGREEN);
		setcolor(BLUE);
		outtextxy(995, 90, "Vertex");
		setlinestyle(0, 0, 2);
	}
	else{
		setcolor(WHITE);
		setlinestyle(0, 0, 3);
		circle(1025, 102, 40);
		setcolor(BLUE);
		setfillstyle(1, WHITE);
		fillellipse(1025, 102, 40, 40);
		setbkcolor(WHITE);
		outtextxy(995, 90, "Vertex");
		setlinestyle(0, 0, 2);
	}
	if(ismouseclick(WM_LBUTTONDOWN) == false && (mousex() - 1140) * (mousex() - 1140) + (mousey() - 102) * (mousey() - 102) <= 40*40){
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		circle(1140, 102, 40);
		setfillstyle(1, LIGHTGREEN);
		fillellipse(1140, 102, 40, 40);
		setcolor(BLUE);
		setbkcolor(LIGHTGREEN);
		outtextxy(1118, 90, "Edge");
		setlinestyle(0, 0, 2);
	}
	else{
		setcolor(WHITE);
		setlinestyle(0, 0, 3);
		circle(1140, 102, 40);
		setcolor(BLUE);
		setfillstyle(1, WHITE);
		fillellipse(1140, 102, 40, 40);
		setbkcolor(WHITE);
		outtextxy(1118, 90, "Edge");
		setlinestyle(0, 0, 2);
	}
	Sleep(50);
}
void EffectFile(){
	char Toolbar[8][15] = {"      New", "     Open", "     Save", " AddVertex", "  AddEdge", "     Move", "   Rename", "  Delete"};
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 10 && mousex() < 155 && mousey() > 10 && mousey() < 52) SubEffectFile(10, 10, 155, 52, Toolbar[0], LIGHTGREEN);
	else SubEffectFile(10, 10, 155, 52, Toolbar[0], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 155 && mousex() < 300 && mousey() > 10 && mousey() < 52) SubEffectFile(155, 10, 300, 52, Toolbar[1], LIGHTGREEN);
	else SubEffectFile(155, 10, 300, 52, Toolbar[1], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 300 && mousex() < 445 && mousey() > 10 && mousey() < 52) SubEffectFile(300, 10, 445, 52, Toolbar[2], LIGHTGREEN);	
	else SubEffectFile(300, 10, 445, 52, Toolbar[2], WHITE);	
	Sleep(50);
	
}
void EffectToolbar(){
	char Toolbar[8][15] = {"      New", "     Open", "     Save", " AddVertex", "  AddEdge", "     Move", "   Rename", "  Delete"};
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 445 && mousex() < 590 && mousey() > 10 && mousey() < 52) SubEffectToolbar(445, 10, 590, 52, Toolbar[3], LIGHTGREEN);
	else SubEffectToolbar(445, 10, 590, 52, Toolbar[3], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 590 && mousex() < 735 && mousey() > 10 && mousey() < 52) SubEffectToolbar(590, 10, 735, 52, Toolbar[4], LIGHTGREEN);
	else SubEffectToolbar(590, 10, 735, 52, Toolbar[4], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 735 && mousex() < 880 && mousey() > 10 && mousey() < 52) SubEffectToolbar(735, 10, 880, 52, Toolbar[5], LIGHTGREEN);
	else SubEffectToolbar(735, 10, 880, 52, Toolbar[5], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 880 && mousex() < 1025 && mousey() > 10 && mousey() < 52) SubEffectToolbar(880, 10, 1025, 52, Toolbar[6], LIGHTGREEN);
	else SubEffectToolbar(880, 10, 1025, 52, Toolbar[6], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 1025 && mousex() < 1140 && mousey() > 10 && mousey() < 52) SubEffectToolbar(1025, 10, 1140, 52, Toolbar[7], LIGHTGREEN);
	else SubEffectToolbar(1025, 10, 1140, 52, Toolbar[7], WHITE);
	Sleep(50);
}
void EffectMenu(){
	char Menu[9][15] = {"    DFS", "    BFS", "    X->Y", "   TPLT", "Hamilton", "    Euler", "  Dinh tru", "Dinh that", "Canh cau"};
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 14 && mousex() < 139 && mousey() > 99 && mousey() < 168) SubEffectMenu(14, 99, 139, 168, Menu[0], LIGHTGREEN);
	else SubEffectMenu(14, 99, 139, 168, Menu[0], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 143 && mousex() < 268 && mousey() > 99 && mousey() < 168) SubEffectMenu(143, 99, 268, 168, Menu[1], LIGHTGREEN);
	else SubEffectMenu(143, 99, 268, 168, Menu[1], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 272 && mousex() < 397 && mousey() > 99 && mousey() < 168) SubEffectMenu(272, 99, 397, 168, Menu[2], LIGHTGREEN);
	else SubEffectMenu(272, 99, 397, 168, Menu[2], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 14 && mousex() < 139 && mousey() > 172 && mousey() < 241) SubEffectMenu(14, 172, 139, 241, Menu[3], LIGHTGREEN);
	else SubEffectMenu(14, 172, 139, 241, Menu[3], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 143 && mousex() < 268 && mousey() > 172 && mousey() < 241) SubEffectMenu(143, 172, 268, 241, Menu[4], LIGHTGREEN);
	else SubEffectMenu(143, 172, 268, 241, Menu[4], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 272 && mousex() < 397 && mousey() > 172 && mousey() < 241) SubEffectMenu(272, 172, 397, 241, Menu[5], LIGHTGREEN);
	else SubEffectMenu(272, 172, 397, 241, Menu[5], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 14 && mousex() < 139 && mousey() > 245 && mousey() < 314) SubEffectMenu(14, 245, 139, 314, Menu[6], LIGHTGREEN);
	else SubEffectMenu(14, 245, 139, 314, Menu[6], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 143 && mousex() < 268 && mousey() > 245 && mousey() < 314) SubEffectMenu(143, 245, 268, 314, Menu[7], LIGHTGREEN);
	else SubEffectMenu(143, 245, 268, 314, Menu[7], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 272 && mousex() < 397 && mousey() > 245 && mousey() < 314) SubEffectMenu(272, 245, 397, 314, Menu[8], LIGHTGREEN);
	else SubEffectMenu(272, 245, 397, 314, Menu[8], WHITE);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 15 && mousex() < 398 && mousey() > 318 && mousey() < 391){
		setfillstyle(1, LIGHTGREEN); 
		bar(17, 320, 396, 391);
		setbkcolor(LIGHTGREEN);
		outtextxy(155, 340, "Topo Sort");
	} 
	else{
		setfillstyle(1, WHITE); 
		bar(17, 320, 396, 391);
		setbkcolor(WHITE);
		outtextxy(155, 340, "Topo Sort");
	} 
	Sleep(50);
}
///////////////////////////////////////////ve cung////////////////////////////////////////////////////
void DrawTriangle(int x1, int y1, int x2, int y2, int color) {
	setcolor(color);
	double s60 = sin(60 * M_PI / 180);
	double c60 = cos(60 * M_PI / 180);
	double x3 =	c60 * (x1 - x2) - s60 * (y1 - y2) + x2; 
  	double y3 = s60 * (x1 - x2) + c60 * (y1 - y2) + y2;
  	double x4 = c60 * (x1 - x2) + s60 * (y1 - y2) + x2;
  	double y4 = -s60 * (x1 - x2) + c60 * (y1 - y2) + y2;
  	int polypoints[] = {x2, y2, (int)x3, (int)y3, (int)x4, (int)y4, x2, y2};
  	setfillstyle(1, color);
  	fillpoly(4, polypoints);
  	setfillstyle(1, WHITE);
}
void DrawCurved1(Node *node1, Node *node2, char *tt, int color) {
	setcolor(color);
	setlinestyle(0, 0, 2);
	int x1 = node1->x, y1 = node1->y, x2 = node2->x, y2 = node2->y;
	string name1 = node1->name, name2 = node2->name;
	double s90 = sin(90 * M_PI / 180.0);    
  	double c90 = cos(90 * M_PI / 180.0);
  	// quay doan thang mot goc 90 do
  	double midx = (x1 + x2) * 1.0 / 2, midy = (y1 + y2) * 1.0 / 2;
  	double xI =	c90 * (x2 - midx) - s90 * (y2 - midy) + midx; 
  	double yI = s90 * (x2 - midx) + c90 * (y2 - midy) + midy;
  	// tinh toa do cua cac giao diem cua duong tron tam I voi duong tron node 
  	double r1 = sqrt(pow(xI - x1, 2) + pow(yI - y1, 2));
  	double d = r1;
  	double r2 = 25;
  	double a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
  	double h = sqrt(r1 * r1 - a * a);
  	double tempx1 = xI + a * (x1 - xI) / d;
  	double tempy1 = yI + a * (y1 - yI) / d;
  	double tempx2 = xI + a * (x2 - xI) / d;
  	double tempy2 = yI + a * (y2 - yI) / d;
  	double x3 = tempx1 - h * (y1 - yI) / d;
  	double y3 = tempy1 + h * (x1 - xI) / d;
  	double x4 = tempx2 + h * (y2 - yI) / d;
	double y4 = tempy2 - h * (x2 - xI) / d;
	// tim goc quet
	double param1 = (x3 - xI) * 1.0 / r1;
	double param2 = (x4 - xI) * 1.0 / r1;
	double angle1 = acos(param1) * 180.0 / M_PI;
	double angle2 = acos(param2) * 180.0 / M_PI;
	double startAngle = 0.0, endAngle = 0.0;
	if (x3 >= xI && y3 <= yI && x4 >= xI && y4 <= yI)
		startAngle = -360 + angle2, endAngle = -360 + angle1;
	else if (x3 >= xI && y3 <= yI && x4 >= xI && y4 > yI) 
		startAngle = -angle2, endAngle = -360 + angle1;
	else if (x3 >= xI && y3 > yI && x4 >= xI && y4 > yI)
		startAngle = -angle2, endAngle = -angle1;
	else if (x3 >= xI && y3 > yI && x4 < xI && y4 > yI)
		startAngle = -angle2, endAngle = -angle1;
	else if (x3 < xI && y3 > yI && x4 < xI && y4 > yI) 
		startAngle = -angle2, endAngle = -angle1;
	else if (x3 < xI && y3 > yI && x4 < xI && y4 <= yI) 
		startAngle = -360 + angle2, endAngle = -angle1;
	else if (x3 < xI && y3 <= yI && x4 < xI && y4 <= yI)
		startAngle = -360 + angle2, endAngle = -360 + angle1;
	else if (x3 < xI && y3 <= yI && x4 >= xI && y4 <= yI)
		startAngle = -360 + angle2, endAngle = -360 + angle1;
//	cout << cnt << "\n";
	double s45 = sin(45 * M_PI / 180.0);
	double c45 = cos(45 * M_PI / 180.0);
	// quay diem (x1,y1) mot goc 45, vi la tam giac vuong can 
	double xT = c45 * (x1 - xI) - s45 * (y1 - yI) + xI;
	double yT = s45 * (x1 - xI) + c45 * (y1 - yI) + yI;
	double param = 5 * 1.0 / r1;
	double angle3 = asin(param) * 180.0 / M_PI;
	angle3 *= 2;
	double cAngle3 = cos(angle3 * M_PI / 180.0);
	double sAngle3 = sin(angle3 * M_PI / 180.0);
	double x5 = cAngle3 * (x4 - xI) + sAngle3 * (y4 - yI) + xI;
	double y5 = -sAngle3 * (x4 - xI) + cAngle3 * (y4 - yI) + yI;
	DrawTriangle(x5, y5, x4, y4, color);
	arc(xI, yI, startAngle, endAngle, r1);
	CreateNode(x1, y1, (char*)name1.c_str(), WHITE);
	setfillstyle(1, WHITE);
	fillellipse(x1, y1, 25, 25);
	CreateNode(x1, y1, (char*)name1.c_str(), BLUE);
	CreateNode(x2, y2, (char*)name2.c_str(), WHITE);
	setfillstyle(1, WHITE);
	fillellipse(x2, y2, 25, 25);
	CreateNode(x2, y2, (char*)name2.c_str(), BLUE);
	outtextxy(xT - 5, yT - 5, tt);
}
void CreateCurved(Node *node1, Node *node2, char *tt, int color) {
	setcolor(color);
	setlinestyle(0, 0, 2);
	int x1 = node1->x, y1 = node1->y, x2 = node2->x, y2 = node2->y;
	string name1 = node1->name, name2 = node2->name;
	double s90 = sin(90 * M_PI / 180.0);    
  	double c90 = cos(90 * M_PI / 180.0);
  	double midx = (x1 + x2) * 1.0 / 2, midy = (y1 + y2) * 1.0 / 2;
  	double xI =	c90 * (x1 - midx) - s90 * (y1 - midy) + midx; 
  	double yI = s90 * (x1 - midx) + c90 * (y1 - midy) + midy; 
  	double r1 = sqrt(pow(xI - x1, 2) + pow(yI - y1, 2));
  	double d = r1;
  	double r2 = 25;
  	double a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
  	double h = sqrt(r1 * r1 - a * a);
  	double tempx1 = xI + a * (x1 - xI) / d;
  	double tempy1 = yI + a * (y1 - yI) / d;
  	double tempx2 = xI + a * (x2 - xI) / d;
  	double tempy2 = yI + a * (y2 - yI) / d;
  	double x3 = tempx1 + h * (y1 - yI) / d;
  	double y3 = tempy1 - h * (x1 - xI) / d;
  	double x4 = tempx2 - h * (y2 - yI) / d;
	double y4 = tempy2 + h * (x2 - xI) / d;
	double param1 = (x3 - xI) * 1.0 / r1;
	double param2 = (x4 - xI) * 1.0 / r1;
	double angle1 = acos(param1) * 180.0 / M_PI;
	double angle2 = acos(param2) * 180.0 / M_PI;
//	cout << angle1 << " " << angle2 << "\n";
	double startAngle = 0.0, endAngle = 0.0;
	if (x3 >= xI && y3 <= yI && x4 >= xI && y4 <= yI)
		startAngle = angle1, endAngle = angle2;
	else if (x3 >= xI && y3 > yI && x4 >= xI && y4 <= yI) 
		startAngle = 360 - angle1, endAngle = 360 + angle2;
	else if (x3 >= xI && y3 > yI && x4 >= xI && y4 > yI)
		startAngle = 360 - angle1, endAngle = 360 - angle2;
	else if (x3 < xI && y3 > yI && x4 >= xI && y4 > yI)
		startAngle = 360 - angle1, endAngle = 360 - angle2;
	else if (x3 < xI && y3 > yI && x4 < xI && y4 > yI) 
		startAngle = 360 - angle1, endAngle = 360 - angle2;
	else if (x3 < xI && y3 <= yI && x4 < xI && y4 > yI) 
		startAngle = angle1, endAngle = 360 - angle2;
	else if (x3 < xI && y3 <= yI && x4 < xI && y4 <= yI)
		startAngle = angle1, endAngle = angle2;
	else if (x3 >= xI && y3 <= yI && x4 < xI && y4 <= yI)
		startAngle = angle1, endAngle = angle2;
	double s45 = sin(45 * M_PI / 180.0);
	double c45 = cos(45 * M_PI / 180.0); 
	double xT = c45 * (x2 - xI) - s45 * (y2 - yI) + xI;
	double yT = s45 * (x2 - xI) + c45 * (y2 - yI) + yI;
	if (!(xT > 440 && xT < 1150 && yT > 90 && yT < 560)) {
		DrawCurved1(node1, node2, tt, color);
		return;
	}
	double param = 5 * 1.0 / r1;
	double angle3 = asin(param) * 180.0 / M_PI;
	angle3 *= 2;
	double cAngle3 = cos(angle3 * M_PI / 180.0);
	double sAngle3 = sin(angle3 * M_PI / 180.0);
	double x5 = cAngle3 * (x4 - xI) - sAngle3 * (y4 - yI) + xI;
	double y5 = sAngle3 * (x4 - xI) + cAngle3 * (y4 - yI) + yI;
	//line(xI, yI, x5, y5);
	DrawTriangle(x5, y5, x4, y4, color);
	arc(xI, yI, startAngle, endAngle, r1);
	CreateNode(x1, y1, (char*)name1.c_str(), WHITE);
	setfillstyle(1, WHITE);
	fillellipse(x1, y1, 25, 25);
	CreateNode(x1, y1, (char*)name1.c_str(), BLUE);
	CreateNode(x2, y2, (char*)name2.c_str(), WHITE);
	setfillstyle(1, WHITE);
	fillellipse(x2, y2, 25, 25);
	CreateNode(x2, y2, (char*)name2.c_str(), BLUE);
	outtextxy(xT - 5, yT - 5, tt);
}
void CreateLine(Node *node1, Node *node2, char *tt, int color) {
	// tim diem dau tien
	setcolor(color);
	setlinestyle(0, 0, 2);
	int x1 = node1->x, y1 = node1->y, x2 = node2->x, y2 = node2->y;
	string name1 = node1->name, name2 = node2->name;
	double xx2 = 0, yy2 = 0, xx1 = x1, yy1 = y1;
	xx1 -= x2, yy1 -= y2;
	double a = yy2 - yy1;
	double b = xx1 - xx2;
	double c = a * xx1 + b * yy1;
	double x0 = -a * c * 1.0 / (a * a + b * b), y0 = -b * c / (a * a + b * b);
	double d = 25 * 25 - c * c * 1.0 / (a * a + b * b);
	double mult = sqrt(d / (a * a + b * b));
	double ax, ay;
	ax = x0 + b * mult;
	ay = y0 - a * mult;
	ax += x2, ay += y2; // diem cuoi de ve mui ten
	// tim diem thu 2 
	xx1 = 0, yy1 = 0, xx2 = x2, yy2 = y2;
	xx2 -= x1, yy2 -= y1;
	a = yy2 - yy1;
	b = xx1 - xx2;
	c = a * xx1 + b * yy1;
	x0 = -a * c * 1.0 / (a * a + b * b), y0 = -b * c / (a * a + b * b);
	d = 25 * 25 - c * c * 1.0 / (a * a + b * b);
	mult = sqrt(d / (a * a + b * b)); 
	double bx, by;
	bx = x0 - b * mult;
	by = y0 + a * mult;
	bx += x1, by += y1;
	// tim diem de ve mui ten
	double vectorx = x1 - x2, vectory = y1 - y2;
	double factor = 10 / sqrt(pow(vectorx, 2) + pow(vectory, 2));
	vectorx *= factor;
	vectory *= factor;
	double x3 = ax + vectorx, y3 = ay + vectory;
	// tim trung diem
	double xT = (x1 + x2) * 1.0 / 2;
	double yT = (y1 + y2) * 1.0 / 2;
	// ve duong thang
	line(ax, ay, bx, by);
	DrawTriangle(x3, y3, ax, ay, color);
	outtextxy(xT - 5, yT - 5, tt);
}
void DrawGraph(Node *node[14], int numberNode, int adj[14][14], int type[14][14]) {
	setlinestyle(0, 0, 2);
	for (int i = 0; i < numberNode; ++i) {
		string s = node[i]->name;
		CreateNode(node[i]->x, node[i]->y, (char*)s.c_str(), BLUE);
	}
	for (int i = 0; i < numberNode; ++i) {
		for(int j = 0; j < numberNode; j++){
			if(type[i][j] == 1){
				string value = (to_string(adj[i][j]).size() == 1 ? "0" + to_string(adj[i][j]) : to_string(adj[i][j]));
				CreateLine(node[i], node[j], (char*)value.c_str(), BLUE);
			}
			else if(type[i][j] == 2){
				string value = (to_string(adj[i][j]).size() == 1 ? "0" + to_string(adj[i][j]) : to_string(adj[i][j]));
				CreateCurved(node[i], node[j], (char*)value.c_str(), BLUE);
			}
		}
	}
}
void DeleteEdge(Node *node[14], int &numberNode, int adj[14][14], int type[14][14], int x1, int y1, int x2, int y2, int index1, int index2) {
	if (index1 != index2) {
		if (adj[index1][index2]) {
			string empty = "     ";
			if (type[index1][index2] == 1) 
				CreateLine(node[index1], node[index2], (char*)empty.c_str(), WHITE);
			else if (type[index1][index2] == 2) 
				CreateCurved(node[index1], node[index2], (char*)empty.c_str(), WHITE);
			adj[index1][index2] = 0;
			type[index1][index2] = 0;
			DrawGraph(node, numberNode, adj, type);
		}
	}
}
void DeleteVertex(Node *node[14], int &numberNode, int adj[14][14], int type[14][14], int x, int y, int index) {
	string empty = "      ";
	for (int row = 0; row < numberNode; ++row) {
		if (adj[row][index]) {
			if (type[row][index] == 1) {
				CreateLine(node[row], node[index], (char*)empty.c_str(), WHITE);
			} else if (type[row][index] == 2) {
				CreateCurved(node[row], node[index], (char*)empty.c_str(), WHITE);
			}
		}
	}
	for (int col = 0; col < numberNode; ++col) {
		if (adj[index][col]) {
			if (type[index][col] == 1) {
				CreateLine(node[index], node[col], (char*)empty.c_str(), WHITE);
			} else if (type[index][col] == 2) {
				CreateCurved(node[index], node[col], (char*)empty.c_str(), WHITE);
			}
		}
	}
	CreateNode(x, y, (char*)empty.c_str(), WHITE);
	// xoa dinh -> xoa node trong mang node
	for (int i = index; i < numberNode - 1; ++i)
		node[i] = node[i + 1];
	// xoa cot
	for (int i = index; i < numberNode - 1; ++i) {
		for (int j = 0; j < numberNode; ++j) {
			adj[j][i] = adj[j][i + 1]; 
			type[j][i] = type[j][i + 1];
		}
	} 
	// xoa hang
	for (int i = index; i < numberNode - 1; ++i) {
		for (int j = 0; j < numberNode - 1; ++j) {
			adj[i][j] = adj[i + 1][j];
			type[i][j] = type[i + 1][j];
		}
	}
	numberNode--;
	DrawGraph(node, numberNode, adj, type);
}
void Move(Node *node[14], int &numberNode, int adj[14][14], int type[14][14], int x1, int y1, int x2, int y2, int index) {
	// xoa nut hien tai
	string empty = "      ";
	for (int row = 0; row < numberNode; ++row) {
		if (adj[row][index]) {
			if (type[row][index] == 1) {
				CreateLine(node[row], node[index], (char*)empty.c_str(), WHITE);
			} else if (type[row][index] == 2) {
				CreateCurved(node[row], node[index], (char*)empty.c_str(), WHITE);
			}
		}
	}
	for (int col = 0; col < numberNode; ++col) {
		if (adj[index][col]) {
			if (type[index][col] == 1) {
				CreateLine(node[index], node[col], (char*)empty.c_str(), WHITE);
			} else if (type[index][col] == 2) {
				CreateCurved(node[index], node[col], (char*)empty.c_str(), WHITE);
			}
		}
	}
	CreateNode(x1, y1, (char*)empty.c_str(), WHITE);
	node[index]->x = x2, node[index]->y = y2;
	DrawGraph(node, numberNode, adj, type);
}
///////////////////////////////////////////thuat toan/////////////////////////////////////////////////
