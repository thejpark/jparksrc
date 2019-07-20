#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
class node {
    public:
        node():complete{false} {}
        unordered_map<char, shared_ptr<node> > ms;
        bool complete;
        ~node() {}
};

class Trie {
public:
    
    shared_ptr<node> root;

    Trie(): root{new node()} {}
    void add(string& s) 
    {
        int i = 0;
        int len = s.size();
        //
        shared_ptr<node> n = root;
        while(i < len)
        {
            auto it = n->ms.find(s[i]);
            if (it == n->ms.end())
                break;
            n = it->second;
            ++i;
        }

        while(i < len)
        {
            shared_ptr<node> temp{new node()};
            n->ms[s[i]] = temp;
            n = temp;
            ++i;
        }

        n->complete = true;
    }
};


class Solution {
public:
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        Trie trie;

        for (auto& e : wordDict)
        {
            trie.add(e);
        }
        
        unordered_map<int, vector<string>> mm;
        vector<string> r;

        foo(trie, s, 0, r, mm);
        
        for (auto& e : mm)
        {
            cout << e.first << ": " << endl;
            for (auto&ee : e.second)
            {
                cout << ">" << ee << endl;
            }
        }
        return r;
    }

    
    void foo(Trie& trie,
            string& s, 
            int idx,
            vector<string>& r,
            unordered_map<int, vector<string>>& mm)
     {
        if (idx == s.size())
        {
            r.push_back("");
            return;
        }
        
        // use cache
        if (mm.find(idx) != mm.end())
        {
            r = mm[idx];
            return;
        }
        
        shared_ptr<node> n = trie.root;
        int i = 0;
        
        string tt;
        vector<string> rr;
        while (n->ms.find(s[idx + i]) != n->ms.end())
        {
            n = n->ms[s[idx + i]];
            tt += s[idx + i];

            if (n->complete)
            {
                foo(trie, s, idx + i + 1, rr, mm);
                for (auto& e : rr)
                {
                    if (e.size() > 0)
                        r.push_back(tt + " " + e);
                    else
                        r.push_back(tt);
                }
                rr.clear();
            }
            ++i;
        }
        mm[idx] = r;
    }
};
int main()
{
    Solution s;

    vector<string> v {"cat","cats","and","sand","dog"};
    auto r = s.wordBreak("catsanddog", v);

    for (auto&e : r)
    {
        cout << e << endl; 
    }
}
