#include<bits/stdc++.h>
using namespace std;

bool D(const string& s){
return s=="int" ||s=="float" ||s=="double"|| s=="char"|| s=="void"|| s=="long" || s=="short";
}
bool Id(const string& s){
    if (s.empty() || !(isalpha(s[0]) || s[0] == '_'))
    return false;
    for (int i = 1; i < (int)s.size(); i++)
    if (!(isalnum(s[i]) || s[i] == '_'))
    return false;
return true;
}

string com(const string& l, bool& inBlock){
string s = l;
    if (inBlock){
        size_t end = s.find("*/");
        if (end == string::npos) return "";
        s = s.substr(end + 2);
        inBlock = false;
    }
size_t start = s.find("/*");
    if (start != string::npos) {
        size_t end = s.find("*/", start + 2);
        if (end == string::npos) {
            s = s.substr(0, start);
            inBlock = true;
        } else {
            s = s.substr(0, start) + s.substr(end + 2);
        }
    }
    size_t sl = s.find("//");
    if (sl != string::npos) s = s.substr(0, sl);
    return s;
}
vector<string>tk(const string& line) {
    vector<string> t;
    string cur;

    auto push = [&]() {
        if (!cur.empty()) {
            t.push_back(cur);
            cur.clear();
        }
    };
    for(int i =0;i<(int)line.size(); i++){
        char c = line[i];
        if (isspace(c)){
        push();
            continue;
        }
        if(isalnum(c)||c == '_'){
            cur += c;
            continue;
        }
        push();
        if(i+1<(int)line.size()){
            string two = line.substr(i, 2);
            if(two=="=="||two=="!="||two=="<="||two==">="){
                t.push_back(two);
                i++;
                continue;
            }
        }
        t.push_back(string(1, c));
    }
push();
    return t;
}

int main() {
    ifstream file("input.c");
    if(!file){
    cout<<"File not found\n";
    return 1;
    }
    bool bl = false;
    string l;
    int ln = 0;
    vector<int> br;
    vector<int> If;
    unordered_map<string,unordered_set<string>>dec;
    vector<string>sc ={"global"};

    string curType = "";
    bool declMode = false,inParams = false,pendingFunc = false, lastSemi = false,inFor = false ,err = false;
    
    string fn = "";
    while(getline(file, l)){
        ln++;
        l = com(l, bl);
        if(l.empty() ||l[0] == '#')continue;
        vector<string>tok =tk(l);
        for (int i = 0; i < (int)tok.size(); i++) {
            string s = tok[i];
            if (s == "for") {
                inFor = true;
                lastSemi = false;
                continue;
            }
            if (D(s)) {
                curType = s;
                declMode = true;
                continue;
            }
            if (declMode && i + 1 < (int)tok.size() && tok[i + 1] == "(" && Id(s)) {
                fn = s;
                pendingFunc = true;
                dec["global"].insert(fn);
                continue;
            }
            if(s == "("){
                if(pendingFunc){
                    sc.push_back(fn);
                    inParams = true;
                    pendingFunc = false;
                }
                continue;
            }
            if(s == ")"){
                if (inParams) inParams = false;
                inFor = false;
                continue;
            }
            if(s == "{"){
                br.push_back(ln);
                continue;
            }

            if(s == "}"){
                if(br.empty()){
                    cout<<"Unmatched '}' at line "<<ln<<endl;
                    err = true;
                } else {
                    br.pop_back();
                }

                if (sc.size() > 1) sc.pop_back();
                continue;
            }
            if(s == "if"){
                If.push_back(ln);
                continue;
            }
            if(s == "else"){
                if (If.empty()) {
                    cout<<"Unmatched 'else' at line "<<ln<<endl;
                    err = true;
                } else {
                    If.pop_back();
                }
                continue;
            }
            if(s == ";"){
                if(!inFor && lastSemi){
                    cout<<"Duplicate ';' at line "<<ln<< endl;
                    err= true;
                }
                lastSemi = true;
                declMode = false;
                curType = "";
                continue;
            } else {
                if (s != ";") lastSemi = false;
            }
            if (s == ",") continue;
            if (Id(s) && (declMode || inParams)) {
                string scope = sc.back();
                if (dec[scope].count(s)) {
                    cout<<"Duplicate identifier declaration: "<<s<<" at line "<<ln<<endl;
                    err= true;
                } else {
                    dec[scope].insert(s);
                }
            }
        }
    }
    while (!br.empty()) {
        cout<<"Unbalanced '{' detected at line "<<br.back()<<endl;
        br.pop_back();
        err = true;
    }
    if (!err) cout<<"No syntax errors found.\n";
    return 0;
}