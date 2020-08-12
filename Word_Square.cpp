// https://leetcode.com/problems/valid-word-square/
// https://techdevguide.withgoogle.com/resources/former-coding-interview-question-word-squares/?types=coding-interview-question#code-challenge

class Solution{
public:
	int n;
	unordered_map < string, vector < string > > mp;
	vector < string > square;
	vector < vector < string > > squares;

	void build(int i){
		if(i == n){
			squares.push_back(square);
			return;
		}
		string prefix;
		for(int k = 0; k < i; k++)
			prefix += square[k][i];
		for(string word : mp[prefix]){
			square[i] = word;
			build(i+1);
    }

	vector < vector < string > > wordSquaes(vector < string > &words){
		n = words[0].size();
		square.resize(n);
		for(string word : words)
			for(int i = 0; i < n; i++)
				mp[word.substr(0, i)].push_back(word);
		
        build(0);
        return squares;
    }
};
