#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> bruteMatchPattern(const string &txt, const string &pat, int err = 0) {
  int freq = 0, n = txt.size(), m = pat.size();
  vector<int> ans;
  for(int i = 0; i < n - m; i++) {
    int total_err = 0;
    for(int j = 0; j < m; j++) {
      total_err = total_err + (txt[i + j] != pat[j]);
    }
    if (total_err <= err) {
      ans.push_back(i);
    }
  }
  return ans;
}
