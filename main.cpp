#include <winbgim.h>
#include <iostream>
#include <dirent.h>
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
#define LIGHTGRAY 7 
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
/////////////////////////////////////////////////////////////////////_Define Object_/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////_Initialization Button_/////////////////////////////////////////////////////////////////////
Button newButton, openButton, saveButton, addVertexButton, addEdgeButton, moveButton, deleteVertexButton, deleteEdgeButton; 
Button dfsButton, bfsButton, shortestPathButton, ComponentButton, hamiltonButton, eulerButton, dinhTruButton, dinhThatButton, bridgeEdgeButton, topoSortButton;
Button helpArea, processingArea, realProcessingArea, closeButton, scannerArea, continueButton, cancelButton, toolbarArea, algorithmArea;
ButtonCircle delVertex, delEdge;
/////////////////////////////////////////////////////////////////////_Word Warp_/////////////////////////////////////////////////////////////////////
#define KEY_UP 72
#define KEY_DOWN 80
const int maxLine = 1000;
const int margin = 5;
const int marginLine = 0;
struct WordWrap {
	string result[maxLine];
	int size = 0;
	int linePerPage;
	int toRight;
	int start;
	WordWrap(int toRight) {
		this->toRight = toRight;
		
	}
 	void StoreString(string res, Button helpArea) {
		settextstyle(3, HORIZ_DIR, 2);
		int len = res.length();
		int x1 = helpArea.x1, x2 = helpArea.x2;
		int y2 = helpArea.y2, y1 = helpArea.y1;
		int fontHeight = textheight((char*)res.c_str());
		string temp = "";
		int j, tj;
		char *msg;
		int low = 0;
		for (int i = 0; i <= len; ++i) {	
			if (i < len) {
				temp += res[i];
				msg = (char*)temp.c_str();
				if (x1 + margin + textwidth(msg) > x2 - margin - toRight) {
					j = i;
					tj = i;	
					if (res[i] != ' ') { 
						while(res[i] != ' ' && i >= low) 
							i--;
						i++;
						if (i == low) { // nếu trở về trước thì chắc chắn chỉ có một từ
							while(x1 + margin + textwidth(msg) > x2 - margin - toRight) {
								temp.resize(temp.length() - 1);
								msg = (char*)temp.c_str();	
								j--;
							}
							i = j;
							low = j + 1;
						} else { // nếu ko trở về trước được thì chắc chắn có nhiều hơn 1 từ
							while(res[j] != ' ' && j < len) 
								j++;
							while(tj > i - 1) {
								temp.resize(temp.length() - 1);
								tj--;
							}
							low = i;
							i--;
						}
					} else { // ký tự thêm vào là khoảng trắng
						while(res[i] == ' ' && i >= low) {
							temp.resize(temp.length() - 1);
							i--;
						}
						msg = (char*)temp.c_str();
						while(res[j] == ' ' && j < len) {
							j++;
						}
						if (x1 + margin + textwidth(msg) > x2 - margin - toRight) {
							while(x1 + margin + textwidth(msg) > x2 - margin - toRight) {
								temp.resize(temp.length() - 1);
								msg = (char*)temp.c_str();
								i--;
							}
							low = i + 1;
						} else {
							low = j;
							i = j - 1;
						}
					}
					result[size] = temp;
					temp = "";
					size++;
				}
			} 
			if (i == len) {
				msg = (char*)temp.c_str();
				if (x1 + margin + textwidth(msg) > x2 - margin - toRight) {
					int lenTemp = temp.length();
					string tt = "";
					for (int i = 0; i <= lenTemp; ++i) {
						if (i < lenTemp) {
							tt += temp[i];
							msg = (char*)tt.c_str();
							if (x1 + margin + textwidth(msg) > x2 - margin - toRight) {
								if (x1 + margin + textwidth(msg) > x2 - margin - toRight) {
									tt.resize(tt.length() - 1);
									msg = (char*)tt.c_str();
									i--;
								}
								result[size] = temp;
								tt = "";
								size++;
							}
						} else {
							result[size] = temp;
							tt = "";
							size++;
						}
					}
				} else {
					result[size] = temp;
					temp = "";
					size++;
				}	
			}
		}
		start = -1;	
		linePerPage = (y2 - margin - (y1 + margin)) / (fontHeight + marginLine);
	}
	void PrintPage(bool down, Button helpArea) {
		bool isLessThan = true;
		if (size >= linePerPage) {
			if (down) {
				if (start + linePerPage > size - 1) {
					return;
				} else {
					start++;
				}
			} else {
				if (start - 1 < 0) {
					return;
				} else {
					start--;
				}
			}
			isLessThan = false;
		}
		if (isLessThan) start++;
		setcolor(BLUE);	
		int x1 = helpArea.x1, y1 = helpArea.y1, x2 = helpArea.x2, y2 = helpArea.y2;
		int fontHeight = textheight((char*)result[0].c_str());
		setfillstyle(1, WHITE);
		bar(x1 + 1, y1 + 1, x2 - toRight, y2 - margin);
		int xTxtTop, yTxtTop;
		for (int i = start; i < min(start + linePerPage, start + size); ++i) {
			xTxtTop = x1 + margin;
			yTxtTop = y1 + margin + (fontHeight + marginLine) * (i - start);
			setbkcolor(WHITE);
			outtextxy(xTxtTop, yTxtTop, (char*)result[i].c_str());
		}
	}
	int GetIndex(int x, int y, Button helpArea) {
		int x1 = helpArea.x1, y1 = helpArea.y1, x2 = helpArea.x2;	
		int fontHeight = textheight((char*)result[0].c_str());	
		int xTxtTop, yTxtTop, xTxtBot, yTxtBot;	
		for (int i = start; i < min(start + linePerPage, start + size); ++i) {
			xTxtTop = x1;
			yTxtTop = y1 + margin + (fontHeight + marginLine) * (i - start);
			xTxtBot = x2 - toRight;
			yTxtBot = yTxtTop + fontHeight;
			if (x > xTxtTop && x < xTxtBot && y > yTxtTop && y < yTxtBot)
				return i;
		}
		return -1;
	}		
};

/////////////////////////////////////////////////////////////////////_Screen_/////////////////////////////////////////////////////////////////////
void createScreenWelcome(string s);
void CreateScreen();
void CreateButton();
void DrawMenuTable();
void DrawButtonForMenu(Button button);
void DrawButtonForToolBar(Button button);
void DrawButtonForNoti(Button button);
void DrawToolBar();
void DrawMatrix();
void DrawWeightMatrix(Graph &graph);
void DrawSubDel();
string OpenScreen();
string ShowFileName(WordWrap word, char &key, string ans, Button showFileNameArea, Button fileNameButton, Button OpenButton, bool &isOpened);

/////////////////////////////////////////////////////////////////////_Check algorithm_/////////////////////////////////////////////////////////////////////
bool CheckNode(int x, int y, int mx, int my);
bool CheckClickButton(Button button, int x, int y);
bool CheckReClickNode(Graph graph, int mx, int my);
bool CheckName(Graph &graph, string name);
bool CheckPos(Graph &graph, int mx, int my);

/////////////////////////////////////////////////////////////////////_Draw Object_/////////////////////////////////////////////////////////////////////
void CreateNode(int x, int y, char name[], int color);
bool AddNode(Graph &graph, int &x, int &y, string &ten, bool flag);
void Rename(int x, int y, string &ten);
string AddNameWeight(string name);
string AddFileName();
void NotificationFull(string Noti);
void DrawTriangle(int x1, int y1, int x2, int y2, int color);
void FlipCurved(Node *node1, Node *node2, char *tt, int color);
void CreateCurved(Node *node1, Node *node2, char *tt, int color);
void CreateLine(Node *node1, Node *node2, char *tt, int color);
void DrawGraph(Graph &graph);
void DrawEdge(Graph &graph, int idx1, int color);
void DeleteEdge(Graph &graph, int x1, int y1, int x2, int y2, int index1, int index2);
void DeleteVertex(Graph &graph, int x, int y, int index);
void Move(Graph &graph, int x1, int y1, int x2, int y2, int index);
/////////////////////////////////////////////////////////////////////_Algorithm_/////////////////////////////////////////////////////////////////////
void EffectToolbar(Button button, int colorbk, int colortext, int colorborder);
void E2Toolbar(Button button, int colorbk, int colortext, int colorborder);
bool CheckInButton(Button button);
void EffectFile();
void EffectToolbar();
bool RunningToolbar(Graph &graph, string fileName, int &x, int &y, bool flag);
void RunningAlgorithm(Graph graph, int x, int y, WordWrap &word, Button helpArea, Button upButton, Button downButton, Button scrollbar, bool &showResult);
int ChooseVertex(Graph graph, int &x, int &y);
bool OpenSave(Graph &graph, string nameFile);
bool NewSave(Graph &graph, string &nameFile, bool &isFirstSave);
void EffectVertex(Graph graph, int u, int colorbk, int colortext);
void EffectEdge(Graph graph, int u, int v, int color);
void DFS (Graph graph, int f);
void BFS (Graph graph, int start);
void Component (Graph graph);
int minDistance(int distance[], bool tick[], int V);
void Dijkstra(Graph graph, int start, int end);
bool dfsCheck(Graph g, int u, int v);
bool IsConnected(Graph g, int u, int v);
void KnotPoint(Graph graph, int u, int v, WordWrap &word, Button helpArea);
void BridgeEdge(Graph graph, WordWrap &word, Button helpArea);
void ArticulationPoint(Graph graph, WordWrap &word, Button helpArea);
int CountComponents(Graph g, int start);
bool IsEulerCircuit(Graph g);
void EulerCycle(Graph graph, WordWrap &word, Button helpArea);
void HamCycle(Graph graph, WordWrap &word, Button helpArea);
bool RecursiveHam(Graph g, int path[], int count[], int pos);
bool IsSafe(int v, Graph g, int path[], int count[], int pos);
void TopologicalSort(Graph graph);
void OutputTopoSort(Graph graph, int iDaDK[], int sizeDaDK, int iMuonDK[], int sizeMuonDK, string mon[], int sizeMon, string daDK[], string muonDK[]);
bool isDAG(Graph graph);
int ReadFileTopo(char fileName[], string res[], int &size, int graphSize, bool checkData = false);
void RunningTopologicalSort(Graph graph);
void IndexArray(string a[], int size1, string b[], int res[], int size2);
int FindIdByName(string res[], int size, string s);

/////////////////////////////////////////////////////////////////////_Print resul_/////////////////////////////////////////////////////////////////////
string RemoveSpace(string s);
void DrawButton(Button btn, int color, bool fill);
void DeleteButton(Button btn);
void UpdateValue(WordWrap &word, int scrollbarArea, Button &scrollbar, int &thumbHeight, int &jump, int &u0);
void DrawResult(Button upButton, Button downButton, Button scrollbar);
/////////////////////////////////////////////////////////////////////_Conver Value_/////////////////////////////////////////////////////////////////////
string ToStringLen2(int n);
string ToString(int n);
int ToInt(string s);
/////////////////////////////////////////////////////////////////////_File_/////////////////////////////////////////////////////////////////////
void WriteFile(char *fileName, Graph &graph);
void ReadFile(char *fileName, Graph &graph);

