#include <iostream>
#define MAX 100

using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int start;          // Time executed = current time - start (if this process is executing)
    int waiting;
    int turnaround;
    int completed;
    int priority;       // 1(highest) to 7(lowest)

    Process () {
        pid = arrival = burst = waiting = turnaround = completed = priority = 0;
        start = -1;  // Not started
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
        Process temp = q[front];      // Had A PRETTY NASTY ERROR!!
                                    //Believe me you don't wanna know
        if(front == -1) {
            throw "Queue Empty";
        }
        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }
        return temp;
    }

    bool isEmpty() {
        return front == -1;
    }

    Process* first(){
        return &q[front];
    }

    int getSize() {
        return rear-front;
    }
};
