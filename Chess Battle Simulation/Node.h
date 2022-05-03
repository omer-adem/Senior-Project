#pragma once

class Node
{
private:

public:
	Node* parent = nullptr;
	int x;
	int y;
	bool selected = false;
	Node() { x = -1; y = -1; }
	Node(int yy, int xx) { x = xx; y = yy; }
};