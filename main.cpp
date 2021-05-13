#include <winbgim.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "stack.h"
#include "queue.h"
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
const int maxx = 1200, maxy = 800, MAXN = 14;
struct Node{
	string name;
	int x, y;
	Node() { }
    Node(string Name, int X, int Y) {
        name = Name;
        x = X; 
        y = Y;
    }
    // ~Node() { }
};
typedef struct Node Node;
struct Button{
	string name;
	int x1, y1, x2, y2;
};
typedef struct Button Button;
struct ButtonCircle{
	string name;
	int x, y, r;
};
typedef struct ButtonCircle ButtonCircle;
struct Graph{
	int numberNode;
	int adj[MAXN][MAXN], type[MAXN][MAXN];
	Node *node[MAXN];
	Graph(){
		numberNode = 0;
		for(int i = 0; i < MAXN; i++){
			node[i] = NULL;
			for(int j = 0; j < MAXN; j++){
				adj[i][j] = 0;
				type[i][j] = 0;
			}
		}
	}
	~Graph(){}
};
typedef struct Graph Graph;
struct nodeTmp{
	int parentNode, childNode;
	nodeTmp(){
		parentNode = 0;
		childNode = 0;
	}
	~nodeTmp(){}
};
typedef struct nodeTmp nodeTmp;
Button newButton, openButton, saveButton, addVertexButton, addEdgeButton, moveButton, renameButton, deleteButton; 
Button dfsButton, bfsButton, shortestPathButton, ComponentButton, hamiltonButton, eulerButton, dinhTruButton, dinhThatButton, bridgeEdgeButton, topoSortButton;
Button helpArea, processingArea, realProcessingArea, closeButton, scannerArea, continueButton, cancelButton;
ButtonCircle delVertex, delEdge;
void createScreenWelcome(string s);
void CreateScreen();
void CreateNode(int x, int y, char name[], int color);
void DrawSubDel();
void CreateButton();
void DrawMenuTable();
void DrawToolBar();
void DrawMatrix();
void DrawWeightMatrix(Graph &graph);
void DrawButtonForMenu(Button button);
void DrawButtonForToolBar(Button button);
void DrawButtonForNoti(Button button);
string AddName_Weight(string name);
string AddFileName();
bool CheckNode(int x, int y, int mx, int my);
bool CheckClickButton(Button button, int x, int y);
bool CheckClickCircle(ButtonCircle button, int x, int y);
bool CheckName(Graph &graph, string name);
bool CheckPos(Graph &graph, int mx, int my);
void CheckSave(Graph graph, bool isfirstSave, string &nameFile);
bool AddNode(Graph &graph, int &x, int &y, string &ten, bool flag);
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
void FlipCurved(Node *node1, Node *node2, char *tt, int color);
void CreateCurved(Node *node1, Node *node2, char *tt, int color);
void CreateLine(Node *node1, Node *node2, char *tt, int color);
void DrawGraph(Graph &graph);
void DeleteEdge(Graph &graph, int x1, int y1, int x2, int y2, int index1, int index2);
void DeleteVertex(Graph &graph, int x, int y, int index);
void Move(Graph &graph, int x1, int y1, int x2, int y2, int index);
// void DFS (Graph &graph, int f);
string ToStringLen2(int n);
string ToString(int n);
int ToInt(string s);
void WriteFile(char *fileName, Graph &graph);
void ReadFile(char *fileName, Graph &graph);
void DFS (Graph graph, int f);
void BFS (Graph graph, int start);
void Component (Graph graph);
void DrawEdge(Graph &graph, int idx1, int color);
int main(){

	// createScreenWelcome();
	CreateScreen();
	CreateButton();
	restart:
	Graph graph;
	int x, y;
	string nameNode, nameFile;
	label:
	NotificationFull("HAY MO DO THI CO SAN HOAC TAO MOT DO THI MOI!");
	while(true){//Kiem tra khi mới vào. CHỉ được nhấn 1 trong 2 nút: New, Open
		// EffectFile();
		if(kbhit()){
			char key = getch();
			if(key == 27) break;
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(x != -1 && y != -1){
			if(CheckClickButton(closeButton, x, y)){// VO TINH NHAN NUT THOAT LUON
				saveExit:
				NotificationFull("BAN CO MUON LUU LAI KHONG?");
				DrawButtonForNoti(continueButton);
				DrawButtonForNoti(cancelButton);
				while(true){
					if(kbhit()){
						char key = getch();
						if(key == 27) break;
					}
					getmouseclick(WM_LBUTTONDOWN, x, y);
					if(x != -1 && y != -1){
						if(CheckClickButton(continueButton, x, y)){
							reAddExit:
							nameFile = AddFileName();
							if(!nameFile.empty()){
								nameFile = "saves/" + nameFile;
								nameFile += ".txt";
								ofstream graphFile((char*)nameFile.c_str());
								graphFile.close();
								WriteFile((char*)nameFile.c_str(), graph);
								goto exit;
							}
							else goto reAddExit;
						}
						else if(CheckClickButton(cancelButton, x, y)) goto exit;
					}
				}
				exit:
				closegraph();
				return 0;
				// setbkcolor(BLACK);
				// createScreenWelcome("VIET NAM VO DOI");
			}
			else{
				if(x > newButton.x1 && x < newButton.x2 && y > newButton.y1 && y < newButton.y2){//Nhat nut New
					bool isfirstSave = false;
					gtnew:
					NotificationFull("HAY CHON CHUC NANG!");
					while(true){
						if(kbhit()){
							char key = getch();
							if(key == 27) break;
						}
						// EffectToolbar();
						getmouseclick(WM_LBUTTONDOWN, x, y);
						if(x != -1 && y != -1){
							gtAction:
							if(CheckClickButton(closeButton, x, y)){
								goto gtnew;
							}
							else if(CheckClickButton(saveButton, x, y)){//Nhan nut Save	
								NotificationFull("BAN CO MUON LUU LAI KHONG?");
								DrawButtonForNoti(continueButton);
								DrawButtonForNoti(cancelButton);
								while(true){
									if(kbhit()){
										char key = getch();
										if(key == 27) break;
									}
									getmouseclick(WM_LBUTTONDOWN, x, y);
									if(x != -1 && y != -1){
										if(CheckClickButton(continueButton, x, y)){
											reAddCt:
											nameFile = AddFileName();
											if(!nameFile.empty()){
												nameFile = "saves/" + nameFile;
												nameFile += ".txt";
												ofstream graphFile((char*)nameFile.c_str());
												graphFile.close();
												WriteFile((char*)nameFile.c_str(), graph);
												isfirstSave = true;
												goto gtnew;
											}
											else goto reAddCt;
										}
										else if(CheckClickButton(cancelButton, x, y)) goto gtnew;
									}
								}
							}
							else if(CheckClickButton(addVertexButton, x, y)){//Nhan nut AddVerTex
								addV:
								if(graph.numberNode < 14){
									NotificationFull("CLICK CHUOT VAO VUNG TRONG DE THEM DINH HOAC NHAN THOAT!");
									while(true){
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(CheckClickButton(closeButton, x, y)){
												
											}
											else if(CheckClickButton(processingArea, x, y)){
												if(CheckPos(graph, x, y)){
													AddNode(graph, x, y, nameNode, true);
													while(CheckName(graph, nameNode) == false){
														nameNode = AddName_Weight("ten");
														Rename(x, y, nameNode);
													}
													Node *n = new Node;
													n->name = nameNode;
													n->x = x;
													n->y = y;
													graph.node[graph.numberNode] = n;
													graph.numberNode++;
													DrawWeightMatrix(graph);
													goto addV;

												}
												else{
													goto addV;
												}
											}
											else{
												goto gtAction;

											}
										}
										// else goto gtnew;
									}	
								}
								else{
									NotificationFull("DO THI DA DAY, KHONG THE THEM DINH!");
									goto gtnew;
								}
							}
							else if(CheckClickButton(addEdgeButton, x, y)){//Nhan nut AddEdge
								if(graph.numberNode < 2){
									NotificationFull("SO LUONG DINH CHUA DU. MOI NHAP THEM DINH!");
								}
								else{
									addE:
									NotificationFull("CLICK VAO DINH DAU!");
									while(true){
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(CheckClickButton(closeButton, x, y)){												
												goto saveExit;
											}
											else if(CheckClickButton(realProcessingArea, x, y)){
												bool flag = true;	
												int x1 = 0, y1 = 0, x2 = 0, y2 = 0, idx1 = -1, idx2 = -1;
												string value = "";
												for(int i=0; i<graph.numberNode; i++){
													if(CheckNode(graph.node[i]->x, graph.node[i]->y, x, y)){
														idx1 = i;
														x1 = graph.node[i]->x;
														y1 = graph.node[i]->y;
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
															for(int i = 0; i < graph.numberNode; i++){
																if(CheckNode(graph.node[i]->x, graph.node[i]->y, x, y)){
																	idx2 = i; 
																	x2 = graph.node[i]->x;
																	y2 = graph.node[i]->y;
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
													if(graph.adj[idx1][idx2] == 0 && graph.adj[idx2][idx1] != 0) {
														CreateCurved(graph.node[idx1], graph.node[idx2], (char*)value.c_str(), BLUE);
														graph.type[idx1][idx2] = 2;
													}
													else if(graph.adj[idx1][idx2] == 0 && graph.adj[idx2][idx1] == 0){
														CreateLine(graph.node[idx1], graph.node[idx2], (char*)value.c_str(), BLUE);
														graph.type[idx1][idx2] = 1;
													}
													else if(graph.adj[idx1][idx2] != 0){
														CreateLine(graph.node[idx1], graph.node[idx2], (char*)value.c_str(), BLUE);
														graph.type[idx1][idx2] = 1;
													}													graph.adj[idx1][idx2] = (value[0]-'0')*10+(value[1]-'0');
													setfillstyle(1, WHITE);
													DrawWeightMatrix(graph);
													goto addE;
												}
											}
											else{
												goto gtAction;
											}
										}
									}
								}																			
							}
							else if(CheckClickButton(renameButton, x, y)){//Nhan nut Rename
								if(graph.numberNode < 1){
									NotificationFull("DO THI RONG. HAY THEM DINH!");
								}
								else{
									reN:
									NotificationFull("HAY CLICK VAO DINH CAN DOI TEN!");
									while(true){
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(CheckClickButton(closeButton, x, y)){
												goto saveExit;
											}
											else if(CheckClickButton(realProcessingArea, x, y)){
												string nameNode = "";
												bool flag = true;
												for(int i=0; i < graph.numberNode; i++){
													if(CheckNode(graph.node[i]->x, graph.node[i]->y, x, y)){
														setcolor(RED);
														setlinestyle(0, 0, 3);
														circle(graph.node[i]->x, graph.node[i]->y, 25);
														setcolor(BLUE);
														setlinestyle(0, 0, 2);
														nameNode = AddName_Weight("ten dinh");
														Rename(graph.node[i]->x, graph.node[i]->y, nameNode);
														while(CheckName(graph, nameNode) == false){
															nameNode = AddName_Weight("ten dinh");
														}
														Rename(graph.node[i]->x, graph.node[i]->y, nameNode);
														graph.node[i]->name = nameNode;
														DrawWeightMatrix(graph);
														flag = false;
														break;
													}
												}
												goto reN;	
											}
											else{
												goto gtAction;
											}
										}
									}	
								}
							}
							
							else if(CheckClickButton(moveButton, x, y)){//Nhan nut Move
								if(graph.numberNode < 1){
									NotificationFull("DO THI RONG. HAY THEM DINH");
								}
								else{
									move:
									NotificationFull("CLICK VAO DINH CAN DI CHUYEN!");
									int x1 = 0, y1 = 0, x2 = 0, y2 = 0, idx = -1;
									while(true){//Bat phim dau
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(CheckClickButton(closeButton, x, y)){
												goto saveExit;
											}
											else if(CheckClickButton(realProcessingArea, x, y)){
												string nameNode="";
												bool flag = true;
												for(int i=0; i<graph.numberNode; i++){
													if(CheckNode(graph.node[i]->x, graph.node[i]->y, x, y)){
														x1 = graph.node[i]->x;
														y1 = graph.node[i]->y;
														idx = i;
														nameNode = graph.node[i]->name;
														setcolor(RED);
														setlinestyle(0, 0, 3);
														circle(graph.node[i]->x, graph.node[i]->y, 25);
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
															if(CheckPos(graph, x, y)){
																x2 = x;
																y2 = y;
																break;
															}
															else{
																goto movee;//nhap lai noi can den 
															}	
														}	
													}
													Move(graph, x1, y1, x2, y2, idx);
												}
											}
											else{
												goto gtAction;
											}
										}
									}
								}
							}

							else if(CheckClickButton(deleteButton, x, y)){//Nhan nut Delete
								del:
								if(graph.numberNode < 1){
									NotificationFull("DO THI RONG. HAY THEM DINH!");
								}
								else{
									NotificationFull("HAY CHON CHUC NANG!");
									DrawSubDel();
									while(true){
										if(kbhit()){
											char key = getch();
											if(key == 27) break;
										}
										// EffectDel();
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if(CheckClickButton(closeButton, x, y)){
												goto saveExit;
											}
											else if(CheckClickCircle(delVertex, x, y)){// xoa dinh
												bar(maxx/3 + 12, 61, maxx - 13, 592);
												DrawGraph(graph);
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
														if(CheckClickButton(realProcessingArea, x, y)){
															for(int i=0; i<graph.numberNode; i++){
																if(CheckNode(graph.node[i]->x, graph.node[i]->y, x, y)){
																	setcolor(RED);
																	setlinestyle(0, 0, 3);
																	circle(graph.node[i]->x, graph.node[i]->y, 25);
																	x = graph.node[i]->x;
																	y = graph.node[i]->y;
																	idx = i;
																	flag = false;
																	break;
																}
															}
															if(flag == true){
																goto delV;
															}
															else{
																DeleteVertex(graph, x, y, idx);
																DrawWeightMatrix(graph);
																goto del;
															}
														}
														else {
															goto delV;
														}
													}
												}
											}
											else if(CheckClickCircle(delEdge, x, y)){//xoa canh
												if(graph.numberNode < 2){
													NotificationFull("DO THI KHONG CO CANH DE XOA!");
													bar(maxx/3 + 12, 61, maxx - 13, 592);
													DrawGraph(graph);
												}
												else{
													bar(maxx/3 + 12, 61, maxx - 13, 592);
													DrawGraph(graph);
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
															if(CheckClickButton(realProcessingArea, x, y)){
																bool flag = true;
																for(int i=0; i < graph.numberNode; i++){
																	if(CheckNode(graph.node[i]->x, graph.node[i]->y, x, y)){
																		x1 = graph.node[i]->x;
																		y1 = graph.node[i]->y;
																		idx1 = i;
																		setcolor(RED);
																		setlinestyle(0, 0, 3);
																		circle(graph.node[i]->x, graph.node[i]->y, 25);
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
																			for(int i=0; i < graph.numberNode; i++){
																				if(CheckNode(graph.node[i]->x, graph.node[i]->y, x, y) && graph.node[i]->x != x1 && graph.node[i]->y != y1){
																					x2 = graph.node[i]->x;
																					y2 = graph.node[i]->y;
																					idx2 = i;
																					setcolor(RED);
																					setlinestyle(0, 0, 3);
																					circle(graph.node[i]->x, graph.node[i]->y, 25);
																					flag = false;
																					break;
																				}
																			}	
																			if(flag == true){
																				goto delEE;
																			}
																			else{
																				if(graph.adj[idx1][idx2]){
																					DeleteEdge(graph, x1, y1, x2, y2, idx1, idx2);
																					DrawWeightMatrix(graph);	
																				} 
																				else {
																					bar(maxx/3 + 12, 61, maxx - 13, 592);
																					DrawGraph(graph);
																				}
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
											else{
												bar(maxx/3 + 12, 61, maxx - 13, 592);
												DrawGraph(graph);
												goto gtAction;
											} 
										}
									}
								}
							}
							//////////////////////////
						}	
					}
				}

				else if(CheckClickButton(openButton, x, y)){//Nhan nut Open
					Graph g;
					ReadFile("saves/test1.txt", g);
					DrawGraph(g);
					DrawWeightMatrix(g);
					NotificationFull("HAY CLICK VAO THUAT TOAN CAN DEMO");
					// Component(g);
					BFS(g, 0);
					// while(true){
					// 	if(kbhit()){
					// 		char key = getch();
					// 		if(key == 27) break;
					// 	}
					// 	getmouseclick(WM_LBUTTONDOWN, x, y);
					// 	if(x != -1 && y != -1){
					// 		if(CheckClickButton(dfsButton, x, y)){

					// 		}
					// 		else if(CheckClickButton(bfsButton, x, y)){
								
					// 		}
					// 		else if(CheckClickButton(shortestPathButton, x, y)){
								
					// 		}
					// 		else if(CheckClickButton(ComponentButton, x, y)){
								
					// 		}
					// 		else if(CheckClickButton(hamiltonButton, x, y)){
								
					// 		}
					// 		else if(CheckClickButton(eulerButton, x, y)){
								
					// 		}
					// 		else if(CheckClickButton(dinhTruButton, x, y)){
								
					// 		}
					// 		else if(CheckClickButton(dinhThatButton, x, y)){
								
					// 		}
					// 		else if(CheckClickButton(bridgeEdgeButton, x, y)){
								
					// 		}
					// 		else if(CheckClickButton(topoSortButton, x, y)){
								
					// 		}
					// 	}
					// }
				}
			}
		}
	}
	return 0;
}

void CheckSave(Graph graph, bool isfirstSave, string &nameFile){
	NotificationFull("BAN CO MUON LUU LAI FILE DO THI HAY KHONG!");			
	if(isfirstSave == false){// DANG NEW FILE
		
	}
	else{//DANG OPEN FILE
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
				if(CheckClickButton(continueButton, x, y)){
					WriteFile((char*)nameFile.c_str(), graph);
				}
				// else if(CheckClickButton(cancelButton, x, y)){
				// 	return true;
				// }
			}
		}
	}
}

