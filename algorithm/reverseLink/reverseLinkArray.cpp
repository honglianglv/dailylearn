#include <iostream>

using namespace std;
struct Node{
    int value;
    Node* next;
};

Node* reverseLinkArray(Node* head);
Node* reverseLinkArrayV2(Node* head);

void printLinkArray(Node* head);

int main(int argc, char **argv) {
    Node* head;
    Node item1; 
    item1.value = 1;
    head = &item1;
    Node item2;
    item2.value = 2;
    item1.next = &item2;
    Node item3; 
    item3.value = 3;
    item2.next = &item3; 
    Node item4;
    item4.value = 4;
    item3.next = &item4; 
    item4.next = NULL;
    Node item5;
    item5.value = 5;
    item4.next = &item5; 
    item5.next = NULL;

    printLinkArray(head);
    head = reverseLinkArrayV2(head);
    printLinkArray(head);
}

Node* reverseLinkArray(Node* head) {
    Node* nextNode; 
    Node* preNode = NULL;

    if (head == NULL) {
        return head;
    }
    while (head != NULL) {
        nextNode = head->next;
        head->next = preNode;
        preNode = head;
        head = nextNode;
    }
    return preNode;
}

Node* reverseLinkArrayV2(Node* head) {
    Node* curHead = head; 
    Node* nextNode;
    if (head == NULL) {
        return head;
    }
    while (head->next != NULL) {
        nextNode = head->next;
        head->next = nextNode->next;
        nextNode->next = curHead;
        curHead = nextNode;
    }
    return curHead;
}


void printLinkArray(Node* head) {
    while (head != NULL) {
        cout << head->value << endl;
        head = head->next;
    }
}
