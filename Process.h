#include <iostream>
#define MAX 100

using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int start;
    int waiting;
    int turnaround;
    int completed;

    Process () {
        pid = arrival = burst = waiting = turnaround = completed = 0;
        start = -1;
    }
};

struct ProcessQueue {
    Process q[MAX];
    int front;
    int rear;

    ProcessQueue() {
        front = rear = -1;
    }

    void insertQ(Process p) {
        if(front == -1) {
            front = 0;
            rear = 0;
        } else {
            rear++;
        }
        q[rear] = p;
    }

    Process delQ() {
        if(front == -1) {
            throw "Queue Empty";
        }
        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }
        return q[front-1];
    }

    void displayQ() {
        cout << "\nPID\t\tArrival\t\tBurst\t\tStart\t\tTurnaround\t\tWaiting\t\tCompleted\n";
        for (int i=front; i<=rear; i++) {
            cout << q[i].pid << "\t\t" << q[i].arrival << "\t\t" << q[i].burst << "\t\t" << q[i].start << "\t\t" << q[i].turnaround << "\t\t" << q[i].waiting << "\t\t" << q[i].completed << endl;
        }
    }

    bool isEmpty() {
        return front == -1;
    }

    Process* first(){
        return &q[front];
    }
};
