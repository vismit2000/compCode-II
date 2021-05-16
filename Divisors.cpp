const int nax = 1e6 + 5;
vector<int> divisors[nax];

for(int n = 2; n < nax; ++n) {
  for(int x = 2 * n; x < nax; x += n) {
    divisors[x].push_back(n);
  }
}
