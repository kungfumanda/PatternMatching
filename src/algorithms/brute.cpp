#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> bruteMatchPattern(const string &txt, const string &pat) {
  int freq = 0, n = txt.size(), m = pat.size();
  vector<int> ans;
  for(int i = 0; i < n - m; i++) {
    bool oc = true;
    for(int j = 0; j < m; j++) {
      oc = oc && (txt[i + j] == pat[j]);
    }
    if (oc) {
      ans.push_back(i);
    }
  }
  return ans;
}

int main() {
  vector<int> occ = bruteMatchPattern("abracadabrabrabrabrabrabrabrabrabrabra","abra");
  for (int x: occ) {
    cout<<x<<endl;
  }
  cout<<occ.size()<<endl;
}