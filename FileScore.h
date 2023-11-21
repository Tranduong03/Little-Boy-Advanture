#pragma once

#include <fstream>

using namespace std;

struct Node {
	int score = 0;
	string name = "";
	Node* next = nullptr;	// nút tiếp theo
	Node* prev = nullptr; // nút trước đó
};

class File
{
public:
	File();
	~File();
	void CleanUp();
	Node* CreateNode(int score, string name);
	bool isEmpty();
	void write() const;
	void read();
	Node* Head() { return head; }
	Node* Tail() { return tail; }
	void addNode(int cur_score, string cur_name);

private:
	Node* head, * tail;
};