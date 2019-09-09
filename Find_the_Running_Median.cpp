//Problem: https://www.hackerrank.com/challenges/find-the-running-median/problem
//Solution Approach: https://stackoverflow.com/questions/10657503/find-running-median-from-a-stream-of-integers

#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the runningMedian function below.
 */
vector<double> runningMedian(vector<int> a) 
{
    vector <double> ans;
    ans.push_back(a[0]/1.0);
    int n = a.size();
    if(n == 1)
        return ans;

    ans.push_back((a[0]/1.0 + a[1])/2);

    priority_queue <int> maxHeap;
    priority_queue < int, vector <int>, greater <int> > minHeap;

    maxHeap.push(min(a[0], a[1]));
    minHeap.push(max(a[0], a[1]));

    for(int i = 2; i < n; i++)
    {
        if(a[i] < maxHeap.top())
            maxHeap.push(a[i]);
        else
            minHeap.push(a[i]);

        //Balance the heaps

        int temp;

        if(maxHeap.size() == minHeap.size()-2)
        {
            temp = minHeap.top();
            minHeap.pop();
            maxHeap.push(temp);
        }
        else if(minHeap.size() == maxHeap.size()-2)
        {
            temp = maxHeap.top();
            maxHeap.pop();
            minHeap.push(temp);
        }

        if(maxHeap.size() == minHeap.size())
            ans.push_back((maxHeap.top()/1.0 + minHeap.top())/2);
        else if(maxHeap.size() > minHeap.size())
            ans.push_back(maxHeap.top()/1.0);
        else
            ans.push_back(minHeap.top()/1.0);
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }

    vector<double> result = runningMedian(a);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
