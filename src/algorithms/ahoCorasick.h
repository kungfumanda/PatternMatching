#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const int charSize = 256;
vector<int> fail, terminal;
vector<vector<int>> trie;

void addPatternAho(string s) {  
  int node = 0, pos = 0;
  for (char c: s) {
    if (trie[node][c] == -1) {
      trie[node][c] = trie.size();
      trie.push_back(vector<int>(charSize,-1));
      fail.push_back(0);
      terminal.push_back(0);
    }
    node = trie[node][c];
  }
  if(terminal.size() == node) {
    terminal.push_back(1);
  }else {
    terminal[node] = 1;
  }
}

void addFails(){
  queue<int> q;
  q.push(0);
  while(!q.empty()) {
    int node = q.front();
    q.pop();
    for(int c=0; c<charSize; c++){
      int &val = trie[node][c];
      int f = node == 0 ? 0 : trie[fail[node]][c];
      if (val == -1) {
        val = f;
      } else {
        fail[val] = f;
        q.push(val);
      }
    }
  }
}

int ahoSearch(const string &s) {
  int node = 0;
  for(char c: s) {
    node = trie[node][c];
    if(terminal[node]) {
      return 1;
    }
  }
  return 0;
}


void ahoClearData() {
  fail.clear();
  terminal.clear();
  trie.clear();
  trie.push_back(vector<int>(256, -1));
}

int ahoCorasickMatchPattern(const string &txt, const string &pat) {
  ahoClearData();
  addPatternAho(pat);
  addFails();
  return ahoSearch(txt);
}
