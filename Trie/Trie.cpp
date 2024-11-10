#include <string>
#include <iostream>
#include <stack>
#include <stdio.h>
#include <fstream>
#include <unordered_map>
using namespace std;
//Add meaning of word by selenium or OTHER TOOLS
//UI
struct Trie {
    bool endOfWord;
    string meaning;
    unordered_map<char, Trie*> map;
    Trie() {
        endOfWord = false;
    }

    void insert(string &word, string &meaning) {
        Trie* cur = this;
        for (char& x : word) {
            if (cur->map.find(x) == cur->map.end())
                cur->map[x] = new Trie();
            cur = cur->map[x];
        }
        if (cur->endOfWord) {
            cout << "Tu nay da co nghia" << endl;
            return;
        }
        cur->endOfWord = true;
        cur->meaning = meaning;
    }

    bool search(string &s) {
        Trie* cur = this;
        for (char& x : s) {
            if (cur->map.find(x) != cur->map.end())
                cur = cur->map[x];
            else {
                cout << "Khong co tu nay" << endl;
                return false;
            }
        }
        if(cur->endOfWord) cout << cur->meaning << endl;
		else cout << "Khong phai 1 tu hoan chinh" << endl;
        return cur->endOfWord;
    }
    void Delete(string &s) {
        Trie* cur = this;
        stack <pair<Trie*, char>> st;
        for (char& x : s) {
            if (cur->map.find(x) != cur->map.end()) {
                st.push({ cur,x });
                cur = cur->map[x];
            }
            else {
                cout << "Khong co tu nay trong tu dien" << endl;
                return;
            }
        }
        cur->endOfWord = false;
        while (!cur->endOfWord && cur->map.size() == 0) {
            Trie* par = st.top().first;
			char c = st.top().second;
			st.pop();
			delete par->map[c];
            par->map.erase(c);
			cur = par;
        }
        //Test
        if (search(s)) cout << "Tu nay van con trong tu dien" << endl;
        else cout << "Tu nay da bi xoa" << endl;
    }
    bool startsWith(string &s) {
        Trie* cur = this;
        for (char& x : s) {
            if (cur->map.find(x) != cur->map.end())
                cur = cur->map[x];
            else return false;
        }
        return true;
    }
};
int main() {
    fstream input; 
    input.open("input.txt", ios::in);
    fstream output;
    output.open("output.txt", ios::out);
    Trie* root = new Trie();
    int n;
    string word, meaning;
    char q;
    input >> n;
    int i = 0;
    for (i; i < n; i++) {
        input >> q;
        cout << q << endl;
        if (q == 'i') {
            input >> word >> meaning;
            root->insert(word, meaning);
        }
        else if (q == 's') {
            input >> word;
            root->search(word);
        }
        else {
            input >> word;
            root->Delete(word);
        }
	}
    input.close();
    output.close();
}