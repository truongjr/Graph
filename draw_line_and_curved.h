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
}
void DrawCurved1(int x1, int y1, int x2, int y2, char *tt, int color) {
	setcolor(color);
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
	outtextxy(xT - 5, yT - 5, tt);
}
void CreateCurved(int x1, int y1, int x2, int y2, char *tt, int color) {
	setcolor(color);
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
	if (!(xT > 0 && yT > 0 && xT < 1000 && yT < 700)) {
		DrawCurved1(x1, y1, x2, y2, tt, color);
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
	outtextxy(xT - 5, yT - 5, tt);
}
void CreateLine(int x1, int y1, int x2, int y2, char *tt, int color) {
	// tim diem dau tien
	setcolor(color);
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
	for (int i = 0; i < numberNode; ++i) {
		string temp = node[i]->name;
		char *res = &temp[0];
		CreateNode(node[i]->x, node[i]->y, res, BLUE);
	}
	for (int i = 0; i < numberNode; ++i) {
		for (int row = i; row < numberNode; ++row) {
			if (adj[row][i]) {
				string s = to_string(adj[row][i]);
				char *res = &s[0];
				CreateLine(node[row]->x, node[row]->y, node[i]->x, node[i]->y, res, BLUE);
				type[row][i] = 1;
			}
		}
		for (int col = i; col < numberNode; ++col) {
			if (adj[i][col]) {
				string s = to_string(adj[i][col]);
				char *res = &s[0];
				if (adj[col][i]) {
					CreateCurved(node[i]->x, node[i]->y, node[col]->x, node[col]->y, res, BLUE);
					type[i][col] = 2;
				} else {
					CreateLine(node[i]->x, node[i]->y, node[col]->x, node[col]->y, res, BLUE);
					type[i][col] = 1;
				}
			}
		}
	}
}
void DeleteEdge(Node *node[14], int &numberNode, int adj[14][14], int type[14][14]) {
	int x1, y1, x2, y2;
	int src = -1, dest = -1;
	bool flag = true;
	while(!kbhit() && flag) {
		getmouseclick(WM_LBUTTONDOWN, x1, y1);
		if (x1 != -1 && y1 != -1) {
			for (int i = 0; i < numberNode; ++i) {
				if (CheckNode(node[i]->x, node[i]->y, x1, y1)) {
					x1 = node[i]->x;
					y1 = node[i]->y;
					flag = false;
					src = i;
					break;
				}
			}
		}
	}
	flag = true;
	while(!kbhit() && flag) {
		getmouseclick(WM_LBUTTONDOWN, x2, y2);
		if (x2 != -1 && y2 != -1) {
			for (int i = 0; i < numberNode; ++i) {
				if (CheckNode(node[i]->x, node[i]->y, x2, y2)) {
					x2 = node[i]->x;
					y2 = node[i]->y;
					flag = false;
					dest = i;
					break;
				}
			}
		}
	}
	if (src != dest) {
		if (adj[src][dest]) {
			string empty = "  ";
			char *res = &empty[0];
			if (type[src][dest] == 1) 
				CreateLine(node[src]->x, node[src]->y, node[dest]->x, node[dest]->y, res, WHITE);
			else if (type[src][dest] == 2) 
				CreateCurved(node[src]->x, node[src]->y, node[dest]->x, node[dest]->y, res, WHITE);
			adj[src][dest] = 0;
			type[src][dest] = 0;
			DrawGraph(node, numberNode, adj, type);
		}
	}
}
void DeleteVertex(Node *node[14], int &numberNode, int adj[14][14], int type[14][14]) {
	int x, y;
	bool flag = true;
	int index = -1;
	while(!kbhit() && flag) {
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if (x != -1 && y != -1) {
			for (int i = 0; i < numberNode; ++i) {
				if (CheckNode(node[i]->x, node[i]->y, x, y)) {
					index = i;
					x = node[i]->x;
					y = node[i]->y;
					flag = false;
					break;
				}
			}
		}
	}
	string empty = "  ";
	char *res = &empty[0];
	CreateNode(x, y, res, 0);
	for (int row = 0; row < numberNode; ++row) {
		if (adj[row][index]) {
			if (type[row][index] == 1) {
				CreateLine(node[row]->x, node[row]->y, node[index]->x, node[index]->y, res, WHITE);
			} else if (type[row][index] == 2) {
				CreateCurved(node[row]->x, node[row]->y, node[index]->x, node[index]->y, res, WHITE);
			}
		}
	}
	for (int col = 0; col < numberNode; ++col) {
		if (adj[index][col]) {
			if (type[index][col] == 1) {
				CreateLine(node[index]->x, node[index]->y, node[col]->x, node[col]->y, res, WHITE);
			} else if (type[index][col] == 2) {
				CreateCurved(node[index]->x, node[index]->y, node[col]->x, node[col]->y, res, WHITE);
			}
		}
	}
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
void Move(Node *node[14], int &numberNode, int adj[14][14], int type[14][14]) {
	int x1, y1, x2, y2;
	int index = -1;
	bool flag = true;
	// bat phim dau
	while(!kbhit() && flag) {
		getmouseclick(WM_LBUTTONDOWN, x1, y1);
		if (x1 != -1 && y1 != -1) {
			for (int i = 0; i < numberNode; ++i) {
				if (CheckNode(node[i]->x, node[i]->y, x1, y1)) {
					x1 = node[i]->x;
					y1 = node[i]->y;
					flag = false;
					index = i;
					break;
				}
			}
		}
	}
	// bat phim sau
	while(!kbhit() && !flag) {
		getmouseclick(WM_LBUTTONDOWN, x2, y2);
		if (x2 != -1 && y2 != -1) {
			int i;
			for (i = 0; i < numberNode; ++i) {
				if (CheckNode(node[i]->x, node[i]->y, x2, y2)) {
					break;	
				}
			}
			if (i == numberNode) {
				break;
			} 
		}
	}
	// xoa nut hien tai
	string empty = "  ";
	char *res = &empty[0];
	CreateNode(x1, y1, res, 0);
	// xoa cac canh hien tai
	for (int row = 0; row < numberNode; ++row) {
		if (adj[row][index]) {
			if (type[row][index] == 1) {
				CreateLine(node[row]->x, node[row]->y, node[index]->x, node[index]->y, res, WHITE);
			} else if (type[row][index] == 2) {
				CreateCurved(node[row]->x, node[row]->y, node[index]->x, node[index]->y, res, WHITE);
			}
		}
	}
	for (int col = 0; col < numberNode; ++col) {
		if (adj[index][col]) {
			if (type[index][col] == 1) {
				CreateLine(node[index]->x, node[index]->y, node[col]->x, node[col]->y, res, WHITE);
			} else if (type[index][col] == 2) {
				CreateCurved(node[index]->x, node[index]->y, node[col]->x, node[col]->y, res, WHITE);
			}
		}
	}
	node[index]->x = x2, node[index]->y = y2;
	DrawGraph(node, numberNode, adj, type);
}
