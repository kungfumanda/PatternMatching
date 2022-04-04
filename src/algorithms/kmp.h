#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> getBorder(string str) {
  int n = str.size();
  vector<int> border(n, -1);
  for(int i = 1, j = -1; i < n; i++) {
    while(j >= 0 && str[i] != str[j + 1]) {
      j = border[j];
    }
    if(str[i] == str[j + 1]) {
      j++;
    }
    border[i] = j;
  }
  return border;
}

vector<int> kmpMatchPattern(const string &txt, const string &pat, const vector<int> &border) {
  int freq = 0;
  vector<int> ans;
  for(int i = 0, j = -1; i < txt.size(); i++) {
    while(j >= 0 && txt[i] != pat[j + 1]) {
      j = border[j];
    }
    if(pat[j + 1] == txt[i]) {
      j++;
    }
    if(j + 1 == (int) pat.size()) {
      //found occurence
      ans.push_back(i - pat.size() + 1);
      freq++;
      j = border[j];
    }
  }
  return ans;
}

vector<int> kmpMatchPattern (const string &txt, const string &pat) {
  vector<int> border = getBorder(txt);
  return kmpMatchPattern(txt, pat, border);
}
