#pragma once
#include "Node.h"

class LinkedStack {
public:
	LinkedStack() : top(NULL) {}
	~LinkedStack(){	// new의 반대 delete하여 메모리 할당 해제
		while (!isEmpty()) {
			delete pop();
		}
	}
private:
	Node* top;	// head 포인터
public:
	bool isEmpty() { return top == NULL; }
	void push(Node* p) { // present node
		if (isEmpty()) { top = p; }
		else {
			p->setLink(top);	// 새로운 노드가 맨 위 노드를 가르킴으로써 맨 위 노드가 됨
			top = p;			// p가 맨 위
		}
	}
	Node* pop() {
		if (isEmpty()) return NULL;
		Node* p = top;
		top = top->getLink();
		return p;
	}
	Node* peek() { return top; };	// top이 NULL이면 NULL 반환, node가 있으면 node 반환됨
	void dispaly() {
		printf("[LinkedStack]\n");
		for (Node* p = top; p != NULL; p = p->getLink()) {
			p->display();
		}
		printf("\n");
	}
};