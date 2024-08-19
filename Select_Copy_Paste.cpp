#include <bits/stdc++.h>
using namespace std;

enum Mode
{
    SELECTCOPYPASTE,
    PASTE
};

struct Node
{
    int noOfAs;
    int steps;
    int noOfAsCopied;
    Mode mode;
    
    Node(int a, int s, int c, Mode m) : noOfAs(a), steps(s), noOfAsCopied(c), mode(m) {}
};

// Custom comparator
struct CompareNoOfAs {
    bool operator()(const Node& n1, const Node& n2) {
        return n1.steps > n2.steps;
    }
};

int main()
{
    priority_queue< Node, vector < Node >, CompareNoOfAs > q;

    q.push({1, 0, 0, SELECTCOPYPASTE});

    while (!q.empty())
    {
        Node n = q.top();
        q.pop();

        if (n.noOfAs >= 100000)
        {
            cout << n.steps << endl;
            break;
        }

        switch (n.mode)
        {
        case SELECTCOPYPASTE:
            q.push({n.noOfAs * 2, n.steps + 3, n.noOfAs, PASTE});
            break;
        case PASTE:
            q.push({n.noOfAs, n.steps, n.noOfAsCopied, SELECTCOPYPASTE});
            q.push({n.noOfAs + n.noOfAsCopied, n.steps + 1, n.noOfAsCopied, PASTE});
            break;
        }
    }

    return 0;
}
