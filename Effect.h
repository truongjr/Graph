/////////////////////////////////////////////////Hieu ung///////////////////////////////////////
//Hieu ung cho 3 nut: New, Open, Save
void SubEffectFile(int x1, int y1, int x2, int y2, char a[], int color, bool flag){
	if(flag == true){
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		setfillstyle(1, color); 
		bar(x1+3, y1+3, x2-3, y2-3);
		setbkcolor(color);
		outtextxy(x1 + 10, y1 + 5, a); 
		setlinestyle(0, 0, 2);
		Sleep(1);
	}
	else{
		setcolor(WHITE);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		// setlinestyle(0, 0, 2);
		// rectangle(x1, y1, x2, y2);
		setfillstyle(1, color); 
		bar(x1+2, y1+2, x2-2, y2-2);
		setbkcolor(color);
		outtextxy(x1 + 10, y1 + 5, a); 
		setlinestyle(0, 0, 2);
		Sleep(10);
	}
}
//Hieu ung cho 5 nut con lai tren thanh Toolbar
void SubEffectToolbar(int x1, int y1, int x2, int y2, char a[], int color, bool flag){
	if(flag == true){
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		setfillstyle(1, color); 
		bar(x1+3, y1+3, x2-3, y2-3);
		setbkcolor(color);
		outtextxy(x1 + 10, y1 + 5, a); 
		setlinestyle(0, 0, 2);
		Sleep(10);
	}
	else{
		setcolor(WHITE);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		// setlinestyle(0, 0, 2);
		// rectangle(x1, y1, x2, y2);
		setfillstyle(1, color); 
		bar(x1+2, y1+2, x2-2, y2-2);
		setbkcolor(color);
		outtextxy(x1 + 10, y1 + 5, a); 
		setlinestyle(0, 0, 2);
		Sleep(10);
	}
}
//Hieu ung cho bang menu
void SubEffectMenu(int x1, int y1, int x2, int y2, char a[], int color, bool flag){
	if(flag == true){
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		setfillstyle(1, color); 
		bar(x1+3, y1+3, x2-3, y2-3);
		setbkcolor(color);
		outtextxy(x1 + 14, y1 + 18, a); 
		setlinestyle(0, 0, 2);
		Sleep(10);
	}
	else{
		setcolor(WHITE);
		setlinestyle(0, 0, 3);
		rectangle(x1+3, y1+3, x2-3, y2-3);
		setcolor(BLUE);
		// setlinestyle(0, 0, 2);
		// rectangle(x1, y1, x2, y2);
		setfillstyle(1, color); 
		bar(x1+2, y1+2, x2-2, y2-2);
		setbkcolor(color);
		outtextxy(x1 + 14, y1 + 18, a); 
		setlinestyle(0, 0, 2);
		Sleep(10);
	}
}
//Hieu ung cho dep 
void EffectFile(){
	char Toolbar[8][15] = {"      New", "     Open", "     Save", " AddVertex", "  AddEdge", "     Move", "   Rename", "  Delete"};
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 10 && mousex() < 155 && mousey() > 10 && mousey() < 52) SubEffectFile(10, 10, 155, 52, Toolbar[0], LIGHTGREEN, true);
	else SubEffectFile(10, 10, 155, 52, Toolbar[0], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 155 && mousex() < 300 && mousey() > 10 && mousey() < 52) SubEffectFile(155, 10, 300, 52, Toolbar[1], LIGHTGREEN, true);
	else SubEffectFile(155, 10, 300, 52, Toolbar[1], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 300 && mousex() < 445 && mousey() > 10 && mousey() < 52) SubEffectFile(300, 10, 445, 52, Toolbar[2], LIGHTGREEN, true);	
	else SubEffectFile(300, 10, 445, 52, Toolbar[2], WHITE, false);	
}
void EffectToolbar(){
	char Toolbar[8][15] = {"      New", "     Open", "     Save", " AddVertex", "  AddEdge", "     Move", "   Rename", "  Delete"};
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 445 && mousex() < 590 && mousey() > 10 && mousey() < 52) SubEffectToolbar(445, 10, 590, 52, Toolbar[3], LIGHTGREEN, true);
	else SubEffectToolbar(445, 10, 590, 52, Toolbar[3], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 590 && mousex() < 735 && mousey() > 10 && mousey() < 52) SubEffectToolbar(590, 10, 735, 52, Toolbar[4], LIGHTGREEN, true);
	else SubEffectToolbar(590, 10, 735, 52, Toolbar[4], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 735 && mousex() < 880 && mousey() > 10 && mousey() < 52) SubEffectToolbar(735, 10, 880, 52, Toolbar[5], LIGHTGREEN, true);
	else SubEffectToolbar(735, 10, 880, 52, Toolbar[5], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 880 && mousex() < 1025 && mousey() > 10 && mousey() < 52) SubEffectToolbar(880, 10, 1025, 52, Toolbar[6], LIGHTGREEN, true);
	else SubEffectToolbar(880, 10, 1025, 52, Toolbar[6], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 1025 && mousex() < 1140 && mousey() > 10 && mousey() < 52) SubEffectToolbar(1025, 10, 1140, 52, Toolbar[7], LIGHTGREEN, true);
	else SubEffectToolbar(1025, 10, 1140, 52, Toolbar[7], WHITE, false);
}
void EffectMenu(){
	char Menu[9][15] = {"    DFS", "    BFS", "    X->Y", "   TPLT", "Hamilton", "    Euler", "  Dinh tru", "Dinh that", "Canh cau"};
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 14 && mousex() < 139 && mousey() > 99 && mousey() < 168) SubEffectMenu(14, 99, 139, 168, Menu[0], LIGHTGREEN, true);
	else SubEffectMenu(14, 99, 139, 168, Menu[0], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 143 && mousex() < 268 && mousey() > 99 && mousey() < 168) SubEffectMenu(143, 99, 268, 168, Menu[1], LIGHTGREEN, true);
	else SubEffectMenu(143, 99, 268, 168, Menu[1], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 272 && mousex() < 397 && mousey() > 99 && mousey() < 168) SubEffectMenu(272, 99, 397, 168, Menu[2], LIGHTGREEN, true);
	else SubEffectMenu(272, 99, 397, 168, Menu[2], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 14 && mousex() < 139 && mousey() > 172 && mousey() < 241) SubEffectMenu(14, 172, 139, 241, Menu[3], LIGHTGREEN, true);
	else SubEffectMenu(14, 172, 139, 241, Menu[3], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 143 && mousex() < 268 && mousey() > 172 && mousey() < 241) SubEffectMenu(143, 172, 268, 241, Menu[4], LIGHTGREEN, true);
	else SubEffectMenu(143, 172, 268, 241, Menu[4], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 272 && mousex() < 397 && mousey() > 172 && mousey() < 241) SubEffectMenu(272, 172, 397, 241, Menu[5], LIGHTGREEN, true);
	else SubEffectMenu(272, 172, 397, 241, Menu[5], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 14 && mousex() < 139 && mousey() > 245 && mousey() < 314) SubEffectMenu(14, 245, 139, 314, Menu[6], LIGHTGREEN, true);
	else SubEffectMenu(14, 245, 139, 314, Menu[6], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 143 && mousex() < 268 && mousey() > 245 && mousey() < 314) SubEffectMenu(143, 245, 268, 314, Menu[7], LIGHTGREEN, true);
	else SubEffectMenu(143, 245, 268, 314, Menu[7], WHITE, false);
	if(ismouseclick(WM_LBUTTONDOWN) == false && mousex() > 272 && mousex() < 397 && mousey() > 245 && mousey() < 314) SubEffectMenu(272, 245, 397, 314, Menu[8], LIGHTGREEN, true);
	else SubEffectMenu(272, 245, 397, 314, Menu[8], WHITE, false);
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