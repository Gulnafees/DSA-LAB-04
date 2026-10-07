/*
This problem can be effectively modeled using a circular linked list, since the last person is followed by the first, and eliminations require efficient pointer updates.
Task 2:
Write a program to simulate the Josephus Problem using a circular linked list.
1.	Input Requirements:
•	Number of people, N (each person assigned an ID: 1, 2, …, N).
•	Step count, k (the interval at which a person is eliminated).
2.	Circular Linked List Representation:
•	Each node should represent a person with:
	Person ID (integer).
	Pointer to the next person (circular linkage).
3.	Operations to Implement:
•	Create Circle – Build a circular linked list of N people.
•	Elimination Process – Starting from person 1, eliminate every k-th person. Update the links after each elimination.
•	Display Eliminated Order – Print the order in which people are eliminated.
•	Display Survivor – At the end, print the ID of the last surviving person.
*/
#include <iostream>
using namespace std;

//node structur for circuler list
struct PersonNode {
    int id;
    PersonNode* next;
};

//class to manage josephus problem
class JosephusProblem {
private:
    PersonNode* head = nullptr;

public:
    //1.create circle of n peopel
    void createCircle(int n) {
        if (n <= 0) return;

        PersonNode* prevNode = nullptr;

        for (int i = 1; i <= n; i++) {
            PersonNode* newNode = new PersonNode();
            newNode->id = i;

            if (head == nullptr) {
                head = newNode;
            } else {
                prevNode->next = newNode;
            }
            prevNode = newNode;
        }
        // make it circuler
        prevNode->next = head;
    }

    //2. eliminate every k-th person
    void eliminatePerson(int k) {
        if (head == nullptr || k <= 0) {
            cout << "Invalid input." << endl;
            return;
        }

        cout << "--- Elimination Order ---" << endl;

        PersonNode* curr = head;
        PersonNode* prev = nullptr;

        //find last node to set prev initialy
        while (curr->next != head) {
            curr = curr->next;
        }
        prev = curr;
        curr = head;

        // loop untill 1 person left
        while (curr->next != curr) {
            //cont k steps
            for (int count = 1; count < k; count++) {
                prev = curr;
                curr = curr->next;
            }

            //eliiminate k-th node
            cout << "Person " << curr->id << " eliminated." << endl;
            prev->next = curr->next;

            PersonNode* temp = curr;
            curr = curr->next;
            delete temp;
        }

        head = curr;
        cout << "\n--- Survivor ---" << endl;
        cout << "Person " << head->id << " is the survivor!" << endl;

        //clean up last node
        delete head;
        head = nullptr;
    }
};

int main() {
    JosephusProblem jp;
    int n, k;

    cout << "Enter number of people (N): ";
    cin >> n;
    cout << "Enter step count (k): ";
    cin >> k;

    jp.createCircle(n);
    jp.eliminatePerson(k);

    return 0;
}