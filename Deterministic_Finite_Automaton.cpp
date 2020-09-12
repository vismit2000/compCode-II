// https://www.thetopsites.net/article/58803071.shtml
/*
Deterministic finite automaton(DFA) is a finite state machine that accepts/rejects finite strings of symbols and only produces a unique computation (or run) of the automation for each input string.

DFAs can be represented using state diagrams. For example, in the automaton shown below, there are three states: S0, S1, and S2 (denoted graphically by circles). The automaton takes a finite sequence of 0s and 1s as input. For each state, there is a transition arrow leading out to a next state for both 0 and 1. Upon reading a symbol, a DFA jumps deterministically from a state to another by following the transition arrow. For example, if the automaton is currently in state S0 and current input symbol is 1 then it deterministically jumps to state S1. A DFA has a start state (denoted graphically by an arrow coming in from nowhere) where computations begin, and a set of accept states (denoted graphically by a double circle) which help define when a computation is successful.

img

These are some strings above DFA accepts,

0
00
000
11
110
1001
You are given a DFA in input and an integer N. You have to tell how many distinct strings of length N the given DFA accepts. Return answer modulo 109+7.
*/

int Solution::automata(vector<int> &A, vector<int> &B, vector<int> &C, int D, int N) 
{
    int K = A.size();
    int dp[N+1][K];
    
    for(int i = 0; i <= N; i++)
        for(int j = 0; j < K; j++)
            dp[i][j] = 0;
            
    for(int ele : C)
        dp[0][ele] = 1;
        
    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < K; j++)
        {
            //cout << i <<  "  " << j << endl;
            dp[i][j] = (dp[i-1][A[j]] + dp[i-1][B[j]]) % 1000000007;
        }
    }
    
    return dp[N][D];
}
