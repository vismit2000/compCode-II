#include <bits/stdc++.h>
using namespace std;

class Node
{
    string directoryName;
    vector <Node*> subDirectories;
public:
    Node(string name)
    {
        directoryName = name;
        subDirectories.clear();
    }

    int mkdir(string path)
    {
        //base case
        if(path == "")
            return 0;
        vector <string> splitPath = splitUpPath(path);

        //Check if subdirectory already exists
        for(Node* directory : subDirectories)
        {
            if(directory->directoryName == splitPath[0])
                return directory->mkdir(splitPath[1]);
        }

        //Create subdirectory
        Node *node = new Node(splitPath[0]);
        subDirectories.push_back(node);
        return 1 + node->mkdir(splitPath[1]);
    }

    vector <string> splitUpPath(string path)
    {
        vector<string> ret;
        path = path.substr(1);
        size_t index = path.find("/");
        if(index == string::npos)
        {
            ret.push_back(path);
            ret.push_back("");
        }
        else
        {
            ret.push_back(path.substr(0, index));
            ret.push_back(path.substr(index));
        }
        return ret;
    }
};

int main() 
{
    int t;
    cin>>t;
    for(int q = 1; q<= t; q++)
    {
        cout<<"Case #"<<q<<": ";
        int N, M;
        cin>>N>>M;
        string path;
        Node *root = new Node("");
        while(N--)
        {
            cin>>path;
            root->mkdir(path);
        }
        int ans = 0;
        while(M--)
        {
            cin>>path;
            ans += root->mkdir(path);
        }
        cout<<ans<<endl;
    }
    return 0;
}
