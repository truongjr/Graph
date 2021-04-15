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
void drawtriangle(int x1, int y1, int x2, int y2, int color) {
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
void drawcurved1(int x1, int y1, int x2, int y2, char *tt, int color) {
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
	double startAngle, endAngle;
	int cnt;
	if (x3 >= xI && y3 <= yI && x4 >= xI && y4 <= yI)
		startAngle = -360 + angle2, endAngle = -360 + angle1, cnt = 1;
	else if (x3 >= xI && y3 <= yI && x4 >= xI && y4 > yI) 
		startAngle = -angle2, endAngle = -360 + angle1, cnt = 2;
	else if (x3 >= xI && y3 > yI && x4 >= xI && y4 > yI)
		startAngle = -angle2, endAngle = -angle1, cnt = 3;
	else if (x3 >= xI && y3 > yI && x4 < xI && y4 > yI)
		startAngle = -angle2, endAngle = -angle1, cnt = 4;
	else if (x3 < xI && y3 > yI && x4 < xI && y4 > yI) 
		startAngle = -angle2, endAngle = -angle1, cnt = 5;
	else if (x3 < xI && y3 > yI && x4 < xI && y4 <= yI) 
		startAngle = -360 + angle2, endAngle = -angle1, cnt = 6;
	else if (x3 < xI && y3 <= yI && x4 < xI && y4 <= yI)
		startAngle = -360 + angle2, endAngle = -360 + angle1, cnt = 7;
	else if (x3 < xI && y3 <= yI && x4 >= xI && y4 <= yI)
		startAngle = -360 + angle2, endAngle = -360 + angle1, cnt = 8;
	cout << cnt << "\n";
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
	drawtriangle(x5, y5, x4, y4, color);
	arc(xI, yI, startAngle, endAngle, r1);
	outtextxy(xT, yT, tt);
}
void Create_curved(int x1, int y1, int x2, int y2, char *tt, int color) {
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
	cout << angle1 << " " << angle2 << "\n";
	double startAngle, endAngle;
	int cnt;
	if (x3 >= xI && y3 <= yI && x4 >= xI && y4 <= yI)
		startAngle = angle1, endAngle = angle2, cnt = 1;
	else if (x3 >= xI && y3 > yI && x4 >= xI && y4 <= yI) 
		startAngle = 360 - angle1, endAngle = 360 + angle2, cnt = 2;
	else if (x3 >= xI && y3 > yI && x4 >= xI && y4 > yI)
		startAngle = 360 - angle1, endAngle = 360 - angle2, cnt = 3;
	else if (x3 < xI && y3 > yI && x4 >= xI && y4 > yI)
		startAngle = 360 - angle1, endAngle = 360 - angle2, cnt = 4;
	else if (x3 < xI && y3 > yI && x4 < xI && y4 > yI) 
		startAngle = 360 - angle1, endAngle = 360 - angle2, cnt = 5;
	else if (x3 < xI && y3 <= yI && x4 < xI && y4 > yI) 
		startAngle = angle1, endAngle = 360 - angle2, cnt = 6;
	else if (x3 < xI && y3 <= yI && x4 < xI && y4 <= yI)
		startAngle = angle1, endAngle = angle2, cnt = 7;
	else if (x3 >= xI && y3 <= yI && x4 < xI && y4 <= yI)
		startAngle = angle1, endAngle = angle2, cnt = 8;
	cout << cnt << "\n";
	double s45 = sin(45 * M_PI / 180.0);
	double c45 = cos(45 * M_PI / 180.0); 
	double xT = c45 * (x2 - xI) - s45 * (y2 - yI) + xI;
	double yT = s45 * (x2 - xI) + c45 * (y2 - yI) + yI;
	if (!(xT > 0 && yT > 0 && xT < 1000 && yT < 700)) {
		drawcurved1(x1, y1, x2, y2, tt, color);
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
	drawtriangle(x5, y5, x4, y4, color);
	arc(xI, yI, startAngle, endAngle, r1);
	outtextxy(xT, yT, tt);
}
void Create_line(int x1, int y1, int x2, int y2, char *tt, int color) {
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
	drawtriangle(x3, y3, ax, ay, color);
	outtextxy(xT, yT, tt);
}
