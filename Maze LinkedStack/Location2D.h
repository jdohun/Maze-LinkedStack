#pragma once
#include <cstdio>
class Location2D {
public:
	Location2D(int r = 0, int c = 0)
		: row(r), col(c) 
	{ }
private:
	int row;	 // 현재 위치의 행 번호
	int col;	 // 현재 위치의 열 번호
public:
	// 위치 p가 자신의 이웃인지 검사하는 함수
	bool isNeighbor(Location2D& p) {
		return ((row == p.row && (col == p.col - 1 || col == p.col + 1)) // 열번호가 같고 행이 이웃하거나
			|| (col == p.col && (row == p.row - 1 || row == p.row + 1))); // 행번호가 같고 열이 이웃하면 true
	}
	// 위치 p가 자신과 같은 위치인지를 검사하는 함수 (연산자 오버로딩)
	bool operator==(Location2D& p) { return row == p.row && col == p.col; }
	
	void display() { printf("row : %d, col : %d\n", row, col); }

	int getRow() { return row; }
	int getCol() { return col; }
	void setRow(int r) { row = r; }
	void setCol(int c) { col = c; }
};