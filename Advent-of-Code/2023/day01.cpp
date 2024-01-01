#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);


int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n; cin >> n;
    vector < string > v(n);
    for(int i = 0; i < n; i++) cin >> v[i];

    vector < int > a(n, INF), posa(n, INF), b(n, -1), posb(n, -1), calibration(n);
    vector < string > letters {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for(int i = 0; i < n; i++){
        for(int j = 0; j < v[i].length(); j++){
            if(v[i][j] >= '0' && v[i][j] <= '9'){
                if(a[i] == INF) a[i] = v[i][j] - '0', posa[i] = j;
                b[i] = v[i][j] - '0', posb[i] = j;
            }
        }
        for(int j = 0; j < letters.size(); j++){
            int first = v[i].find(letters[j]);
            int last = v[i].rfind(letters[j]);
            if(first != string::npos && first < posa[i]) a[i] = j + 1, posa[i] = first;
            if(last != string::npos && last > posb[i]) b[i] = j + 1, posb[i] = last;
        }
        calibration[i] = a[i] * 10 + b[i];
    }
    cout << accumulate(calibration.begin(), calibration.end(), 0) << endl;
}