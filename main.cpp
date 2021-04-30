#include <winbgim.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <cmath>
#include "stack.h"
// #include"queue.h"
using namespace std;
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
struct Node{
	string name;
	int x, y;
};
typedef struct Node Node;
struct Button{
	string name;
	int x1, y1, x2, y2;
};
typedef struct Button Button;
struct ButtonCircle{
	int x, y, r;
};
typedef struct ButtonCircle ButtonCircle;
const int maxx = 1200, maxy = 800;
int d[100];
int cu=0;
Button newButton, openButton, saveButton, addVertexButton, addEdgeButton, moveButton, renameButton, deleteButton; 
Button dfsButton, bfsButton, shortestPathButton, tpltButton, hamiltonButton, eulerButton, dinhTruButton, dinhThatButton, canhCauButton, topoSortButton;
Button helpArea, processingArea, realProcessingArea, closeButton, scannerArea, continueButton, cancelButton;
ButtonCircle delVertex, delEdge;
void createScreenWelcome(string s);
void CreateScreen();
void CreateNode(int x, int y, char name[], int color);
void CreateNotificationDel();
void CreateButton();
void DrawMenuTable();
void DrawToolBar();
void DrawWeightMatrix();
void DrawButtonForMenu(Button button);
void DrawButtonForToolBar(Button button);
void DrawButtonForNoti(Button button);
string AddName_Weight(string name);
bool CheckNode(int x, int y, int mx, int my);
bool CheckButton(Button button, int x, int y);
bool CheckName(Node *node[], int numberNode, string name);
bool CheckPos(Node *node[], int numberNode, int mx, int my);
bool AddNode(Node *node[], int numberNode, int &x, int &y, string &ten, bool flag);
void Rename(int x, int y, string &ten);
void NotificationFull(string Noti);
// void SubEffectToolbar(Button button);
// void SubEffectMenu(int x1, int y1, int x2, int y2, char a[], int color);
// void SubEffectNumber(int x, int y, string number, int color);
// void EffectToolbar();
// void EffectFile();
// void EffectMenu();
// void EffectDel();
// void EffectNumber();
void DrawTriangle(int x1, int y1, int x2, int y2, int color);
void DrawCurved1(Node *node1, Node *node2, char *tt, int color);
void CreateCurved(Node *node1, Node *node2, char *tt, int color);
void CreateLine(Node *node1, Node *node2, char *tt, int color);
void DrawGraph(Node *node[], int numberNode, int adj[14][14], int type[14][14]);
void DeleteEdge(Node *node[], int &numberNode, int adj[14][14], int type[14][14], int x1, int y1, int x2, int y2, int index1, int index2);
void DeleteVertex(Node *node[], int &numberNode, int adj[14][14], int type[14][14], int x, int y, int index);
void Move(Node *node[], int &numberNode, int adj[14][14], int type[14][14], int x1, int y1, int x2, int y2, int index);
void DFS (Node *node[14], int numberNode, int adj[14][14], Node *n);

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
	//Tao Button id
	CreateButton();
	int x, y;
	string ten;
	lable:
	NotificationFull("HAY MO DO THI CO SAN HOAC TAO MOT DO THI MOI!");
	while(true){//Kiem tra khi mới vào. CHỉ được nhấn 1 trong 2 nút: New, Open
		// EffectFile();
		if(kbhit()){
			char key = getch();
			if(key == 27) break;
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(x != -1 && y != -1){
			if(x > closeButton.x1 && x < closeButton.x2 && y > closeButton.y1 && y < closeButton.y2){
				break;
				closegraph();
				// setbkcolor(BLACK);
				// createScreenWelcome("VIET NAM VO DOI");
			}
			else{
				if(x > newButton.x1 && x < newButton.x2 && y > newButton.y1 && y < newButton.y2){//Nhat nut New
					NotificationFull("HAY NHAP DO THI MOI!");
					gtnew:
					while(true){
						if(kbhit()){
							char key = getch();
							if(key == 27) break;
						}
						// EffectToolbar();
						getmouseclick(WM_LBUTTONDOWN, x, y);
						if(x != -1 && y != -1){
							if(x > closeButton.x1 && x < closeButton.x2 && y > closeButton.y1 && y < closeButton.y2){
								goto lable;
							}
							else if(x > addVertexButton.x1 && x < addVertexButton.x2 && y > addVertexButton.y1 && y < addVertexButton.y2){//Nhan nut AddVerTex
								addV:
								if(numberNode < 14){
									NotificationFull("CLICK CHUOT VAO VUNG TRONG DE THEM DINH HOAC NHAN THOAT!");
									while(true){
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x > closeButton.x1 && x < closeButton.x2 && y > closeButton.y1 && y < closeButton.y2){
												NotificationFull("BAN DA THOAT CHUC NANG!");
												goto gtnew;
											}
											else if(x > realProcessingArea.x1 && x < realProcessingArea.x2 && y > realProcessingArea.y1 && y < realProcessingArea.y2){
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
							else if(x > addEdgeButton.x1 && x < addEdgeButton.x2 && y > addEdgeButton.y1 && y < addEdgeButton.y2){//Nhan nut AddEdge
								if(numberNode < 2){
									NotificationFull("SO LUONG DINH CHUA DU. MOI NHAP THEM DINH!");
								}
								else{
									addE:
									NotificationFull("CLICK VAO DINH DAU HOAC NHAN X DE THOAT!");
									while(true){
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x > closeButton.x1 && x < closeButton.x2 && y > closeButton.y1 && y < closeButton.y2){												NotificationFull("BAN DA THOAT CHUC NANG!");
												goto gtnew;
											}
											else if(x > realProcessingArea.x1 && x < realProcessingArea.x2 && y > realProcessingArea.y1 && y < realProcessingArea.y2){
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
													while(true){
														if(kbhit()){
															char key = getch();
															if(key == 27) break;
														}
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
							else if(x > renameButton.x1 && x < renameButton.x2 && y > renameButton.y1 && y < renameButton.y2){//Nhan nut Rename
								if(numberNode < 1){
									NotificationFull("DO THI RONG. HAY THEM DINH!");
								}
								else{
									reN:
									NotificationFull("HAY CLICK VAO DINH CAN DOI TEN HOAC NHAN X DE THOAT!");
									while(true){
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x > closeButton.x1 && x < closeButton.x2 && y > closeButton.y1 && y < closeButton.y2){
												NotificationFull("BAN DA THOAT CHUC NANG!");
												goto gtnew;
											}
											else if(x > realProcessingArea.x1 && x < realProcessingArea.x2 && y > realProcessingArea.y1 && y < realProcessingArea.y2){
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
							
							else if(x > moveButton.x1 && x < moveButton.x2 && y > moveButton.y1 && y < moveButton.y2){//Nhan nut Move
								if(numberNode < 1){
									NotificationFull("DO THI RONG. HAY THEM DINH");
								}
								else{
									move:
									NotificationFull("CLICK VAO DINH CAN DI CHUYEN HOAC NHAN X DE THOAT!");
									int x1 = 0, y1 = 0, x2 = 0, y2 = 0, idx = -1;
									while(true){//Bat phim dau
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x > closeButton.x1 && x < closeButton.x2 && y > closeButton.y1 && y < closeButton.y2){
												NotificationFull("BAN DA THOAT CHUC NANG!");
												goto gtnew;
											}
											else if(x > realProcessingArea.x1 && x < realProcessingArea.x2 && y > realProcessingArea.y1 && y < realProcessingArea.y2){
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

							else if(x > deleteButton.x1 && x < deleteButton.x2 && y > deleteButton.y1 && y < deleteButton.y2){//Nhan nut Delete
								del:
								if(numberNode < 1){
									NotificationFull("DO THI RONG. HAY THEM DINH!");
								}
								else{
									NotificationFull("HAY CHON CHUC NANG XOA HOAC NHAN X DE THOAT!");
									CreateNotificationDel();
									while(true){
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										// EffectDel();
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(x > closeButton.x1 && x < closeButton.x2 && y > closeButton.y1 && y < closeButton.y2){
												NotificationFull("BAN DA THOAT CHUC NANG!");
												bar(maxx/3 + 12, 61, maxx - 13, 592);
												DrawGraph(node, numberNode, adj, type);
												goto gtnew;
											}
											else if((x - 1025)*(x - 1025) + (y - 102)*(y-102) <= 40*40){// xoa dinh
												bar(maxx/3 + 12, 61, maxx - 13, 592);
												DrawGraph(node, numberNode, adj, type);
												delV:
												NotificationFull("HAY CLICK VAO DINH CAN XOA!");
												int x, y, idx;
												bool flag = true;
												while(true){//Bat phim dau
													if(kbhit()){
														char key = getch();
														if(key == 27) break;
													}
													getmouseclick(WM_LBUTTONDOWN, x, y);
													if(x != -1 && y != -1){
														if((x - 1025)*(x - 1025) + (y - 102)*(y-102) <= 40*40){
															NotificationFull("BAN DA THOAT CHUC NANG!");
															goto gtnew;
														}
														else if(x > realProcessingArea.x1 && x < realProcessingArea.x2 && y > realProcessingArea.y1 && y < realProcessingArea.y2){
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
												if(numberNode < 2){
													NotificationFull("DO THI KHONG CO CANH DE XOA!");
													bar(maxx/3 + 12, 61, maxx - 13, 592);
													DrawGraph(node, numberNode, adj, type);
													goto addV;
												}
												else{
													bar(maxx/3 + 12, 61, maxx - 13, 592);
													DrawGraph(node, numberNode, adj, type);
													delE:
													NotificationFull("HAY CLICK VAO DINH DAU!");
													int x1, y1, x2, y2, idx1, idx2;
													while(true){//Bat phim dau
														if(kbhit()){
															char key = getch();
															if(key == 27) break;
														}
														getmouseclick(WM_LBUTTONDOWN, x, y);
														if(x != -1 && y != -1){
															if(x > closeButton.x1 && x < closeButton.x2 && y > closeButton.y1 && y < closeButton.y2){
																NotificationFull("BAN DA THOAT CHUC NANG!");
																goto gtnew;
															}
															else if(x > realProcessingArea.x1 && x < realProcessingArea.x2 && y > realProcessingArea.y1 && y < realProcessingArea.y2){
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
																	NotificationFull("HAY CLICK VAO DINH CUOI!");
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
	initwindow(1209, 813);
	setbkcolor(15);
	setcolor(BLUE);
	setlinestyle(0, 0, 10);
	cleardevice();
	CreateButton();
	//ve khung man hinh
	rectangle(0, 0, maxx, maxy);
	setlinestyle(0, 0, 2);
	settextstyle(3, HORIZ_DIR, 3);
	rectangle(maxx / 3 + 9, 58, maxx - 10, 595);
	rectangle(maxx / 3 + 9, 601, maxx - 10, maxy - 10);
	DrawToolBar();
	DrawMenuTable();
	DrawWeightMatrix();
}
//TAO NODE
void CreateNode(int x, int y, char name[], int color){
	setcolor(color);
	setlinestyle(0, 0, 3);//(kieu duong, ..., kich thuoc)
	settextstyle(3, HORIZ_DIR, 3);//(font, ngang doc, do dam)
	outtextxy(x-13, y-13, name);
	circle(x, y, 25);
	
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
	reAdd:
	setfillstyle(1, WHITE);
	bar(maxx / 3 + 10, 602, maxx - 11, maxy - 11);
	string s = "Nhap vao " + name + " (01 -> 99): ";
	outtextxy(maxx/3 + 20, 610, (char*)s.c_str());
	string ans = "";
	int n = 0;
	while(n < 2){
		if(kbhit() == true){
			char key = getch();
			if(key >= 48 && key <= 57){
				ans += to_string(key - 48);
				n++;
				outtextxy(735, 610, (char*)ans.c_str());
			}
		}
	}
	if(ans == "00") goto reAdd;
	int x, y;
	DrawButtonForNoti(continueButton);
	DrawButtonForNoti(cancelButton);
	while(true){
		if(kbhit()){
			char key = getch();
			if(key == 27) break;
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(x != -1 && y != -1){
			if(CheckButton(continueButton, x, y)){
				return ans;
			}
			else if(CheckButton(cancelButton, x, y)){
				goto reAdd;
			}
		}
	}
}
void CreateButton (){
	newButton.name = "      New", newButton.x1 = 10, newButton.y1 = 10, newButton.x2 = 155, newButton.y2 = 52;
	openButton.name = "     Open", openButton.x1 = 155, openButton.y1 = 10, openButton.x2 = 300, openButton.y2 = 52;
	saveButton.name = "     Save", saveButton.x1 = 300, saveButton.y1 = 10, saveButton.x2 = 445, saveButton.y2 = 52;
	addVertexButton.name = " AddVertex", addVertexButton.x1 = 445, addVertexButton.y1 = 10, addVertexButton.x2 = 590, addVertexButton.y2 = 52;
	addEdgeButton.name = "  AddEdge", addEdgeButton.x1 = 590, addEdgeButton.y1 = 10, addEdgeButton.x2 = 735, addEdgeButton.y2 = 52;
	moveButton.name = "     Move", moveButton.x1 = 735, moveButton.y1 = 10, moveButton.x2 = 880, moveButton.y2 = 52;
	renameButton.name = "   Rename", renameButton.x1 = 880, renameButton.y1 = 10, renameButton.x2 = 1025, renameButton.y2 = 52;
	deleteButton.name = "  Delete", deleteButton.x1 = 1025, deleteButton.y1 = 10, deleteButton.x2 = 1140, deleteButton.y2 = 52;
	dfsButton.name = "    DFS", dfsButton.x1 = 14, dfsButton.y1 = 99, dfsButton.x2 = 139, dfsButton.y2 = 168;
	bfsButton.name = "    BFS", bfsButton.x1 = 143, bfsButton.y1 = 99, bfsButton.x2 = 268, bfsButton.y2 = 168;
	shortestPathButton.name = "    X->Y", shortestPathButton.x1 = 272, shortestPathButton.y1 = 99, shortestPathButton.x2 = 397, shortestPathButton.y2 = 168;
	tpltButton.name = "   TPLT", tpltButton.x1 = 14, tpltButton.y1 = 172, tpltButton.x2 = 139, tpltButton.y2 =241;
	hamiltonButton.name = "Hamilton", hamiltonButton.x1 = 143, hamiltonButton.y1 = 172, hamiltonButton.x2 = 268, hamiltonButton.y2 = 241;
	eulerButton.name = "    Euler", eulerButton.x1 = 272, eulerButton.y1 = 172, eulerButton.x2 = 397, eulerButton.y2 = 241;
	dinhTruButton.name = "  Dinh tru", dinhTruButton.x1 = 14, dinhTruButton.y1 = 245, dinhTruButton.x2 = 139, dinhTruButton.y2 = 314;
	dinhThatButton.name = "Dinh that", dinhThatButton.x1 = 143, dinhThatButton.y1 = 245, dinhThatButton.x2 = 268, dinhThatButton.y2 = 314;
	canhCauButton.name = "Canh cau", canhCauButton.x1 = 272, canhCauButton.y1 = 245, canhCauButton.x2 = 397, canhCauButton.y2 = 314;
	topoSortButton.name = "Topo Sort", topoSortButton.x1 = 14, topoSortButton.y1 = 318, topoSortButton.x2 = maxx/3 - 3, topoSortButton.y2 = maxy/2 - 9;
	helpArea.name = "", helpArea.x1 = maxx/3 + 9, helpArea.y1 = 601, helpArea.x2 = maxx - 10, helpArea.y2 = maxy - 10;
	processingArea.name = "", processingArea.x1 = maxx/3 + 9, processingArea.y1 = 58, processingArea.x2 = maxx - 10, processingArea.y2 = 595; 
	realProcessingArea.name = "", realProcessingArea.x1 = 440, realProcessingArea.y1 = 90, realProcessingArea.x2 = 1150, realProcessingArea.y2 = 560;
	closeButton.name = " X", closeButton.x1 = 1140, closeButton.y1 = 10, closeButton.x2 = 1190, closeButton.y2 = 52;
	scannerArea.name = "", scannerArea.x1 = maxx/3 + 9, scannerArea.y1 = 601, scannerArea.x2 = maxx - 10, scannerArea.y2 = 696;
	continueButton.name = "Tiep tuc", continueButton.x1 = maxx/3 + 9, continueButton.y1 = 696, continueButton.x2 = 800, continueButton.y2 = maxy - 10;
	cancelButton.name = "Chinh sua", cancelButton.x1 = 800, cancelButton.y1 = 696, cancelButton.x2 = maxx-10, cancelButton.y2 = maxy - 10;
	delVertex.x = 1025, delVertex.y = 102, delVertex.r = 40;
	delEdge.x = 1140, delEdge.y = 102, delEdge.r = 40;
}
void DrawButtonForMenu(Button button){
	rectangle(button.x1, button.y1, button.x2, button.y2);
	if(button.name != "Topo Sort") outtextxy(button.x1 + 14, button.y1 + 18, (char*)button.name.c_str());
	else outtextxy(155, 340, (char*)button.name.c_str());
}
void DrawButtonForToolBar(Button button){
	rectangle(button.x1, button.y1, button.x2, button.y2);
	outtextxy(button.x1 + 10, button.y1 + 5, (char*)button.name.c_str());
}
void DrawButtonForNoti(Button button){
	rectangle(button.x1, button.y1, button.x2, button.y2);
	outtextxy(button.x1 + 150, button.y1 + 30, (char*)button.name.c_str());
}
void DrawToolBar(){
	DrawButtonForToolBar(newButton);
	DrawButtonForToolBar(openButton);
	DrawButtonForToolBar(saveButton);
	DrawButtonForToolBar(addVertexButton);
	DrawButtonForToolBar(addEdgeButton);
	DrawButtonForToolBar(moveButton);
	DrawButtonForToolBar(renameButton);
	DrawButtonForToolBar(deleteButton);
	DrawButtonForToolBar(closeButton);
}
void DrawMenuTable(){
	//ve khung menu
	rectangle(10, 58, maxx / 3 + 2, maxy / 2 - 5);
	rectangle(10, 58, maxx / 3 + 2, 95);
	outtextxy(137, 63, "ALGORITHM");
	DrawButtonForMenu(dfsButton);
	DrawButtonForMenu(bfsButton);
	DrawButtonForMenu(shortestPathButton);
	DrawButtonForMenu(tpltButton);
	DrawButtonForMenu(hamiltonButton);
	DrawButtonForMenu(eulerButton);
	DrawButtonForMenu(dinhTruButton);
	DrawButtonForMenu(dinhThatButton);
	DrawButtonForMenu(canhCauButton);
	DrawButtonForMenu(topoSortButton);
}
void DrawWeightMatrix(){
	outtextxy(100, 410, "MA TRAN TRONG SO");
	setlinestyle(0, 0, 1);
	for(int j = 0; j < 14; j++){
		for(int i = 0; i < 14; i++){
			rectangle(10 + i*28, maxy/2+40 + j*25, 10 + i*28 + 28, maxy/2 + 40 + 25 + j*25);
		}
	}
	setlinestyle(0, 0, 2);
	rectangle(10, maxy / 2, maxx / 3 + 2, maxy / 2 + 40);
	rectangle(10, maxy / 2, maxx / 3 + 2, maxy - 10);
}
/////////////////////////////////////////////////Tao Dinh///////////////////////////////////////
//Kiem tra vi tri click chuot co o ben trong Node hay khong
bool CheckNode(int x, int y, int mx, int my){
	return (((mx - x)*(mx - x) + (my - y)*(my - y) <= 25*25)&&((mx > 440 && mx < 1150 && my > 90 && my < 560)));
}
bool CheckButton(Button button, int x, int y){
	return (x > button.x1 && x < button.x2 && y > button.y1 && y < button.y2);
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
	settextstyle(3, HORIZ_DIR, 2);
	bar(helpArea.x1 + 1, helpArea.y1 + 1, helpArea.x2 - 1, helpArea.y2 - 1);
	setcolor(RED);
	outtextxy(helpArea.x1 + 11, helpArea.y1 + 19, (char *)Noti.c_str());
	setcolor(BLUE);
	settextstyle(3, HORIZ_DIR, 3);
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

// void DFS (Node *node[14], int numberNode, int adj[14][14], int n){
	
// }
// for(int i=0; i<numberNode; i++){
// 									for(int j=0; j<numberNode; j++){
// 										cout<<adj[i][j]<<' ';
// 									}
// 									cout<<'\n';
// 								}
// 								for(int i=0; i<numberNode; i++){
// 									cout<<node[i]->name<<' ';
// 								}
// 								cout<<'\n';

// 								int tmp = 0;
// 								bool tick[numberNode];
// 								for(int i = 0; i < numberNode; i++) tick[i] = false;
// 								Stack st;
// 								st.push(0);
// 								while(st.empty() == false){
// 									st.pop(tmp);
// 									if(tick[tmp] == false){
// 										tick[tmp] = true;
// 										cout<<tmp<<' ';
// 										setcolor(tmp);
// 										setlinestyle(0, 0, 3);
// 										circle(node[tmp]->x, node[tmp]->y, 25);
// 										setcolor(BLUE);
// 										Sleep(1000);
// 									}
// 									for(int j = numberNode - 1; j >= 0; j--){
// 										if(adj[tmp][j] != 0 && tick[j] == false){
// 											st.push(j);
// 										}
// 									}
// 								}
// 								while(!kbhit());