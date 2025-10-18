#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXL = 10010;
const int MAXT = 10010;

struct Tok { 
    int tp; ll v; char o; 
};

int prec(char c){
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/'||c=='%') return 2;
    if(c=='^') return 3;
    return 0;
}
bool rassoc(char c){ return c=='^'; }
bool isop(char c){ return c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='^'; }

char buf[MAXL];
Tok toks[MAXT];
int tn;

bool tokenize(const char *s){
    tn = 0;
    int n = strlen(s), i = 0;
    bool expectNum = true;
    while(i < n){
        char c = s[i];
        if(c==' '||c=='\t' || c=='\r' || c=='\n') { 
            i++; continue; 
        }
        if(c=='(') {
            toks[tn++] = {1,0,'('}; 
            i++; expectNum = true; 
            continue; 
        }
        if(c==')') { 
            toks[tn++] = {1,0,')'}; 
            i++; expectNum = false; 
            continue; 
        }
        if(isop(c)){
            if(expectNum){
                if(c=='+'||c=='-'){
                    int j = i; bool neg = (s[j]=='-'); if(s[j]=='+'||s[j]=='-') j++;
                    if(j<n && isdigit((unsigned char)s[j])){
                        ll x=0;
                        while(j<n && isdigit((unsigned char)s[j])) x = x*10 + (s[j++]-'0');
                        if(neg) x = -x;
                        toks[tn++] = {0,x,0};
                        i = j; expectNum = false;
                        continue;
                    } else return false; 
                } else {
                    return false; 
                }
            } else {
                toks[tn++] = {1,0,c};
                i++; expectNum = true;
                continue;
            }
        }
        if(isdigit((unsigned char)c)){
            int j=i; ll x=0;
            while(j<n && isdigit((unsigned char)s[j])) x = x*10 + (s[j++]-'0');
            toks[tn++] = {0,x,0};
            i=j; expectNum = false; continue;
        }
        return false;
    }
    return true;
}


Tok pst[MAXT];
int pn;

bool toPost(){
    pn = 0;
    char st[MAXT]; int sp = -1;
    for(int i=0;i<tn;i++){
        Tok t = toks[i];
        if(t.tp==0) pst[pn++] = t;
        else{
            char c = t.o;
            if(c=='(') st[++sp]=c;
            else if(c==')'){
                bool f=false;
                while(sp>=0){
                    char tt = st[sp--];
                    if(tt=='('){ f=true; break; }
                    pst[pn++] = {1,0,tt};
                }
                if(!f) return false;
            } else if(isop(c)){
                while(sp>=0 && st[sp]!='('){
                    char top = st[sp];
                    int p1 = prec(top), p2 = prec(c);
                    if(p1>p2 || (p1==p2 && !rassoc(c))){ pst[pn++] = {1,0,top}; sp--; }
                    else break;
                }
                st[++sp]=c;
            } else return false;
        }
    }
    while(sp>=0){
        char tt = st[sp--];
        if(tt=='('||tt==')') return false;
        pst[pn++] = {1,0,tt};
    }
    return true;
}

bool powSafe(ll a, ll b, ll &r){
    if(b<0) return false;
    ll res = 1;
    ll base = a;
    while(b){
        if(b&1) res = res * base;
        b >>= 1;
        if(b) base = base * base;
    }
    r = res; return true;
}

int main(){
    int N;
    if(scanf("%d\n",&N)!=1) return 0;
    for(int tc=0; tc<N; ++tc){
        if(!fgets(buf, MAXL, stdin)){ printf("error.\n"); continue; }
        // remove trailing newline
        int L = strlen(buf);
        while(L>0 && (buf[L-1]=='\n' || buf[L-1]=='\r')) buf[--L]=0;
        if(L==0){ printf("error.\n"); continue; }
        if(!tokenize(buf)){ printf("error.\n"); continue; }
        if(tn==0){ printf("error.\n"); continue; }
        if(!toPost()){ printf("error.\n"); continue; }
        ll stv[MAXT]; int sp = 0;
        bool div0=false, err=false;
        for(int i=0;i<pn;i++){
            Tok t = pst[i];
            if(t.tp==0){ stv[sp++]=t.v; }
            else{
                if(sp<2){ err=true; break; }
                ll b = stv[--sp];
                ll a = stv[--sp];
                ll r=0;
                char o = t.o;
                if(o=='+') r = a + b;
                else if(o=='-') r = a - b;
                else if(o=='*') r = a * b;
                else if(o=='/'){
                    if(b==0){ div0=true; break; }
                    r = a / b;
                } else if(o=='%'){
                    if(b==0){ div0=true; break; }
                    r = a % b;
                } else if(o=='^'){
                    if(!powSafe(a,b,r)){ err=true; break; }
                } else { err=true; break; }
                stv[sp++] = r;
            }
        }
        if(div0){ printf("Divide 0.\n"); continue; }
        if(err || sp!=1){ printf("error.\n"); continue; }
        printf("%lld\n", stv[0]);
    }
    return 0;
}