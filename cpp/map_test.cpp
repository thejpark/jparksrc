#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <stack>
#include <queue>

using namespace std;

void map_test()
{

    string s;
    
    map<string, int> wc;

    while(cin >> s) {
        ++wc[s];
    }

    for(map<string, int>::const_iterator it = wc.begin(); it != wc.end(); ++it) {

        cout << it->first << ":" << it->second << endl;

    }
    
}

void string_test()
{
    string s;
    string::iterator it;
    

    cin >> s;

    cout << s << endl;

    it = s.begin();
    
    s.erase(it);

    cout << s << endl;
        


}


void unique()
{
    string s;
    map<char, int> cc;

    cin >> s;

    for(int i = 0; i != s.size(); i++) {
        ++cc[s[i]];
    }
    

    for(map<char, int>::const_iterator it = cc.begin(); it != cc.end(); it++ ){

        if (it->second > 1)
            cout << it->first << " : " << it->second << endl;
        
    }
    



}


void unique2()
{
    string s;

    cin >> s;

    sort(s.begin(), s.end());

    cout << s << endl;

    char c = s[0];
    
    for (string::const_iterator it = s.begin() + 1; it != s.end(); it++) {

        if (c == *it)
            cout << "found " << c << endl;

        c = *it;
    }
    



}


void reverse()
{
    char *s = "abcde";
    int size = strlen(s);
    char *r = (char *)malloc(size + 1);
    int i;


    for (i = 0; i < size; i++) {
        r[size - i - 1] = s[i];
    }
    r[size] = 0;
    cout << r << endl;
    

}


void rem_dup()
{
    string s;

    cin >> s;

    for (int i = 0; i < s.size(); i++) {
        
        for (int j = i + 1; j < s.size();) {
            
            if (s[i] == s[j]) {
                string::iterator it = s.begin() + j;
                s.erase(it);
            } else {
                j++;
            }
            
        }
        
    }
    

    cout << s << endl;
    

}

void replace()
{
    string s;

    cin >> s;

    for (int i = 0; i < s.size();) {

        if (s[i] == ' ') {

            s[i] = '%';
            s.insert(i + 1, "20%");
            i += 3;
        } else {
            i++;
        }
        
    }
    
    cout << s << endl;
}


void test_find()
{
    string s1;
    string s2;
    typedef  string::const_iterator iter;
    string s3;

    cin >> s1 >> s2;

    iter be  = s1.begin();
    iter end  = s1.end();

    if (search(be, end, s2.begin(), s2.end()) != end) {
        cout << " found " << endl;
    } else  {
        cout << " not found" << endl;
    }
               
}


void t_merge(vector<int> &a, vector<int> &b1, vector<int> &b2)
{
    int i = 0, j = 0, k = 0;
    int end1 = b1.size() - 1;
    int end2 = b2.size() - 1;
    

    cout << "begin t merge" << endl;
    
    while (k <= a.size() - 1) {

        cout << "iteration " << k << "with " << b1[i] << " " << b2[j] << endl;
        
        if (i > end1) {
            
            a[k++] = b2[j++];
            cout << "... 1 " << endl;

        } else if (j > end2) {
            
            a[k++] = b1[i++];
            cout << "... 2 " << endl;
        } else if (b1[i] > b2[j]) {
            a[k++] = b2[j++];
            cout << "... 3 " << endl;
        } else if (b1[i] < b2[j]) {

            a[k++] = b1[i++];
            cout << "... 4 " << endl;
        } else {
            a[k++] = b1[i++];
            a[k++] = b2[j++];
            cout << "... 5 " << endl;
        }
    }
    

    for (i = 0; i < a.size(); i++)
        cout << a[i];
    
    cout << "   end t merge" << endl;
        
        
}


void t_merge_sort(vector<int> &out, vector<int> &a, int be, int end)
{
    cout << "merge_sort " << be << ":" << end << endl;

    if (end == be) {
        out[0] = a[be];
        return;
    }

    int mid = be + (end - be) / 2;
   
    vector<int> b1, b2;
    b1.resize(mid - be + 1);
    b2.resize(end - mid);
    
    t_merge_sort(b1, a, be, mid);
    t_merge_sort(b2, a, mid + 1, end);

    t_merge (out, b1, b2);

}

void test_merge()
{

    vector<int> vi, vr;

    int i;
    
    while (cin >> i)
        vi.push_back(i);

    cout << "size is " << vi.size() << endl;

    vr.resize(vi.size());
    
    t_merge_sort(vr, vi, 0, vi.size() - 1);

    cout << "size is " << vr.size() << endl;
    for (i = 0; i < vr.size(); i++)
        cout << vr[i];
    
    cout << endl;
}

void vec_str_test()
{
/* vector::push_back creates a copy of it argument.*/
    string s;
    vector<string> vs;
    

    for (int i = 0; i < 5; i++) {
        
        cin >> s;
        vs.push_back(s);

    }
    
    for (int i = 0; i < 5; i++) {
        s = vs[i];
        cout << s << endl;
    }
    
    
}

void print_comb(vector<char> &va, vector<char> &vb)
{



}


void comb_2_seq()
{

    vector<char> vc1, vc2;

    vc1.push_back('a');
    vc1.push_back('b');
    vc1.push_back('c');

    vc2.push_back('x');
    vc2.push_back('y');
    vc2.push_back('z');

    print_comb(vc1 vc2);
}


void subset()
{
    
}


    


int main()
{
    
}





