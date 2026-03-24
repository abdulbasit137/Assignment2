#include <iostream>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

/*==================== QUESTION 1: DOUBLE STACK ====================*/
#define MAX 200
struct DoubleStack {
    int arr[MAX];
    int top1;
    int top2;
};

void init(DoubleStack &ds) {
    ds.top1 = -1;
    ds.top2 = MAX;
}

void push(DoubleStack &ds, int x) {
    if (ds.top1 + 1 == ds.top2) {
        cout << "Stack Overflow\n";
        return;
    }
    if (x <= 1000) ds.arr[++ds.top1] = x;
    else ds.arr[--ds.top2] = x;
}

void display(DoubleStack ds) {
    cout << "Stack1: ";
    for (int i = 0; i <= ds.top1; i++) cout << ds.arr[i] << " ";
    cout << "\nStack2: ";
    for (int i = MAX - 1; i >= ds.top2; i--) cout << ds.arr[i] << " ";
    cout << endl;
}


/*==================== QUESTION 2 ====================*/
#define SIZE 100
struct StackArr {
    string arr[SIZE];
    int top;
};

void initStack(StackArr &s) { s.top = -1; }
bool isEmpty(StackArr s) { return s.top == -1; }

void pushStack(StackArr &s, string x) { s.arr[++s.top] = x; }
string popStack(StackArr &s) { return s.arr[s.top--]; }

void displayStack(StackArr s) {
    for (int i = s.top; i >= 0; i--) cout << s.arr[i] << " ";
    cout << endl;
}

void removeYellow(StackArr &S) {
    StackArr T; initStack(T);
    while (!isEmpty(S)) {
        string x = popStack(S);
        if (x != "yellow") pushStack(T, x);
    }
    while (!isEmpty(T)) pushStack(S, popStack(T));
}


/*==================== QUESTION 3 ====================*/
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

string infixToPostfix(string exp) {
    stack<char> st;
    string result = "";

    for (char c : exp) {
        if (isalnum(c)) result += c;
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top(); st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                result += st.top(); st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        result += st.top(); st.pop();
    }
    return result;
}


/*==================== QUESTION 4 ====================*/
int getValue(char c) {
    if (c == 'A') return 12;
    if (c == 'B') return 3;
    if (c == 'C') return 7;
    if (c == 'D') return 4;
    if (c == 'E') return 2;
    if (c == 'F') return 5;
    return c - '0';
}

int evaluatePostfix(string exp) {
    stack<int> st;
    for (char c : exp) {
        if (isalnum(c)) st.push(getValue(c));
        else {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            if (c == '+') st.push(a + b);
            if (c == '-') st.push(a - b);
            if (c == '*') st.push(a * b);
            if (c == '/') st.push(a / b);
            if (c == '^') st.push(pow(a, b));
        }
    }
    return st.top();
}


/*==================== QUESTION 5 ====================*/
void printAlgorithms() {
    cout << "Infix->Prefix: Reverse, swap brackets, postfix, reverse\n";
    cout << "Prefix Eval: scan right->left, use stack\n";
}


/*==================== QUESTION 6 ====================*/
// (same as yours)
struct QueueUsingStacks {
    stack<int> s1, s2;
    void enqueue(int x) { s1.push(x); }
    int dequeue() {
        if (s2.empty()) {
            while (!s1.empty()) { s2.push(s1.top()); s1.pop(); }
        }
        int x = s2.top(); s2.pop();
        return x;
    }
};


/*==================== QUESTION 7 ====================*/
#define CQSIZE 10
struct CircularQueue {
    int arr[CQSIZE];
    int front, rear;
};

void initCQ(CircularQueue &q) { q.front = q.rear = -1; }
bool isEmptyCQ(CircularQueue q) { return q.front == -1; }
bool isFullCQ(CircularQueue q) { return (q.rear + 1) % CQSIZE == q.front; }

void enqueueCQ(CircularQueue &q, int x) {
    if (isFullCQ(q)) return;
    if (q.front == -1) q.front = 0;
    q.rear = (q.rear + 1) % CQSIZE;
    q.arr[q.rear] = x;
}

int dequeueCQ(CircularQueue &q) {
    int x = q.arr[q.front];
    if (q.front == q.rear) q.front = q.rear = -1;
    else q.front = (q.front + 1) % CQSIZE;
    return x;
}

void reverseCQ(CircularQueue &q) {
    stack<int> s;
    while (!isEmptyCQ(q)) s.push(dequeueCQ(q));
    while (!s.empty()) { enqueueCQ(q, s.top()); s.pop(); }
}

void displayCQ(CircularQueue q) {
    if (isEmptyCQ(q)) return;
    int i = q.front;
    while (true) {
        cout << q.arr[i] << " ";
        if (i == q.rear) break;
        i = (i + 1) % CQSIZE;
    }
    cout << endl;
}


/*==================== QUESTION 9: DEQUE ====================*/
#define DQSIZE 10

struct Deque {
    int arr[DQSIZE];
    int front, rear;
};

void initDeque(Deque &d) {
    d.front = d.rear = -1;
}

bool isEmptyDeque(Deque d) {
    return d.front == -1;
}

bool isFullDeque(Deque d) {
    return (d.rear + 1) % DQSIZE == d.front;
}

// PUSH (front insertion)
void PUSH(Deque &d, int x) {
    if (isFullDeque(d)) {
        cout << "Deque Overflow\n";
        return;
    }
    if (isEmptyDeque(d)) {
        d.front = d.rear = 0;
    } else {
        d.front = (d.front - 1 + DQSIZE) % DQSIZE;
    }
    d.arr[d.front] = x;
}

// POP (remove from front)
int POP(Deque &d) {
    if (isEmptyDeque(d)) {
        cout << "Deque Underflow\n";
        return -1;
    }
    int x = d.arr[d.front];
    if (d.front == d.rear)
        d.front = d.rear = -1;
    else
        d.front = (d.front + 1) % DQSIZE;
    return x;
}

// Inject (insert at rear)
void Inject(Deque &d, int x) {
    if (isFullDeque(d)) {
        cout << "Deque Overflow\n";
        return;
    }
    if (isEmptyDeque(d)) {
        d.front = d.rear = 0;
    } else {
        d.rear = (d.rear + 1) % DQSIZE;
    }
    d.arr[d.rear] = x;
}

// Eject (remove from rear)
int Eject(Deque &d) {
    if (isEmptyDeque(d)) {
        cout << "Deque Underflow\n";
        return -1;
    }
    int x = d.arr[d.rear];
    if (d.front == d.rear)
        d.front = d.rear = -1;
    else
        d.rear = (d.rear - 1 + DQSIZE) % DQSIZE;
    return x;
}

void displayDeque(Deque d) {
    if (isEmptyDeque(d)) return;
    int i = d.front;
    while (true) {
        cout << d.arr[i] << " ";
        if (i == d.rear) break;
        i = (i + 1) % DQSIZE;
    }
    cout << endl;
}


/*==================== MAIN ====================*/
int main() {

    cout << "===== QUESTION 9: DEQUE =====\n";

    Deque d;
    initDeque(d);

    PUSH(d, 10);
    PUSH(d, 20);
    Inject(d, 30);
    Inject(d, 40);

    cout << "Deque after insertions: ";
    displayDeque(d);

    cout << "POP (front removed): " << POP(d) << endl;
    cout << "EJECT (rear removed): " << Eject(d) << endl;

    cout << "Final Deque: ";
    displayDeque(d);

    return 0;
}