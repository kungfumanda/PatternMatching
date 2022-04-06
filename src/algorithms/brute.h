#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> bruteForcePatts;
int brute_err = 0;

vector<int> bruteMatchPattern(const string &txt, const string &pat) {
  int freq = 0, n = txt.size(), m = pat.size();
  int min_correct = pat.size() - brute_err;
  vector<int> ans;
  for(int i = 0; i < n - m + 1; i++) {
    bool found_error = 0;
    for(int j = 0; j < m && !found_error ; j++) {
      found_error |= (txt[i + j] != pat[j]);
    }
    if(!found_error) {
      ans.push_back(i);
    }
  }
  return ans;
}

void bruteAddPatternListAndError(vector<string> &pats, int error) {
  brute_err = error;
  bruteForcePatts.assign(pats.begin(), pats.end());
}

int bruteMatchPatternList(const string &text) {
  for(string pat: bruteForcePatts) {
    if (!bruteMatchPattern(text, pat).empty()) {
      return 1;
    }
  }
  return 0;
}
