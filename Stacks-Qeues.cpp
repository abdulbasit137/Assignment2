#include <iostream>
using namespace std;

/*QUESTION 1: TWO STACKS IN ONE ARRAY*/
#define MAX 200

struct DoubleStack {
    int arr[MAX];
    int top1;  // stack for <= 1000
    int top2;  // stack for > 1000
};

// Initialize
void init(DoubleStack &ds) {
    ds.top1 = -1;
    ds.top2 = MAX;
}

// Push
void push(DoubleStack &ds, int x) {
    if (ds.top1 + 1 == ds.top2) {
        cout << "Stack Overflow\n";
        return;
    }

    if (x <= 1000) {
        ds.arr[++ds.top1] = x;
    } else {
        ds.arr[--ds.top2] = x;
    }
}

// Displaying both stacks
void display(DoubleStack ds) {
    cout << "Stack1 (<=1000): ";
    for (int i = 0; i <= ds.top1; i++)
        cout << ds.arr[i] << " ";

    cout << "\nStack2 (>1000): ";
    for (int i = MAX - 1; i >= ds.top2; i--)
        cout << ds.arr[i] << " ";

    cout << endl;
}


/*QUESTION 2: STACK  */
#define SIZE 100

struct Stack {
    string arr[SIZE];
    int top;
};

void initStack(Stack &s) {
    s.top = -1;
}

bool isEmpty(Stack s) {
    return s.top == -1;
}

bool isFull(Stack s) {
    return s.top == SIZE - 1;
}

void pushStack(Stack &s, string x) {
    if (isFull(s)) {
        cout << "Stack Overflow\n";
        return;
    }
    s.arr[++s.top] = x;
}

string popStack(Stack &s) {
    if (isEmpty(s)) {
        cout << "Stack Underflow\n";
        return "";
    }
    return s.arr[s.top--];
}

void displayStack(Stack s) {
    for (int i = s.top; i >= 0; i--)
        cout << s.arr[i] << " ";
    cout << endl;
}


/* PEZ CANDY ALGORITHM */
void removeYellow(Stack &S) {
    Stack T;
    initStack(T);

    // Step 1: Remove yellow, store others in T
    while (!isEmpty(S)) {
        string x = popStack(S);

        if (x != "yellow") {
            pushStack(T, x);
        }
    }

    // Step 2: Restore order back to S
    while (!isEmpty(T)) {
        pushStack(S, popStack(T));
    }
}


/*SIX STACKS IN ONE ARRAY*/
#define N 60

struct SixStacks {
    int arr[N];
    int top[6];
    int start[6];
};

// Initializeing six stacks
void initSixStacks(SixStacks &ss) {
    int blockSize = N / 6;

    for (int i = 0; i < 6; i++) {
        ss.start[i] = i * blockSize;
        ss.top[i] = ss.start[i] - 1;
    }
}

// Pushe into spaecific stack
void pushSix(SixStacks &ss, int stackNum, int value) {
    int end = (stackNum + 1) * (N / 6);

    if (ss.top[stackNum] + 1 == end) {
        cout << "Stack " << stackNum << " Overflow\n";
        return;
    }

    ss.arr[++ss.top[stackNum]] = value;
}

// Display one stack
void displaySix(SixStacks ss, int stackNum) {
    cout << "Stack " << stackNum << ": ";
    for (int i = ss.start[stackNum]; i <= ss.top[stackNum]; i++)
        cout << ss.arr[i] << " ";
    cout << endl;
}


/* STACK OF STACKS */
struct SimpleStack {
    int arr[10];
    int top;
};

struct StackOfStacks {
    SimpleStack stacks[5];
};

// Initialize
void initSOS(StackOfStacks &sos) {
    for (int i = 0; i < 5; i++)
        sos.stacks[i].top = -1;
}

// Push into a specific stack
void pushSOS(StackOfStacks &sos, int index, int value) {
    if (sos.stacks[index].top == 9) {
        cout << "Inner Stack Overflow\n";
        return;
    }
    sos.stacks[index].arr[++sos.stacks[index].top] = value;
}

// Display stack
void displaySOS(StackOfStacks sos, int index) {
    cout << "Stack " << index << ": ";
    for (int i = sos.stacks[index].top; i >= 0; i--)
        cout << sos.stacks[index].arr[i] << " ";
    cout << endl;
}



int main() {

    cout << "===== QUESTION 1: DOUBLE STACK =====\n";
    DoubleStack ds;
    init(ds);

    push(ds, 100);
    push(ds, 2000);
    push(ds, 500);
    push(ds, 1500);

    display(ds);


    cout << "\n===== QUESTION 2: PEZ CANDY =====\n";
    Stack S;
    initStack(S);

    pushStack(S, "red");
    pushStack(S, "yellow");
    pushStack(S, "green");
    pushStack(S, "yellow");
    pushStack(S, "blue");

    cout << "Original Stack:\n";
    displayStack(S);

    removeYellow(S);

    cout << "After Removing Yellow:\n";
    displayStack(S);


    cout << "\n===== SIX STACKS IN ONE ARRAY =====\n";
    SixStacks ss;
    initSixStacks(ss);

    pushSix(ss, 0, 10);
    pushSix(ss, 1, 20);
    pushSix(ss, 2, 30);

    displaySix(ss, 0);
    displaySix(ss, 1);
    displaySix(ss, 2);


    cout << "\n===== STACK OF STACKS =====\n";
    StackOfStacks sos;
    initSOS(sos);

    pushSOS(sos, 0, 1);
    pushSOS(sos, 0, 2);
    pushSOS(sos, 1, 10);

    displaySOS(sos, 0);
    displaySOS(sos, 1);

    return 0;
}