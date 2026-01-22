#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <deque>

using namespace std;

int main()
{
    stack<char> s;
   
    s.push('k');
    s.push('l');
    s.push('o');
    s.push('f');
    
    
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();

    /*for (int i=0;i<4;i++) {
        cout << s.top() << endl;
        s.pop();
    }*/
    
   
    
    cout << "==================" << endl;

    queue<char> q;
    cout << q.empty() << endl; // output true (1)
    cout << "==================" << endl;
    
    
    s.push('a');
    s.push('b');
    
    while (!s.empty())
    {                    // s has 2 more items
        q.push(s.top()); // enqueue 'b' and 'a'
        s.pop();
    }
    q.push('z');               // add one more item
    cout << q.front() << endl; // prints 'b'
    cout << q.back() << endl;  // prints 'z'

    // output 'b', 'a', then 'z' (until queue is empty), according to the insertion order above
    cout << "==================" << endl;
    while (!q.empty())
    {
        cout << q.front() << endl; // take the front first
        q.pop();                   // before popping it
    }

    cout << "==================" << endl;

    deque<char> d;
    d.push_back('a');
    d.push_back('b');
    d.push_back('c');
    cout << d.front() << " - " << d.back() << endl; // prints 'a - c'
    d.push_front('d');
    cout << d[0] << d[1] << d[2] << d[3] << endl;   // only in C++, 'dabc'
    cout << d.front() << " - " << d.back() << endl; // prints 'd - c'
    d.pop_back();
    cout << d.front() << " - " << d.back() << endl; // prints 'd - b'
    d.pop_front();
    cout << d.front() << " - " << d.back() << endl; // prints 'a - b'

    return 0;
}
