#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned long long** masks;
int ascii_l = 256;
int sz;
int err;
unsigned long long literal;


void orr(unsigned long long* mas, unsigned long long* nas){
    for(int i=0 ; i<sz ; i++) {           
            mas[i] |= nas[i];                      
        }  
}

void shift(unsigned long long* mas){
    mas[0] <<= 1;
    
    for(int i=1;i<sz;i++) {
        mas[i-1] |= mas[i] >> 63;               
        mas[i] <<= 1; 
    }
}

void shiftOr(unsigned long long* mask, unsigned long long* charmask, int len) {
    if (mask == NULL) {
       memset(charmask, -1, len);
    } else {
        shift(charmask);
        orr(mask, charmask);
    }
}


void andd(unsigned long long* mas, unsigned long long* nas){
    for(int i=0 ; i<sz ; i++) {           
            mas[i] &= nas[i];                      
        }  
}

void setPattern(string pat, int err) {

    if(masks != NULL) {
        cout<<"nnn"<<endl;
    }

    sz = ((pat.size() -1) >> 6) + 1;
    literal = 1ll << (pat.size()%64);
    unsigned long long mask[sz];
    memset(mask, -1, sz*sizeof(unsigned long long));
    mask[sz-1] = -2;

    masks = new unsigned long long*[256];
    memset(masks,0,ascii_l*sizeof(unsigned long long*));
    cout<<ascii_l*sizeof(unsigned long long*)<<endl;

    for (char c : pat) {
        unsigned long long* aux = masks[c];
        
        if (aux == NULL){
            masks[c] = new unsigned long long[sz];
            aux = masks[c];
            memset(aux, -1, ascii_l*sizeof(unsigned long long));
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

int search(const string& txt) {
    unsigned long long matchs[err+1][sz];
    unsigned long long prevs[err+1][sz];
    unsigned long long temp[sz+1];
    unsigned long long* match;
    
    int aux = sz * sizeof(unsigned long long);

    memset(matchs, -1, (err+1)*sz*sizeof(unsigned long long));

    for(int i=1; i<err+1;i++) {
        matchs[i][sz-1] <<= i;
    }

    for(char c: txt) {
        unsigned long long* match;
        matchs[0]; //starts compute
        
        for(int i=0; i<err; i ++){ //changes the prev
            for(int j=0; j<sz; j++) {
                prevs[i][j] = matchs[i][j];
            }
        }
        
        unsigned long long* mask = masks[c];
        shiftOr(mask, match, aux);

        for (int r=1; r<(err+1);r++) {
            unsigned long long* prev = prevs[r-1];
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
              
        }       //ends compute
        
        if(~match[0] & literal) {
            return 1;
        }
    }  // ends for char

    //starts compute        
    for(int i=0; i<err; i ++){ //changes the prev
        for(int j=0; j<sz; j++) {
            prevs[i][j] = matchs[i][j];
        }
    }
    
    unsigned long long* mask = masks['\n'];
    shiftOr(mask, match, aux);

    for (int r=1; r<(err+1);r++) {
        unsigned long long* prev = prevs[r-1];
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
            
    }       //ends compute
    
    if(~match[0] & literal) {
        return 1;
    }

    return 0;

}


int WumSearch(const string &txt, const string &pat, int err = 0) {
    //cout<<"aa"<<endl;
    setPattern(pat, err);
    return search(txt);
}

int main() {
    //cout<<"aa"<<endl;
    string txt = "abazzzzzzzcaba";
    string pat = "aba";
    int ans = WumSearch(txt, pat, 0);
    cout<<ans<<endl;
}