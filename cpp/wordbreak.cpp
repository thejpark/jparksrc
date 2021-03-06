#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
class node {
    public:
        node():complete{false} {}
        unordered_map<char, node* > ms;
        bool complete;
        ~node() {}
};

class Trie {
public:

    node* root;

    Trie(): root{new node()} {}
    void add(string& s)
    {
        int i = 0;
        int len = s.size();
        //
        node* n = root;
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
            node* temp{new node()};
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

        node* n = trie.root;
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
