#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> getBorder(string pat) {
  int n = pat.size();
  vector<int> border(n, -1);
  for(int i = 1, j = -1; i < n; i++) {
    while(j >= 0 && pat[i] != pat[j + 1]) {
      j = border[j];
    }
    if(pat[i] == pat[j + 1]) {
      j++;
    }
    border[i] = j;
  }
  return border;
}

int kmpMatchPattern(const string &txt, const string &pat, const vector<int> &border) {
  for(int i = 0, j = -1; i < txt.size(); i++) {
    while(j >= 0 && txt[i] != pat[j + 1]) {
      j = border[j];
    }
    if(pat[j + 1] == txt[i]) {
      j++;
    }
    if(j + 1 == pat.size()) {
      return 1;
    }
  }
  return 0;
}

int kmpMatchPattern (const string &txt, const string &pat) {
  vector<int> border = getBorder(pat);
  return kmpMatchPattern(txt, pat, border);
}
