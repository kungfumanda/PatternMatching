#include <iostream>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <vector>

using namespace std;
typedef int ukkState;

set<ukkState> F;
const int delta_size = 256;
map<ukkState, ukkState> delta[delta_size];
string pattern;
int pattern_size;
int err;

vector<int> make_transition(const vector<int>& base, int chr) {
  vector<int> state = vector<int>(pattern_size + 1, 0);
  for(int i = 1; i <= pattern_size; i++) {
      state[i] = min(min(base[i] + 1, base[i-1] + (chr != pattern[i-1] ? 1 : 0)), min(err+1, state[i-1]+1));
  }
  return state;
}

void clearData() {
  F.clear();
  for(int i = 0; i < delta_size; i++){
    delta[i].clear();
  }
}

void setPattern(string s, int error = 0) {
  err = error;
  pattern = s;
  pattern_size = pattern.size();
  clearData();

  vector<int> state;
  for(int i = 0, sze = s.length(); i <= sze; i++) {
    state.push_back(i);
  }

  queue<int> q;
  map<ukkState, vector<int> > stateMap;
  map<vector<int>, ukkState > revStateMap;
  stateMap[1] = state;
  revStateMap[state] = 1;
  q.push(1);
  int next_free_id = 2;
  while(!q.empty()) {
    int now = q.front();
    q.pop();
    state = stateMap[now];
    for(int i = 0; i < delta_size; i++) { 
      auto next_state = make_transition(state, i);
      int next_state_id = revStateMap[next_state];

      if(!next_state_id) {
        revStateMap[next_state] = next_free_id;
        stateMap[next_free_id] = next_state;
        next_state_id = next_free_id++;
        q.push(next_state_id);
      }

      if(next_state[pattern_size] <= err) {
        F.insert(next_state_id);
      }

      delta[i][now] = next_state_id;
    }
  }
}

vector<int> search(const string& txt) {
  int state = 1, occ = 0;
  vector<int> ans;
  for(int i = 0; i < txt.size(); i++) {
    state = delta[txt[i]][state];
    if(F.count(state)){
      ans.push_back(i);
    }
  }
  return ans;
}

vector<int> ukkMatchPattern(const string &txt, const string &pat, int err = 0) {
  clearData();
  setPattern(pat, err);
  vector<int> end_pat = search(txt);
  vector<int> ans;
  for(int end: end_pat) {
    ans.push_back(end - pat.size() + 1);
  }
  return ans;
}

int main() {
  string txt = "abazzzzzzzcaba";
  string pat = "aba";
  vector<int> ans = ukkMatchPattern(txt, pat, 1);
  for (int x: ans) {
    cout<<x<<endl;
  }
}