int main(){
	// createScreenWelcome();
	CreateScreen();
	CreateButton();
	Graph graph;
	int x, y;
	string nameNode, nameFile;
	label:
	NotificationFull("HAY MO DO THI CO SAN HOAC TAO MOT DO THI MOI!");
	while(true){//Kiem tra khi mới vào. CHỉ được nhấn 1 trong 2 nút: New, Open
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
				bool flag = true;
				if(x > newButton.x1 && x < newButton.x2 && y > newButton.y1 && y < newButton.y2){//Nhat nut New
					NotificationFull("Chon chuc nang");
					string fileName = "";
					flag = false;
					if(RunningToolbar(graph, fileName, x, y, flag) == false) return 0;
				}
				else if(CheckClickButton(openButton, x, y)){//Nhan nut Open  
					string nameFile = OpenScreen();
					nameFile = "saves/" + nameFile;
					ReadFile((char*)nameFile.c_str(), graph);
					DrawGraph(graph);
					DrawWeightMatrix(graph);
					NotificationFull("HAY CHON CHUC NANG!");
					flag = true;
					if(RunningToolbar(graph, nameFile, x, y, flag) == false) return 0;
				}
			}
		}
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////_Screen_/////////////////////////////////////////////////////////////////////
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
void DisableMinimizeButton (HWND hwnd){
 	SetWindowLong (hwnd, GWL_STYLE,
               GetWindowLong (hwnd, GWL_STYLE) & ~ WS_MINIMIZEBOX);
}
void EnableMinimizeButton (HWND hwnd){
 	SetWindowLong (hwnd, GWL_STYLE,
               GetWindowLong (hwnd, GWL_STYLE) | WS_MINIMIZEBOX);
}
void DisableMaximizeButton (HWND hwnd){
 	SetWindowLong (hwnd, GWL_STYLE,
               GetWindowLong (hwnd, GWL_STYLE) & ~ WS_MAXIMIZEBOX);
}
void EnableMaximizeButton (HWND hwnd){
 	SetWindowLong (hwnd, GWL_STYLE,
               GetWindowLong (hwnd, GWL_STYLE) | WS_MAXIMIZEBOX);
}
void DisableCloseButton (HWND hwnd){
 	EnableMenuItem (GetSystemMenu (hwnd, FALSE), SC_CLOSE,
                MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
}
void EnableCloseButton (HWND hwnd){
 	EnableMenuItem (GetSystemMenu (hwnd, FALSE), SC_CLOSE,
                MF_BYCOMMAND | MF_ENABLED);
}
void CreateScreen(){
	initwindow(1209, 813);
	HWND hwnd = GetActiveWindow();
	if(hwnd) SetWindowText(hwnd, "Graph");
	DisableMaximizeButton(hwnd);
	DisableMinimizeButton(hwnd);
	DisableCloseButton(hwnd);
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
void CreateButton (){
	toolbarArea.name = "", toolbarArea.x1 = 10, toolbarArea.y1 = 10, toolbarArea.x2 = 1190, toolbarArea.y2 = 52;
	newButton.name = "      New", newButton.x1 = 10, newButton.y1 = 10, newButton.x2 = 155, newButton.y2 = 52;
	openButton.name = "     Open", openButton.x1 = 155, openButton.y1 = 10, openButton.x2 = 300, openButton.y2 = 52;
	saveButton.name = "     Save", saveButton.x1 = 300, saveButton.y1 = 10, saveButton.x2 = 445, saveButton.y2 = 52;
	addVertexButton.name = " AddVertex", addVertexButton.x1 = 445, addVertexButton.y1 = 10, addVertexButton.x2 = 590, addVertexButton.y2 = 52;
	addEdgeButton.name = "  AddEdge", addEdgeButton.x1 = 590, addEdgeButton.y1 = 10, addEdgeButton.x2 = 735, addEdgeButton.y2 = 52;
	moveButton.name = "     Move", moveButton.x1 = 735, moveButton.y1 = 10, moveButton.x2 = 880, moveButton.y2 = 52;
	deleteVertexButton.name = " DelVertex", deleteVertexButton.x1 = 880, deleteVertexButton.y1 = 10, deleteVertexButton.x2 = 1025, deleteVertexButton.y2 = 52;
	deleteEdgeButton.name = "DelEdge", deleteEdgeButton.x1 = 1025, deleteEdgeButton.y1 = 10, deleteEdgeButton.x2 = 1140, deleteEdgeButton.y2 = 52;
	algorithmArea.name = "", algorithmArea.x1 = 10, algorithmArea.y1 = 52, algorithmArea.x2 = maxx / 3 + 2, algorithmArea.y2 = 395;                 
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
	setlinestyle(0, 0, 2);
	rectangle(button.x1, button.y1, button.x2, button.y2);
	settextstyle(3, HORIZ_DIR, 3);
	if(button.name != "Topo Sort") outtextxy(button.x1 + 14, button.y1 + 18, (char*)button.name.c_str());
	else outtextxy(155, 340, (char*)button.name.c_str());
}
void DrawButtonForToolBar(Button button){
	setlinestyle(0, 0, 2);
	rectangle(button.x1, button.y1, button.x2, button.y2);
	settextstyle(3, HORIZ_DIR, 3);
	outtextxy(button.x1 + 10, button.y1 + 5, (char*)button.name.c_str());
}
void DrawButtonForNoti(Button button){
	setlinestyle(0, 0, 2);
	rectangle(button.x1, button.y1, button.x2, button.y2);
	settextstyle(3, HORIZ_DIR, 3);
	outtextxy(button.x1 + 150, button.y1 + 30, (char*)button.name.c_str());
}
void DrawToolBar(){
	setfillstyle(1, WHITE);
	bar(toolbarArea.x1, toolbarArea.y1, toolbarArea.x2, toolbarArea.y2);
	DrawButtonForToolBar(newButton);
	DrawButtonForToolBar(openButton);
	DrawButtonForToolBar(saveButton);
	DrawButtonForToolBar(addVertexButton);
	DrawButtonForToolBar(addEdgeButton);
	DrawButtonForToolBar(moveButton);
	DrawButtonForToolBar(deleteVertexButton);
	DrawButtonForToolBar(deleteEdgeButton);
	DrawButtonForToolBar(closeButton);
}
void DrawMenuTable(){
	setfillstyle(1, WHITE);
	bar(algorithmArea.x1 + 1, algorithmArea.y1 + 1, algorithmArea.x2, algorithmArea.y2);
	setlinestyle(0, 0, 2);
	rectangle(10, 58, maxx / 3 + 2, 395);
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
	setcolor(BLUE);
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
			if(graph.adj[i][j] != 0) outtextxy(10 + (j+1)*28 + 5, maxy/2 + 40 + (i+1)*25 + 1, (char*)ToStringLen2(graph.adj[i][j]).c_str());
			else outtextxy(10 + (j+1)*28 + 5 - 1, maxy/2 + 40 + (i+1)*25 + 1, " ");
		}
	}
	settextstyle(3, HORIZ_DIR, 3);
}
string OpenScreen(){
	int x = -1, y = -1;
	Button fileNameButton, propertyButton, exitButton, OpenButton, showFileNameArea, upButton, downButton;
	showFileNameArea.name = "", showFileNameArea.x1 = 510, showFileNameArea.y1 = 148, showFileNameArea.x2 = 1090, showFileNameArea.y2 = 445;
	fileNameButton.name = "", fileNameButton.x1 = 516, fileNameButton.y1 = 499, fileNameButton.x2 = 883, fileNameButton.y2 = 537;
	propertyButton. name = "Only file text(.txt)", propertyButton.x1 = 890, propertyButton.y1 = 452, propertyButton.x2 = 1083, propertyButton.y2 = 490;
	exitButton.name = "  Cancel", exitButton.x1 = 995, exitButton.y1 = 499, exitButton.x2 = 1083, exitButton.y2 = 537;
	OpenButton.name = "    Open", OpenButton.x1 = 890, OpenButton.y1 = 499, OpenButton.x2 = 988, OpenButton.y2 = 537;
	setcolor(BLACK);
	rectangle(maxx/3 + 9 + 100, 58 + 50, maxx - 110, 595 - 50);
	rectangle(maxx/3 + 9 + 100, 58 + 50, maxx - 110, 108 + 40);
	setfillstyle(1, LIGHTBLUE);
	bar(maxx/3 + 9 + 100, 58 + 50, maxx - 110, 108 + 40);
	setcolor(WHITE);
	setbkcolor(LIGHTBLUE);
	outtextxy(maxx/3 + 9 + 110, 108 + 5, "OPEN");
	setcolor(BLACK);
	setfillstyle(1, LIGHTGRAY);
	bar(maxx/3 + 9 + 101, 446, maxx - 111, 544);
	setlinestyle(0, 0, 1);
	setfillstyle(1, WHITE);
	bar(helpArea.x1, helpArea.y1, helpArea.x2, helpArea.y2);
	//thong bao
	rectangle(propertyButton.x1, propertyButton.y1, propertyButton.x2, propertyButton.y2);
	bar(propertyButton.x1 + 1, propertyButton.y1 + 1, propertyButton.x2, propertyButton.y2);
	//open
	rectangle(OpenButton.x1, OpenButton.y1, OpenButton.x2, OpenButton.y2);
	bar(OpenButton.x1 + 1, OpenButton.y1 + 1, OpenButton.x2, OpenButton.y2);
	//cancle
	rectangle(exitButton.x1, exitButton.y1, exitButton.x2, exitButton.y2);
	bar(exitButton.x1 + 1, exitButton.y1 + 1, exitButton.x2, exitButton.y2);
	//ten file
	rectangle(fileNameButton.x1, fileNameButton.y1, fileNameButton.x2, fileNameButton.y2);
	bar(fileNameButton.x1 + 1, fileNameButton.y1 + 1, fileNameButton.x2, fileNameButton.y2);
	setcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	settextstyle(3, HORIZ_DIR, 2);
	outtextxy(maxx/3 + 9 + 101 + 5, 450, "File name:");
	setbkcolor(WHITE);
	outtextxy(propertyButton.x1 + 5, propertyButton.y1 + 5, (char*)propertyButton.name.c_str());
	outtextxy(OpenButton.x1 + 5, OpenButton.y1 + 5, (char*)OpenButton.name.c_str());
	outtextxy(exitButton.x1 + 5, exitButton.y1 + 5, (char*)exitButton.name.c_str());
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	dirent *entry;
	WordWrap word1(20);
	char path[] = "saves";
	DIR *dir = opendir(path);
	if(dir == NULL) return "";
	else{
		while((entry = readdir(dir)) != NULL){
			string temp(entry->d_name);
			if(temp == "." || temp =="..") continue;
			else{
				word1.StoreString(temp, showFileNameArea);
			}
		}
		closedir(dir);
	}
	bool isTrue = false, isOpened = false;
	string ans = "";
	char key;
	int n = 0; 
	WordWrap word(22);
	if(isTrue == false){
		word = word1;
	}
	label:
	string s = ShowFileName(word, key, ans, showFileNameArea, fileNameButton, OpenButton, isOpened);
	if(s == "false") {
		if((key >= 'A' && key <= 'Z') || (key >= 'a' && key <='z') || (key >= '0' && key <= '9')){
			ans += key;
		}
		if(key == 8 && ans.size() > 0){
			ans.pop_back();
		}
		WordWrap wordTemp(20);
		for(int i = 0; i < word1.size; i++){
			if(word1.result[i].substr(0, ans.size()) == ans) {
				wordTemp.StoreString(word1.result[i], showFileNameArea);
			}
		}
		if(wordTemp.size > 0) word = wordTemp;
		else word = word1;
		outtextxy(fileNameButton.x1 + 5, fileNameButton.y1 + 5, "                                            ");
		outtextxy(fileNameButton.x1 + 5, fileNameButton.y1 + 5, (char*)ans.c_str());
		goto label;
	} else {
		return s;
	}
}
string ShowFileName(WordWrap word, char &key, string ans, Button showFileNameArea, Button fileNameButton, Button OpenButton, bool &isOpened){
	Button upButton;
	setlinestyle(0, 0, 1);
	upButton.x1 = showFileNameArea.x2 - 20;
	upButton.y1 = showFileNameArea.y1;
	upButton.x2 = showFileNameArea.x2;
	upButton.y2 = showFileNameArea.y1 + 20;
	DrawButton(upButton, BLACK, false);
	Button downButton;
	downButton.x1 = showFileNameArea.x2 - 20;
	downButton.y1 = showFileNameArea.y2 - 20;
	downButton.x2 = showFileNameArea.x2;
	downButton.y2 = showFileNameArea.y2;
	DrawButton(downButton, BLACK, false);
	setlinestyle(0, 0, 2);
	line(upButton.x1, upButton.y2, downButton.x1, downButton.y1);
	word.PrintPage(true, showFileNameArea);
	Button scrollbar;
	scrollbar.x1 = upButton.x1;
	scrollbar.y1 = upButton.y2;
	scrollbar.x2 = upButton.x2 - 1;
	int x, y;
	int tempIndex = -1;
	int index;
	int nextx, nexty, dist, d = 0;
	int scrollbarArea = downButton.y1 - upButton.y2;
	int thumbHeight = round(word.linePerPage * scrollbarArea * 1.0 / word.size);
	int jump = round((scrollbarArea - thumbHeight) * 1.0 / (word.size - word.linePerPage)); // chỉnh chỗ này, bỏ -1
	scrollbar.y2 = scrollbar.y1 + thumbHeight;
	bool isHover = false;
	bool draw = true;
	int u0 = scrollbar.y2;
	bool isChoose = false;
	string res = "";
	int chooseIndex = -1;
	if (word.size > word.linePerPage) {
		DrawButton(scrollbar, LIGHTGRAY, true);
		settextstyle(11, HORIZ_DIR, 1);
		string up = "/\\";
		string down = "\\/";
		int height = textheight((char*)up.c_str());
		int width = textwidth((char*)up.c_str());
		outtextxy((upButton.x1 + upButton.x2) / 2 - width / 2, (upButton.y1 + upButton.y2) / 2 - height / 2, (char*)up.c_str());
		outtextxy((downButton.x1 + downButton.x2) / 2 - width / 2, (downButton.y1 + downButton.y2) / 2 - height / 2, (char*)down.c_str());
		settextstyle(3, HORIZ_DIR, 2);
	} else draw = false;
	while(true) {
		if (kbhit()) {
			key = getch();
			if(key && key != 224){
				if(isOpened == true){
					if((key >= 'A' && key <= 'Z') || (key >= 'a' && key <='z') || (key >= '0' && key <= '9') || key == 8){
						return "false";
					}
				}
			}
			else{
				char ex = getch();
				if(ex == KEY_UP){
					goto upbutton;
				}
				if(ex == KEY_DOWN){
					goto downbutton;
				}
			}
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (CheckClickButton(scrollbar, x, y) && draw) {
				isHover = true;
				dist = y - scrollbar.y1;
			}
			if (CheckClickButton(upButton, x, y) && draw) { // thêm hiệu ứng bấm nút thì thanh cuộn tự nhảy lên
				upbutton:
				DeleteButton(scrollbar);
				if (d == 0) {
					scrollbar.y2 = u0;
				} else {
					d--;
					if (d == 0)
						scrollbar.y2 = u0;
					else 
						scrollbar.y2 = u0 + d * jump;
				}
				scrollbar.y1 = scrollbar.y2 - thumbHeight;
				DrawButton(scrollbar, LIGHTGRAY, true);
				word.PrintPage(false, showFileNameArea);
			}
			if (CheckClickButton(downButton, x, y) && draw) { // thêm hiệu ứng bấm nút thì thanh cuộn tự nhảy xuống
				downbutton:
				DeleteButton(scrollbar);
				if (d == word.size - word.linePerPage) {
					scrollbar.y2 = downButton.y1;
				} else if (d < word.size - word.linePerPage) {
					d++;
					if (d == word.size - word.linePerPage) 
						scrollbar.y2 = downButton.y1;
					else
						scrollbar.y2 = u0 + d * jump;
				}
				scrollbar.y1 = scrollbar.y2 - thumbHeight;
				DrawButton(scrollbar, LIGHTGRAY, true);
				word.PrintPage(true, showFileNameArea);
			}
			if (word.GetIndex(x, y, showFileNameArea) != -1) {
				index = word.GetIndex(x, y, showFileNameArea);
				int x1 = showFileNameArea.x1, y1 = showFileNameArea.y1, x2 = showFileNameArea.x2;	
				int height = textheight((char*)word.result[0].c_str());
				if (tempIndex != -1) {
					setfillstyle(1, WHITE);
					int xBoxTop = x1 + 1;
					int yBoxTop = y1 + margin + (height + marginLine) * (tempIndex - word.start);
					int xBoxBot = x2 - word.toRight;
					int yBoxBot = yBoxTop + height;
					bar(xBoxTop, yBoxTop, xBoxBot, yBoxBot);
					setbkcolor(WHITE);
					outtextxy(x1 + margin, yBoxTop, (char*)word.result[tempIndex].c_str());
					setbkcolor(WHITE);	
				}	
				setfillstyle(1, GREEN);
				int xBoxTop = x1 + 1;
				int yBoxTop = y1 + margin + (height + marginLine) * (index - word.start);
				int xBoxBot = x2 - word.toRight;
				int yBoxBot = yBoxTop + height;
				bar(xBoxTop, yBoxTop, xBoxBot, yBoxBot);
				setbkcolor(GREEN);
				outtextxy(x1 + margin, yBoxTop, (char*)word.result[index].c_str());
				setbkcolor(WHITE);
				isChoose = true;
				chooseIndex = index;
				tempIndex = index;
			}
			if(CheckClickButton(fileNameButton, x, y)){
				if(isOpened == false) isOpened = true;
				key = getch();
				if((key >= 'A' && key <= 'Z') || (key >= 'a' && key <='z') || (key >= '0' && key <= '9') || key == 8){
					return "false";
				}
			}
			if(CheckClickButton(OpenButton, x, y)){
				if(isChoose == true){
					res = word.result[chooseIndex];
					return res;
				}
				else{
					for(int i=0; i<word.size; i++){
						if(word.result[i] == ans + ".txt"){
							res = word.result[i];
							return res;
						} 
					}
				}
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if (ismouseclick(WM_LBUTTONUP)) {
			if (isHover == true && draw) { // xóa cái vẽ button vì ko cần thiết
				isHover = false;
			}
			clearmouseclick(WM_LBUTTONUP);
		}
		if (ismouseclick(WM_MOUSEMOVE)) {
			if (isHover == true && draw) { // vẽ thanh cuộn trước r vẽ nội dung sau
				getmouseclick(WM_MOUSEMOVE, nextx, nexty);
				DeleteButton(scrollbar);
				bool changed = false;
                int curr = scrollbar.y2;
                int currd = d;
                scrollbar.y1 = nexty - dist;
                scrollbar.y2 = scrollbar.y1 + thumbHeight;
                if (scrollbar.y2 > downButton.y1) {
                    scrollbar.y2 = downButton.y1;
                    scrollbar.y1 = scrollbar.y2 - thumbHeight;
                    d = word.size - word.linePerPage;
                    changed = true;
                } else if (scrollbar.y1 < upButton.y2) {
                    scrollbar.y1 = upButton.y2;
                    scrollbar.y2 = scrollbar.y1 + thumbHeight;
                    d = 0;
                    changed = true;
                }
                int after = scrollbar.y2;
                int afterd = round((after - u0) * 1.0 / jump);
                if (afterd > word.size - word.linePerPage) {
                    afterd = word.size - word.linePerPage;
                }
                DrawButton(scrollbar, LIGHTGRAY, true);
                if (!changed) {
                    if (afterd > d) d++;
                    else if (afterd < d) d--;
                }
                if (afterd > currd) {
                    word.PrintPage(true, showFileNameArea);
                } else if (afterd < currd) {
                    word.PrintPage(false, showFileNameArea);
                }
			}
			clearmouseclick(WM_MOUSEMOVE);
		}	
	}
	exit:
	return res;
}

/////////////////////////////////////////////////////////////////////_Check algorithm_/////////////////////////////////////////////////////////////////////
bool CheckNode(int x, int y, int mx, int my){
	return (((mx - x)*(mx - x) + (my - y)*(my - y) <= 25*25) && ((mx > realProcessingArea.x1 && mx < realProcessingArea.x2 && my > realProcessingArea.y1 && my < realProcessingArea.y2)));
}
bool CheckClickButton(Button button, int x, int y){	
	return (x > button.x1 && x < button.x2 && y > button.y1 && y < button.y2);
}
bool CheckReClickNode(Graph graph, int mx, int my){
	for(int i = 0; i < graph.numberNode; i++){
		if(CheckNode(graph.node[i]->x, graph.node[i]->y, mx, my)){
			return true;
		}
	}
	return false;
}
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
bool CheckPos(Graph &graph, int mx, int my){
	if(graph.numberNode == 0){
		if(mx > realProcessingArea.x1 && mx < realProcessingArea.x2 && my > realProcessingArea.y1 && my < realProcessingArea.y2) return true;
		else return false;
	}
	else {
		if(mx > realProcessingArea.x1 && mx < realProcessingArea.x2 && my > realProcessingArea.y1 && my < realProcessingArea.y2){ //return true;
			for (int i = 0; i < graph.numberNode; ++i){
				if((mx - graph.node[i]->x)*(mx - graph.node[i]->x) + (my - graph.node[i]->y)*(my - graph.node[i]->y) <  100 * 100){
					return false;
				}
			}
			return true;
		} 
		else return false;
	}		
}
/////////////////////////////////////////////////////////////////////_Draw Object_/////////////////////////////////////////////////////////////////////
void CreateNode(int x, int y, char name[], int color){
	setcolor(color);
	setlinestyle(0, 0, 3);//(kieu duong, ..., kich thuoc)
	settextstyle(3, HORIZ_DIR, 3);//(font, ngang doc, do dam)
	outtextxy(x-13, y-13, name);
	circle(x, y, 25);
}
bool AddNode(Graph &graph, int &x, int &y, string &ten, bool flag){
	if(CheckPos(graph, x, y)){
		if(flag == true){//tao moi dinh
			setlinestyle(0, 0, 2);
			circle(x, y, 25);
			ten = AddNameWeight("ten dinh");
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
void Rename(int x, int y, string &ten){// x, y sau nay se truyen node[i].x, node[i].y
	fillellipse(x, y, 25, 25);
	setlinestyle(0, 0, 2);
	circle(x, y, 25);
	CreateNode(x, y, (char*)ten.c_str(), BLUE);
}
string AddNameWeight(string name){
	add:
	setfillstyle(1, WHITE);
	bar(maxx / 3 + 10, 602, maxx - 11, maxy - 11);
	string s = "Nhap vao " + name + " (01 -> 99): ";
	outtextxy(maxx/3 + 20, 610, (char*)s.c_str());
	string ans = "";
	int n = 0, x = -1, y = -1;
	DrawButtonForNoti(continueButton);
	DrawButtonForNoti(cancelButton);
	while(true){
		if(kbhit() == true){
			char key = getch();
			if(key >= 48 && key <= 57 && n < 2){
				ans += to_string(key - 48);
				n++;
				outtextxy(735, 610, (char*)ans.c_str());
			}
			if(n > 0){
				if(key == 8){
					ans.pop_back();
					outtextxy(735, 610, "                  ");
					outtextxy(735, 610, (char*)ans.c_str());
					n--;
				}
			}
			if(n == 2){
				if(ans == "00") {
					ans = "";
					goto add;
				}
				else{
					if(key == 13){
						goto enter;
					} 
					if(key == 27) return "";
				}
			}
		} 
		if(n == 2){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if(x != -1 && y != -1){
				if(CheckClickButton(continueButton, x, y)){
					if(n < 2) goto add;
					enter:
					return ans;
				}
				else if(CheckClickButton(cancelButton, x, y)){
					goto add;
				}
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
	int n = 0; // kich thuoc cua chuoi
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
void NotificationFull(string Noti){
	setbkcolor(WHITE);
	setfillstyle(1, WHITE);
	settextstyle(3, HORIZ_DIR, 2);
	bar(helpArea.x1 + 1, helpArea.y1 + 1, helpArea.x2 - 1, helpArea.y2 - 1);
	setcolor(RED);
	outtextxy(helpArea.x1 + 11, helpArea.y1 + 19, (char *)Noti.c_str());
	setcolor(BLUE);
	settextstyle(3, HORIZ_DIR, 3);
}
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
	setbkcolor(WHITE);
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
	setbkcolor(WHITE);
	setlinestyle(0, 0, 2);
	settextstyle(3, HORIZ_DIR, 3);
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
	arc(round(xO), round(yO), round(startAngle), round(endAngle), round(r1));
	outtextxy(round(xT) - 12, round(yT) - 12, tt);
	DrawTriangle(round(x5), round(y5), round(x4), round(y4), color);
}
void CreateLine(Node *node1, Node *node2, char *tt, int color) {
	// tim diem dau tien
	setcolor(color);
	setbkcolor(WHITE);
	setlinestyle(0, 0, 2);
	settextstyle(3, HORIZ_DIR, 3);
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
	outtextxy(xT - 13, yT - 13, tt);
	DrawTriangle(x3, y3, ax, ay, color);
}
void DrawGraph(Graph &graph) {
	setfillstyle(1, WHITE);
	setbkcolor(WHITE);
	bar(processingArea.x1 + 1, processingArea.y1 + 1, processingArea.x2 - 1, processingArea.y2 - 1);
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
	DrawWeightMatrix(graph);
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
	graph.node[graph.numberNode - 1] = NULL;
	// xoa cot
	for (int i = index; i < graph.numberNode - 1; ++i) {
		for (int j = 0; j < graph.numberNode; ++j) {
			graph.adj[j][i] = graph.adj[j][i + 1]; 
			graph.type[j][i] = graph.type[j][i + 1];
		}
	} 
	for (int i = 0; i < graph.numberNode; ++i) 
		graph.adj[i][graph.numberNode - 1] = graph.type[i][graph.numberNode - 1] = 0; 
	// xoa hang
	for (int i = index; i < graph.numberNode - 1; ++i) {
		for (int j = 0; j < graph.numberNode - 1; ++j) {
			graph.adj[i][j] = graph.adj[i + 1][j];
			graph.type[i][j] = graph.type[i + 1][j];
		}
	}
	for (int i = 0; i < graph.numberNode - 1; ++i)
		graph.adj[graph.numberNode - 1][i] = graph.type[graph.numberNode - 1][i] = 0;
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
void EffectAlgorithm(Button button, int colorbk, int colortext, int colorborder){
	setlinestyle(0, 0, 3);
	setcolor(BLUE);
	rectangle(button.x1, button.y1, button.x2 - 1, button.y2 - 1);
	setlinestyle(0, 0, 2);
	setcolor(colorbk);
	setbkcolor(colorbk);
	setfillstyle(1, colorbk);
	bar(button.x1 + 1, button.y1, button.x2 - 2, button.y2 - 2);
	setcolor(colortext);
	if(button.name != "Topo Sort") outtextxy(button.x1 + 14, button.y1 + 18, (char*)button.name.c_str());
	else outtextxy(155, 340, (char*)button.name.c_str());
}
void EffectToolbar(Button button, int colorbk, int colortext, int colorborder){
	setlinestyle(0, 0, 3);
	setcolor(BLUE);
	rectangle(button.x1, button.y1, button.x2 - 1, button.y2 - 1);
	setlinestyle(0, 0, 2);
	setcolor(colorbk);
	setbkcolor(colorbk);
	setfillstyle(1, colorbk);
	bar(button.x1 + 1, button.y1, button.x2 - 2, button.y2 - 2);
	setcolor(colortext);
	outtextxy(button.x1 + 10, button.y1 + 5, (char*)button.name.c_str());
}
void DrawButton(){
	DrawToolBar();
	DrawMenuTable();
	DrawMatrix();
}
/////////////////////////////////////////////////////////////////////_Algorithm_/////////////////////////////////////////////////////////////////////
bool RunningToolbar(Graph &graph, string fileName, int &x, int &y, bool flag){
	string nameNode;
	bool isFirstSave = true;
	Button upButton;
	upButton.x1 = helpArea.x2 - 20, upButton.y1 = helpArea.y1, upButton.x2 = helpArea.x2, upButton.y2 = helpArea.y1 + 20;
	Button downButton;
	downButton.x1 = helpArea.x2 - 20, downButton.y1 = helpArea.y2 - 20, downButton.x2 = helpArea.x2, downButton.y2 = helpArea.y2;
	Button scrollbar;
	scrollbar.x1 = upButton.x1, scrollbar.y1 = upButton.y2, scrollbar.x2 = upButton.x2 - 1;
	int nextx, nexty, dist, d = 0;
	int scrollbarArea = downButton.y1 - upButton.y2;
	int thumbHeight, jump, u0;
	bool isHover = false, showResult = false, showScrollbar = false;
	WordWrap word(22);
	gtnew:	
	NotificationFull("Chon chuc nang");
	while(true){
		if(kbhit()){
			char key = getch();
			if(key == 27) break;
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			action:
			if(CheckClickButton(closeButton, x, y)){
				DrawButton();
				EffectToolbar(closeButton, RED, WHITE, BLACK);
				DrawGraph(graph);
				if(flag == true){
					OpenSave(graph, fileName);
					return false;
				}
				else{
					NewSave(graph, fileName, isFirstSave);
					return false;
				}
			}
			else if(CheckClickButton(saveButton, x, y)){
				DrawButton();
				EffectToolbar(saveButton, GREEN, WHITE, BLACK);
				DrawGraph(graph);
				if(flag == true){
					OpenSave(graph, fileName);
					goto gtnew;
				}
				else{
					NewSave(graph, fileName, isFirstSave);
					goto gtnew;
				}
			}
			else if(CheckClickButton(algorithmArea, x, y)){
				RunningAlgorithm(graph, x, y, word, helpArea, upButton, downButton, scrollbar, showResult);
				if (showResult) {
					scrollbar.x1 = upButton.x1, scrollbar.y1 = upButton.y2, scrollbar.x2 = upButton.x2 - 1;
					UpdateValue(word, scrollbarArea, scrollbar, thumbHeight, jump, u0);
					if (word.size > word.linePerPage) {
						showScrollbar = true;
						d = 0;
						DrawResult(upButton, downButton, scrollbar);
					} else {
						showScrollbar = false;
					}
					word.PrintPage(true, helpArea);
				}
			} 
			else if (CheckClickButton(scrollbar, x, y) && showResult && showScrollbar) {
				isHover = true;
                dist = y - scrollbar.y1;
			} 
			else if (CheckClickButton(upButton, x, y) && showResult && showScrollbar) {
				DeleteButton(scrollbar);
				if (d == 0) {
					scrollbar.y2 = u0;
				} else {
					d--;
					if (d == 0)
						scrollbar.y2 = u0;
					else 
						scrollbar.y2 = u0 + d * jump;
				}
				scrollbar.y1 = scrollbar.y2 - thumbHeight;
				DrawButton(scrollbar, BLUE, true);
				word.PrintPage(false, helpArea);
			}
			else if (CheckClickButton(downButton, x, y) && showResult && showScrollbar) {
				DeleteButton(scrollbar);
				if (d == word.size - word.linePerPage) {
					scrollbar.y2 = downButton.y1;
				} else if (d < word.size - word.linePerPage) {
					d++;
					if (d == word.size - word.linePerPage) 
						scrollbar.y2 = downButton.y1;
					else
						scrollbar.y2 = u0 + d * jump;
				}
				scrollbar.y1 = scrollbar.y2 - thumbHeight;
				DrawButton(scrollbar, BLUE, true);
				word.PrintPage(true, helpArea);
			} 
			else if(CheckClickButton(newButton, x, y)){
				DrawButton();
				EffectToolbar(newButton, GREEN, WHITE, BLACK);
				DrawGraph(graph);
				if(flag == true){
					OpenSave(graph, fileName);
				}
				else{
					NewSave(graph, fileName, isFirstSave);
				}
				flag = false;	
				isFirstSave = true;
				Graph g;
				graph = g;
				bar(processingArea.x1 + 1, processingArea.y1 + 1, processingArea.x2 - 1, processingArea.y2 - 1);
				DrawGraph(graph);
				goto gtnew;
			}
			else if(CheckClickButton(openButton, x, y)){
				DrawButton();
				EffectToolbar(openButton, GREEN, WHITE, BLACK);
				DrawGraph(graph);
				if(flag == true){
					OpenSave(graph, fileName);
				}
				else{
					NewSave(graph, fileName, isFirstSave);
				}
				Graph g;
				graph = g;
				bar(processingArea.x1 + 1, processingArea.y1 + 1, processingArea.x2 - 1, processingArea.y2 - 1);
				DrawGraph(graph);
				string nameFile = OpenScreen();
				nameFile = "saves/" + nameFile;
				ReadFile((char*)nameFile.c_str(), graph);
				DrawGraph(graph);
				flag = true;
				goto gtnew;
			}
			else if(CheckClickButton(addVertexButton, x, y)){//Nhan nut AddVerTex
				DrawButton();
				EffectToolbar(addVertexButton, GREEN, WHITE, BLACK);
				DrawGraph(graph);
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
								continue;
							}
							else if(CheckClickButton(realProcessingArea, x, y)){
								if(CheckReClickNode(graph, x, y)){
									string nameNode = "";
									for(int i=0; i < graph.numberNode; i++){
										if(CheckNode(graph.node[i]->x, graph.node[i]->y, x, y)){
											setcolor(RED);
											setlinestyle(0, 0, 3);
											circle(graph.node[i]->x, graph.node[i]->y, 25);
											setcolor(BLUE);
											setlinestyle(0, 0, 2);
											nameNode = AddNameWeight("ten dinh");
											Rename(graph.node[i]->x, graph.node[i]->y, nameNode);
											while(CheckName(graph, nameNode) == false){
												nameNode = AddNameWeight("ten dinh");
											}
											Rename(graph.node[i]->x, graph.node[i]->y, nameNode);
											graph.node[i]->name = nameNode;
											DrawWeightMatrix(graph);
											goto addV;
										}
									}
								}
								else if(CheckPos(graph, x, y)){
									AddNode(graph, x, y, nameNode, true);
									while(CheckName(graph, nameNode) == false){
										nameNode = AddNameWeight("ten dinh");
										Rename(x, y, nameNode);
									}
									Node *n = new Node(nameNode, x, y);
									graph.node[graph.numberNode] = n;
									graph.numberNode++;
									DrawWeightMatrix(graph);
									goto addV;
								}
								else goto addV;
							}
							else if(CheckClickButton(toolbarArea, x, y) || CheckClickButton(algorithmArea, x, y)) goto action;
							else goto gtnew;
						}
					}	
				}
				else{
					NotificationFull("DO THI DA DAY, KHONG THE THEM DINH!");
					goto gtnew;
				}
			}
			else if(CheckClickButton(addEdgeButton, x, y)){//Nhan nut AddEdge
				DrawButton();
				EffectToolbar(addEdgeButton, GREEN, WHITE, BLACK);
				DrawGraph(graph);
				if(graph.numberNode < 2){
					NotificationFull("SO LUONG DINH CHUA DU. MOI NHAP THEM DINH!");
				}
				else{
					reClick:
					int start = 0;
					bool flag = true;
					NotificationFull("CLICK VAO DINH DAU!");
					while(true){
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
										setlinestyle(0, 0 , 3);
										circle(graph.node[i]->x, graph.node[i]->y, 25);
										setcolor(BLUE);
										setlinestyle(0, 0, 2);
										start = i;
										flag = false;
										break;
									}
								}
								if(flag == true) goto reClick;
								else{
									int idx1 = start;
									NotificationFull("CLICK VAO DINH CUOI!");
									int idx2 = ChooseVertex(graph, x, y);
									string value = AddNameWeight("trong so");
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
									}													
									graph.adj[idx1][idx2] = (value[0]-'0')*10+(value[1]-'0');
									setfillstyle(1, WHITE);
									DrawWeightMatrix(graph);
									DrawGraph(graph);
									goto reClick;
								}
							}
							else{
								if(CheckClickButton(toolbarArea, x, y) || CheckClickButton(algorithmArea, x, y)) goto action;
								else goto gtnew;
							} 	
						}
					}
				}																			
			}
			else if(CheckClickButton(moveButton, x, y)){//Nhan nut Move
				DrawButton();
				EffectToolbar(moveButton, GREEN, WHITE, BLACK);
				DrawGraph(graph);
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
								continue;
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
									while(1){
										if (kbhit()) {
										}
										getmouseclick(WM_LBUTTONDOWN, x, y);
										if(x != -1 && y != -1){
											if((graph.node[idx]->x - x)*(graph.node[idx]->x - x) + (graph.node[idx]->y - y)*(graph.node[idx]->y - y) <= 100*100){
												x2 = x;
												y2 = y;
												break;
											}
											else{
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
									}
									Move(graph, x1, y1, x2, y2, idx);
									goto move;
								}
							}
							else{
								if(CheckClickButton(toolbarArea, x, y) || CheckClickButton(algorithmArea, x, y)) goto action;
								else goto gtnew;
							}
						}
					}
				}
			}
			else if(CheckClickButton(deleteVertexButton, x, y)){// xoa dinh
				DrawButton();
				EffectToolbar(deleteVertexButton, GREEN, WHITE, BLACK);
				DrawGraph(graph);
				delV:
				NotificationFull("HAY CLICK VAO DINH CAN XOA!");
				int idx;
				bool flag = true;
				while(true){//Bat phim dau
					if(kbhit()){
						char key = getch();
						if(key == 27) break;
					}
					getmouseclick(WM_LBUTTONDOWN, x, y);
					if(x != -1 && y != -1){
						if(CheckClickButton(processingArea, x, y)){
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
								int idx1 = x, idx2 = y;
								delay(1000);
								DeleteVertex(graph, idx1, idx2, idx);
								DrawWeightMatrix(graph);
								goto delV;
							}
						}
						else if(CheckClickButton(toolbarArea, x, y) || CheckClickButton(algorithmArea, x, y)) goto action;
						else goto gtnew;
					}
				}
			}
			else if(CheckClickButton(deleteEdgeButton, x, y)){//xoa canh
				DrawButton();
				EffectToolbar(deleteEdgeButton, GREEN, WHITE, BLACK);
				DrawGraph(graph);
				if(graph.numberNode < 2){
					NotificationFull("DO THI KHONG CO CANH DE XOA!");
				}
				else{
					delS:
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
								if(flag == true) goto delS;
								else{
									delE:
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
												goto delE;
											}
											else{
												DeleteEdge(graph, x1, y1, x2, y2, idx1, idx2);
												DrawWeightMatrix(graph);
												goto delS;
											}
										}	
									}
								}
							}
							else if(CheckClickButton(toolbarArea, x, y) || CheckClickButton(algorithmArea, x, y)) goto action;
							else goto gtnew;
						}
					}
				}
			}
		} 
		if (ismouseclick(WM_LBUTTONUP)) {
			if (isHover == true && showResult && showScrollbar) { // xóa cái vẽ button vì ko cần thiết
				isHover = false;
			}
			clearmouseclick(WM_LBUTTONUP);
		}
		if (ismouseclick(WM_MOUSEMOVE)) {
			if (isHover == true && showResult) { // vẽ thanh cuộn trước r vẽ nội dung sau
				getmouseclick(WM_MOUSEMOVE, nextx, nexty);
				DeleteButton(scrollbar);
				bool changed = false;
                int curr = scrollbar.y2;
                int currd = d;
                scrollbar.y1 = nexty - dist;
                scrollbar.y2 = scrollbar.y1 + thumbHeight;
                if (scrollbar.y2 > downButton.y1) {
                    scrollbar.y2 = downButton.y1;
                    scrollbar.y1 = scrollbar.y2 - thumbHeight;
                    d = word.size - word.linePerPage;
                    changed = true;
                } else if (scrollbar.y1 < upButton.y2) {
                    scrollbar.y1 = upButton.y2;
                    scrollbar.y2 = scrollbar.y1 + thumbHeight;
                    d = 0;
                    changed = true;
                }
                int after = scrollbar.y2;
                int afterd = round((after - u0) * 1.0 / jump);
                if (afterd > word.size - word.linePerPage) {
                    afterd = word.size - word.linePerPage;
                }
                DrawButton(scrollbar, BLUE, true);
                if (!changed) {
                    if (afterd > d) d++;
                    else if (afterd < d) d--;
                }
                if (afterd > currd) {
                    word.PrintPage(true, helpArea);
                } else if (afterd < currd) {
                    word.PrintPage(false, helpArea);
                }
			}
			clearmouseclick(WM_MOUSEMOVE);
		}
	}
}
void RunningAlgorithm(Graph graph, int x, int y, WordWrap &word, Button helpArea, Button upButton, Button downButton, Button scrollbar, bool &showResult){
	bool flag = true;
	if (showResult) {
		setfillstyle(1, WHITE);
		bar(helpArea.x1 + 1, helpArea.y1 + 1, helpArea.x2 - 1, helpArea.y2 - 1);
	}
	if(CheckClickButton(dfsButton, x, y)){
		DrawButton();
		EffectAlgorithm(dfsButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		showResult = false;
		NotificationFull("HAY CLICK VAO DINH BAT DAU!");
		int start = ChooseVertex(graph, x, y);
		NotificationFull("BAT DAU THUAT TOAN!");
		DFS(graph, start);
	}
	else if(CheckClickButton(bfsButton, x, y)){
		DrawButton();
		EffectAlgorithm(bfsButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		showResult = false;
		NotificationFull("HAY CLICK VAO DINH BAT DAU!");
		int start = ChooseVertex(graph, x, y);
		NotificationFull("BAT DAU THUAT TOAN!");
		BFS(graph, start);
	}
	else if(CheckClickButton(shortestPathButton, x, y)){
		DrawButton();
		EffectAlgorithm(shortestPathButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		showResult = false;
		NotificationFull("HAY CLICK VAO DINH BAT DAU!");
		int start = ChooseVertex(graph, x, y);
		NotificationFull("HAY CLICK VAO DINH KET THUC!");
		int end = ChooseVertex(graph, x, y);
		NotificationFull("BAT DAU THUAT TOAN!");
		Dijkstra(graph, start, end);
	}
	else if(CheckClickButton(ComponentButton, x, y)){
		DrawButton();
		EffectAlgorithm(ComponentButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		Component(graph);
	}
	else if(CheckClickButton(hamiltonButton, x, y)){
		DrawButton();
		EffectAlgorithm(hamiltonButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		showResult = true;
		HamCycle(graph, word, helpArea);
	}
	else if(CheckClickButton(eulerButton, x, y)){
		DrawButton();
		EffectAlgorithm(eulerButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		showResult = true;
		EulerCycle(graph, word, helpArea);	
	}
	else if(CheckClickButton(dinhTruButton, x, y)){
		DrawButton();
		EffectAlgorithm(dinhTruButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		showResult = true;
		ArticulationPoint(graph, word, helpArea);	
	}
	else if(CheckClickButton(dinhThatButton, x, y)){
		DrawButton();
		EffectAlgorithm(dinhThatButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		showResult = true;
		NotificationFull("HAY CLICK VAO DINH BAT DAU!");
		int start = ChooseVertex(graph, x, y);
		NotificationFull("HAY CLICK VAO DINH KET THUC!");
		int end = ChooseVertex(graph, x, y);
		KnotPoint(graph, start, end, word, helpArea);	
	}
	else if(CheckClickButton(bridgeEdgeButton, x, y)){
		DrawButton();
		EffectAlgorithm(bridgeEdgeButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		showResult = true;
		BridgeEdge(graph, word, helpArea);	
	}
	else if(CheckClickButton(topoSortButton, x, y)){
		DrawButton();
		EffectAlgorithm(topoSortButton, GREEN, WHITE, BLACK);
		DrawGraph(graph);
		flag = false;
		showResult = true;
		RunningTopologicalSort(graph);	
	}
}
int ChooseVertex(Graph graph, int &x, int &y){
	int start = 0;
	bool flag = true;
	reClick:
	while(true){
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
						setlinestyle(0, 0 , 3);
						circle(graph.node[i]->x, graph.node[i]->y, 25);
						setcolor(BLUE);
						setlinestyle(0, 0, 2);
						start = i;
						flag = false;
						break;
					}
				}
				if(flag == true) goto reClick;
				else break;
			}
			else goto reClick;
		}
	}
	return start;
}
bool OpenSave(Graph &graph, string nameFile){
	int x = -1, y = -1;
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
				WriteFile((char*)nameFile.c_str(), graph);
				NotificationFull("Da luu");
				return true;
			}
			else if(CheckClickButton(cancelButton, x, y)){
				NotificationFull("Khong luu");
				return false;
			} 
		}
	}
}
bool NewSave(Graph &graph, string &nameFile, bool &isFirstSave){
	int x = -1, y = -1;
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
				if(isFirstSave == true){
					reAddName:
					nameFile = AddFileName();
					if(!nameFile.empty()){
						nameFile = "saves/" + nameFile;
						nameFile += ".txt";
						ofstream graphFile((char*)nameFile.c_str());
						graphFile.close();
						WriteFile((char*)nameFile.c_str(), graph);
						isFirstSave = false;
						return true;
					}
					else goto reAddName;
				}
				else {
					WriteFile((char*)nameFile.c_str(), graph);
					NotificationFull("Da luu");
					return true;
				}
			}
			else if(CheckClickButton(cancelButton, x, y)){
				NotificationFull("Khong luu");
				return false;
			} 
		}
	}
}
void EffectVertex(Graph graph, int u, int colorbk, int colortext){
	delay(1000);
	setcolor(colorbk);
	setbkcolor(colorbk);
	setfillstyle(1, colorbk);
	fillellipse(graph.node[u]->x, graph.node[u]->y, 25, 25);
	CreateNode(graph.node[u]->x, graph.node[u]->y, (char*)graph.node[u]->name.c_str(), colortext);
	setcolor(colorbk);
	circle(graph.node[u]->x, graph.node[u]->y, 25);
}
void EffectEdge(Graph graph, int u, int v, int color){
	delay(1000);
	string value = ToStringLen2(graph.adj[u][v]);
	if (graph.type[u][v] == 1) {
		CreateLine(graph.node[u], graph.node[v], (char*)value.c_str(), color);
	}				
	else if (graph.type[u][v] == 2) {
		CreateCurved(graph.node[u], graph.node[v], (char*)value.c_str(), color);
	}
}
void DFS (Graph graph, int start){
	string noti = "Thu tu duyet: "; 
	bool isVisited[MAXN];
	int tick[MAXN][MAXN];
	for(int i=0; i<graph.numberNode; i++){
		isVisited[i] = false;
		for(int j = 0; j<graph.numberNode; j++){
			tick[i][j] = 0;
		}
	}
	Stack st;
	st.push(start);
	noti += graph.node[start]->name + " -> ";
	cout<<start<<' ';
	isVisited[start] = true;
	while(!st.empty()){
		int u;
		st.pop(u);
		for(int v = 0; v < graph.numberNode; v++){
			if(graph.adj[u][v] != 0 && isVisited[v] == false) {
				cout<<v<<' ';
				noti += graph.node[v]->name + " -> ";
				st.push(u);
				st.push(v);
				tick[u][v] = 1;
				isVisited[v] = true;
				EffectVertex(graph, u, COLOR(210,105,30), WHITE);
				EffectVertex(graph, u, GREEN, WHITE);				
				EffectEdge(graph, u, v, RED);
				EffectVertex(graph, v, GREEN, WHITE);
				break;
			}
			else if(graph.adj[u][v] != 0 && isVisited[v] == true && tick[u][v] == 0){
				tick[u][v] = 1;
				EffectVertex(graph, u, COLOR(210,105,30), WHITE);
				EffectVertex(graph, u, GREEN, WHITE);				
				EffectEdge(graph, u, v, BLACK);
			}
		}
	}
	noti.erase(noti.end()-4, noti.end());
	NotificationFull(noti);
}
void BFS (Graph graph, int start){
	bool isVisited[MAXN];
	int tick[MAXN][MAXN];
	string noti = "Thu tu duyet: "; 
	for(int i=0; i<graph.numberNode; i++){
		isVisited[i] = false;
		for(int j = 0; j<graph.numberNode; j++){
			tick[i][j] = 0;
		}
	}
	Queue q;
	q.push(start);
	isVisited[start] = true;
	while(!q.empty()) {
		int u;
		q.pop(u);	
		noti += graph.node[u]->name + " -> ";
		for (int v = 0; v < graph.numberNode; v++) {
			if (graph.adj[u][v] != 0 && isVisited[v] == false) {
				q.push(v);
				isVisited[v] = true;
				tick[u][v] = 1;
				EffectVertex(graph, u, COLOR(210,105,30), WHITE);
				EffectVertex(graph, u, GREEN, WHITE);				
				EffectEdge(graph, u, v, RED);
				EffectVertex(graph, v, GREEN, WHITE);
			}
			else if(graph.adj[u][v] != 0 && isVisited[v] == true && tick[u][v] == 0){
				tick[u][v] = 1;
				EffectVertex(graph, u, COLOR(210,105,30), WHITE);
				EffectVertex(graph, u, GREEN, WHITE);				
				EffectEdge(graph, u, v, BLACK);
			}
		}
	}
	noti.erase(noti.end()-4, noti.end());
	NotificationFull(noti);
}	
void Component (Graph graph){
	int temp[MAXN][MAXN];
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
            temp[i][j] = 0;
    for (int i = 0; i < graph.numberNode; ++i) 
        for (int j = 0; j < graph.numberNode; ++j)
            if (graph.adj[i][j]) 
                temp[i][j] = temp[j][i] = 1;       
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
							string value = ToStringLen2(graph.adj[tmp][i]);
							DrawEdge(graph, tmp, i, count + 1);
						}
					}
				}
			}
			for(int k=graph.numberNode - 1; k >= 0; k--){
				if(temp[tmp][k] != 0 && tick[k] == false){
					st.push(k);
				}
			}	
		}
	}	
	string noti = "Do thi co " + to_string(count) + " thanh phan lien thong!";
	cout<<"So thanh phan lien thong la: "<<count;
	NotificationFull(noti);
}	
/////////////////////////////////////////////////////////////////Dijkstra/////////////////////////////////////////////////////////////////////////////////
int minDistance(int distance[], bool tick[], int V){
	int min = INT_MAX, minIndex = -1;
	for(int i=0; i<V; i++) {
		if(min >= distance[i] && tick[i] == false){
			min = distance[i];
			minIndex = i;
		}
	}
	return minIndex;
}	
void Dijkstra(Graph graph, int start, int end){
	string noti = "Duong di ngan nhat tu " + graph.node[start]->name + " den " + graph.node[end]->name + " la: ";
	bool tick[graph.numberNode];
	int distance[graph.numberNode];
	int parent[graph.numberNode];
	for(int i=0; i<graph.numberNode; i++){
		tick[i] = false;
		distance[i] = INT_MAX;
		parent[i] = -1;
	}
	distance[start] = 0;
	parent[start] = start;
	for(int count = 0; count < graph.numberNode - 1; count++){
		int u = minDistance(distance, tick, graph.numberNode);
		tick[u] = true;
		for(int v = 0; v < graph.numberNode; v++){
			if(tick[v] == false && graph.adj[u][v] && distance[u] != INT_MAX && distance[u] + graph.adj[u][v] < distance[v]){
				distance[v] = distance[u] + graph.adj[u][v];
				parent[v] = u;
			}
		}
	}
	if(distance[end] == INT_MAX){
		string noti = "Khong ton tai duong di tu dinh " + graph.node[start]->name + " den dinh " + graph.node[end]->name + "!";
		NotificationFull(noti);
	}
	else{
		if(parent[end] != -1 && distance[end] != INT_MAX){
			int listAns[graph.numberNode];
			int sizeListAns=0;
			Stack ans;
			ans.push(end);

			while(end != start){
				ans.push(parent[end]);
				end = parent[end];
			}
			while(ans.empty() == false){
				int t = -1;
				ans.pop(t);
				listAns[sizeListAns] = t;
				sizeListAns++;
			}
			for(int i=0; i<sizeListAns; i++){
				noti += graph.node[listAns[i]]->name + " -> "; 
			} 
			noti.erase(noti.end() - 4, noti.end());
			if(sizeListAns > 0){
				for(int i=0; i<sizeListAns; i++){
					if(i>0){	
						EffectEdge(graph, listAns[i-1], listAns[i], RED);
					}
					EffectVertex(graph, listAns[i], GREEN, WHITE);
				}
			}
		}
		NotificationFull(noti);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
int StringToInt(string s) {
    int n = s.length(), ans = 0;
    for (int i = 0; i < n; ++i) 
        ans = ans * 10 + (s[i] - '0');
    return ans;
}
int CountComponents(Graph g, int start) {
    int temp[MAXN][MAXN];
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
            temp[i][j] = 0;
    for (int i = 0; i < g.numberNode; ++i) 
        for (int j = 0; j < g.numberNode; ++j)
            if (g.adj[i][j]) 
                temp[i][j] = temp[j][i] = 1;       
    bool vis[MAXN];
    for (int i = 0; i < g.numberNode; ++i) vis[i] = false;
    if (start != -1) vis[start] = true;
    int count = 0;
    for (int i = 0; i < g.numberNode; ++i) {
        if (vis[i] == false) {
            count++;
            Queue q;
            q.push(i);
            vis[i] = true;
            while(!q.empty()) {
                int u;
                q.pop(u);
                for (int i = 0; i < g.numberNode; ++i) {
                    if (temp[u][i] && vis[i] == false) {
                        q.push(i);
                        vis[i] = true;
                    }
                }
            }
        }
    }
    return count;
}
/////////////////////// Dinh that ////////////////////////////
bool dfsCheck(Graph g, int u, int v) {
    bool vis[MAXN];
    for (int i = 0; i < g.numberNode; ++i) vis[i] = false;
    Stack stack;
    stack.push(u);
    vis[u] = true;
    int numCheckedVertex = 0;
    while(!stack.empty()) {
        int start;
        stack.pop(start);
        if (start == v) return 1;
        ++numCheckedVertex;
        for (int i = 0; i < g.numberNode; ++i) 
            if (!vis[i] && g.adj[start][i]) {
                vis[i] = true;
                stack.push(i);
            }
    }
    return (numCheckedVertex == g.numberNode);
}
bool IsConnected(Graph g, int u, int v) {
    bool vis[MAXN];
    for (int i = 0; i < g.numberNode; ++i) vis[i] = false;
    Queue q;
    q.push(u);
    vis[u] = true;
    while(!q.empty()) {
        int t;
        q.pop(t);
        for (int i = 0; i < g.numberNode; ++i) {
            if (g.adj[t][i] && !vis[i]) {
                q.push(i);
                vis[i] = true;
                /// neu nut i = v thi co lien thong //////////
                if (i == v)
                    return true;
            }
        }
    }
    return false;
}
void KnotPoint(Graph graph, int u, int v, WordWrap &word, Button helpArea) {
	WordWrap wordTemp(22);
	word = wordTemp;
	string ans = "";
	if (graph.adj[u][v] || !dfsCheck(graph, u, v)) {
		ans = "Khong co dinh that (Ton tai duong di truc tiep / Khong co duong di)!";
		cout << "Khong co dinh that (Ton tai duong di truc tiep / Khong co duong di)\n";
		word.StoreString(ans, helpArea);
		return;
	}
    int temp[MAXN][MAXN];
    int res[MAXN];
    int index = 0;
    for (int i = 0; i < graph.numberNode; ++i) 
        for (int j = 0; j < graph.numberNode; ++j)
            temp[i][j] = graph.adj[i][j];
    for (int i = 0; i < graph.numberNode; ++i) {
        ///////////////////// loai bo dinh /////////////////////
        for (int j = 0; j < graph.numberNode; ++j) 
            graph.adj[j][i] = graph.adj[i][j] = 0;
        // kiem tra co duong di tu u den v hay ko//////////////
        if (!IsConnected(graph, u, v)) 
            if (i != u && i != v) 
                res[index++] = i;
        // khoi phuc lai trang thai truoc do///////////////////
        for (int j = 0; j < graph.numberNode; ++j) 
            graph.adj[j][i] = temp[j][i], graph.adj[i][j] = temp[i][j];
    }
    if (index == 0) {
		ans = "Khong co dinh that giua " + to_string(u) + " va " + to_string(v) + "!";
		word.StoreString(ans, helpArea);
    	cout << "Khong co dinh that giua " << u << " va " << v << "\n"; 
	} else {
		cout << "Co " << index << " dinh that giua " << u << " va " << v << ":\n";
		ans = "Co " + to_string(index) + " dinh that giua " + to_string(u) + " va " + to_string(v) + ": ";
		word.StoreString(ans, helpArea);
		ans = "";
		for (int i = 0; i < index; ++i){
			cout << res[i] << "\n";
			ans += graph.node[res[i]]->name + ", ";
			setlinestyle(0, 0, 3);
			setcolor(GREEN);
			circle(graph.node[res[i]]->x, graph.node[res[i]]->y, 25);
			setcolor(WHITE);
			delay(1000);
		}
		ans.erase(ans.end() - 2, ans.end());
		word.StoreString(ans, helpArea);
	}
}
///////////////////////////////////////////////////////////////

// /////////////////////Chu trinh Euler///////////////////////////
bool IsEulerCircuit(Graph g) {
    int numberComponents = CountComponents(g, -1);
    if (numberComponents != 1) return false;
    const int size = g.numberNode;
    int inWards[size], outWards[size];
    for (int i = 0; i < size; ++i)
        inWards[i] = outWards[i] = 0;
    int sum = 0;
    for (int u = 0; u < size; ++u) {
        sum = 0;
        for (int v = 0; v < size; ++v) {
            if (g.adj[u][v]) {
                inWards[v]++;
                sum++;
            }
        }
        outWards[u] = sum;
    }
    for (int i = 0; i < size; ++i)
        if (inWards[i] != outWards[i])
            return false;
    return true;
}
void EulerCycle(Graph graph, WordWrap &word, Button helpArea) {
    string ans;
	WordWrap wordTemp(22);
	word = wordTemp;
    if (!IsEulerCircuit(graph)) {
		ans = "Khong ton tai chu trinh Euler";
		word.StoreString(ans, helpArea);
        cout << "Khong ton tai chu trinh Euler";
        return;
    }
    Stack stack;
    int countEdge = 0;
    for (int u = 0; u < graph.numberNode; ++u) 
        for (int v = 0; v < graph.numberNode; ++v) 
            if (graph.adj[u][v])
                countEdge++;
    int temp[MAXN][MAXN];
    for (int u = 0; u < graph.numberNode; ++u) 
        for (int v = 0; v < graph.numberNode; ++v)
            temp[u][v] = graph.adj[u][v];
    int path[MAXN + 1];
    stack.push(0);
    int index = 0;
    while(!stack.empty()) {
        int s;
        stack.pop(s);
        stack.push(s);
        bool isEmpty = true;
        int t;
        for (t = 0; t < graph.numberNode; ++t) {
            if (temp[s][t]) {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty == false) {
            stack.push(t);
            temp[s][t] = 0;
        } else {
            stack.pop(s);
            path[index++] = s;
        }
    }
	ans = "Ton tai chu trinh Euler: ";
	word.StoreString(ans, helpArea);
	ans = "";
    cout << "Ton tai chu trinh Euler:\n";
    for (int i = index - 1; i >= 0; --i){
		if(i < index - 1){	
			EffectEdge(graph, path[i+1], path[i], RED);
		}
		EffectVertex(graph, path[i], GREEN, WHITE);
        cout << path[i] << " ";
		ans += graph.node[path[i]]->name + " -> ";
	}
	ans.erase(ans.end() - 4, ans.end());
	// ans = "But just as I didn't want to resent my kids, I also didn't want to find myself too much in love with them. There are parents who don't like to hear their little girl crying at night, at the vast approaching dark of sleep, and so in their torment think why not feed her a lollipop, and a few years later that kid's got seven cavities and a pulled tooth. This is how we've arrived at the point where we give every kid on the team a trophy in the name of participation. I didn't want to love my kids so much that I was blind to their shortcomings, limitations, and mediocre personalities, not to mention character flaws and criminal leanings. But I could, I thought, I could love a kid that much. A kid really could be everything, and that scared me. Because once a kid is everything, not only might you lose all perspective and start proudly displaying his participation trophies, you might also fear for that kid's life every time he leaves your sight. I didn't want to live in perpetual fear. People don't recover from the death of a child. I knew I wouldn't. I knew that having a kid would be my chance to improve upon my shitty childhood, that it would be a repudiation of my dad's suicide and a celebration of life, but if that kid taught me how to love him, how to love, period, and then I lost him as I lost my dad, that would be it for me. I'd toss in the towel. Fuck it, fuck this world and all its heartbreak. I'd tell that to Connie, and she'd tell me that if that was how I felt I was already a slave to the fear, and good luck.";
	word.StoreString(ans, helpArea);
}
// ///////////////////////////////////////////////////////////////

// /////////////////// Chu trinh Hamilton /////////////////////////////////
/* Ham kiem tra xem dinh 'v' co the them vao vi tri 'pos' 
trong chu trinh hamilton duoc hay khong */
bool IsSafe(int v, Graph g, int path[], int count[], int pos) {
    /* Kiem tra dinh hien tai co phai la dinh lien ke 
        cua dinh truoc do hay khong */ 
    if (!g.adj[path[pos - 1]][v]) return false;
    /* Kiem tra dinh da co truoc do hay chua*/
    if (count[v] > 1) return false;
    return true;
}
bool RecursiveHam(Graph g, int path[], int count[], int pos) {
    /* Kiem tra neu toan bo cac dinh da duoc tham*/
    if (pos == g.numberNode) {
        /* Va kiem tra xem co canh noi tu dinh cuoi den
            dinh dau trong 'path' hay khong*/
        if (g.adj[path[pos - 1]][path[0]])
            return true;
        else
            return false;
    }
    /* Khong tham dinh 0 vi ta mac dinh 0 la diem bat dau cua chu trinh*/
    for (int v = 1; v < g.numberNode; ++v) {
        if (IsSafe(v, g, path, count, pos)) {
            path[pos] = v;
            if (RecursiveHam(g, path, count, pos + 1))
                return true;
            path[pos] = -1;
        }
    }
    return false;
}
void HamCycle(Graph graph, WordWrap &word, Button helpArea) { 
    int path[MAXN];
    int count[MAXN];
    for (int i = 0; i < graph.numberNode; ++i) {
        path[i] = -1;
        count[i] = 0;
    }
    path[0] = 0;
    count[0] = 1;
	WordWrap wordTemp(22);
	word = wordTemp;
	string ans;
    if (RecursiveHam(graph, path, count, 1) == false) {
        cout << "Khong ton tai chu trinh Hamilton";
		ans = "Khong ton tai chu trinh Hamilton";
		word.StoreString(ans, helpArea);
        return;
    } 
    cout << "Ton tai chu trinh Hamilton:\n";
	ans = "Ton tai chu trinh Hamilton: ";
	NotificationFull(ans);
	word.StoreString(ans, helpArea);
	path[graph.numberNode] = 0;
	ans = "";
    for (int i = 0; i <= graph.numberNode; ++i){
		if(i > 0){	
			EffectEdge(graph, path[i-1], path[i], RED);
		}
		EffectVertex(graph, path[i], GREEN, WHITE);
		ans += graph.node[path[i]]->name + " -> ";
	}
	ans.erase(ans.end() - 4, ans.end());
	word.StoreString(ans, helpArea);
}
// ////////////////////////////////////////////////////////////////////////

///////////////////////////////Canh cau/////////////////////////////////
void BridgeEdge(Graph graph, WordWrap &word, Button helpArea) {
    int numComponents = CountComponents(graph, -1);
    int count = 0, edges = 0;
    for (int i = 0; i < graph.numberNode; ++i) 
        for (int j = 0; j < graph.numberNode; ++j)
            if (graph.adj[i][j])
                edges++;
    const int numEdges = edges;
    int bridgeEdges[numEdges][2];
    for (int i = 0; i < graph.numberNode; ++i) {
        for (int j = 0; j < graph.numberNode; ++j) {
            if (graph.adj[i][j]) {
                int value = graph.adj[i][j];
                // Loai bo canh
                graph.adj[i][j] = 0;
                // Dem so thanh phan lien thong sau khi da cat canh
                int numComAfterRemove = CountComponents(graph, -1);
                // Khoi phuc lai ban dau
                graph.adj[i][j] = value;
                if (numComAfterRemove > numComponents) {
                    bridgeEdges[count][0] = i;
                    bridgeEdges[count][1] = j;
                    count++;
                }
            }
        }
    }
	WordWrap wordTemp(22);
	word = wordTemp;
	string ans = "";
    if (count == 0) {
		ans = "Khong ton tai canh cau!";
        cout << "Khong ton tai canh cau";
		word.StoreString(ans, helpArea);
    } else {
		ans = "Co " + to_string(count) + " canh cau!";
		word.StoreString(ans, helpArea);
        cout << "Co " << count << " canh cau:\n";
		ans = "";
        for (int i = 0; i < count; ++i) {
        	ans += "(" + graph.node[bridgeEdges[i][0]]->name + ", " + graph.node[bridgeEdges[i][1]]->name + ") ";
			delay(1000);
			string value = ToStringLen2(graph.adj[bridgeEdges[i][0]][bridgeEdges[i][1]]);
			if (graph.type[bridgeEdges[i][0]][bridgeEdges[i][1]] == 1) {
				CreateLine(graph.node[bridgeEdges[i][0]], graph.node[bridgeEdges[i][1]], (char*)value.c_str(), WHITE);
				CreateLine(graph.node[bridgeEdges[i][0]], graph.node[bridgeEdges[i][1]], (char*)value.c_str(), RED);
			}				
			else if (graph.type[bridgeEdges[i][0]][bridgeEdges[i][1]] == 2) {
				CreateCurved(graph.node[bridgeEdges[i][0]], graph.node[bridgeEdges[i][1]], (char*)value.c_str(), WHITE);
				CreateCurved(graph.node[bridgeEdges[i][0]], graph.node[bridgeEdges[i][1]], (char*)value.c_str(), RED);
			}
		}
		word.StoreString(ans, helpArea);
    }
}
////////////////////////////////////////////////////////////////////////

///////////////////////////////Dinh Tru/////////////////////////////////
void ArticulationPoint(Graph graph, WordWrap &word, Button helpArea) {
    int numberComponents = CountComponents(graph, -1);
    int count = 0;
    int vertex[MAXN];
    int temp[MAXN][MAXN];
    for (int i = 0; i < graph.numberNode; ++i) 
        for (int j = 0; j < graph.numberNode; ++j)
            temp[i][j] = graph.adj[i][j];
    for (int i = 0; i < graph.numberNode; ++i) {
        // Xoa dinh
        for (int j = 0; j < graph.numberNode; ++j)
            graph.adj[i][j] = graph.adj[j][i] = 0;
        int numComAfterRemove = CountComponents(graph, i);
        // Khoi phuc
        for (int j = 0; j < graph.numberNode; ++j)
            graph.adj[i][j] = temp[i][j],graph.adj[j][i] = temp[j][i];
        if (numComAfterRemove > numberComponents)
            vertex[count++] = i;
    }
	WordWrap wordTemp(22);
	word = wordTemp;
	string ans;
    if (count == 0) {
		ans = "Do thi khong co dinh tru";
        cout << "Do thi khong co dinh tru";
		word.StoreString(ans, helpArea);
    } 
	else {
		ans = "Do thi co " + to_string(count) + " dinh tru: ";
		word.StoreString(ans, helpArea);
		ans = "";
        cout << "Do thi co " << count << " dinh tru:\n";
        for (int i = 0; i < count; ++i){
			delay(1000);
			setlinestyle(0, 0, 3);
			setcolor(RED);
			circle(graph.node[vertex[i]]->x, graph.node[vertex[i]]->y, 25);
			setcolor(WHITE);
            cout << graph.node[vertex[i]]->name << "\n"; 
			ans += graph.node[vertex[i]]->name + ", ";
		}
		ans.erase(ans.end() - 2, ans.end());
		word.StoreString(ans, helpArea);
    }
}
////////////////////////////////////////////////////////////////////////

// ////////////////////////////Topo Sort///////////////////////////////////
int ReadFileTopo(char fileName[], string res[], int &size, int graphSize, bool checkData) {
    ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        file.close();
        return 0;
    }
    string line;
    int count = 0;
    while(getline(file, line) && count < graphSize) {
        string temp = RemoveSpace(line);
        if (temp.length() > 50)
            res[count++] = RemoveSpace(temp.substr(0, 50));
        else
            res[count++] = temp;
    }
    size = count;
    if (checkData) {
        if (size == graphSize)
            return 1;
        else
            return -1;
    }
    return 1;
}
int FindIdByName(string res[], int size, string s) {
    for (int i = 0; i < size; ++i)
        if (res[i] == s)
            return i;
    return -1;
}
void IndexArray(string a[], int size1, string b[], int res[], int size2) {
    for (int i = 0; i < size2; ++i)
        res[i] = FindIdByName(a, size1, b[i]);
}
bool isDAG(Graph graph) {
    const int graphSize = graph.numberNode;
    int inDegree[graphSize];
    for (int i = 0; i < graphSize; ++i)
        inDegree[i] = 0;
    for (int u = 0; u < graphSize; ++u)
        for (int v = 0; v < graphSize; ++v) 
            if (graph.adj[u][v]) 
                inDegree[v]++;

    Queue queue;
    for (int i = 0; i < graphSize; ++i)
        if (inDegree[i] == 0)
            queue.push(i);
    int cnt = 0;
    while(!queue.empty()) {
        int u;
        queue.pop(u);
        for (int v = 0; v < graphSize; ++v)
            if (graph.adj[u][v]) 
                if (--inDegree[v] == 0)
                    queue.push(v);
        cnt++;
    }
    if (cnt != graphSize) return false;
    return true;
}
void OutputTopoSort(Graph graph, int iDaDK[], int sizeDaDK, int iMuonDK[], int sizeMuonDK, string mon[], int sizeMon, string daDK[], string muonDK[]) {
    if (!isDAG(graph)) {
        cout << "Do thi ton tai chu trinh";
        return;
    }
    int graphSize = graph.numberNode;
    int inDegree[MAXN];
    int group[MAXN];
    for (int i = 0; i < graphSize; ++i)
        inDegree[i] = group[i] = 0;
    for (int u = 0; u < graphSize; ++u) 
        for (int v = 0; v < graphSize; ++v)
            if (graph.adj[u][v]) 
                inDegree[v]++;
    int count = 0;
    int index1 = 0, index2 = 0;
    int size1 = 0, size2 = 0;
    Queue queue;
    for (int i = 0; i < graph.numberNode; ++i)
        if (!inDegree[i])
            queue.push(i), group[i] = count, size1++;
    while(!queue.empty()) {
        int u;
        queue.pop(u);
        group[u] = count;
        for (int v = 0; v < graph.numberNode; ++v) 
            if (graph.adj[u][v]) {
                inDegree[v]--;
                if (inDegree[v] == 0)
                    queue.push(v), size2++;
            }
        if (index2 - index1 == size1) {
            index1 = index2;
            size1 = size2;
            size2 = 0;
            count++;
        }
    } 
    bool vis[MAXN];
    for (int i = 0; i < graphSize; ++i)
        vis[i] = false;
    for (int i = 0; i < sizeDaDK; ++i)
        if (iDaDK[i] != -1)
            vis[iDaDK[i]] = true;
    bool ok = false;
    int v;
    for (int i = 0; i < sizeMuonDK; ++i) {
        v = iMuonDK[i];
        if (v == -1) {
            cout << "Mon " << muonDK[i] << " khong co trong danh sach mon hoc";
            continue;
        }
        if (group[v] == 0) {
            if (vis[v])
                cout << "Mon " << mon[v] << " khong the dang ky vi da hoc xong";
            else
                cout << "Mon " << mon[v] << " khong the dang ky vi day la mon co so"; 
        } else {
            if (vis[v]) 
                cout << "Mon " << mon[v] << " khong the dang ky vi da hoc xong";
            else {
                ok = false;
                for (int u = 0; u < graphSize; ++u) {
                    if (group[u] < group[v] && graph.adj[u][v] && vis[u]) {
                        cout << "Mon " << mon[v] << " co the dang ky duoc";
                        ok = true;
                        break;
                    }
                }
                if (!ok) {
                    for (int u = 0; u < graphSize; ++u) {
                        if (group[u] < group[v] && graph.adj[u][v] && !vis[u]) {
                            cout << "Mon " << mon[v] << " khong the dang ky duoc vi mon " << mon[u] << " chua duoc dang ky";
                            break;
                        }
                    }
                }
            }
        }
    }
}
void TopologicalSort1(Graph graph) {
    int graphSize = graph.numberNode;
    char dsMon[] = "DanhSachMon.txt";
    char daDKy[] = "DaDangKy.txt";
    char muonDky[] = "MuonDangKy.txt";
    int sizeMon, sizeDaDK, sizeMuonDK;
    string mon[MAXN], daDK[MAXN], muonDK[MAXN];
    switch(ReadFileTopo(dsMon, mon, sizeMon, graphSize, true)) {
        case -1: 
            cout << "Du lieu nhap vao khong du! Vui long nhap it nhat " << graphSize << " mon";
            return;
        case 0:
            cout << "Loi mo file";
            return;
        default:
            break;
    }
    if (!ReadFileTopo(daDKy, daDK, sizeDaDK, graphSize, false)) {
        cout << "Loi mo file";
        return;
    }
    if (!ReadFileTopo(muonDky, muonDK, sizeMuonDK, graphSize, false)) {
        cout << "Loi mo file";
        return;
    }
    int iDaDK[MAXN];
    int iMuonDK[MAXN];
    IndexArray(mon, sizeMon, daDK, iDaDK, sizeDaDK);
    IndexArray(mon, sizeMon, muonDK, iMuonDK, sizeMuonDK);
    OutputTopoSort(graph, iDaDK, sizeDaDK, iMuonDK, sizeMuonDK, mon, sizeMon, daDK, muonDK);
}
void RunningTopologicalSort(Graph graph) {
	NotificationFull("Bat dau thuat toan!");
	const int graphSize = graph.numberNode;
	int inDegree[graphSize];
	int res[graphSize];
	int index = 0;
	for (int i = 0; i < graph.numberNode; ++i)
		inDegree[i] = 0;
	for (int u = 0; u < graph.numberNode; ++u) 
		for (int v = 0; v < graph.numberNode; ++v) 
			if (graph.adj[u][v])
				inDegree[v]++;
	Queue queue;
	setlinestyle(0, 0, 2);
	for (int i = 0; i < graph.numberNode; ++i)
		if (!inDegree[i]) {
			setcolor(RED);
			circle(graph.node[i]->x, graph.node[i]->y, 25);
			setcolor(WHITE);
			queue.push(i);
		}
	delay(1000);
	for (int i = 0; i < graph.numberNode; ++i)
		if (!inDegree[i]) {
			setcolor(YELLOW);
			circle(graph.node[i]->x, graph.node[i]->y, 25);
			setcolor(WHITE);
		}
	while(!queue.empty()) {
		int u;
		queue.pop(u);
		res[index++] = u;
		delay(1000);
		setcolor(RED);
		circle(graph.node[u]->x, graph.node[u]->y, 25);
		setcolor(WHITE);
		for (int v = 0; v < graph.numberNode; ++v) {
			if (graph.adj[u][v]) {
				inDegree[v]--;
				delay(1000);
				DrawEdge(graph, u, v, BLACK);
				if (inDegree[v] == 0) {
					queue.push(v);
					delay(1000);
					setcolor(YELLOW);
					circle(graph.node[v]->x, graph.node[v]->y, 25);
					setcolor(WHITE);
				}
			}
		}
		delay(1000);
		setcolor(BLACK);
		circle(graph.node[u]->x, graph.node[u]->y, 25);
		setcolor(WHITE);
	}
	string noti = "Thu tu topo: ";
	cout << "Thu tu topo:\n";
	for (int i = 0; i < graphSize; ++i){
		cout << res[i] << " ";
		noti += to_string(res[i]) + " "; 
	}
	NotificationFull(noti);
}

/////////////////////////////////////////////////////////////////////_Print resul_/////////////////////////////////////////////////////////////////////
string RemoveSpace(string s) {
    int n = s.length();
    int i, j = -1;
    while(++j < n && (s[j] == ' ' || s[j] == '\t'));
    string res;
    for (i = j; i < n; ++i) {
        if (s[i] == ' ' || s[i] == '\t') {
            while((s[i] == ' ' || s[i] == '\t') && i < n)
                i++;
            i--; 
            res += " ";
        } else {
            res += s[i];
        }
    }
    j = res.length();
    while(--j >= 0 && (res[j] == ' ' || res[j] == '\t'));
    res = res.substr(0, j + 1);
    return res;
}
void UpdateValue(WordWrap &word, int scrollbarArea, Button &scrollbar, int &thumbHeight, int &jump, int &u0) {
	thumbHeight = round(word.linePerPage * scrollbarArea * 1.0 / word.size);
	jump = round((scrollbarArea - thumbHeight) * 1.0 / (word.size - word.linePerPage));
	scrollbar.y2 = scrollbar.y1 + thumbHeight - 1;
	u0 = scrollbar.y2;
}
void DrawButton(Button btn, int color, bool fill) {
	if (fill) {
		setfillstyle(1, color);
		bar(btn.x1 + 1, btn.y1 + 1, btn.x2, btn.y2);
	} else {
		setcolor(color);
		rectangle(btn.x1, btn.y1, btn.x2, btn.y2);
	}
}
void DeleteButton(Button btn) {
	setfillstyle(1, WHITE);
	bar(btn.x1 + 1, btn.y1 + 1, btn.x2, btn.y2);
}
void DrawResult(Button upButton, Button downButton, Button scrollbar) {
	setcolor(BLUE);
	setlinestyle(0, 0, 1);
	DrawButton(upButton, BLUE, false);
	DrawButton(downButton, BLUE, false);
	DrawButton(scrollbar, BLUE, true);
	settextstyle(11, HORIZ_DIR, 1);
	string up = "/\\";
    string down = "\\/";
    int height = textheight((char*)up.c_str());
    int width = textwidth((char*)up.c_str());
    outtextxy((upButton.x1 + upButton.x2) / 2 - width / 2, (upButton.y1 + upButton.y2) / 2 - height / 2, (char*)up.c_str());
    outtextxy((downButton.x1 + downButton.x2) / 2 - width / 2, (downButton.y1 + downButton.y2) / 2 - height / 2, (char*)down.c_str());
	setlinestyle(0, 0, 2);
	line(upButton.x1, upButton.y1, downButton.x1, downButton.y2);
	settextstyle(3, HORIZ_DIR, 2);
}

/////////////////////////////////////////////////////////////////////_Conver Value_/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////_File_/////////////////////////////////////////////////////////////////////
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