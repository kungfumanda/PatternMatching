#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

#define ull unsigned long long

vector<vector<ull>> masks;
vector<vector<ull>> matchs;
vector<vector<ull>> prevs;
vector<ull> temp;
vector<ull> mask;
int ascii_l = 256;
int sz;
int err_wu;
ull literal;

vector<string> wunamberPatList;

void orr(vector<ull> &mas, vector<ull> &nas){
    for(int i=0 ; i<sz ; i++) {           
        mas[i] |= nas[i];                      
    }
}

void shift(vector<ull> &mas){
    mas[0] <<= 1;
    for(int i=1;i<sz;i++) {
        mas[i-1] |= mas[i] >> 63;               
        mas[i] <<= 1; 
    }
}

void andd(vector<ull> &mas, vector<ull> &nas){
    for(int i=0 ; i<sz ; i++) {           
        mas[i] &= nas[i];                      
    }
}

vector<ull>& generateMatch(char c) {
    // Read next char and process next bitmap
    vector<ull> &match = matchs[0];
    
    for(int i=0; i<err_wu; i++){ //changes the prev
        for(int j=0; j<sz; j++) {
            prevs[i][j] = matchs[i][j];
        }
    }
    
    mask = masks[c];
    if(mask.size() == 0) {
        vector<ull> aux(sz, -1);
        match.assign(aux.begin(), aux.end());
    }else {
        // Shift or on match
        shift(match);
        orr(match, mask);
    }
    for (int r=1; r<=err_wu; r++) {
        vector<ull> &prev = prevs[r-1];
        vector<ull> &matchR = matchs[r];
        if(mask.size() == 0){
            vector<ull> aux(sz, -1);
            matchR.assign(aux.begin(), aux.end());
        }else {
            // Shift or on matchR
            shift(matchR);
            orr(matchR, mask);
        }
        
        for (int i=0; i < sz; i++) {
            temp[i] = matchs[r-1][i];
        }
        shift(temp);
        andd(matchR,temp);
        andd(matchR,prev);
        shift(prev);
        andd(matchR, prev);
        if(r == err_wu) {
            return matchR;
        }
    }

    return match;
}

void setPatternWu(string pat, int err = 0) {

    sz = (((int)(pat.size() - 1)) >> 6) + 1;
    literal = 1ll << ((pat.size()-1)%64);
    vector<ull> mask(sz, -1);
    mask[sz-1] = -2;

    masks = vector<vector<ull>>(256);

    for (char c : pat) {
        vector<ull> &aux = masks[c];

        if(aux.size()==0) {
            masks[c] = vector<ull>(sz, -1);
            aux = masks[c];
        }

        for(int i=0 ; i<sz ; i++) {   //and        
            aux[i] &= mask[i];
        }
        shift(mask);
        mask[sz-1] |= 1; // checar se deveria ser dentro do for    
    }
}

void wuuSetUpSearch() {
    matchs = vector<vector<ull>>(err_wu+1, vector<ull>(sz, -1));
    prevs = vector<vector<ull>>(err_wu+1, vector<ull>(sz, -1));
    temp = vector<ull>(sz);

    for(int i=1; i <= err_wu;i++) {
        matchs[i][sz-1] <<= i;
    }
}

int searchWu(const string& txt) {
    matchs = vector<vector<ull>>(err_wu+1, vector<ull>(sz, -1));
    prevs = vector<vector<ull>>(err_wu+1, vector<ull>(sz, -1));
    temp = vector<ull>(sz);
    
    for(int i=1; i<err_wu+1;i++) {
        matchs[i][sz-1] <<= i;
    }

    // starts for char
    for(char c: txt) {
        vector<ull> &match = generateMatch(c);
        if(~match[0] & literal) {
            return 1;
        }
    }  // ends for char
    return 0;
}

int wumSearch(const string &txt, const string &pat, int err = 0) {
    setPatternWu(pat, err);
    err_wu = err;
    return searchWu(txt);
}

void wumAddPattern(const string& pat, int err = 0) {
    err_wu = err;
    wunamberPatList.push_back(pat);
}

int wumMatchPattern (const string &txt, int err = 0) {
    for (string pat: wunamberPatList) {
        if (wumSearch(txt, pat, err)) {
            return 1;
        }
    }
    return 0;
}
