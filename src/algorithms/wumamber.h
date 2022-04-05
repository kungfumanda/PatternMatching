#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

#define ull unsigned long long

vector<vector<ull>> masks;
int ascii_l = 256;
int sz;
int err_wu;
ull literal;

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

void shiftOr(vector<ull> &mask, vector<ull> &charmask, int &len) {
    if(mask.size() == 0){
        mask = vector<ull>(sz, -1);
    }else {
        shift(charmask);
        orr(mask, charmask);
    }
}

void andd(vector<ull> &mas, vector<ull> &nas){
    for(int i=0 ; i<sz ; i++) {           
        mas[i] &= nas[i];                      
    }  
}

vector<ull>  generateMatch(int c, vector<vector<ull>> &matchs, vector<vector<ull>> &prevs, vector<ull> &temp, int aux, int err_wu, int sz) {
    vector<ull> &match = matchs[0]; //starts compute
        
    for(int i=0; i<err_wu; i ++){ //changes the prev
        for(int j=0; j<sz; j++) {
            prevs[i][j] = matchs[i][j];
        }
    }
    
    vector<ull> &mask = masks[c];
    shiftOr(mask, match, aux);
    for (int r=1; r<(err_wu+1);r++) {
        vector<ull> &prev = prevs[r-1];
        match = matchs[r];
        shiftOr(mask,match,aux);
        
        for (int i=0; i < sz; i++) {
            temp[i] = matchs[r-1][i];
        }
        shift(temp);
        andd(match,temp);
        andd(match,prev);
        shift(prev);
        andd(match, prev);
    }

    return match;
}

void setPatternWu(string pat, int err_wu) {

    sz = ((pat.size() -1) >> 6) + 1;
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
        
        mask[0] <<= 1;                            //shift
        for(int i=1 ; i<sz ; i++) {           
            mask[i-1] |= mask[i] >> 63;               
            mask[i] <<= 1;                         
        }
        mask[sz-1] |= 1; // checar se deveria ser dentro do for    
    }
}

int searchWu(const string& txt) {
    vector<vector<ull>> matchs(err_wu+1, vector<ull>(sz, -1));
    vector<vector<ull>> prevs(err_wu+1, vector<ull>(sz, -1));
    vector<ull> temp(sz, -1);
    
    int aux = sz * sizeof(ull);

    for(int i=1; i<err_wu+1;i++) {
        matchs[i][sz-1] <<= i;
    }

    for(char c: txt) {
        vector<ull> match = generateMatch(c, matchs, prevs, temp, aux, err_wu, sz);
        
        if(~match[0] & literal) {
            return 1;
        }
    }  // ends for char

    vector<ull> match = generateMatch('\n', matchs, prevs, temp, aux, err_wu, sz); 
    
    if(~match[0] & literal) {
        return 1;
    }
    return 0;
}


int wumSearch(const string &txt, const string &pat, int err_wu = 0) {
    //cout<<"aa"<<endl;
    setPatternWu(pat, err_wu);
    return searchWu(txt);
}
