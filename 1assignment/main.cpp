#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <fstream>
#include <string>
using namespace std;

void print_list(list<int> l, string sep = "\n");
void print_stack(stack<int> s, string sep = "\n");
void print_queue(queue<int> q, string sep = "\n");

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("ERROR\n");
		exit(1);
	}

    queue<int> qu1;
    stack<int> st1;
    list<int>  li1;
	
    ifstream test1(argv[1]);
	string value = "432";
    
    while (getline(test1, value)) {
        qu1.push(stoi(value));
        st1.push(stoi(value));
        li1.push_front(stoi(value));
    }

    cout << "QUEUE CONTENTS:\n";
    print_queue(qu1, " ");
    cout << "\nSTACK CONTENTS:\n";
    print_stack(st1, " ");
    cout << "\nLIST CONTENTS:\n";
    li1.sort();
    print_list(li1, " ");
    cout << '\n';

    return 0;
}

void print_queue(queue<int> q, string sep)
{
    queue<int> temp = q;
    while (!temp.empty()) {
        cout << temp.front() << sep;
        temp.pop();
    }
}

void print_stack(stack<int> s, string sep)
{
    stack<int> temp = s;
    while (!temp.empty()) {
        cout << temp.top() << sep;
        temp.pop();
    }
}

void print_list(list<int> l, string sep)
{
    list<int>::iterator it;
    for (it = l.begin(); it != l.end(); ++it)
        cout << *it << sep;
}
