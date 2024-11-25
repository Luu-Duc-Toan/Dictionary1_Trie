#include <string>
#include <iostream>
#include <stack>
#include <stdio.h>
#include <fstream>
#include <unordered_map>
using namespace std;
//UI
struct Trie {
    bool endOfWord;
    vector<string> meanings;
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
            for (string& dicMeaning : meanings) {
				if (dicMeaning == meaning) return;
            }
			cur->meanings.push_back(meaning);
            return;
        }
        cur->endOfWord = true;
        cur->meanings.push_back(meaning);
    }

    vector<string> search(string &s) {
        Trie* cur = this;
        for (char& x : s) {
            if (cur->map.find(x) != cur->map.end())
                cur = cur->map[x];
            else {
                cout << "Khong co tu nay" << endl;
                return {};
            }
        }
		if (cur->endOfWord) return cur->meanings;
		else cout << "Khong phai 1 tu hoan chinh" << endl;
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
        if (search(s).size() == 0) cout << "Tu nay van con trong tu dien" << endl;
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
    string word, meaning;
    string line;

    while (!input.eof()) {
		getline(input, line);
        int start = 0;
		int end = line.find_first_of(' ', start);
		word = line.substr(start, end - start);
        while (end != -1) {
            start = end + 1;
            end = line.find(' ', start);
			meaning = line.substr(start, end - start);
			root->insert(word, meaning);
        }
    }
    
    input.close();
    output.close();
}