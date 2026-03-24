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

    if (x <= 1000)
        ds.arr[++ds.top1] = x;
    else
        ds.arr[--ds.top2] = x;
}

void display(DoubleStack ds) {
    cout << "Stack1 (<=1000): ";
    for (int i = 0; i <= ds.top1; i++)
        cout << ds.arr[i] << " ";

    cout << "\nStack2 (>1000): ";
    for (int i = MAX - 1; i >= ds.top2; i--)
        cout << ds.arr[i] << " ";

    cout << endl;
}


/*==================== QUESTION 2: STACK ====================*/
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
    for (int i = s.top; i >= 0; i--)
        cout << s.arr[i] << " ";
    cout << endl;
}

void removeYellow(StackArr &S) {
    StackArr T;
    initStack(T);

    while (!isEmpty(S)) {
        string x = popStack(S);
        if (x != "yellow") pushStack(T, x);
    }

    while (!isEmpty(T))
        pushStack(S, popStack(T));
}


/*==================== QUESTION 3: INFIX → POSTFIX ====================*/
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
        if (isalnum(c))
            result += c;

        else if (c == '(')
            st.push(c);

        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();
        }

        else {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}


/*==================== QUESTION 4: POSTFIX EVALUATION ====================*/
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
        if (isalnum(c)) {
            st.push(getValue(c));
        } else {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();

            switch (c) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
                case '^': st.push(pow(a, b)); break;
            }
        }
    }
    return st.top();
}


/*==================== QUESTION 5: ALGORITHMS ====================*/
void printAlgorithms() {
    cout << "\nINFIX → PREFIX ALGORITHM:\n";
    cout << "1. Reverse infix expression\n";
    cout << "2. Replace ( with ) and vice versa\n";
    cout << "3. Convert to postfix\n";
    cout << "4. Reverse postfix → prefix\n";

    cout << "\nPREFIX EVALUATION ALGORITHM:\n";
    cout << "1. Scan from right to left\n";
    cout << "2. If operand → push\n";
    cout << "3. If operator → pop 2 operands\n";
    cout << "4. Apply operator and push result\n";
}


/*==================== QUESTION 6 ====================*/

// Queue using 2 stacks
struct QueueUsingStacks {
    stack<int> s1, s2;

    void enqueue(int x) {
        s1.push(x);
    }

    int dequeue() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int x = s2.top();
        s2.pop();
        return x;
    }
};

// Stack using 2 queues
struct StackUsingQueues {
    queue<int> q1, q2;

    void push(int x) {
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    int pop() {
        int x = q1.front();
        q1.pop();
        return x;
    }
};

// Queue of Queues
struct QueueOfQueues {
    queue<queue<int>> qq;

    void addQueue(queue<int> q) {
        qq.push(q);
    }

    void display() {
        while (!qq.empty()) {
            queue<int> q = qq.front();
            qq.pop();

            while (!q.empty()) {
                cout << q.front() << " ";
                q.pop();
            }
            cout << endl;
        }
    }
};


/*==================== MAIN ====================*/
int main() {

    cout << "===== QUESTION 1 =====\n";
    DoubleStack ds;
    init(ds);
    push(ds, 100);
    push(ds, 2000);
    push(ds, 500);
    push(ds, 1500);
    display(ds);


    cout << "\n===== QUESTION 2 =====\n";
    StackArr S;
    initStack(S);

    pushStack(S, "red");
    pushStack(S, "yellow");
    pushStack(S, "green");
    pushStack(S, "yellow");
    pushStack(S, "blue");

    displayStack(S);
    removeYellow(S);
    displayStack(S);


    cout << "\n===== QUESTION 3 (INFIX → POSTFIX) =====\n";
    cout << infixToPostfix("(A+B)*(C-D)") << endl;
    cout << infixToPostfix("A^B*C-D+E/F") << endl;
    cout << infixToPostfix("A/(B+C*D-E)") << endl;
    cout << infixToPostfix("A-B*C+D/E") << endl;
    cout << infixToPostfix("(A+B)^2-(C-D)/2") << endl;


    cout << "\n===== QUESTION 4 (POSTFIX EVALUATION) =====\n";
    cout << evaluatePostfix("AB+CD-*") << endl;
    cout << evaluatePostfix("AB^C*D-EF/+") << endl;
    cout << evaluatePostfix("ABCD*+E-/") << endl;
    cout << evaluatePostfix("ABC*-DE/+") << endl;
    cout << evaluatePostfix("AB+2^CD-2/-") << endl;


    cout << "\n===== QUESTION 5 =====\n";
    printAlgorithms();


    cout << "\n===== QUESTION 6 =====\n";

    QueueUsingStacks q;
    q.enqueue(10);
    q.enqueue(20);
    cout << "Dequeue: " << q.dequeue() << endl;

    StackUsingQueues s;
    s.push(5);
    s.push(10);
    cout << "Pop: " << s.pop() << endl;

    QueueOfQueues qq;
    queue<int> q1, q2;
    q1.push(1); q1.push(2);
    q2.push(3); q2.push(4);

    qq.addQueue(q1);
    qq.addQueue(q2);

    cout << "Queue of Queues:\n";
    qq.display();

    return 0;
}