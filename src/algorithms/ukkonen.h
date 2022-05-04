#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// Char size
const int char_count = 256;
const int max_patt_size = 1000;
// Finish nodes
unordered_set<int> F[max_patt_size];
// Transitions
unordered_map<int, int> tree[max_patt_size][char_count];
vector<string> ukkonenPatList;
string pattern;
int pattern_size;
int pattern_count = 0;
int err_ukk;

void ukkonenAddPattern(string s, int err_ukkor = 0) {
  int pat_id = pattern_count++;
  ukkonenPatList.push_back(s);
  err_ukk = err_ukkor;
  pattern = s;
  pattern_size = pattern.size();

  vector<int> state;
  for(int i = 0, sze = s.length(); i <= sze; i++) {
    state.push_back(i);
  }

  queue<int> q;
  map<int, vector<int>> state_map;
  map<vector<int>, int> rev_state_map;
  state_map[1] = state;
  rev_state_map[state] = 1;
  q.push(1);
  int next_free_id = 2;
  while(!q.empty()) {
    int now = q.front();
    q.pop();
    state = state_map[now];
    for(int i = 0; i < char_count; i++) { 
      // Build next state vector
      vector<int> next_state;
      next_state.push_back(0);
      for(int j = 1; j <= pattern_size; j++) {
          unsigned char cur_char = pattern[j-1];
          next_state.push_back(min(min(state[j] + 1, state[j-1] + (i != cur_char)), min(err_ukk+1, next_state[j-1]+1)));
      }

      // Search rev state map for new discovered state, if 0 its a new one.
      int next_state_id = rev_state_map[next_state];

      if(!next_state_id) {
        // New state found, adding it to queue
        rev_state_map[next_state] = next_free_id;
        state_map[next_free_id] = next_state;
        next_state_id = next_free_id++;
        q.push(next_state_id);
      }
      // Add this state as answer state if num errors to achieve is less then edit distance
      if(next_state[pattern_size] <= err_ukk) {
        F[pat_id].insert(next_state_id);
      }

      // Update tree with next state
      tree[pat_id][i][now] = next_state_id;
    }
  }
}

vector<int> searchUkk(const string& txt, int pat_id) {
  int state = 1, occ = 0;
  vector<int> ans;
  for(int i = 0; i < txt.size(); i++) {
    state = tree[pat_id][txt[i]][state];
    if(F[pat_id].count(state)){
      ans.push_back(i);
    }
  }
  return ans;
}

void ukkClearData() {
  pattern_count = 0;
  ukkonenPatList.clear();
  for(int j = 0; j<max_patt_size; j++) {
    F[j].clear();
    for(int i = 0; i<char_count; i++) {
      tree[j][i].clear();
    }
  }
}

vector<int> ukkMatchPattern(const string &txt, int pat_id) {
  vector<int> end_pat = searchUkk(txt, pat_id);
  vector<int> ans;
  for(int end: end_pat) {
    ans.push_back(end - ukkonenPatList[pat_id].size() + 1);
  }
  return ans;
}

int ukkonenMatchPattern(string &txt) {
  for(int i = 0; i<pattern_count; i++) {
    if (!ukkMatchPattern(txt, i).empty()) {
      return 1;
    }
  }
  return 0;
}
