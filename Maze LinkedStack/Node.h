#pragma once
#include "Location2D.h"
	
// Student 객체를 저장할 노드 클래스 : 객체 간의 link를 위해 생성
class Node : public Location2D{
public:
	Node(int row, int col)
		: Loc(new Location2D(row, col)), link(NULL)
	{ }
	~Node() { if (Loc != NULL) delete Loc; }
private:
	Location2D* Loc;
	Node* link;	// 다음 노드를 가리킬 포인터 변수
public:
	Node* getLink() { return link; }
	void setLink(Node* p) { link = p; }
	Location2D* getLocation() { return Loc; }
};