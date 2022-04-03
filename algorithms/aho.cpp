#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> fail, word;
vector<vector<int>> transition;

void setPattern(string s, int err = 0) {  
  int node = 0, pos = 0;
  while(true){
    if (pos == s.size()) {
      word[node] = 1;
      break;
    } else {
      char c = s[pos];
      if (transition[node][c] == -1) {
        transition[node][c] = transition.size();
        transition.push_back(vector<int>(256,-1));
        fail.push_back(0);
        word.push_back(0);
      }
      node = transition[node][c];
      pos++;
    }
  }
}

void clearData() {
  fail.clear();
  word.clear();
  transition.clear();
  transition.push_back(vector<int>(256,-1));
  word.push_back(0);
  fail.push_back(0);
}

void prepare(){
  queue<int> q;
  for(auto s: transition[0]) {
    if(s != -1) {
      q.push(s);
    }
  }
  while(!q.empty()) {
    int s = q.front();
    q.pop();
    for(int c=0;c<256;c++){
      if (transition[s][c] != -1) {
        int s2 = transition[s][c];
        q.push(s2);
        int f = fail[s];
        while(transition[f][c]!=-1 && f) {
          f = fail[f];
        }
        if(transition[f][c] == -1)
          fail[s2] = 0;
        else
          fail[s2] = transition[f][c];
      }
    }
  }
}

vector<int> search(string s) {
  int state = 0;
  vector<int> ans;
  for(int i = 0; i < s.size(); i++) {
    while(state && transition[state][s[i]]==-1)
      state = fail[state];
    if(transition[state][s[i]]!=-1)
      state = transition[state][s[i]];
    if(word[state])
      ans.push_back(i); 
  }
  cout<<"size and search: "<<ans.size()<<endl;
  return ans;
}

vector<int> ahoMatchPattern(const string &txt, const string &pat, int err = 3) {
  clearData();
  setPattern(pat, err);
  prepare();
  vector<int> end_pat = search(txt);
  vector<int> ans;
  for(int end: end_pat) {
    ans.push_back(end - pat.size() + 1);
  }
  return ans;
}

int main() {
  string txt = "abacaba";
  string pat = "aba";
  vector<int> occ = ahoMatchPattern(txt, pat, 3);
  for (int x: occ) {
    cout<<x<<endl;
  }
  cout<<occ.size()<<endl;
}