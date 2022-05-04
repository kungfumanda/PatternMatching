#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <utility>

#define pii pair<int,int>

using namespace std;

string text;
string pat;

vector<int> sort_letters(string &txt) {
  int n = txt.size();
  set<int> chars;
  for(unsigned char c : txt) {
    chars.insert(c);
  }
  map<int, int> pos;
  int cur_pos = 0;
  while(chars.size()) {
    int cur_value = *chars.begin();
    chars.erase(cur_value);
    pos[cur_value] = cur_pos++;
  }

  vector<int> ans;
  for(unsigned char c: txt) {
    ans.push_back(pos[c]);
  }
  return ans;
}

vector<vector<int>> build_pos(string &txt) {
  int n = txt.size(), cur_sz = 1, cur_pot = 1;
  vector<vector<int>> pos;
  vector<vector<pair<pii, int>>> pos_order;

  vector<int> cur_pos = sort_letters(txt);
  pos.push_back(cur_pos);

  while(cur_pot < n) {
    vector<pair<pii, int>> next_val;
    for(int i = 0; i<n; i++) {
      int next_pos = i + cur_pot;
      next_val.push_back(make_pair(make_pair(pos[cur_sz-1][i], next_pos < n ? pos[cur_sz-1][next_pos] : -1), i));
    }
    sort(next_val.begin(), next_val.end());
    for(auto x: next_val) {
      pii y = x.first;
      cout<<y.first<<','<<y.second<<' ';
    }
    cout<<endl;
    vector<int> next_pos(n, 0);
    int cur_pos = 0;
    for(int i = 1; i<n; i++) {
      pii curp = next_val[i].first;
      pii prevp = next_val[i - 1].first;
      int cur_id = next_val[i].second;
      if(curp != prevp) {
        cur_pos ++;
      }
      next_pos[cur_id] = cur_pos;
    }
    pos.push_back(next_pos);

    cur_pot = cur_pot*2;
    cur_sz = cur_sz+1;
  }
  return pos;
}

vector<int> build_sarr(vector<int> &last_pos) {
  int n = last_pos.size();
  vector<int> sa(n, 0);
  for(int i = 0; i<n; i++) {
    sa[last_pos[i]] = i;
  }
  return sa;
}

bool is_first(const int &pos1, const string &pat) {
  int n = text.size();
  int m = pat.size();
  int i = pos1, j = 0;
  for( ; i < n && j < m; i++, j++) {
    if(text[i] != pat[j]) {
      return text[i] < pat[j];
    }
  }
  return j != m;
}

bool is_after(const int &pos1, const string &pat) {
  int n = text.size();
  int m = pat.size();
  int i = pos1, j = 0;
  for( ; i < n && j < m; i++, j++) {
    if(text[i] != pat[j]) {
      return text[i] < pat[j];
    }
  }
  return 1;
}

int search_sarr(string& pat, vector<int> &sarr) {
  int lower = lower_bound(sarr.begin(), sarr.end(), pat, is_first) - sarr.begin();
  int upper = lower_bound(sarr.begin(), sarr.end(), pat, is_after) - sarr.begin();
  if (upper >= lower) {
    return upper - lower;
  }else {
    return 0;
  }
}

int main() {
  string txt = "abracadabra";
  text = txt;
  pat = "ra";
  vector<vector<int>> pos = build_pos(txt);
  vector<int> sarr = build_sarr(pos[pos.size()-1]);
  
  for(auto x: pos) {
    for(auto y: x) {
      cout<<y<<' ';
    }
    cout<<endl;
  }
  for(auto x: sarr) {
    cout<<txt.substr(x, txt.size() - x)<<endl;
  }
  cout<<endl;
  for(int i = 0; i<txt.size(); i++) {
    cout<<is_first(sarr[i], pat)<<", ";
  }
  cout<<endl;
  for(int i = 0; i<txt.size(); i++) {
    cout<<is_after(sarr[i], pat)<<", ";
  }
  cout<<endl;
  int l = search_sarr(pat, sarr);
  cout<<l<<endl;

  return 0;
}