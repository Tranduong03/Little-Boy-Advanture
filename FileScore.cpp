#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "FileScore.h"

using namespace std;

File::File()
{
	head = tail = nullptr;
}
File::~File()
{
	CleanUp();
}
bool File::isEmpty()
{
	return head == nullptr;
}
void File::CleanUp()
{
	for (Node* i = head; i != NULL; i = i->next)
	{
		Node* newNode = head;
		head = head->next;
		delete newNode;
	}
}
Node* File::CreateNode(int score, string name)
{
    Node* newNode = new Node();
    newNode->name = name;
    newNode->score = score;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}
void File::read()
{
    ifstream infile("output.txt");
    // ofstream outfile("Sort_Score.txt", ios_base::out);

    string line;
    int score = 0;
    string name = "";

    while (getline(infile, line))
    {
        istringstream iss(line);
        iss >> score;
        getline(iss >> ws, name);

        Node* newNode = CreateNode(score, name);
        if (isEmpty())
        {
            head = tail = newNode;
        }
        else {
            Node* temp = NULL;
            for (Node* i = head; i != NULL; i = i->next)
            {
                if (i->score > newNode->score)
                {
                    temp = i;
                }
                else {
                    break;
                }
            }

            if ((temp == NULL) && (temp != tail)) {
                // Nếu temp là NULL, nghĩa là nút mới có giá trị lớn nhất
                head->prev = newNode;
                newNode->next = head;
                head = newNode;
            }
            else {
                newNode->next = temp->next;
                newNode->prev = temp;
                temp->next = newNode;
                if (newNode->next != NULL) {
                    newNode->next->prev = newNode;
                }
                else {
                    tail = newNode;
                }
            }
        }
    }

    infile.close();
    // outfile.close();
}
void File::write() const
{
    int count = 1;
	for (Node* i = head; i != NULL; i = i->next) {
		cout << i->score << " ";
        if (count++ == 20)
        {
            break;
        }
	}
}
void File::addNode(int add_score, string add_name)
{
    Node* newNode = CreateNode(add_score, add_name);
    if (isEmpty())
    {
        head = tail = newNode;
    }
    else {
        Node* temp = nullptr;
        for (Node* i = head; i != NULL; i = i->next)
        {
            if (i->score > newNode->score)
            {
                temp = i;
            }
            else {
                break;
            }
        }

        if ((temp == NULL) && (temp != tail)) {
            // Nếu temp là NULL, nghĩa là nút mới có giá trị lớn nhất
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        else {
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next = newNode;
            if (newNode->next != NULL) {
                newNode->next->prev = newNode;
            }
            else {
                tail = newNode;
            }
        }
    }
}