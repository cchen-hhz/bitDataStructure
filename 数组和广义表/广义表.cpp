#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

typedef enum { ATOM, LIST } Elemtype;

struct GLNode {
    Elemtype tag;
    char atom;
    GLNode *head;
    GLNode *tail;
    GLNode(Elemtype t = LIST) : tag(t), atom(0), head(nullptr), tail(nullptr) {}
};

typedef struct GLNode GList;

void GetSubstr(string &substr, string &headstr) {
    string s;
    headstr.clear();
    int flag = 0;
    size_t i = 0;
    while (i < substr.size() && (substr[i] != ',' || flag != 0)) {
        if (substr[i] == '(') flag++;
        else if (substr[i] == ')') flag--;
        headstr.push_back(substr[i]);
        ++i;
    }
    if (i < substr.size() && substr[i] == ',') ++i;
    while (i < substr.size()) {
        s.push_back(substr[i]);
        ++i;
    }
    substr = s;
}

GList *GListcreat(const string &s_in) {
    string s = s_in;
    GList *G;
    GList *p;
    GList *q;
    int len = (int)s.length();
    string substr;
    string headstr;
    if (len == 0 || s == "()") {
        G = NULL;
    } else if (len == 1) {
        G = (GList*)malloc(sizeof(GList));
        G->tag = ATOM;
        G->atom = s[0];
        G->head = NULL;
        G->tail = NULL;
    } else {
        G = (GList*)malloc(sizeof(GList));
        G->tag = LIST;
        p = G;
        string content = s.substr(1, len - 2);
        substr = content;
        while ((int)substr.size() > 0) {
            GList *r;
            GetSubstr(substr, headstr);
            r = GListcreat(headstr);
            p->head = r;
            q = p;
            int newlen = (int)substr.length();
            if (newlen > 0) {
                p = (GList*)malloc(sizeof(GList));
                p->tag = LIST;
                q->tail = p;
            }
        }
        q = p;
        q->tail = NULL;
    }
    return G;
}

void GListPrint(GList *G) {
    GList *p;
    GList *q;
    if (G && G->tag == ATOM) {
        cout << G->atom;
    } else {
        cout << '(';
        while (G) {
            p = G->head;
            q = G->tail;
            if (p && q && p->tag == ATOM) {
                cout << p->atom << ',';
                p = q->head;
                q = q->tail;
            }
            if (p != NULL && !q && p->tag == ATOM) {
                cout << p->atom;
                G = q;
            } else {
                if (!p)
                    cout << "()";
                else
                    GListPrint(p);
                if (q) cout << ',';
                G = q;
            }
        }
        cout << ')';
    }
}

GList *Freelist(GList *G, int n) {
    GList *p;
    if (n == 1) {
        p = G->head;
        G->tail = NULL;
        G = NULL;
        cout << "destroy tail" << endl;
        cout << "free list node" << endl;
    } else if (n == 2) {
        p = G->tail;
        G->head = NULL;
        G = NULL;
        cout << "free head node" << endl;
        cout << "free list node" << endl;
    } else
        exit(0);
    return p;
}

int main() {
    string assistStr;
    cin >> assistStr;
    GList *G;
    int choose;
    G = GListcreat(assistStr);
    cout << "generic list: ";
    GListPrint(G);
    cout << endl;
    while (G && G->tag == LIST) {
        cin >> choose;
        switch (choose) {
            case 1:
                G = Freelist(G, 1);
                cout << "generic list: ";
                GListPrint(G);
                cout << endl;
                break;
            case 2:
                G = Freelist(G, 2);
                cout << "generic list: ";
                GListPrint(G);
                cout << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}