#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <assert.h>

using namespace std;
class MyFindCommonAncestor
{
public:
    string findCommonAncestor(vector<string>& commitHashes,
                               vector<vector<string>>& parentHashes,
                               string commitHash1,
                               string commitHash2)
    {
        set<string> s1 = findParent(commitHash1, commitHashes, parentHashes);
        set<string> s2 = findParent(commitHash2, commitHashes, parentHashes);
        vector<string> r;
        // map or set do not work with back_inserter
        set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), 
                         back_inserter(r));
        return findMin(r, commitHashes);
    }

    string findMin(vector<string>& s, vector<string>& commitHashes)
    {
        int m = commitHashes.size();
        for (auto x: s) {
            int k = findi(commitHashes, x);
            m = min(m, k);
        }
        return commitHashes[m];
    }

    set<string> findParent(string a,
                           vector<string>& ch,
                           vector<vector<string>>& ph)
    {
        int k = findi(ch, a);
        set<string> r;

        if (ph[k].size() == 0)
            return r;

        for (string s: ph[k]) {
            r.insert(s);
            set<string> x = findParent(s, ch, ph);
            r.insert(x.begin(), x.end());
        }

        return r;
    }

private:
    int findi (vector<string>& ch, string ch1)
    {
        for (int i = 0; i < ch.size(); i++) {
            if (ch[i] == ch1)
                return i;
        }
        return -1;
    }
};

int main()
{
    vector<string> commits {"G", "F", "E", "D", "C", "B", "A"};
    vector<vector<string>> parents {
            {"F","D"},
            {"E"},
            {"B"},
            {"C"},
            {"A"},
            {"A"}, 
            {}};
    MyFindCommonAncestor fca;
    string a = fca.findCommonAncestor(commits, parents, string("E"), string("D"));
    assert(a == string("A"));
    a = fca.findCommonAncestor(commits, parents, string("D"), string("F"));
    assert(a == string("A"));
}
