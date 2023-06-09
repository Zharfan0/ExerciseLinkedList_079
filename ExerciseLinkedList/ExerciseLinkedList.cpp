#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;
    Node* START = NULL;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();
    bool search(int rollno, Node** hukmana, Node** current);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    // Beginning of the list
    int roll;
    string nama;
   
    cout << "\nEnter the roll number: ";
    cin >> roll;
    cout << "\nEnter the name: ";
    cin >> nama;

    Node* newnode = new Node(); // Allocate memory for the new node.
    newnode->rollNumber = roll; //Assign value to the data field of the new node.
    newnode->name = nama; 

    if (LAST == NULL) { 
        newnode->next = newnode;
        LAST = newnode; //Make the next field of LAST point to the new node.
    }
    else {
        newnode->next = LAST->next; //Make the next field of the new node point to the successor of LAST
        LAST->next = newnode;
    }


}

bool CircularLinkedList::search(int rollno, Node** hukmana, Node** current) {
    *hukmana = LAST->next;
    *current = LAST->next; 

    while (*current != LAST) {
        if (rollno == (*current)->rollNumber) {
            return true;
        }

        *hukmana = *current;
        *current = (*current)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL; 
}

// ----------------------------------- delNode
bool CircularLinkedList::delNode() {
    int rollno;
    cout << "Enter the roll number of the node to be deleted: ";
    cin >> rollno;

    Node* hukmana = NULL;
    Node* muhammad = NULL;

    if (!search(rollno, &hukmana, &muhammad)) {
        cout << "Node not found." << endl;
        return false;
    }

    // Beginning of the list
    if (hukmana == LAST) { //Make previous point to the successor of LAST.
        if (muhammad->next == muhammad) { // If LAST points to itself
            delete muhammad;
            LAST = NULL;
        }
        else {
            LAST->next = muhammad->next; //Make current point to the successor of LAST
            delete muhammad;
        }

        cout << "Node deleted from the beginning of the list." << endl;
        return true;
    }

    // End of the list
    if (muhammad == LAST) { //Make previous point to the successor of LAST.
        hukmana->next = LAST->next; //Make current point to the successor of LAST.
        LAST = hukmana;

        delete muhammad;
        cout << "Node deleted from the end of the list." << endl;
        return true;
    }

    // Between two nodes in the list
    hukmana->next = muhammad->next;
    delete muhammad;

    cout << "Node deleted from between two nodes in the list." << endl;
    return true;
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty" << endl;
    }
    else {
        cout << "\nRecords in the list are:" << endl;
        Node* currentNode = LAST->next;

        while (currentNode != LAST) {
            cout << currentNode->rollNumber << " " << currentNode->name << endl;
            currentNode = currentNode->next;
        }

        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;

    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-4): ";
            char ch;
            cin >> ch;

            switch (ch) {
            case '1':
                obj.addNode();
                break;
            case '2':
                obj.delNode();
                break;
            case '3':
                obj.traverse();
                break;
            case '4':
                return 0;
            default:
                cout << "Invalid option" << endl;
                break;
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