void RunningAlgorithm(Graph graph, int x, int y){

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
	DrawMatrix();      
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
void DrawSubDel(){
	// settextstyle(3, HORIZ_DIR, 2);
	circle(delVertex.x, delVertex.y, delVertex.r);
	circle(delEdge.x, delEdge.y, delEdge.r);
	outtextxy(delVertex.x - 35, delVertex.y - 14, (char*)delVertex.name.c_str());
	outtextxy(delEdge.x - 28, delEdge.y - 14, (char*)delEdge.name.c_str());
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
			if(CheckClickButton(continueButton, x, y)){
				return ans;
			}
			else if(CheckClickButton(cancelButton, x, y)){
				goto reAdd;
			}
		}
	}
}
string AddFileName(){
	setfillstyle(1, WHITE);
	bar(maxx / 3 + 10, 602, maxx - 11, maxy - 11);
	string s = "Nhap vao ten file( < 30 ki tu): ";
	outtextxy(maxx/3 + 20, 610, (char*)s.c_str());
	string ans = "";
	int n = 0;
	int x, y;
	DrawButtonForNoti(continueButton);
	DrawButtonForNoti(cancelButton);
	while(true){
		add:
		if(kbhit() == true){
			char key = getch();
			if(((key >= 'A' && key <= 'Z') || (key >= 'a' && key <='z') || (key >= '0' && key <= '9')) && n < 30){
				ans += key;
				n++;
				outtextxy(790, 610, (char*)ans.c_str());
			}
			if(n>0){
				if(key == 8) {
					ans.pop_back();
					outtextxy(790, 610, "                                                       ");
					outtextxy(790, 610, (char*)ans.c_str());
					n--;
				}
			}
			if(key == 13) goto enter;
			if(key == 27) return "";
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(x != -1 && y != -1){
			if(CheckClickButton(continueButton, x, y)){
				if(n == 0) goto add;
				enter:
				return ans;
			}
			else if(CheckClickButton(cancelButton, x, y)){
				return "";
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
	shortestPathButton.name = "    X=>Y", shortestPathButton.x1 = 272, shortestPathButton.y1 = 99, shortestPathButton.x2 = 397, shortestPathButton.y2 = 168;
	ComponentButton.name = "   TPLT", ComponentButton.x1 = 14, ComponentButton.y1 = 172, ComponentButton.x2 = 139, ComponentButton.y2 =241;
	hamiltonButton.name = "Hamilton", hamiltonButton.x1 = 143, hamiltonButton.y1 = 172, hamiltonButton.x2 = 268, hamiltonButton.y2 = 241;
	eulerButton.name = "    Euler", eulerButton.x1 = 272, eulerButton.y1 = 172, eulerButton.x2 = 397, eulerButton.y2 = 241;
	dinhTruButton.name = "  Dinh tru", dinhTruButton.x1 = 14, dinhTruButton.y1 = 245, dinhTruButton.x2 = 139, dinhTruButton.y2 = 314;
	dinhThatButton.name = "Dinh that", dinhThatButton.x1 = 143, dinhThatButton.y1 = 245, dinhThatButton.x2 = 268, dinhThatButton.y2 = 314;
	bridgeEdgeButton.name = "Canh cau", bridgeEdgeButton.x1 = 272, bridgeEdgeButton.y1 = 245, bridgeEdgeButton.x2 = 397, bridgeEdgeButton.y2 = 314;
	topoSortButton.name = "Topo Sort", topoSortButton.x1 = 14, topoSortButton.y1 = 318, topoSortButton.x2 = maxx/3 - 3, topoSortButton.y2 = maxy/2 - 9;
	helpArea.name = "", helpArea.x1 = maxx/3 + 9, helpArea.y1 = 601, helpArea.x2 = maxx - 10, helpArea.y2 = maxy - 10;
	processingArea.name = "", processingArea.x1 = maxx/3 + 9, processingArea.y1 = 58, processingArea.x2 = maxx - 10, processingArea.y2 = 595; 
	realProcessingArea.name = "", realProcessingArea.x1 = 440, realProcessingArea.y1 = 90, realProcessingArea.x2 = 1150, realProcessingArea.y2 = 560;
	closeButton.name = " X", closeButton.x1 = 1140, closeButton.y1 = 10, closeButton.x2 = 1190, closeButton.y2 = 52;
	scannerArea.name = "", scannerArea.x1 = maxx/3 + 9, scannerArea.y1 = 601, scannerArea.x2 = maxx - 10, scannerArea.y2 = 696;
	continueButton.name = "Tiep tuc", continueButton.x1 = maxx/3 + 9, continueButton.y1 = 696, continueButton.x2 = 800, continueButton.y2 = maxy - 10;
	cancelButton.name = "     Huy", cancelButton.x1 = 800, cancelButton.y1 = 696, cancelButton.x2 = maxx-10, cancelButton.y2 = maxy - 10;
	delVertex.name = "Vertex", delVertex.x = 1025, delVertex.y = 102, delVertex.r = 40;
	delEdge.name = "Edge", delEdge.x = 1140, delEdge.y = 102, delEdge.r = 40;
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
	rectangle(10, 58, maxx / 3 + 2, 400 - 5);
	rectangle(10, 58, maxx / 3 + 2, 95);
	outtextxy(137, 63, "ALGORITHM");
	DrawButtonForMenu(dfsButton);
	DrawButtonForMenu(bfsButton);
	DrawButtonForMenu(shortestPathButton);
	DrawButtonForMenu(ComponentButton);
	DrawButtonForMenu(hamiltonButton);
	DrawButtonForMenu(eulerButton);
	DrawButtonForMenu(dinhTruButton);
	DrawButtonForMenu(dinhThatButton);
	DrawButtonForMenu(bridgeEdgeButton);
	DrawButtonForMenu(topoSortButton);
}
void DrawMatrix(){
	setfillstyle(1, WHITE);
	bar(10, 400, maxx/3 + 2, maxy - 10);
	outtextxy(100, 410, "MA TRAN TRONG SO");
	setlinestyle(0, 0, 1);
	for(int j = 0; j < 14; j++){
		for(int i = 0; i < 14; i++){
			rectangle(10 + i * 28, 440 + j * 25, 10 + i * 28 + 28, 440 + 25 + j * 25);
		}
	}
	setlinestyle(0, 0, 2);
	rectangle(10, 400, maxx / 3 + 2, 440);
	rectangle(10, 400, maxx / 3 + 2, maxy - 10);
}
void DrawWeightMatrix(Graph &graph){
	DrawMatrix();
	settextstyle(3, HORIZ_DIR, 1);
	for(int i = 0; i < graph.numberNode; i++){
		if(graph.numberNode > i){
			setcolor(RED);
			outtextxy(10 + 5 - 1, maxy/2 + 40 + (i+1)*25 + 1, (char*)graph.node[i]->name.c_str());
			outtextxy(10 + (i+1)*28 + 3, maxy/2 + 40 + 1, (char*)graph.node[i]->name.c_str());
		}
		for(int j = 0; j < graph.numberNode; j++){
			setcolor(BLUE);
			if(graph.adj[i][j] != 0) outtextxy(10 + (j+1)*28 + 5, maxy/2 + 40 + (i+1)*25 + 1, (char*)to_string(graph.adj[i][j]).c_str());
			else outtextxy(10 + (j+1)*28 + 5 - 1, maxy/2 + 40 + (i+1)*25 + 1, " ");
		}
	}
	settextstyle(3, HORIZ_DIR, 3);
}
/////////////////////////////////////////////////Tao Dinh///////////////////////////////////////
//Kiem tra vi tri click chuot co o ben trong Node hay khong
bool CheckNode(int x, int y, int mx, int my){
	return (((mx - x)*(mx - x) + (my - y)*(my - y) <= 25*25) && ((mx > realProcessingArea.x1 && mx < realProcessingArea.x2 && my > realProcessingArea.y1 && my < realProcessingArea.y2)));
}
bool CheckClickButton(Button button, int x, int y){	
	return (x > button.x1 && x < button.x2 && y > button.y1 && y < button.y2);
}
bool CheckClickCircle(ButtonCircle button, int x, int y){
	return ((x - button.x) * (x - button.x) + (y - button.y) * (y - button.y) <= button.r * button.r);
}
//KIEM TRA VI TRI
bool CheckPos(Graph &graph, int mx, int my){
	if(graph.numberNode == 0){
		if(mx > realProcessingArea.x1 && mx < realProcessingArea.x2 && my > realProcessingArea.y1 && my < realProcessingArea.y2) return true;
		else return false;
	}
	else {
		if(mx > realProcessingArea.x1 && mx < realProcessingArea.x2 && my > realProcessingArea.y1 && my < realProcessingArea.y2){ //return true;
			for (int i = 0; i < graph.numberNode; ++i){
				if((mx - graph.node[i]->x)*(mx - graph.node[i]->x) + (my - graph.node[i]->y)*(my - graph.node[i]->y) <  75 * 75){
					return false;
				}
			}
			return true;
		} 
		else return false;
	}		
}
//THEM NODE 
bool AddNode(Graph &graph, int &x, int &y, string &ten, bool flag){
	if(CheckPos(graph, x, y)){
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
bool CheckName(Graph &graph, string nameNode){
	if(graph.numberNode == 0) return true;
	else{
		for(int i = 0; i < graph.numberNode; i++){
			if(graph.node[i]->name == nameNode){
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
	x1 = 2 * x1 - x2;
	y1 = 2 * y1 - y2;
	double x3 =	c60 * (x1 - x2) - s60 * (y1 - y2) + x2; 
  	double y3 = s60 * (x1 - x2) + c60 * (y1 - y2) + y2;
  	double x4 = c60 * (x1 - x2) + s60 * (y1 - y2) + x2;
  	double y4 = -s60 * (x1 - x2) + c60 * (y1 - y2) + y2;
  	int polypoints[] = {x2, y2, (int)x3, (int)y3, (int)x4, (int)y4, x2, y2};
  	setfillstyle(1, color);
  	fillpoly(4, polypoints);
}
void FlipCurved(Node *node1, Node *node2, char *tt, int color) {
	setcolor(color);
	setlinestyle(0, 0, 2);
	int x1 = node1->x, y1 = node1->y, x2 = node2->x, y2 = node2->y;
  	// quay doan thang mot goc 90 do nguoc chieu kim dong ho
  	float midx = (x1 + x2) * 1.0 / 2, midy = (y1 + y2) * 1.0 / 2;
  	float xO = (y2 - midy) + midx; 
  	float yO = -(x2 - midx) + midy;
  	// tinh toa do cua cac giao diem cua duong tron tam O voi duong tron
  	float r1 = sqrt(pow(xO - x1, 2) + pow(yO - y1, 2));
  	float d = r1;
  	float r2 = 25;
  	float a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
  	float h = sqrt(r1 * r1 - a * a);
  	float tempx1 = xO + a * (x1 - xO) / d;
  	float tempy1 = yO + a * (y1 - yO) / d;
  	float tempx2 = xO + a * (x2 - xO) / d;
  	float tempy2 = yO + a * (y2 - yO) / d;
  	float x3 = tempx1 + h * (y1 - yO) / d;
  	float y3 = tempy1 - h * (x1 - xO) / d;
  	float x4 = tempx2 - h * (y2 - yO) / d;
	float y4 = tempy2 + h * (x2 - xO) / d;
	// tim goc quet
	float angle1 = acos(float(x1 - xO) / r1) * 180.0 / M_PI;
	float angle2 = acos(1 - float(pow(r2, 2)) / (2 * pow(r1, 2))) * 180.0 / M_PI;
	if (y1 >= yO) angle1 = 360 - angle1;
	float startAngle = angle1 + angle2;
	float x5 = float(32 * x4 - 7 * x2) / 25;
	float y5 = float(32 * y4 - 7 * y2) / 25;
	float len45 = sqrt(pow(x5 - x4, 2) + pow(y5 - y4, 2));
	float len35 = sqrt(pow(x3 - x5, 2) + pow(y3 - y5, 2));
	float sweep = acos((2 * pow(r1, 2) - pow(len35, 2)) / (2 * pow(r1, 2))) * 180.0 / M_PI;
	sweep += asin(len45 / (2 * r1));
	float endAngle = startAngle + sweep; 
	DrawTriangle(round(x5), round(y5), round(x4), round(y4), color);
	arc(round(xO), round(yO), round(startAngle), round(endAngle), round(r1));
	float sin45 = sin(45 * M_PI / 180);
	float cos45 = cos(45 * M_PI / 180);
	float xT = sin45 * (x1 - xO) + cos45 * (y1 - yO) + xO;
	float yT = -sin45 * (x1 - xO) + cos45 * (y1 - yO) + yO;
	outtextxy(round(xT) - 12, round(yT) - 12, tt);
}
void CreateCurved(Node *node1, Node *node2, char *tt, int color) {
	setcolor(color);
	setlinestyle(0, 0, 2);
	int x1 = node1->x, y1 = node1->y, x2 = node2->x, y2 = node2->y;
  	// quay doan thang mot goc 90 do nguoc chieu kim dong ho
  	float midx = (x1 + x2) * 1.0 / 2, midy = (y1 + y2) * 1.0 / 2;
  	float xO = -(y2 - midy) + midx; 
  	float yO = (x2 - midx) + midy;
  	// tinh toa do cua cac giao diem cua duong tron tam O voi duong tron
  	float r1 = sqrt(pow(xO - x1, 2) + pow(yO - y1, 2));
  	float d = r1;
  	float r2 = 25;
  	float a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
  	float h = sqrt(r1 * r1 - a * a);
  	float tempx1 = xO + a * (x1 - xO) / d;
  	float tempy1 = yO + a * (y1 - yO) / d;
  	float tempx2 = xO + a * (x2 - xO) / d;
  	float tempy2 = yO + a * (y2 - yO) / d;
  	float x3 = tempx1 - h * (y1 - yO) / d;
  	float y3 = tempy1 + h * (x1 - xO) / d;
  	float x4 = tempx2 + h * (y2 - yO) / d;
	float y4 = tempy2 - h * (x2 - xO) / d;
	// tim goc quet
	float angle1 = acos(float(x1 - xO) / r1) * 180.0 / M_PI;
	float angle2 = acos(1 - float(pow(r2, 2)) / (2 * pow(r1, 2))) * 180.0 / M_PI;
	if (y1 >= yO) angle1 = -angle1;
	float startAngle = angle1 - angle2;
	float x5 = float(32 * x4 - 7 * x2) / 25;
	float y5 = float(32 * y4 - 7 * y2) / 25;
	float len45 = sqrt(pow(x5 - x4, 2) + pow(y5 - y4, 2));
	float len35 = sqrt(pow(x3 - x5, 2) + pow(y3 - y5, 2));
	float sweep = acos((2 * pow(r1, 2) - pow(len35, 2)) / (2 * pow(r1, 2))) * 180.0 / M_PI;
	sweep += asin(len45 / (2 * r1));
	float endAngle = startAngle - sweep;
	float temp = startAngle;
	startAngle = endAngle;
	endAngle = temp;
	//swap(startAngle, endAngle); 
	float sin45 = sin(45 * M_PI / 180);
	float cos45 = cos(45 * M_PI / 180);
	float xT = sin45 * (x1 - xO) - cos45 * (y1 - yO) + xO;
	float yT = sin45 * (x1 - xO) + cos45 * (y1 - yO) + yO;
	if (!(xT > 440 && xT < 1150 && yT > 90 && yT < 560)) {
		FlipCurved(node1, node2, tt, color);
		return;
	}
	DrawTriangle(round(x5), round(y5), round(x4), round(y4), color);
	arc(round(xO), round(yO), round(startAngle), round(endAngle), round(r1));
	outtextxy(round(xT) - 12, round(yT) - 12, tt);
}
void CreateLine(Node *node1, Node *node2, char *tt, int color) {
	// tim diem dau tien
	setcolor(color);
	setlinestyle(0, 0, 2);
	int x1 = node1->x, y1 = node1->y, x2 = node2->x, y2 = node2->y;
	string name1 = node1->name, name2 = node2->name;
	float xx2 = 0, yy2 = 0, xx1 = x1, yy1 = y1;
	xx1 -= x2, yy1 -= y2;
	float a = yy2 - yy1;
	float b = xx1 - xx2;
	float c = a * xx1 + b * yy1;
	float x0 = -a * c * 1.0 / (a * a + b * b), y0 = -b * c / (a * a + b * b);
	float d = 25 * 25 - c * c * 1.0 / (a * a + b * b);
	float mult = sqrt(d / (a * a + b * b));
	float ax, ay;
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
	float bx, by;
	bx = x0 - b * mult;
	by = y0 + a * mult;
	bx += x1, by += y1;
	// tim diem de ve mui ten
	float vectorx = x1 - x2, vectory = y1 - y2;
	float factor = 7 / sqrt(pow(vectorx, 2) + pow(vectory, 2));
	vectorx *= factor;
	vectory *= factor;
	float x3 = ax + vectorx, y3 = ay + vectory;
	// tim trung diem
	float xT = (x1 + x2) * 1.0 / 2;
	float yT = (y1 + y2) * 1.0 / 2;
	// ve duong thang
	line(ax, ay, bx, by);
	DrawTriangle(x3, y3, ax, ay, color);
	outtextxy(xT - 13, yT - 13, tt);
}
void DrawGraph(Graph &graph) {
	setlinestyle(0, 0, 2);
	for (int i = 0; i < graph.numberNode; ++i) {
		string s = graph.node[i]->name;
		CreateNode(graph.node[i]->x, graph.node[i]->y, (char*)s.c_str(), BLUE);
	}
	for (int i = 0; i < graph.numberNode; ++i) {
		for(int j = 0; j < graph.numberNode; j++){
			if(graph.type[i][j] == 1){
				string value = (to_string(graph.adj[i][j]).size() == 1 ? "0" + to_string(graph.adj[i][j]) : to_string(graph.adj[i][j]));
				CreateLine(graph.node[i], graph.node[j], (char*)value.c_str(), BLUE);
			}
			else if(graph.type[i][j] == 2){
				string value = (to_string(graph.adj[i][j]).size() == 1 ? "0" + to_string(graph.adj[i][j]) : to_string(graph.adj[i][j]));
				CreateCurved(graph.node[i], graph.node[j], (char*)value.c_str(), BLUE);
			}
		}
	}
}
void DeleteEdge(Graph &graph, int x1, int y1, int x2, int y2, int index1, int index2) {
	if (index1 != index2) {
		if (graph.adj[index1][index2]) {
			string empty = "     ";
			if (graph.type[index1][index2] == 1) 
				CreateLine(graph.node[index1], graph.node[index2], (char*)empty.c_str(), WHITE);
			else if (graph.type[index1][index2] == 2) 
				CreateCurved(graph.node[index1], graph.node[index2], (char*)empty.c_str(), WHITE);
			graph.adj[index1][index2] = 0;
			graph.type[index1][index2] = 0;
			DrawGraph(graph);
		}
	}
}
void DeleteVertex(Graph &graph, int x, int y, int index) {
	string empty = "      ";
	for (int row = 0; row < graph.numberNode; ++row) {
		if (graph.adj[row][index]) {
			if (graph.type[row][index] == 1) {
				CreateLine(graph.node[row], graph.node[index], (char*)empty.c_str(), WHITE);
			} else if (graph.type[row][index] == 2) {
				CreateCurved(graph.node[row], graph.node[index], (char*)empty.c_str(), WHITE);
			}
		}
	}
	for (int col = 0; col < graph.numberNode; ++col) {
		if (graph.adj[index][col]) {
			if (graph.type[index][col] == 1) {
				CreateLine(graph.node[index], graph.node[col], (char*)empty.c_str(), WHITE);
			} else if (graph.type[index][col] == 2) {
				CreateCurved(graph.node[index], graph.node[col], (char*)empty.c_str(), WHITE);
			}
		}
	}
	CreateNode(x, y, (char*)empty.c_str(), WHITE);
	// xoa dinh -> xoa node trong mang node
	for (int i = index; i < graph.numberNode - 1; ++i)
		graph.node[i] = graph.node[i + 1];
	// xoa cot
	for (int i = index; i < graph.numberNode - 1; ++i) {
		for (int j = 0; j < graph.numberNode; ++j) {
			graph.adj[j][i] = graph.adj[j][i + 1]; 
			graph.type[j][i] = graph.type[j][i + 1];
		}
	} 
	// xoa hang
	for (int i = index; i < graph.numberNode - 1; ++i) {
		for (int j = 0; j < graph.numberNode - 1; ++j) {
			graph.adj[i][j] = graph.adj[i + 1][j];
			graph.type[i][j] = graph.type[i + 1][j];
		}
	}
	graph.numberNode--;
	DrawGraph(graph);
}
void Move(Graph &graph, int x1, int y1, int x2, int y2, int index) {
	// xoa nut hien tai
	string empty = "      ";
	for (int row = 0; row < graph.numberNode; ++row) {
		if (graph.adj[row][index]) {
			if (graph.type[row][index] == 1) {
				CreateLine(graph.node[row], graph.node[index], (char*)empty.c_str(), WHITE);
			} else if (graph.type[row][index] == 2) {
				CreateCurved(graph.node[row], graph.node[index], (char*)empty.c_str(), WHITE);
			}
		}
	}
	for (int col = 0; col < graph.numberNode; ++col) {
		if (graph.adj[index][col]) {
			if (graph.type[index][col] == 1) {
				CreateLine(graph.node[index], graph.node[col], (char*)empty.c_str(), WHITE);
			} else if (graph.type[index][col] == 2) {
				CreateCurved(graph.node[index], graph.node[col], (char*)empty.c_str(), WHITE);
			}
		}
	}
	CreateNode(x1, y1, (char*)empty.c_str(), WHITE);
	graph.node[index]->x = x2, graph.node[index]->y = y2;
	DrawGraph(graph);
}
//////////////////////////////////////////file///////////////////////////////////////////////////////
int ToInt(string s) {
	int n = s.length(), res = 0;
	for (int i = 0; i < n; ++i)
		res = res * 10 + s[i] - '0';
	return res;
}
string ToString(int n) {
    if (n == 0) return "0";
    string ans = "";
    while(n) {
        int r = n % 10;
        ans = (char)(r + '0') + ans;
        n /= 10;
    }
    return ans;
}
string ToStringLen2(int n) {
    string s = ToString(n);
    if (s.length() == 1) s = "0" + s;
    return s;
}
void WriteFile(char *fileName, Graph &graph) {
	ofstream myFile;
	myFile.open(fileName);
	myFile << graph.numberNode << "\n";
	for (int i = 0; i < graph.numberNode; ++i) {
		for (int j = 0; j < graph.numberNode; ++j) 
			myFile << graph.adj[i][j] << " ";
		myFile << "\n";
	}
	for (int i = 0; i < graph.numberNode; ++i) {
		int name = ToInt(graph.node[i]->name); 
		myFile << name << " " << graph.node[i]->x << " " << graph.node[i]->y << "\n";
	}
	myFile.close();
}
void ReadFile(char *fileName, Graph &graph) {
	ifstream myFile;
	myFile.open(fileName);
	myFile >> graph.numberNode;
	for (int i = 0; i < graph.numberNode; ++i) 
		for (int j = 0; j < graph.numberNode; ++j) {
			myFile >> graph.adj[i][j];
			if (graph.adj[i][j]) 
				if (i < j) 
					graph.type[i][j] = 1;
				else 
					if (graph.adj[j][i])
						graph.type[i][j] = 2;
					else
						graph.type[i][j] = 1;
		}
	int name, x, y;
	for (int i = 0; i < graph.numberNode; ++i) {
		myFile >> name >> x >> y;
		graph.node[i] = new Node(ToStringLen2(name), x, y);
	} 
	myFile.close();
}
void DrawEdge(Graph &graph, int idx1, int idx2, int color){
	if(graph.type[idx1][idx2] == 1){
		string value = (to_string(graph.adj[idx1][idx2]).size() == 1 ? "0" + to_string(graph.adj[idx1][idx2]) : to_string(graph.adj[idx1][idx2]));
		CreateLine(graph.node[idx1], graph.node[idx2], (char*)value.c_str(), color);
	}
	else if(graph.type[idx1][idx2] == 2){
		string value = (to_string(graph.adj[idx1][idx2]).size() == 1 ? "0" + to_string(graph.adj[idx1][idx2]) : to_string(graph.adj[idx1][idx2]));
		CreateCurved(graph.node[idx1], graph.node[idx2], (char*)value.c_str(), color);
	}
}
// ///////////////////////////////////////////thuat toan/////////////////////////////////////////////////
void DFS (Graph graph, int start){
	bool *vis = new bool[graph.numberNode]; // danh dau da tham hay chua
	int *p = new int[graph.numberNode]; 	// danh dau dinh cha
	for (int i = 0; i < graph.numberNode; ++i)
		vis[i] = false, p[i] = -1;
	Stack st;
	st.push(start);
	NotificationFull("DEMO THUAT TOAN DFS!");
	while(!st.empty()) {
		int u;
		st.pop(u);
		if (!vis[u]) {
			if (p[u] != -1) {
				string value = ToStringLen2(graph.adj[ p[u] ][u]);
				Sleep(1000);
				if (graph.type[ p[u] ][u] == 1) {
					CreateLine(graph.node[ p[u] ], graph.node[u], (char*)value.c_str(), WHITE);
					CreateLine(graph.node[ p[u] ], graph.node[u], (char*)value.c_str(), RED);
				}
				else if (graph.type[ p[u] ][u] == 2) {
					CreateCurved(graph.node[ p[u] ], graph.node[u], (char*)value.c_str(), WHITE);
					CreateCurved(graph.node[ p[u] ], graph.node[u], (char*)value.c_str(), RED);
				}
				Sleep(1000);
				setlinestyle(0, 0, 3);
				setcolor(GREEN);
				circle(graph.node[u]->x, graph.node[u]->y, 25);
				setcolor(WHITE);
			} 
			else {
				Sleep(1000);
				setlinestyle(0, 0, 3);
				setcolor(GREEN);
				circle(graph.node[u]->x, graph.node[u]->y, 25);
				setcolor(WHITE);
			}
			vis[u] = true;
		} 
		for (int v = graph.numberNode - 1; v >= 0; --v) {
			if (graph.adj[u][v] && !vis[v]) {
				st.push(v);
				p[v] = u;
			}
		}
	}
	NotificationFull("DA HOAN THANH!");
	delete[] vis;
	delete[] p;
}
void BFS (Graph graph, int start){
	bool *vis = new bool[graph.numberNode]; // danh dau da tham hay chua
	int *parent = new int[graph.numberNode]; 	// danh dau dinh cha
	for (int i = 0; i < graph.numberNode; ++i)
		vis[i] = false, parent[i] = -1;
	Queue q;
	q.push(start);
	NotificationFull("DEMO THUAT TOAN DFS!");
	while(!q.empty()) {
		int u;
		q.pop(u);	
		if (vis[u] == false) {
			vis[u] = true;
			if (parent[u] != -1) {
				string value = ToStringLen2(graph.adj[ parent[u] ][u]);
				Sleep(1000);
				if (graph.type[ parent[u] ][u] == 1) {
					CreateLine(graph.node[ parent[u] ], graph.node[u], (char*)value.c_str(), WHITE);
					CreateLine(graph.node[ parent[u] ], graph.node[u], (char*)value.c_str(), RED);
				}				
				else if (graph.type[ parent[u] ][u] == 2) {
					CreateCurved(graph.node[ parent[u] ], graph.node[u], (char*)value.c_str(), WHITE);
					CreateCurved(graph.node[ parent[u] ], graph.node[u], (char*)value.c_str(), RED);
				}
				Sleep(1000);
				setlinestyle(0, 0, 3);
				setcolor(GREEN);
				circle(graph.node[u]->x, graph.node[u]->y, 25);
				setcolor(WHITE);
			} 
			else {
				Sleep(1000);
				setlinestyle(0, 0, 3);
				setcolor(GREEN);
				circle(graph.node[u]->x, graph.node[u]->y, 25);
				setcolor(WHITE);
			}
		} 
		for (int v = 0; v < graph.numberNode; v++) {
			if (graph.adj[u][v] != 0 && vis[v] == false) {
				q.push(v);
				parent[v] = u;
			}
		}
	}
	NotificationFull("DA HOAN THANH!");
	delete[] vis;
	delete[] parent;
}	
void Component (Graph graph){
	int T[graph.numberNode];
	int count = 0;
	for(int i=0; i<graph.numberNode; i++) T[i] = 0;
	for(int i=0; i < graph.numberNode; i++){
		bool tick[graph.numberNode];
		int tmp = 0;
		for(int j=0; j<graph.numberNode; j++) tick[j] = false;
		Stack st;
		bool flag = true;
		st.push(i);
		if(T[i] == 0){
			count++;
			cout<<'\n'<<count<<": ";
			flag = false;	
		} 
		while(st.empty() == false){
			st.pop(tmp);
			if(tick[tmp] == false){
				tick[tmp] = true;
				T[tmp]++;
				if(flag == false){
					cout<<tmp + 1<<' ';
					setcolor(count + 1);
					setlinestyle(0, 0, 3);
					circle(graph.node[tmp]->x, graph.node[tmp]->y, 25);
					for(int i = 0; i < graph.numberNode; i++){
						if(graph.adj[tmp][i]){
							string value = (to_string(graph.adj[tmp][i]).size() == 1 ? "0" + to_string(graph.adj[tmp][i]) : to_string(graph.adj[tmp][i]));
							DrawEdge(graph, tmp, i, count + 1);
						}
					}
				}
			}
			for(int k=graph.numberNode - 1; k >= 0; k--){
				if(graph.adj[tmp][k] != 0 && tick[k] == false){
					st.push(k);
				}
			}	
		}
	}	
	cout<<"So thanh phan lien thong la: "<<count;
}	
/////////////////////////////////////////////////////////////////Dijkstra/////////////////////////////////////////////////////////////////////////////////
// int minDistance(int distance[], bool tick[]){
// 	int min = INT_MAX, minIndex = -1;
// 	for(int i=0; i<V; i++) {
// 		if(min > distance[i] && tick[i] == false){
// 			min = distance[i];
// 			minIndex = i;
// 		}
// 	}
// 	return minIndex;
// }	
// void Dijkstra(Graph graph, int f){
// 	bool tick[graph.numberNode];
// 	int distance[graph.numberNode];
// 	for(int i=0; i<graph.numberNode; i++){
// 		tick[i] = false;
// 		distance[i] = INT_MAX;
// 	}
// 	dist[f] = 0;
// 	for(int count = 0; count < graph.numberNode - 1; count++){
// 		int u = minDistance(distance, tick);
// 		tick[u] = true;
// 		for(int v = 0; v < graph.numberNode; v++){
// 			if(tick[v] == false && graph.adj[u][v] && distance[u] != INT_MAX && distance[u] + graph.adj[u][v] < distance[v]){
// 				distance[v] = distance[u] + graph.adj[u][v];
// 			}
// 		}
// 	}
// 	for(int i=0; i < graph.numberNode; i++){
// 		cout<<i+1<<' '<<distance[i]<<'\n';
// 	}
// }
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
// int StringToInt(string s) {
//     int n = s.length(), ans = 0;
//     for (int i = 0; i < n; ++i) 
//         ans = ans * 10 + (s[i] - '0');
//     return ans;
// }
// int CountComponents(Graph g, int start) {
//     int temp[MAXN][MAXN];
//     for (int i = 0; i < MAXN; ++i)
//         for (int j = 0; j < MAXN; ++j)
//             temp[i][j] = 0;
//     for (int i = 0; i < g.numberNode; ++i) 
//         for (int j = 0; j < g.numberNode; ++j)
//             if (g.adj[i][j]) 
//                 temp[i][j] = temp[j][i] = 1;       
//     bool vis[MAXN];
//     for (int i = 0; i < g.numberNode; ++i) vis[i] = false;
//     if (start != -1) vis[start] = true;
//     int count = 0;
//     for (int i = 0; i < g.numberNode; ++i) {
//         if (vis[i] == false) {
//             count++;
//             Queue q;
//             q.push(i);
//             vis[i] = true;
//             while(!q.empty()) {
//                 int u;
//                 q.pop(u);
//                 for (int i = 0; i < g.numberNode; ++i) {
//                     if (temp[u][i] && vis[i] == false) {
//                         q.push(i);
//                         vis[i] = true;
//                     }
//                 }
//             }
//         }
//     }
//     return count;
// }
// /////////////////////// Dinh that ////////////////////////////
// bool dfsCheck(int u, int v, Graph g) {
//     bool vis[MAXN];
//     for (int i = 0; i < g.numberNode; ++i) vis[i] = false;
//     Stack stack;
//     stack.push(u);
//     vis[u] = true;
//     int numCheckedVertex = 0;
//     while(!stack.empty()) {
//         int start;
//         stack.pop(start);
//         if (start == v) return 1;
//         ++numCheckedVertex;
//         for (int i = 0; i < g.numberNode; ++i) 
//             if (!vis[i] && g.adj[start][i]) {
//                 vis[i] = true;
//                 stack.push(i);
//             }
//     }
//     return (numCheckedVertex == g.numberNode);
// }
// bool IsConnected(int u, int v, Graph g) {
//     bool vis[MAXN];
//     for (int i = 0; i < g.numberNode; ++i) vis[i] = false;
//     Queue q;
//     q.push(u);
//     vis[u] = true;
//     while(!q.empty()) {
//         int t;
//         q.pop(t);
//         for (int i = 0; i < g.numberNode; ++i) {
//             if (g.adj[t][i] && !vis[i]) {
//                 q.push(i);
//                 vis[i] = true;
//                 /// neu nut i = v thi co lien thong //////////
//                 if (i == v)
//                     return true;
//             }
//         }
//     }
//     return false;
// }
// void KnotPoint(int u, int v, Graph g) {
// 	if (g.adj[u][v] || !dfsCheck(u, v, g)) {
// 		cout << "Khong co dinh that (Ton tai duong di truc tiep / Khong co duong di)\n";
// 		return;
// 	}
//     int temp[MAXN][MAXN];
//     int res[MAXN];
//     int index = 0;
//     for (int i = 0; i < g.numberNode; ++i) 
//         for (int j = 0; j < g.numberNode; ++j)
//             temp[i][j] = g.adj[i][j];
//     for (int i = 0; i < g.numberNode; ++i) {
//         ///////////////////// loai bo dinh /////////////////////
//         for (int j = 0; j < g.numberNode; ++j) 
//             g.adj[j][i] = g.adj[i][j] = 0;
//         // kiem tra co duong di tu u den v hay ko//////////////
//         if (!IsConnected(u, v, g)) 
//             if (i != u && i != v) 
//                 res[index++] = i;
//         // khoi phuc lai trang thai truoc do///////////////////
//         for (int j = 0; j < g.numberNode; ++j) 
//             g.adj[j][i] = temp[j][i], g.adj[i][j] = temp[i][j];
//     }
//     if (index == 0) {
//     	cout << "Khong co dinh that giua " << u << " va " << v << "\n"; 
// 	} else {
// 		cout << "Co " << index << " dinh that giua " << u << " va " << v << ":\n";
// 		for (int i = 0; i < index; ++i)
// 			cout << res[i] << "\n";
// 	}
// }
// ///////////////////////////////////////////////////////////////

// /////////////////////Chu trinh Euler///////////////////////////
// bool IsEulerCircuit(Graph g) {
//     int numberComponents = CountComponents(g, -1);
//     if (numberComponents != 1) return false;
//     for (int i = 0; i < g.numberNode; ++i) {
//         int degPlus = 0, degNeg = 0;
//         for (int j = 0; j < g.numberNode; ++j) { 
//             if (g.adj[i][j])
//                 degPlus++;
//             if (g.adj[j][i]) 
//                 degNeg++;
//         }
//         if (degPlus != degNeg) 
//             return false;
//     }
//     return true;
// }
// void EulerCycle(Graph g) {
//     if (!IsEulerCircuit(g)) {
//         cout << "Khong ton tai chu trinh Euler";
//         return;
//     }
//     int temp[MAXN][MAXN];
//     int len = 0;
//     for (int i = 0; i < g.numberNode; ++i) 
//         for (int j = 0; j < g.numberNode; ++j) {
//             temp[i][j] = g.adj[i][j];
//             if (g.adj[i][j]) len++;
//         }
//     const int lenPath = len;
//     int path[lenPath];
//     Stack stack;
//     stack.push(0); 
//     int currVertex = 0, index = 0;
//     while(!stack.empty()) {
//         int t = -1;
//         /* tim node dau tien ma currVertex noi toi */
//         for (int i = 0; i < g.numberNode; ++i) 
//             if (temp[currVertex][i]) {
//                 t = i;
//                 break;
//             }
//         if (t != -1) {
//             stack.push(currVertex);
//             int nextVertex = t;
//             temp[currVertex][nextVertex] = 0;
//             currVertex = nextVertex;
//         } else {
//             path[index++] = currVertex;
//             len++;
//             int u;
//             stack.pop(u);
//             currVertex = u;
//         }
//     }
//     cout << "Ton tai chu trinh Euler:\n";
//     for (int i = 0; i < len; ++i)
//         cout << path[i] << " -> ";
//     cout << 0 << "\n";
// }
// ///////////////////////////////////////////////////////////////

// /////////////////// Chu trinh Hamilton /////////////////////////////////
// /* Ham kiem tra xem dinh 'v' co the them vao vi tri 'pos' 
// trong chu trinh hamilton duoc hay khong */
// bool IsSafe(int v, Graph g, int path[], int count[], int pos) {
//     /* Kiem tra dinh hien tai co phai la dinh lien ke 
//         cua dinh truoc do hay khong */ 
//     if (!g.adj[path[pos - 1]][v]) return false;
//     /* Kiem tra dinh da co truoc do hay chua*/
//     if (count[v] > 1) return false;
//     return true;
// }
// bool RecursiveHam(Graph g, int path[], int count[], int pos) {
//     /* Kiem tra neu toan bo cac dinh da duoc tham*/
//     if (pos == g.numberNode) {
//         /* Va kiem tra xem co canh noi tu dinh cuoi den
//             dinh dau trong 'path' hay khong*/
//         if (g.adj[path[pos - 1]][path[0]])
//             return true;
//         else
//             return false;
//     }
//     /* Khong tham dinh 0 vi ta mac dinh 0 la diem bat dau cua chu trinh*/
//     for (int v = 1; v < g.numberNode; ++v) {
//         if (IsSafe(v, g, path, count, pos)) {
//             path[pos] = v;
//             if (RecursiveHam(g, path, count, pos + 1))
//                 return true;
//             path[pos] = -1;
//         }
//     }
//     return false;
// }
// void HamCycle(Graph g) {
//     int path[MAXN];
//     int count[MAXN];
//     for (int i = 0; i < g.numberNode; ++i) {
//         path[i] = -1;
//         count[i] = 0;
//     }
//     path[0] = 0;
//     count[0] = 1;
//     if (RecursiveHam(g, path, count, 1) == false) {
//         cout << "Khong ton tai chu trinh Hamilton";
//         return;
//     } 
//     cout << "Ton tai chu trinh Hamilton:\n";
//     for (int i = 0; i < g.numberNode; ++i)
//         cout << path[i] << " -> ";
//     cout << path[0] << "\n"; 
// }
// ////////////////////////////////////////////////////////////////////////

// ///////////////////////////////Canh cau/////////////////////////////////
// void BridgeEdge(Graph g) {
//     int numComponents = CountComponents(g, -1);
//     int count = 0, edges = 0;
//     for (int i = 0; i < g.numberNode; ++i) 
//         for (int j = 0; j < g.numberNode; ++j)
//             if (g.adj[i][j])
//                 edges++;
//     const int numEdges = edges;
//     int bridgeEdges[numEdges][2];
//     for (int i = 0; i < g.numberNode; ++i) {
//         for (int j = 0; j < g.numberNode; ++j) {
//             if (g.adj[i][j]) {
//                 int value = g.adj[i][j];
//                 // Loai bo canh
//                 g.adj[i][j] = 0;
//                 // Dem so thanh phan lien thong sau khi da cat canh
//                 int numComAfterRemove = CountComponents(g, -1);
//                 // Khoi phuc lai ban dau
//                 g.adj[i][j] = value;
//                 if (numComAfterRemove > numComponents) {
//                     bridgeEdges[count][0] = i;
//                     bridgeEdges[count][1] = j;
//                     count++;
//                 }
//             }
//         }
//     }
//     if (count == 0) {
//         cout << "Khong ton tai canh cau";
//     } else {
//         cout << "Co " << count << " canh cau:\n";
//         for (int i = 0; i < count; ++i) 
//             cout << "(" << bridgeEdges[i][0] << ", " << bridgeEdges[i][1] << ")\n";
//     }
// }
// ////////////////////////////////////////////////////////////////////////

// ///////////////////////////////Dinh Tru/////////////////////////////////
// void ArticulationPoint(Graph g) {
//     int numberComponents = CountComponents(g, -1);
//     int count = 0;
//     int vertex[MAXN];
//     int temp[MAXN][MAXN];
//     for (int i = 0; i < g.numberNode; ++i) 
//         for (int j = 0; j < g.numberNode; ++j)
//             temp[i][j] = g.adj[i][j];
//     for (int i = 0; i < g.numberNode; ++i) {
//         // Xoa dinh
//         for (int j = 0; j < g.numberNode; ++j)
//             g.adj[i][j] = g.adj[j][i] = 0;
//         int numComAfterRemove = CountComponents(g, i);
//         // Khoi phuc
//         for (int j = 0; j < g.numberNode; ++j)
//             g.adj[i][j] = temp[i][j], g.adj[j][i] = temp[j][i];
//         if (numComAfterRemove > numberComponents)
//             vertex[count++] = i;
//     }
//     if (count == 0) {
//         cout << "Do thi khong co dinh tru";
//     } else {
//         cout << "Do thi co " << count << " dinh tru:\n";
//         for (int i = 0; i < count; ++i)
//             cout << i << "\n"; 
//     }
// }
// ////////////////////////////////////////////////////////////////////////

// ////////////////////////////Topo Sort///////////////////////////////////
// void RecursiveTopoSort(Graph g, int res[], bool vis[], int inDegree[], int &index) {
//     for (int i = 0; i < g.numberNode; ++i) {
//         if (inDegree[i] == 0 && !vis[i]) {
//             for (int j = 0; j < g.numberNode; ++j)
//                 if (g.adj[i][j])
//                     inDegree[j]--;
//             res[index] = i;
//             vis[i] = true;
//             index++;
//             RecursiveTopoSort(g, res, vis, inDegree, index);
//             for (int j = 0; j < g.numberNode; ++j)
//                 if (g.adj[i][j])
//                     inDegree[j]++;
//             vis[i] = false;
//             index--;
//         }
//     }
//     if (index == g.numberNode) {
//         cout << "[";
//         for (int i = 0; i < g.numberNode - 1; ++i)
//             cout << res[i] << ", ";
//         cout << res[g.numberNode - 1] << "]\n";
//     }
// }
// bool IsDAG(Graph g, int inDegree[]) {
//     Queue queue;
//     const int numberNode = g.numberNode;
//     int tempInDeg[numberNode];
//     for (int i = 0; i < g.numberNode; ++i)
//         tempInDeg[i] = inDegree[i];
//     for (int i = 0; i < g.numberNode; ++i)
//         if (!inDegree[i])
//             queue.push(i);
//     while(!queue.empty()) {
//         int u;
//         queue.pop(u);
//         for (int i = 0; i < g.numberNode; ++i) 
//             if (g.adj[u][i]) {
//                 inDegree[i]--;
//                 if (!inDegree[i])
//                     queue.push(i);
//             }
//     }
//     bool isDag = true;
//     for (int i = 0; i < g.numberNode; ++i) 
//         if (inDegree[i]) {
//             isDag = false;
//             break;
//         }
//     for (int i = 0; i < g.numberNode; ++i)
//         inDegree[i] = tempInDeg[i];
//     return isDag;
// }
// void TopoSort(Graph g) {
//     const int numberNode = g.numberNode;
//     bool vis[numberNode];
//     int inDegree[numberNode];
//     for (int i = 0; i < g.numberNode; ++i)
//         vis[i] = false, inDegree[i] = 0;
//     for (int i = 0; i < g.numberNode; ++i)
//         for (int j = 0; j < g.numberNode; ++j)
//             if (g.adj[i][j])
//                 inDegree[j]++;
//     if (!IsDAG(g, inDegree)) {
//         cout << "Do thi ton tai chu trinh";
//     } else {
//         cout << "Tat ca cac thu tu sap xep Topo duoc tim thay:\n";
//         int res[numberNode];
//         int index = 0;
//         RecursiveTopoSort(g, res, vis, inDegree, index);
//     }
// }