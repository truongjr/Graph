void UpdateValue(WordWrap &word, int scrollbarArea, Button &scrollbar, int &thumbHeight, int &jump, int &u0) {
	thumbHeight = round(word.linePerPage * scrollbarArea * 1.0 / word.size);
	jump = round((scrollbarArea - thumbHeight) * 1.0 / (word.size - word.linePerPage));
	scrollbar.y2 = scrollbar.y1 + thumbHeight;
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
	setcolor(WHITE);
	setlinestyle(0, 0, 1);
	setfillstyle(1, WHITE);
    bar(upButton.x1, upButton.y1, downButton.x2, downButton.y2);
	DrawButton(upButton, BLACK, false);
	DrawButton(downButton, BLACK, false);
	DrawButton(scrollbar, COLOR(192, 192, 192), true);
	settextstyle(11, HORIZ_DIR, 1);
	string up = "/\\";
    string down = "\\/";
    int height = textheight((char*)up.c_str());
    int width = textwidth((char*)up.c_str());
	setbkcolor(WHITE);
    outtextxy((upButton.x1 + upButton.x2) / 2 - width / 2, (upButton.y1 + upButton.y2) / 2 - height / 2, (char*)up.c_str());
    outtextxy((downButton.x1 + downButton.x2) / 2 - width / 2, (downButton.y1 + downButton.y2) / 2 - height / 2, (char*)down.c_str());
	line(upButton.x1, upButton.y1, downButton.x1, downButton.y2);
	line(upButton.x2, upButton.y1, downButton.x2, downButton.y2);
	settextstyle(10, HORIZ_DIR, 2);
}
