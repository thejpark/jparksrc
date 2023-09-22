/*
http://web.stanford.edu/class/cs97si/
*/

#include <assert.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <unordered_map>
#include <list>
#include <set>
#include <stack>
#include <algorithm>
#include <numeric>
#include <memory>
#include <queue>
#include <functional>
#include <math.h>
#include <limits.h>
#include <ranges>
using namespace std;


/*

  space complexity:

  http://www.geeksforgeeks.org/g-fact-86/

Space Complexity:
The term Space Complexity is misused for Auxiliary Space at many places. Following are the correct definitions of Auxiliary Space and Space Complexity.

Auxiliary Space is the extra space or temporary space used by an algorithm.

Space Complexity of an algorithm is total space taken by the algorithm with respect to the input size. Space complexity includes both Auxiliary space and space used by input.

For example, if we want to compare standard sorting algorithms on the basis of space, then Auxiliary Space would be a better criteria than Space Complexity. Merge Sort uses O(n) auxiliary space, Insertion sort and Heap Sort use O(1) auxiliary space. Space complexity of all these sorting algorithms is O(n) though.
*/


void hangover()
{
  vector<double> vcard_len;
  double card_len;
  int size;

  while(1) {

    cin >> card_len;
    if (card_len == 0.00)
      break;
    vcard_len.push_back(card_len);
  }

  size = vcard_len.size();
  for (int i = 0; i < size; i++) {
    card_len = 0;
    for (int j = 1; ; j++) {
      card_len += 1 / double(1 + j);
      if (card_len > vcard_len[i]) {
	cout << j << " cards" << endl;
	break;
      }
    }
  }
}


class str_unsort {
public:
  str_unsort(string &s) : str(s), unsort(0) {
    get_unsort();
  }
  string str;
  int unsort;
private:
  void get_unsort()
  {
    int size = str.size();
    for (int i = 0; i < size; i++) {
      for (int j = i + 1; j < size; j++) {
        if (str[i] > str[j])
          unsort++;
      }
    }
  }
};


/* usually, sorting needs swap. */
void dna_sorting()
{
  unsigned int num_str, str_len;
  vector<str_unsort *> vunsort;
  string str;

  cin >> str_len >> num_str;

  for (int i = 0; i < num_str;i++) {
    cin >> str;
    if (str.size() != str_len) {
      cout << "string size not match" << endl;
      return;
    }
    vunsort.push_back(new str_unsort(str));
  }


  int min = 0;
  for (int i = 0; i < num_str; i++) {

    min = i;

    for (int j = i + 1; j < num_str; j++) {
      if(vunsort[min]->unsort > vunsort[j]->unsort)
        min = j;
    }

    if (min != i) {
      str_unsort *tmp;
      tmp = vunsort[i];
      vunsort[i] = vunsort[min];
      vunsort[min] = tmp;

    }

  }


  for (int i = 0; i < num_str; i++) {
    cout << vunsort[i]->str << endl;
  }
}


int get_unsortedness(string s)
{
    int r = 0;
    if (s.size() == 1) return 0;

    for (int i = s.size() - 2; i >= 0; --i)
    {
        for (int j = i; j < s.size() - 1; ++j)
        {
            if (s[j] > s[j + 1])
            {
                r += 1;
                swap(s[j], s[j + 1]);
            }
            else
                break; // we don't need to go further as it is sorted
        } // or we from the right, and use binary search to find where to put?
    }
    return r;
}


void dna_sorting2() //nlogn if we do binary search //jj
{
    int str_len, num_str;
    string str;
    vector<string> vs;

    cin >> str_len >> num_str;

    for (int i = 0; i < num_str;i++) {
        cin >> str;
        if (str.size() != str_len) {
            cout << "string size not match" << endl;
            return;
        }
        vs.push_back(str);
    }

    using dna_elem = pair<int, int>;
    vector<dna_elem> pv;

    for (int i = 0; i < vs.size(); ++i)
    {
        int r = get_unsortedness(vs[i]);
        pv.push_back(dna_elem(i, r));
    }

    auto pred = [&](dna_elem& a, dna_elem& b) {
        return a.second < b.second;
    };

    sort(pv.begin(), pv.end(), pred);

    cout << "the result is" << endl;
    for (int i = 0; i < pv.size(); ++i)
        cout << vs[pv[i].first] << endl;
}


void vertical_histo()
{


  int a['Z' - 'A' + 1];
  int max = 0;
  char cstr[256];

  for (int i = 0; i < 'Z' - 'A' + 1; i++)
    a[i] = 0;

  for (int i = 0; i < 4; i++) {

    cin.getline(cstr, 72);
    cout << "sizeof cstr is " << strlen(cstr) << endl;
    for (int j = 0; j < strlen(cstr); j++) {
      if (cstr[j] < 'A' || cstr[j] > 'Z')
	continue;
      a[cstr[j] - 'A']++;
      if (a[max] < a[cstr[j] - 'A'])
	max = cstr[j] - 'A';
    }

  }

  cout << max << " " << a[max] << endl;
  max = a[max];

  cout << max;

  for (; max > 0; max--) {
    for (int j = 0; j < 'Z' - 'A' + 1; j++) {

      if (a[j] == max) {
	cout << " *";
	a[j] = a[j] - 1;
      } else {
	cout << "  ";
      }

    }
    cout << endl;

  }

}


// each cow in the herd is numbered from 1 to N. find
// how many sequences are (there sum should match to a target
// number. For example, if N is 10 and target number is 10,
// there are 2 sequences (1,2,3,4 and the other is 10).

// O(n^2) time complexity
int herd(int n, int num)
{
  int i, sum = 0;

  for(i = n; i <= num; i++){
    sum += i;
    if (sum == num)
      return i;
  }

  return -1;

}
// http://poj.org/problem?id=2140

void herd_sum()
{
  int num, ret = 0;
  cin >> num;

  for (int i = 1; i <= num;i++)
    {
      int r =  herd(i, num);

      if (r > 0) {
	cout << "got it(" << r << ")";
	ret++;
      }
    }

  cout << endl << ret << endl;

}


// sum_to
// linear time search of the herd sum with some preprocessing
void herd_sum2() //jj
{
    vector<int> vi;
    int t;
    int size;

    cin >> size;

    for (int i = 1; i <= size; ++i)
    {
        vi.push_back(i);
    }

    int mmatch = size;

    vector<int> vi2;

    // to make mi[0]++; // in case sum starts from the beginning
    vi2.emplace_back(0);

    partial_sum(vi.begin(), vi.end(), back_inserter(vi2));

    unordered_map<int, int> mi;
    for (int i = 0; i < vi2.size(); ++i)
    {
        mi[vi2[i]]++;
    }

    int r = 0;
    for (int i = 0; i < vi2.size(); ++i)
    {
        if (mi.find(vi2[i] - mmatch) != mi.end())
        {
            ++r;
        }
    }
    if (r == 0)
        cout << "no sequences found" << endl;
    cout << r << endl;
}




void test_reverse_sum_linked_list()
{
}



void slice(int s, int n, int size)
{

  int d = abs(s - n);

  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++) {

      int w = abs(i - n);
      int h = abs(j - n);


      if (d + w + h > n)
	cout << ".";
      else {
	cout << (d + w + h);

	  }

    }
    cout << endl;
  }


}


void cubic(int s, int n)
{

  int size = n * 2 + 1;

  cout << "Scenario #" << s << endl;



  for (int i = 0; i < size; i++) {

    cout << "slice #" << i + 1 << endl;

    slice(i, n, size);

    }


}


void manhattan()
{

  int num;
  cin >> num;

  int *a = new int[num];

  for (int i = 0; i < num; i++)
    cin >> a[i];

  for (int i = 0; i < num; i++)
    cubic(i, a[i]);


}


void ride()
{

  vector<double> a; // velocity
  vector<double> b; // setoff time
  vector<int> c; // number of rider in a scenario
  vector<double> d; // distances = v * t

  int num;

  /* get input */
  while(1) {

    cin >> num;
    if (num == 0)
      break;

    c.push_back(num);

    for (int i = 0; i < num; i++) {
      int t1, t2;
      cin >> t1 >> t2;
      a.push_back(t1);
      b.push_back(-t2);
      d.push_back(0);
    }

  }


  int idx = 0;

  /* debug print */
  cout << "output" << endl;
  int size = c.size();
#if 0
  cout << "number of scenario is " << size << endl;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < c[i]; j++) {
      cout << a[idx + j] << " " << b[idx + j] << endl;
    }
    idx += c[i];
  }
#endif

  /* calculate*/
  idx = 0;
  for (int i = 0; i < size; i++) {
    int tt = 0; //arrival time of Charlie
    int *group = new int [c[i]];

    // setup group
    for (int j = 1; j < c[i]; j++) {
      if (b[j] > 0) {
	group[j] = 1; // before charlie
	cout << "group 1 " << j << " " << b[j] << endl;
      } else  {
	group[j] = -1; // after charlie
	cout << "group 2 " << j << " " << b[j] << endl;
      }
    }

    for (int t = 1; d[idx] < 4.5 ; t++) {

      d[idx] += a[idx] /3600;

      for (int j = 1; j < c[i]; j++) {
	/* d is distance at time t */

	d[idx + j] = a[idx + j] * (b[idx + j] + t)/3600;

	if(group[j] < 0 && d[idx + j] > d[idx]) {

	  a[idx] = a[idx + j];
	  group[j] = 1;
	  cout << "meet at time " << t << endl;

	}
      }

      tt = t;
    }
    cout << tt << " " << a[idx] << endl;
    idx += c[i];
  }



}


void test_clock()
{

  int hour, min;
  double h_angle, m_angle, Max, Min, angle;
  cin >> hour >> min;

  h_angle = 30 * (hour % 12) + 0.5 * min; /* 1/2 becomes 0 so you should use 0.5 instead. or (double)1/2 */
  m_angle = 6 * min;

  if (m_angle > h_angle) {
    Max = m_angle;
    Min = h_angle;
  } else {
    Max = h_angle;
    Min = m_angle;
  }

  angle = Max - Min;
  if ((Max - Min) < 180)
    cout << angle << endl;
  else
    cout << (360 - angle) << endl;

}

void perm(vector<int>& a, vector<int>& t, vector<vector<int>>& r, map<int, int>& visited) //jj
{
    if (t.size() == a.size())
    {
        r.push_back(t);
        return;
    }
    for (int i = 0; i < a.size(); ++i)
    {
        if (visited[i])
            continue;
        visited[i] = 1;
        t.push_back(a[i]);
        perm(a, t, r, visited);
        t.pop_back();
        visited[i] = 0;
    }
}

void permutation()
{
    vector<int> a = {1, 2, 3};

    vector<int> t;
    vector<vector<int>> r;
    map<int, int> visited;

    perm(a, t, r, visited);

    for (auto& e : r)
    {
        for (auto& ee : e)
        {
            cout << ee << " ";
        }
        cout << endl;
    }
}

void comb(vector<int>& a, int idx, vector<int>& t, vector<vector<int>>& r, int k) //jj
{
    if (t.size() == k)
    {
        r.push_back(t);
        return;
    }

    for (int i = idx; i < a.size(); ++i)
    {
        t.push_back(a[i]);
        comb(a, i + 1, t, r, k);
        t.pop_back();
    }
}


void combination()
{
    vector<int> a = {1, 2, 3, 4};

    vector<int> t;
    vector<vector<int>> r;

    comb(a, 0, t, r, 2); // combination with size 2

    for (auto& e : r)
    {
        for (auto& ee : e)
        {
            cout << ee << " ";
        }
        cout << endl;
    }
}

void powerset()
{
    vector<int> a = {1, 2, 3};

    vector<int> t;
    vector<vector<int>> r;

    for (int i = 1; i <= a.size(); ++i)
        comb(a, 0, t, r, i);

    for (auto& e : r)
    {
        for (auto& ee : e)
        {
            cout << ee << " ";
        }
        cout << endl;
    }
}

void set_of_k_elem(int idx, vector<int>& vi, vector<int>& vr, int k)
{
    if (vr.size() == k)
    {
        cout << "{" ;
        for (auto e : vr)
            cout << e << " ";
        cout << "}" << endl ;
        return;
    }
    for (int i = idx; i < vi.size(); ++i)
    {
        vr.push_back(vi[i]);
        set_of_k_elem(i + 1, vi, vr, k);
        vr.pop_back();
    }

}

void test_set_of_k_elem()
{

    int k, t;
    vector<int> vi;

    cin >> t >> k;

    for (int i = 0; i < t; ++i)
    {
        int tt;
        cin >> tt;
        vi.push_back(tt);
    }

    vector<int> vr;
    set_of_k_elem(0, vi, vr, k);
}

//
//
// find the number of combination sum to 15
// from the array of int from 1 to 10.
// ex) [1, 2, 3, 4, 5] -> 1
// ex) [5, 5, 10, 2,3] -> 4
//
int fff(vector<int>& vi, int idx, int t) //jj
{
    if (t == 0)
        return 1;
    if (t < 0)
        return 0;

    int r = 0;
    for (int i = idx; i < vi.size(); ++i)
    {
        r += fff(vi, i + 1, t - vi[i]);
    }

    return r;
}

// same with knapsack
int fff_2(vector<int>& vi, int idx, int t) //jj
{
    if (t == 0)
        return 1;

    if (idx == vi.size())
        return 0;

    int a = (t < vi[idx]) ? 0 : fff_2(vi, idx + 1, t - vi[idx]);
    int b = fff_2(vi, idx + 1, t);

    return a + b;
}

int fff_dp(vector<int>& vi, int t) //jj
{
    vector<vector<int>> vv(vi.size() + 1, vector<int>(t + 1, 0));

    for (int i = 0; i <= vi.size(); ++i)
    {
        vv[i][0] = 1;
    }

    for (int i = 1; i <= vi.size(); ++i)
    {
        for (int j = 1; j <= t; ++j)
        {
            int a = (j < vi[i - 1]) ? 0 : vv[i - 1][j - vi[i - 1]];
            int b = vv[i - 1][j];
            vv[i][j] = a + b;
        }
    }

    return vv[vi.size()][t];
}

void test_combination_sum_to_15()
{
    int n;
    cin >> n;

    vector<int> vi;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        vi.push_back(t);
    }

    int r = 0;
    r = fff(vi, 0, 15);
    cout << "the result is " << r << endl;
    r = fff_2(vi, 0, 15);
    cout << "the result is " << r << endl;
    r = fff_dp(vi, 15);
    cout << "the result is " << r << endl;
}

/*
Given an infinite number of quarters (25 cents), dimes (10 cents),
nickels (5 cents) and pennies (1 cent), write code to calculate the
number of ways of representing n cents
*/

int makeChange(int n, int denom) {
    int next_denom = 0;

    switch (denom) {
    case 25:
        next_denom = 10;
        break;
    case 10:
        next_denom = 5;
        break;
    case 5:
        next_denom = 1;
        break;
    case 1: // when it comes here, you always find solution.
        return 1;
    }

    int ways = 0;

    for(int i=0;i*denom<=n;i++)
    {
        ways += makeChange(n - i * denom, next_denom);
    }
    return ways;
}

int makeChange(vector<int>& denom, int idx, int n) //jj
{
    if (n == 0)
        return 1;
    if (idx == denom.size())
        return 0;
    int r = 0;
    for (int i = 0; i * denom[idx] <= n; ++i)
    {
        r += makeChange(denom, idx + 1, n - i * denom[idx]);
    }
    return r;
}

// can you implement it using dynamic programming?
// this is combination, not taking care of sequence
int makeChangeDP(vector<int>& denom, int n) //jj
{
    vector<vector<int>> v(denom.size(), vector<int>(n + 1));

    // assume that demon start from smallest number to large number
    for (int i = 0; i < denom.size(); ++i)
    {
        v[i][0] = 1;
        for (int j = 1; j <= n; ++j)
        {
            // without this denom
            int x = (i >= 1)? v[i - 1][j] : 0;

            // with this denom
            int y = (j >= denom[i])? v[i][j - denom[i]] : 0;

            v[i][j] = x + y;
        }
    }

    return v.back().back();
}

// leetcode 322, they do not used idx
int makeMinChange(vector<int>& denom, int idx, int cnt, int n) //jj
{
    if (n == 0)
        return cnt;
    if (idx == denom.size())
        return 1000; // some max number
    int r = 1000; // some max number
    for (int i = 0; i * denom[idx] <= n; ++i)
    {
        int a = makeMinChange(denom, idx + 1, cnt + i, n - i * denom[idx]);
        if (a < r)
            r = a;
    }
    return r;
}

// this is better solution. c is coins, if there is no matching amount then return maxAmount,
// cache is for caching. same with leetcode 279 perfect square
int makeMinChange(vector<int>& c, int amount, int maxAmount, vector<int>& cache)
{
  int r = maxAmount + 1;

  if (amount < 0)
    return r;
  if (amount == 0)
    return 0;

  if (cache[amount] != -1)
    return cache[amount];

  for (int i = 0; i < c.size(); ++i)
    {
      int m = 1 + foo2(c, amount - c[i], maxAmount, cache);
      r = min(r, m);
    }

  cache[amount] = r;
  return r;
}


void test_denom() {
    cout << makeChange(100, 25) << endl;

    vector<int> a {25, 10,  5, 1};
    vector<int> b {1, 5, 10, 25};

    cout << makeChange(a, 0, 100) << endl;
    cout << makeChange(b, 0, 100) << endl;
    cout << makeChangeDP(b, 100) << endl;
    cout << makeMinChange(a, 0, 0, 100) << endl;
}


#if 0
bool has_str(string a, string b)
{



}


void find_url()
{

  string s = "this is https://www.donga.com web site";
  string proto = "://";

  vector<string> vs;

  for (string::const_iterator i = s.begin(); i != s.end();) {

    for (string::const_iterator j = i; j != s.end();) {
      if (*j != ' ')
	break;
      ++j;
    }

    for (string::const_iterator k = j; k != s.end();) {
      if (*k == ' ')
	break;
      ++K;
    }
  }

  string rr = string(j,k);
  if (has_str(rr, proto)) {
      vs.push_back(rr);
    }


}
#endif


void find_parent(vector<int> &a, map<int, int> &t, int b)
{

  a.push_back(b);
  while (1) {
    if (t[b] == 0)
      break;
    b = t[b];
    a.push_back(b);
  }
}


void nearest_common_ancestor() //jj
{
  map<int, int> pairtree;
  vector<int> res;
  int cases, num_node;
  int first, second;

  cin >> cases;


  for (int i = 0; i < cases; i++) {
    cin >> num_node;

    for (int j = 0; j < num_node -1; j++) {

      int p, c;

      cin >> p >> c;

      pairtree[c] = p;

    }

    cin >> first >> second;

    vector<int> a, b;

    find_parent(a, pairtree, first);
    find_parent(b, pairtree, second);

// compare at the same level.
  if (a.size() > b.size())
  {
      int diff = a.size() - b.size();
      a = vector<int>(a.begin() + diff, a.end());
  }
  else
  {
      int diff = b.size() - a.size();
      b = vector<int>(b.begin() + diff, b.end());
  }

  for (int i = 0; i < a.size(); ++i)
  {
      if (a[i] == b[i])
      {
          res.push_back(a[i]);
          break;
      }
  }

  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << endl;

  }
 }
}




/*
  replace expression from stack to queue.
  http://poj.org/problem?id=3367

  1. to replace expression from stack to queue interpretation, first thing is to
     make an AST. In other cases also, if you need to interpret, you need to make an AST.
  2. In this case, we can make a AST using tree-node, or using map.
  3. using map, each element in an input stream point to its parent, so we can make a tree node structure
     for that.
  4. for each element in an input stream, we can set the depth of the node in the AST.
  5. Queue traverse starts from the lower-toup, right-to-left. So traverse each element in that way will
     make the new expression for queue.


*/
void exp_replace_stack_queue() //jj
{

  int num;
  string str;
  vector<string> vs;

  cin >> num;

  for(int i = 0; i < num; i++) {
    cin >> str;
    vs.push_back(str);
  }

  /* scan input from left to right, set parent of each element using map. If we encounter operator, the parent of the two previous element is the operator. */

  /* scan input again to calculate the depth of each element. Use map to find the root of each element. */

  /* from the right to left, traverse the lowest element up to the root will produce the expression for queue. */


}


struct farm {
  int x;
  int y;
  int  grp;
};


int find(vector<struct farm> &vi, int x)
{

  while(vi[x].grp != 0)
    x = vi[x].grp;

  return x; // if grp is 0, then this method returns x instead of 0.
}

int findx(vector<struct farm> &vi, int x)
{
  int dis_x = 0;

  while(vi[x].grp != 0) {
    dis_x += vi[x].x;
    x = vi[x].grp;
  }

  return abs(dis_x);
}

int findy(vector<struct farm> &vi, int y)
{
  int dis_y = 0;

  while(vi[y].grp != 0) {
    dis_y += vi[y].y;
    y = vi[y].grp;
  }

  return abs(dis_y);

}


void uunion(vector<struct farm> &vi, int x, int y)
{
  vi[find(vi, x)].grp = find(vi, y);
  vi[x].x += findx(vi, y);
  vi[x].y += findy(vi, y);
}

// http://poj.org/problem?id=1984
void navi() //jj
{

  int num_farms;
  int num_dirs;
  vector<struct farm> vi;
  int farm1, farm2, dis;
  char dir;

  cin >> num_farms >> num_dirs;

  vi.resize(num_farms + 1);

  for (int i = 0; i < num_dirs; i++) {

    cin >> farm1 >> farm2 >> dis >> dir;
    switch(dir) {
    case 'N':
      vi[farm1].y = dis;
      break;
    case 'S':
      vi[farm1].y = -dis;
      break;
    case 'E':
      vi[farm1].x = dis;
      break;
    case 'W':
      vi[farm1].x = -dis;
      break;
    }

    uunion(vi, farm1, farm2);

  }


  cin >> farm1 >> farm2;

  /* compute manhattan distance. */
  if (find(vi, farm1) == find(vi, farm2)) {
    int res;
    res = abs(findx(vi, farm1) - findx(vi, farm2)) + abs(findy(vi, farm1) - findy(vi, farm2));
    cout << res << endl;

  } else {

    cout << " not joined " << endl;
  }



  cout  << " ----- " << endl;
  for (int i = 1; i <= num_farms; i++) {
    cout << vi[i].grp << endl;
  }


}


// Q: Find number of Islands.
// XXXOO
// OOOXX
// XXOOX
// Return 3 islands.
// 111OO
// OOO22
// 33OO2
// Followup: If the board is too big to fit in memory, how to get the number?

void test_find_number_of_island()
{
    // union/find
}

int b(int);
int a(int);
int d(int);

int b(int n)
{

  if (n < 2)
    return 0;
  if (n == 2)
    return 1;

  return d(n - 2) + b(n - 2);
}

int a(int n)
{
  if (n < 2)
    return 0;
  if (n == 2)
    return 1;

  return d(n - 2) + a(n - 2);
}

int d(int n)
{
  if (n < 2)
    return 0;
  if (n == 2)
    return 3;

  return a(n - 2) + 3 * d(n - 2) + b(n - 2);
}


void dp_tiling()
{

  int n, r;
  cin >> n;


  r = d(n);

  cout << "the result is " << r << endl;
}




int d(vector<vector<int> > &a, int r, int c)
{

  int n = a.size() - 1;

  if (n <= r) {
    return a[r][c];
  } else {
    return a[r][c] + max(d(a, r + 1, c), d(a, r + 1, c + 1));
  }

}


// Do not keep the sum in the tree node, as the modified value in the left tree can affects
// the values in the right. So, in level 3 from the top, the node in the middle is updated twice,
// first for the first node in level two, second for the second node in level two.

//  Instead of function call, store the computed value to an array will be better for
// dynamic programming.


// http://poj.org/problem?id=1163
void tri_sum() //jj
{

  int n, r;
  cin >> n;

  vector<vector<int> > a;
  a.resize(n);

  for (int i = 0; i < n; i++) {

    for (int j = 0; j < i + 1; j++) {

      int k;
      cin >> k;
      a[i].push_back(k);

    }

  }

  r = d(a, 0, 0);

  cout << "the result is " << r << endl;

}

// http://poj.org/problem?id=1163
void dp_triangle_test() //jj
{
    int line;
    cin >> line;
    vector<vector<int>> t(line, vector<int>(line));
    for (int i = 0; i < line; ++i)
    {
        for (int j = 0; j < i + 1; ++j)
        {
            int k;
            cin >> k;
            t[i][j] = k;
        }
    }

    vector<vector<int>> r(line, vector<int>(line));

    for (int i = line - 1; i >= 0; --i)
    {
        for (int j = 0; j < i + 1; ++j)
        {

            if (i == (line - 1))
            {
                r[i][j] = t[i][j];
            }
            else
            {
                r[i][j] = t[i][j] + max(r[i + 1][j], r[i + 1][j + 1]);

            }
        }
    }

    cout << "The result is " << r[0][0] << endl;
}


// http://poj.org/problem?id=1160

// I think it is similar with find_perfect_stall problem.
// or just a combination problem
int get_sum(vector<int>& vi, vector<int>& vt)
{
  int idx = 0;
  int right = vt[idx];
  int left = -1;

  int sum = 0;
  for (int i = 0; i < vi.size(); ++i) {
    if (i < right) {
      if (left == -1) {
        sum += vi[right] - vi[i];
      }
      else {
        sum += min(vi[right] - vi[i], vi[i] - vi[left]);
      }
    }
    else if (i == right) {
      left = right;
      if (idx < vt.size() - 1) {
        right = vt[++idx];
      }
    }
    else {
      sum += vi[i] - vi[right];
    }
  }

  return sum;
}

int get_min_pv(vector<int>& vi, vector<vector<int>>& vr)
{
  int sum = -1;

  for (auto& e : vr) {
    int t = get_sum(vi, e);
    if (sum == -1)
      sum = t;
    else
      sum = min(sum, t);
  }

  return sum;
}

void get_comb(vector<int>& a, vector<vector<int>>& vr, vector<int>& vt, int num_p, int idx)
{
  if (vt.size() == num_p) {
    vr.emplace_back(vt);
  }
  for (int i = idx; i < a.size(); ++i) {
    vt.emplace_back(i);
    get_comb(a, vr, vt, num_p, i + 1);
    vt.pop_back();
  }
}

void post_office() //jj
{

  int num_v, num_p;
  vector<int> vi;
  int t, min_t;

  cin >> num_v >> num_p;

  for(int i = 0; i < num_v; i++) {
    cin >> t;
    vi.push_back(t);
  }

  vector<vector<int>> vr;
  vector<int> vt;
  get_comb(vi, vr, vt, num_p, 0);

  min_t = get_min_pv(vi, vr);

  cout << "The result is " << min_t << endl;
}


// test input: 10 5 1 2 3 6 7 9 11 22 44 50
// test output: 9
void post_office_2()
{
    int num_v, num_p;
    int t, min_t;

    cin >> num_v >> num_p;

    vector<int> v(num_v + 2, 0);
    for(int i = 1; i <= num_v; i++) {
        cin >> t;
        v[i] = t;
    }

    vector<vector<int>> vi(num_v + 2, vector<int>(num_v + 2, 0));

    for (int i = 0; i <= num_v; ++i)
    {
        for (int j = i + 2; j <= num_v + 1; ++j)
        {
            int sum = 0;
            for (int k = i + 1; k < j; ++k)
            {
                if (i == 0)
                {
                    sum += v[j] - v[k];
                }
                else if (j == num_v + 1)
                {
                    sum += v[k] - v[i];
                }
                else
                {
                    int t1 = v[k] - v[i];
                    int t2 = v[j] - v[k];
                    sum += min(t1, t2);
                }
            }
            vi[i][j] = sum;
        }
    }

    min_t = 10000; // some max number

    vector<vector<int>> vr;
    vector<int> vt;
    vector<int> vv(v.begin() + 1, v.end() - 1);

    get_comb(vv, vr, vt, num_p, 0);

    for (int j = 0; j < vr.size(); ++j)
    {
        int t = 0;
        t += vi[0][vr[j][0] + 1];
        for (int k = 0; k < num_p - 1; ++k)
        {
            t += vi[vr[j][k] + 1][vr[j][k + 1] + 1];
        }
        t += vi[vr[j][num_p - 1] + 1][num_v + 1];

        min_t = min(t, min_t);
    }

    cout << "The result is " << min_t << endl;
}

void post_office_3()
{
    int num_v, num_p;
    int t;

    cin >> num_v >> num_p;

    vector<int> v(num_v + 2, 0);
    for(int i = 1; i <= num_v; i++) {
        cin >> t;
        v[i] = t;
    }

    vector<vector<int>> vi(num_v + 2, vector<int>(num_v + 2, 0));

    for (int i = 0; i <= num_v; ++i)
    {
        for (int j = i + 2; j <= num_v + 1; ++j)
        {
            int sum = 0;
            for (int k = i + 1; k < j; ++k)
            {
                if (i == 0)
                {
                    sum += v[j] - v[k];
                }
                else if (j == num_v + 1)
                {
                    sum += v[k] - v[i];
                }
                else
                {
                    int t1 = v[k] - v[i];
                    int t2 = v[j] - v[k];
                    sum += min(t1, t2);
                }
            }
            vi[i][j] = sum;
        }
    }

    vector<vector<int>> vr(num_p + 1, vector<int>(num_v + 1, 0));

    for (int i = 1; i <= num_p; ++i)
    {
        for (int j = 1; j <= num_v; ++j)
        {
            if ((j - i) <= 0)
            {
                vr[i][j] = 10000;
            }
            else
            {
                if (i == 1)
                {
                    vr[i][j] = vi[0][j];
                }
                else
                {
                    int min_t = 10000; // some big number

                    for (int k = j - 1; k > 0; --k)
                    {
                        int tmp = vr[i - 1][k] + vi[k][j];
                        min_t = min(min_t, tmp);
                    }

                    vr[i][j] = min_t;
                }
            }
        }
    }

    int min_t = 10000;

    for (int i = 1; i <= num_v; ++i)
    {
        if (vr[num_p][i] > 0)
        {
            min_t = min(min_t, vr[num_p][i] + vi[i][num_v + 1]);
        }
    }

    cout << "The result is " << min_t << endl;
}



int dp_sum(int left, int right, vector<int>& v, vector<vector<int>>& vv)
{
    // left may be -1, so increase by 1 to get it start with 0 from 2 array vector
    if (vv[left + 1][right + 1] != -1)
        return vv[left + 1][right + 1];

    int result = 0;
    if (left == -1)
    {
        for (int i = 0; i < right; ++i)
        {
            result += v[right] - v[i];
        }
    }
    else if (right == v.size())
    {
        for (int i = left + 1; i < right; ++i)
        {
            result += v[i] - v[left];
        }
    }
    else
    {
        for (int i = left + 1; i < right; ++i)
        {
            result += min(v[i] - v[left], v[right] - v[i]);
        }
    }

    // left may be -1, so increase by 1 to get it start with 0 from 2 array vector
    vv[left + 1][right + 1] = result;
    return result;
}


int dp_post_office(int left, int begin, int count, vector<int>& v, vector<vector<int>>& vv)
{
    if (count == 0)
    {
        return dp_sum(left, v.size(), v, vv);
    }
    if (count == (v.size() - begin))
    {
        return dp_sum(left, begin, v, vv);
    }

    int a = dp_post_office(left, begin + 1, count, v, vv);
    int b = dp_sum(left, begin, v, vv) + dp_post_office(begin, begin + 1, count - 1, v, vv);

    return min(a, b);
}

void post_office_4()
{
    int num_v, num_p;
    int t;

    cin >> num_v >> num_p;

    vector<int> v(num_v, 0);
    for(int i = 0; i < num_v; i++) {
        cin >> t;
        v[i] = t;
    }

    vector<vector<int>> vv(num_v + 2, vector<int>(num_v + 2, -1));
    int result = dp_post_office(-1, 0, num_p, v, vv);
    cout << " the result is " << result << endl;
}


// 'A' the code word 1, 'B' will be 2, and so on down to 'Z' being assigned 26."
// http://poj.org/problem?id=2033
// 25114 -> 6
// 1111111111 -> 89
// 3333333333 -> 1


class acode {
    // I can stick to simple algorithm. And I can go a phase which check if input is healthy or not.
    // for example, if there is more than 1 consecutive 0 in the input, then input is error.
    // So implement happy case, then extend.
public:
    int numDecodings(string s) {

        vector<int> v(s.size() + 1, 0);
        v[0] = 1;

        for (int i = 1; i <= s.size(); ++i)
        {
            int a = 0;
            if (i <= s.size() &&
                i > 1 &&
                ((s[i - 2] == '1' && s[i - 1] >= '0' && s[i - 1] <= '9') ||
                 (s[i - 2] == '2' && s[i - 1] >= '0' && s[i - 1] <= '6')))
                a = v[i - 2];

            int b = 0;
            if (s[i - 1] >= '1' && s[i - 1] <= '9')
                b =  v[i - 1];

            v[i] = a + b;

        }

        return v.back();
    }

    int foo(string& s, int i, vector<int>& m)
    {
        if (s.size() == i)
            return 1;

        if (m[i] != 0)
            return m[i];

        int a = 0;
        if (s.size() > 1 && ((s[i] == '1' && s[i + 1] >= '0' && s[i + 1] <= '9') ||
                             (s[i] == '2' && s[i + 1] >= '0' && s[i + 1] <= '6')))
            a = foo(s, i + 2, m);

        int b = 0;
        if (s[i] >= '1' && s[i] <= '9')
            b = foo(s, i + 1, m);

        m[i] = a + b;
        return a + b;
    }


};

void alphacode() //j
{
    string s;
    cin >> s;
}


int min_elem(vector<int> &vi, set<int> &s)
{
  int min = 100000000;
  int ret = 0;

  for (set<int>::const_iterator it = s.begin(); it != s.end(); it++) {
    if (min > vi[*it]) {
	min = vi[*it];
	ret = *it;
    }
  }
  return ret;
}


// http://poj.org/problem?id=2395
void hay() //jj
{

  int n, m;
  cin >> n >> m;

  vector<vector<int> > vt(n + 1, vector<int>(n + 1));

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      vt[i][j] = 10000000;

  for (int i = 0; i < m; i++) {

    int a, b, len;
    cin >> a >> b >> len;

    vt[a][b] = len;
  }

  /* shortest path algorithm by Dikstra */

  vector<int> d(vt[1].size(), 10000000);

  for (int j = 0; j < vt[1].size(); j++) {
    d[j] = vt[1][j];
  }

  set<int> s, v;
  s.insert(1);

  for (int i = 2; i <= n; i++) {
    v.insert(i);
  }

  while (v.size() > 0) {

    int w = min_elem(d, v);
    s.insert(w);
    v.erase(w);

    cout << "w is " << w << endl;
    for (set<int>::const_iterator it = v.begin(); it != v.end(); it++) {
      d[*it] = min(d[*it], d[w] + vt[w][*it]);

      cout << *it << " is " << d[*it] << endl;
    }

  }

  for (int i = 2; i <= n; i++)
    cout << "to " << i << " is " << d[i];
}

void hay2() //jj
{
  int n, m;
  cin >> n >> m;

  using elem = pair<int, int>;
  auto min_comp = [](elem& a, elem& b) {
    return a.second > b.second;
  };

  map<int, list<elem>> mm;
  set<int> s, v;

  for (int i = 0; i < m; i++) {
    int a, b, len;
    cin >> a >> b >> len;

    mm[a].push_back(elem(b, len));
    mm[b].push_back(elem(a, len));
    v.insert(a);
    v.insert(b);
  }

  /* minimal spanning tree */
  int x = *(v.begin());
  cout << "first is " << x << " and the size of v is " << v.size() << endl;
  s.insert(x);
  v.erase(x);

  priority_queue<elem, vector<elem>, decltype(min_comp)> pq(min_comp);
  for (auto e: mm[x]) {
    pq.emplace(e);
  }

  int t_max = -1;

  while (v.size() > 0) {
      auto w = pq.top();
      s.insert(w.first);
      v.erase(w.first);
      cout << w.first << " and distance is " << w.second << endl;

      t_max = max(t_max, w.second);
      pq.pop();

      for (auto e: mm[w.first]) {
          if (s.contains(e.first))
              continue;
          pq.emplace(e);
      }
  }

  cout << t_max << endl;
}


void test_vector()
{
    vector<vector<int>> va(3);
    // it should be & as it copies otherwise. Always remember to use reference
    for (auto& k : va)
        k.resize(3);

    for (int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            cout << i << "," << j << " is " << va[i][j] << endl;
        }
    }
}

list<string> kdfs(pair<int, int> e, map<pair<int,int>, bool>& visited,
         map<pair<int, int>, list<pair<int, int> > >& adj)
{
    list<pair<int, int>> adjl = adj[e];
    visited[e] = true;
    list<string> r;
    for (auto& a : adjl)
    {
        if (!visited[a])
        {
            auto rr = kdfs(a, visited, adj);
            for (auto& rrr : rr)
                r.push_back(rrr);
        }
    }

    char ss[2];
    ss[0] = 'A' + e.second;
    ss[1] = '1' + e.first;
    r.push_back(string(ss, ss + 2));
    return r;
}

// in the graph problem, node may be a compount value.
void knight_move() //jj
{
    int n, m;
    using elem = pair<int, int>;
    cin >> n >> m ;

    auto h = [&](int x) { return (x >= 0) && (x < n);};
    auto l = [&](int y) { return (y >= 0) && (y < m);};
    // find parent

    map<elem, list<elem>> adj;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (h(i - 2))
            {
                if (l(j - 1))
                    adj[elem(i, j)].push_back(elem(i - 2, j - 1));
                if (l(j + 1))
                    adj[elem(i, j)].push_back(elem(i - 2, j + 1));
            }

            if (h(i + 2))
            {
                if (l(j - 1))
                    adj[elem(i, j)].push_back(elem(i + 2, j - 1));
                if (l(j + 1))
                    adj[elem(i, j)].push_back(elem(i + 2, j + 1));
            }
             if (l(j - 2))
            {
                if (h(i - 1))
                    adj[elem(i, j)].push_back(elem(i - 1, j - 2));
                if (h(i + 1))
                    adj[elem(i, j)].push_back(elem(i + 1, j - 2));
            }

            if (l(j + 2))
            {
                if (h(i - 1))
                    adj[elem(i, j)].push_back(elem(i - 1, j + 2));
                if (h(i + 1))
                    adj[elem(i, j)].push_back(elem(i + 1, j + 2));
            }
        }
    }

    // dfs
    map<pair<int, int>, bool> visited;
    list<string> r = kdfs(elem(0, 0), visited, adj);

    if (r.size() < n * m)
        cout << "impossible" << endl;

    else
        for (auto it = r.rbegin(); it != r.rend(); ++it)
            cout << *it;

    cout << endl;
}


// worm hole  //jj todo
// seems to be just a shortest path starting from itself. Or a network flow from source to dest?
// http://poj.org/problem?id=3259


// http://poj.org/problem?id=1945 //jj todo
// single line with a single integer that is the minimum number of operations it requires to compute the power.
// given two variables (or store) to save temporary variable
// for example, for input 31, output is 6
// we can either multiply or divide.
// (x, 1), (x, x^2), ..., (x, x^32), (x, x^31)
// (1, 0), (1, 2),   ..., (1, 32), (1, 31).
// so, input is (1, 0), and output is either should (31, k) or (k, 31) for some
// k. so, the problem is to construct a graph, and dfs to find the depth, search for the min depth. each node is a pair of integer.


// http://poj.org/problem?id=3169
// layout. //jj todo


// perfect stall
// http://poj.org/problem?id=1274
int find_perfect_stall(map<int, int>& allocated, map<int, int>& visited, map<int, list<int>>& cow) //jj
{
    int m = 0;

    for (auto a : cow)
    {
        if (visited[a.first])
            continue;

        visited[a.first]++;
        int r = 0;
        for (auto e: a.second)
        {
            if (!allocated[e])
            {
                allocated[e]++;
                r = max(r, 1 + find_perfect_stall(allocated, visited, cow));
                allocated[e]--;
            }
        }
        m = max(m, r);
        visited[a.first]--;
    }

    return m;
}

void perfect_stall()
{
    int n, m;
    cin >> n >> m;

    map<int, list<int>> cow;
    for (int i = 1; i <= n; ++i)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j)
        {
            int l;
            cin >> l;
            cow[i].push_back(l);
        }
    }

    cout << "input done" << endl;
    map<int, int> allocated;
    map<int, int> visited;
    int r = find_perfect_stall(allocated, visited, cow);

    cout << r;
}

// Given two strings s and t, you have to decide whether s is a subsequence of t, i.e. if you can remove characters from t such that the concatenation of the remaining characters is s.

// sequence subsequence: yes
// person compression: no
// VERDI vivaVittorioEmanueleReDiItalia: yes
// caseDoesMatter CaseDoesMatter: no

// this can be solved like finding shortest ordered subarray in ctci.
// using array of size equal to s.size(), maintain a state machine.
// then it takes only O(n)
bool aia(string s, string t)
{
    if (s.size() == 0)
        return true;

    if (t.size() == 0)
        return false;

    int index = 0;
    for (auto i = t.begin(); i != t.end(); ++i, index++)
    {
        if ((*i == s[0]) && aia(s.substr(1), t.substr(index + 1)))
            return true;
    }

    return false;
}
// http://poj.org/problem?id=1936
bool aia2(string& s, string& t)
{
    map<int, vector<int>> mi;
    vector<int> vi(s.size(), -1);

    for (int i = 0; i < s.size(); ++i)
    {
        mi[s[i]].emplace_back(i);
    }

    for (int i = 0; i < t.size(); ++i)
    {
        if (mi.find(t[i]) != mi.end())
        {
            for (int k = mi[t[i]].size() - 1; k >= 0; --k)
            {
                int idx = mi[t[i]][k];
                if (idx == 0)
                {
                    vi[0] = i;
                }
                else if (vi[idx - 1] >= 0)
                {
                    vi[idx] = vi[idx - 1];
                    vi[idx - 1] = -1;

                    if (idx == (s.size() - 1))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void all_in_all() //jj
{
    string s, t;
    cin >> s >> t;

    if (aia2(s, t))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

}


// leetcode 115
/*
// in java
Given a string S and a string T, count the number of distinct subsequences of S which equals T.
Input: S = "rabbbit", T = "rabbit"
Output: 3
// DP

class Solution {
public int numDistinct(String s, String t) {

int v[][] = new int[s.length() + 1][t.length() + 1];

for (int i = s.length() - 1; i >= 0; --i)
{
    v[i][t.length()] = 1;
}

for (int i = t.length() - 1; i >= 0; --i)
{
    v[s.length()][i] = 0;
}

v[s.length()][t.length()] = 1;
for (int i = s.length() - 1; i >= 0; --i)
{
    for (int j = t.length() - 1; j >= 0; --j)
    {
        int a = (s.charAt(i) == t.charAt(j)) ? v[i + 1][j + 1] : 0;
        int b = v[i + 1][j];
        v[i][j] = a + b;
    }
}

return v[0][0];
}
}
*/


int get_large(vector<int> vi, int i)
{
    if (vi.size() == (i + 1))
        return vi[i];

    return max(vi[i], vi[i] + get_large(vi, i + 1));
}

void largest_sum() //jj
{
    vector<int> vi;
    int t;
    int size;

    cin >> size;

    for (int i = 0; i < size; ++i)
    {
        cin >> t;
        vi.push_back(t);
        cout << t << " ";
    }
    int max_x = -1000;

    for (int i = 0; i < vi.size(); ++i)
    {
        max_x = max(max_x, get_large(vi, i));
    }

    cout << "the result is " << max_x << endl;


    // use array computation
    vector<int> r(vi.size());

    r[vi.size() - 1] = vi[vi.size() -1];

    max_x = r[vi.size() - 1];
    for (int i = vi.size() - 2; i >= 0; --i)
    {
        r[i] = max (vi[i], vi[i] + r[i + 1]);
        if (r[i] > max_x)
            max_x = r[i];
    }

    cout << "the result is " << max_x << endl;

    int cur_max = vi[0], max_so_far = vi[0];

    for (int i = 1; i < vi.size(); ++i)
    {
        cur_max= max(vi[i], cur_max + vi[i]);
        max_so_far = max(cur_max, max_so_far);
    }

    cout << "the result is " << max_so_far << endl;


    // todo: can we do it with online (or streaming) data?
}


int get_max_path(vector<vector<int>>& v, int i, int j,
                 vector<pair<int, int>> t, vector<pair<int, int>>& r)
{
    if ((i == v.size() - 1) &&
        (j == v[0].size() - 1))
    {
        r = t;
        return v[i][j];
    }
    else if (i == v.size() - 1)
    {
        t.push_back(pair<int, int>(i, j + 1));
        return v[i][j] + get_max_path(v, i, j + 1, t, r);
    }
    else if (j == v[0].size() - 1)
    {
        t.push_back(pair<int, int>(i + 1, j));
        return v[i][j] + get_max_path(v, i + 1, j, t, r);
    }
    else
    {
        vector<pair<int, int>> t1(t);t1.push_back(pair<int, int>(i + 1, j));
        vector<pair<int, int>> t2(t);t2.push_back(pair<int, int>(i, j + 1));
        vector<pair<int, int>> r1, r2;
        int a = get_max_path(v, i + 1, j, t1, r1);
        int b = get_max_path(v, i, j + 1, t2, r2);
        if (a > b)
        {
            r = r1;
            return v[i][j] + a;
        }
        else
        {
            r = r2;
            return v[i][j] + b;
        }
    }
}

void get_max_path(vector<vector<int>>& v, int n, int m)
{
    vector<vector<int>> vs(n, vector<int>(m));

    vs[n - 1][m - 1] = v[n - 1][m - 1];

    for (int i = m - 2; i >= 0; --i)
        vs[n - 1][i] = v[n - 1][i] + vs[n - 1][i + 1];

    for (int i = n - 2; i >= 0; --i)
        vs[i][m - 1] = v[i][m - 1] + vs[i + 1][m - 1];

    for (int i = n - 2; i >= 0; --i)
    {
        for (int j = m - 2; j >= 0; --j)
        {
            vs[i][j] = v[i][j] + max(vs[i + 1][j], vs[i][j + 1]);
        }
    }

    int i = 0;
    int j = 0;
    // take care about the condition. It is !((i == n - 1) && (j == m - 1))
    while (i != n - 1 || j != m - 1)
    {
        cout << i << " " << j << endl;

        if (i == n - 1)
            ++j;
        else if (j == m - 1)
            ++i;
        else if (vs[i + 1][j] > vs[i][j + 1])
            ++i;
        else
            ++j;
        cout << i << " " << j << endl;
    }
}


void largest_path() //jj
{
    int m, n;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int t;
            cin >> t;
            v[i][j] = t;
        }
    }

    vector<pair<int, int>> t, r;
    t.push_back(pair<int, int>(0, 0));
    get_max_path(v, 0, 0, t, r);

    for (int i = 0; i < r.size(); ++i)
        cout << r[i].first << " " << r[i].second << endl;

    cout << "---------------" << endl;

    get_max_path(v,n,m);
}


// find shortest path using array computation.
// frog can jump n steps in on direction (where n is 1 ... )
// but the direction is right and below (no go back).
list<pair<int, int>> get_adj(vector<vector<int>>& v, int i, int j)
{
    list<pair<int, int>> r;

    for (int k = i + 1; k < v.size(); ++k)
        r.push_back(pair<int, int>(k, j));

    for (int k = j + 1; k < v[0].size(); ++k)
        r.push_back(pair<int, int>(i, k));

    return r;
}

int find_shortes_path(vector<vector<int>>& v, int i, int j,
                 vector<pair<int, int>> t, vector<pair<int, int>>& r)
{
    int n = v.size();
    int m = v[0].size();

    if ((i == n - 1) &&
        (j == m - 1))
    {
        r = t;
        return v[i][j];
    }
    else if (i == n - 1)
    {
        t.push_back(pair<int, int>(n - 1, m - 1));
        return v[i][j] + find_shortes_path(v, n - 1, m - 1, t, r);
    }
    else if (j == m - 1)
    {
        t.push_back(pair<int, int>(n - 1, m - 1));
        return v[i][j] + find_shortes_path(v, n - 1, m - 1, t, r);
    }
    else
    {
        auto adj = get_adj(v, i, j);
        int min = 10000; // some max value;
        for (auto& e: adj)
        {
            vector<pair<int, int>> r1;
            vector<pair<int, int>> t1(t);t1.push_back(pair<int, int>(e.first, e.second));
            int a = find_shortes_path(v, e.first, e.second, t1, r1);
            if (min > a)
            {
                min = a;
                r = r1;
            }
        }
        return v[i][j] + min;
    }
}

/*

 7 9 2 11
13 23 1 3
14 11 20 6
22 44 3 15

-> Minimum difficulty = 7 (a[0][0])+ 2(a[0][2]) +3(a[3][2])+15(a[3][3]) = 27
Path trace will have = 7->2->3->15

*/

void shortest_frog_path() //jj
{
    int m, n;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int t;
            cin >> t;
            v[i][j] = t;
        }
    }

    vector<pair<int, int>> t, r;
    t.push_back(pair<int, int>(0, 0));
    int rr = find_shortes_path(v, 0, 0, t, r);

    cout << " the result is " << rr << endl;
    for (auto& e : r)
    {
        cout << e.first << " " << e.second << endl;
    }
}

// find sequences in an array which matches to a number
// [1, 3, 8, 13] , foo(4) --> true, foo(5) --> false
// in linear time (O(n))
void match_sum()
{
    vector<int> vi;
    int t;
    int size;

    cin >> size;

    for (int i = 0; i < size; ++i)
    {
        cin >> t;
        vi.push_back(t);
        cout << t << " ";
    }

    cout << "the number to match is\n";

    int mmatch;
    cin >> mmatch;

    // method 1
    vector<int> vi2(vi.size());

    vi2[0] = vi[0];
    for (int i = 1; i < vi2.size(); ++i)
    {
        vi2[i] = vi2[i - 1] + vi[i];
    }
    cout << endl;


    unordered_map<int, int> mi;
    for (int i = 0; i < vi2.size(); ++i)
    {
        mi[vi2[i]]++;
    }

    mi[0]++; // this is necessary
    for (int i = 0; i < vi2.size(); ++i)
    {
        if (mi[vi2[i] - mmatch] > 0)
        {
            cout << "Found item at " << i << endl;
            return;
        }
    }

    // compare with largest_sum
    // // method 2
    // unordered_map<int, int> mi;
    // int sum = 0;
    // for (int i = 0; i < vi.size(); ++i)
    // {
    //     sum += vi[i];
    //     if (sum == target)
    //     {
    //         cout << "Found item at a to  " << i << endl;
    //         return;
    //     }
    //     if (mi.find(sum - mmatch) != mi.end())
    //     {
    //         cout << "Found item at " mi[sum - mmatchi] + 1 << " to "<< i << endl;
    //         return;
    //     }
    //     mi[sum] = i;
    // }

    cout << "no sequences found" << endl;
}

// match sum, same with the above but without using map
// find sequences in an array which matches to a number
// [1, 3, 8, 13] , foo(4) --> true, foo(5) --> false
// in linear time (O(n))

void match_sum2() //jj: same with herd, but did not used map.
{
    vector<int> vi;
    int t;
    int size;

    cin >> size;

    for (int i = 0; i < size; ++i)
    {
        cin >> t;
        vi.push_back(t);
        cout << t << " ";
    }

    cout << "the number to match is\n";

    int mmatch;
    cin >> mmatch;

    vector<int> vi2(vi.size());

    vi2[0] = vi[0];
    for (int i = 1; i < vi2.size(); ++i)
    {
        vi2[i] = vi2[i - 1] + vi[i];
        cout << vi2[i] << " ";
    }
    cout << endl;

    int i = 0; int j = vi2.size() - 1;

    while ((vi2[j] - vi2[i]) > mmatch)
        --j;

    while (i < j)
    {

        if (((vi2[j] - vi2[i]) == mmatch)
            || (vi2[j] == mmatch)
            || (vi[i] == mmatch))
        {
            cout << "Found item at " << i << endl;
            return;
        }

        ++i;

        while ((vi2[j] - vi2[i]) < mmatch)
            ++j;
    }
    cout << "no more sequences found" << endl;
}


bool find_match_sum(vector<int>& vi, int i, int target)
{
    int sum = 0;
    for (int j = i; j != vi.size(); ++j)
    {
        sum += vi[j];
        if (sum == target)
            return true;
    }
    return false;
}

bool match_sum_case1(vector<int>& vi, int x)
{
    for (int i = 0; i < vi.size(); ++i)
    {
        if (find_match_sum(vi, i, x))
            return true;
    }

    return false;
}


// http://poj.org/problem?id=1785
// A heap is a tree whose internal nodes have each assigned a priority (a number) such that the priority of each internal node is less than the priority of its parent. As a consequence, the root has the greatest priority in the tree, which is one of the reasons why heaps can be used for the implementation of priority queues and for sorting.
// A binary tree in which each internal node has both a label and a priority, and which is both a binary search tree with respect to the labels and a heap with respect to the priorities, is called a treap. Your task is, given a set of label-priority-pairs, with unique labels and unique priorities, to construct a treap containing this data.
// 7 a/7 b/6 c/5 d/4 e/3 f/2 g/1 -> (a/7(b/6(c/5(d/4(e/3(f/2(g/1)))))))
// 7 a/1 b/2 c/3 d/4 e/5 f/6 g/7 -> (((((((a/1)b/2)c/3)d/4)e/5)f/6)g/7)
// 7 a/3 b/6 c/4 d/7 e/2 f/5 g/1 -> (((a/3)b/6(c/4))d/7((e/2)f/5(g/1)))


class bin_search_heap_node
{
public:
    bin_search_heap_node() {}
    bin_search_heap_node(string s, string n)
    {
        label = s;
        number = atoi(n.c_str());
    };

    void print()
    {
        cout << "node is " << label << " " << number << endl;
    }
    string label;
    int number;
};


bin_search_heap_node find_max(vector<bin_search_heap_node>& v)
{
    bin_search_heap_node r;
    r.number = -1000;
    for (auto& e : v)
    {
        if (e.number > r.number)
        {
            r = e;
        }
    }

    return r;
}

vector<bin_search_heap_node> find_left(vector<bin_search_heap_node>& v,
                                       bin_search_heap_node& n)
{
    vector<bin_search_heap_node> ret;

    auto isleft = [&](bin_search_heap_node& e)
      {
          return e.label < n.label;
      };

    copy_if(v.begin(), v.end(), back_inserter(ret), isleft);
    return ret;
}

vector<bin_search_heap_node> find_right(vector<bin_search_heap_node>& v,
                                        bin_search_heap_node& n)
{
    vector<bin_search_heap_node> ret;

    auto is_right = [&](bin_search_heap_node& e)
      {
          return e.label > n.label;
      };

    copy_if(v.begin(), v.end(), back_inserter(ret), is_right);
    return ret;
}


string construct(vector<bin_search_heap_node>& v)
{
    string ret;
    ret = "(";

    bin_search_heap_node n = find_max(v);
    vector<bin_search_heap_node> vl = find_left(v, n);
    vector<bin_search_heap_node> vr = find_right(v, n);

    if (vl.size() > 0)
    {
        string left = construct(vl);
        ret += left;
    }
    ret += n.label + "/" + to_string(n.number);
    if (vr.size() > 0)
    {
        string right = construct(vr);
        ret += right;
    }

    ret += ")";
    return ret;
}


void test_bin_search_heap() //jj
{
    vector<bin_search_heap_node> v;
    int num;
    cin >> num;
    while (num != 0)
    {
        string str;
        cin >> str;
        auto i = find(str.begin(), str.end(), '/');

        v.push_back(bin_search_heap_node(string(str.begin(), i),
                                         string(i + 1, str.end())));
        --num;
    }

    cout << construct(v) << endl;
}


// cube stacking
// http://poj.org/problem?id=1988

struct cube_stack {
    int grp; // grp initially should point to itself
    int leaf; // leaf initially should point to itself
};

int find(vector<cube_stack> &vi, int x)
{
  while(vi[x].grp != x)
    x = vi[x].grp;

  return x;
}

int find_leaf(vector<cube_stack> &vi, int x)
{
    return vi[find(vi, x)].leaf;
}

int find_below(vector<cube_stack> &vi, int x)
{
    int count = 0;
    while(vi[x].grp != x)
    {
        x = vi[x].grp;
        ++count;
    }

    return count;
}

void uunion(vector<cube_stack> &vi, int x, int y)
{
    int leaf = find_leaf(vi, x);
    vi[find(vi, x)].grp = find_leaf(vi, y);
    vi[find(vi, y)].leaf = leaf;
}

void test_cube_stack() //jj
{
    int num_line, num_cube;
    string s;
    cin >> num_cube >> num_line;

    vector<cube_stack> vc;
    vc.resize(num_cube);

    for (int i = 0; i != vc.size(); ++i)
    {
        vc[i].grp = i;
        vc[i].leaf = i;
    }

    while (num_line > 0)
    {
        cin >> s;
        if (s == "M")
        {
            int first, second;
            cin >> first >> second;
            uunion(vc, first, second);
        }
        else if (s == "C")
        {
            int first;
            cin >> first;
            cout << find_below(vc, first) << endl;
        }

        --num_line;
    }
}


// find and catch
// http://poj.org/problem?id=1703
struct gang {
    int grp1;
    int grp2;
};

int find(vector<gang>& vi, int x)
{
    while ((vi[x].grp1 != x) && (vi[x].grp1 != 0))
    {
        x = vi[x].grp1;
    }

    return vi[x].grp1;
}

void uunion(vector<gang>& vi, int x, int y)
{
    if (y == 0)
    {
        vi[x].grp1 = x;
    }
    else
    {
        vi[x].grp1 = find(vi, y);
    }
}


void test_find_and_catch() //jj
{
    int m;
    cin >> m;

    vector<gang> vi;
    vi.resize(100); // assume that at most 99 gangs

    for (int i = 0; i < m; ++i)
    {
        char c;
        int x, y;
        cin >> c >> x >> y;

        if (c == 'D')
        {
            uunion(vi, x, vi[y].grp2);
            uunion(vi, y, vi[x].grp2);
            vi[y].grp2 = x;
            vi[x].grp2 = y;
        }
        else if (c == 'A')
        {
            int grpx = find(vi, x);

            int grpy = find(vi, y);
            if (grpx == 0 || grpy == 0)
                cout << "not yet" << endl;
            else if (grpx == grpy)
                cout << "same gang" << endl;
            else
                cout << "different gang" << endl;
        }
    }
}

// https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
// leetcode 307
class BIT
{
public:
    BIT()
    {
    }

    void push_back(int x)
    {
        leaf.push_back(x);

        // x -= (x & -x); // clear right most 1
        // so, (x & -x) is right most bit


        int size = leaf.size();
#if 0
        int ssum = 0;

        for (int i = size - (size & -size); i < size; ++i)
        {
            ssum += leaf[i];
        }


#endif
#if 0
        int ssum = sum(leaf.size() - 1) + x;
        ssum -= sum(size - (size & -size));
#endif
#if 1
        int i = 1;
        int ssum = x;
        while ((size & i) == 0)
        {
            ssum += inner[size - i - 1];
            i = i * 2;
        }
#endif
        inner.push_back(ssum);
    }

    void update(int i, int x)
    {
        int diff = x - leaf[i - 1];
        leaf[i - 1] = x;

        int size = leaf.size();
        while (i <= size){
            inner[i - 1] += diff;
            i += (i & -i);
        }
    }

    int sum(int i)
    {
        int ssum = 0;
        while (i > 0){
            ssum += inner[i - 1];
            i -= (i & -i);
        }
        return ssum;
    }

    int sum(int i, int j)
    {
        return (sum(j) - sum(i - 1));
    }

    void print()
    {
        for (int i = 0; i < inner.size(); ++i)
        {
            cout << inner[i] << ",";
        }
        cout << endl;

        for (int i = 0; i < leaf.size(); ++i)
        {
            cout << leaf[i] << ",";
        }
        cout << endl;

    }

private:
    vector<int> leaf;
    vector<int> inner;
};


void test_bit() //jj
{
    BIT b;
    for (int i = 1; i <= 10; ++i)
        b.push_back(i);

    b.print();
    assert(b.sum(10) == 55);
    b.update(3, 2);

    for (int i = 1; i <= 10; ++i)
    {
        cout << "sum " << i << " is " << b.sum(i) << endl;
    }
    b.print();
}

/*

N friends are playing a game. Each of them has a list of numbers in front of himself.

Each of N friends chooses a number from his list and reports it to the game administrator. Then the game administrator sorts the reported numbers and shouts the K-th largest number.

You want to know the count all possible numbers that the game administrator can shout.

Input Format:

First line of the input contain an integer T, the number of testcases. Then follow T testcases. For each test case the input is of the following format.

In the first line there are two numbers N and K. In each of next N lines there is an integer a_i followed by a_i integers, ith line describes the list for ith person.

All the numbers in all the lists are unique.

Output Format:

For each testcase print in a separate line the count of numbers that the game administrator can shout.

Sample Input

2 3 3 3 2 5 3 3 8 1 6 3 7 4 9 20 11 1 3 1 2 11 1 4 55 6 80 8 9 19 11 12 13 15 14 177 16 17 18 10 20 21 22 37 24 25 26 27 28 7 190 30 31 32 33 34 35 12 81 23 195 39 40 41 42 43 49 45 46 47 15 48 44 50 51 52 53 54 5 121 57 58 59 98 61 62 3 63 64 65 10 66 67 68 69 70 71 72 73 74 75 4 76 91 29 79 11 7 36 82 83 84 85 86 96 88 89 90 17 77 92 93 172 95 87 97 60 99 100 101 102 103 135 186 106 107 10 108 109 110 111 112 113 114 115 116 117 1 118 8 119 120 56 122 123 124 125 126 9 127 128 129 130 131 132 133 134 104 11 136 137 138 139 140 141 142 143 144 145 146 20 147 148 149 150 151 152 153 154 159 156 157 158 155 180 161 162 163 164 165 166 18 167 168 169 170 171 94 173 174 175 176 15 178 179 160 181 182 183 184 17 185 105 187 188 189 78 191 192 193 194 38 196 197 198 199 200 201

Sample Output

6 89
*/


bool kth_right(vector<int>& v, int num)
{
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] > num)
            return true;
    }
    return false;
}

bool kth_left(vector<int>& v, int num)
{
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] < num)
            return true;
    }
    return false;
}

int kth(int left, int right, int num, int index, vector<vector<int>>& v)
{
    set<int> r, l;

    for (int i = 0; i < v.size(); ++i)
    {
        if (i == index)
            continue;
        if (kth_left(v[i], num))
            l.insert(i);
        if (kth_right(v[i], num))
            r.insert(i);
    }

    vector<int> set_i;

    set_intersection(r.begin(), r.end(), l.begin(), l.end(), back_inserter(set_i));

    if (l.size() >= left && r.size() >= right &&
        (l.size() + r.size() - set_i.size() >= left + right))
        return 1;

    return 0;
}


int get_kth_number(int n, int k, vector<vector<int>>& v) //jj
{
    int r = 0;

    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[i].size(); ++j)
        {
            r += kth(k - 1, n - k, v[i][j], i, v);
        }
    }


    return r;
}


void kth_number()
{
    int n, t, k;

    cin >> t;

    vector<int> r;

    for (int i = 0; i < t; ++i)
    {
        cin >> n >> k;

        vector<vector<int>> v(n);
        for (int j = 0; j < n; ++j)
        {
            int nn;
            cin >> nn;
            for (int jj = 0; jj < nn; ++jj)
            {
                int e;
                cin >> e;
                v[j].push_back(e);
            }
        }

        r.push_back(get_kth_number(n, k, v));
    }


    cout << "the result is" << endl;
    for (auto&e : r)
        cout << e << " ";

    cout << endl;
}

/*
leetcode 907
Given an array of integers A, find the sum of min(B), where B ranges over every (contiguous) subarray of A.
Since the answer may be large, return the answer modulo 10^9 + 7

Input: [3,1,2,4]
Output: 17
Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.  Sum is 17.

sol: for each number, find the number of subarray that makes the number minimal.

for example, the number of subarray which can make 3 minimal is 1, 1 is 6, 2 is 22 and 4 is 1. so 3 * 1 + 1 * 6 + 2 * 2 + 4 * 1 = 17.
we also need to consider that, there can be duplicate elements.
// also see leetcode 316 and 84
*/


class Solution {
public:
    int sumSubarrayMins(vector<int>& A) {

        int sum = 0;
        int r = int(1e9 + 7); //to handle overflow

        unordered_map<int, int> m;

        for (int i = 0; i < A.size(); ++i)
        {
            m[i] = A.size();
        }

        stack<int> s;
        s.push(0);
        for (int i = 1; i < A.size(); ++i)
        {
            while (s.size() > 0 && A[i] < A[s.top()])
            {
                m[s.top()] = i;
                s.pop();
            }
            s.push(i);
         }

        unordered_map<int, int> m2;

        for (int i = A.size() - 1; i >= 0; --i)
        {
            m2[i] = -1;
        }

        stack<int> s2;
        s2.push(A.size() - 1);
        for (int i = A.size() - 2; i >= 0; --i)
        {
            while (s2.size() > 0 && A[i] <= A[s2.top()]) // remove duplicate case by using “<=“ instead of <.
            {
                m2[s2.top()] = i;
                s2.pop();
            }
            s2.push(i);
         }

        for (int i = 0; i < A.size(); ++i)
        {
            sum = (sum + A[i] * (m[i] - i) * (i - m2[i])) % r;
        }

        return sum;
    }
};

/*
  Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
 */

int largestRectangleArea(vector<int>& heights)
{
    stack<int> s;

    vector<int> l(heights.size(), heights.size() - 1);
    vector<int> r(heights.size(), 0);

    for (int i = 0; i < heights.size(); ++i)
    {
        while (!s.empty() && heights[s.top()] > heights[i])
        {
            l[s.top()] = i - 1;
            s.pop();
        }
        s.push(i);
    }


    while(!s.empty())
        s.pop();

    for (int i = heights.size() - 1; i >= 0; --i)
    {
        while (!s.empty() && heights[s.top()] > heights[i])
        {
            r[s.top()] = i + 1;
            s.pop();
        }
        s.push(i);
    }

    int m = 0;

    for (int i = 0; i < heights.size(); ++i)
    {
        int size = heights[i] * (l[i] - r[i] + 1);
        m = max(m, size);
    }

    return m;
}

/*

Q2 BasketBall game
A group of N high school students wants to play a basketball game. To divide themselves into two teams they first rank all the players in the following way:

Players with a higher shot percentage are rated higher than players with a lower shot percentage. If two players have the same shot percentage, the taller player is rated higher.

Luckily there are no two players with both the same shot percentage and height so they are able to order themselves in an unambiguous way. Based on that ordering each player is assigned a draft number from the range [1..N], where the highest-rated player gets the number 1, the second highest-rated gets the number 2, and so on. Now the first team contains all the players with the odd draft numbers and the second team all the players with the even draft numbers.

Each team can only have P players playing at a time, so to ensure that everyone gets similar time on the court both teams will rotate their players according to the following algorithm: Each team starts the game with the P players who have the lowest draft numbers. If there are more than P players on a team after each minute of the game the player with the highest total time played leaves the playing field. Ties are broken by the player with the higher draft number leaving first. To replace her the player on the bench with the lowest total time played joins the game. Ties are broken by the player with the lower draft number entering first.

The game has been going on for M minutes now. Your task is to print out the names of all the players currently on the field, (that is after M rotations).

Input

The first line of the input consists of a single number T, the number of test cases.

Each test case starts with a line containing three space separated integers N M P

The subsequent N lines are in the format " ". See the example for clarification.

Constraints

1 ? T ? 50 2 * P ? N ? 30 1 ? M ? 120 1 ? P ? 5 Each name starts with an uppercase English letter, followed by 0 to 20 lowercase English letters. There can be players sharing the same name. Each shot percentage is an integer from the range [0..100]. Each height is an integer from the range [100..240]

Output

For each test case i numbered from 1 to T, output "Case #i: ", followed by 2 * P space separated names of the players playing after M rotations. The names should be printed in lexicographical order.

Example

In the first example if you sort all the players by their shot percentage you get the list: [Wai, Purav, Weiyan, Slawek, Lin, Meihong]. This makes the two teams: [Wai, Weiyan, Lin] [Purav, Slawek, Meihong]

The game starts with Lin and Meihong sitting on the bench in their respective teams. After the first minute passes it's time for Weiyan and Slawek to sit out since they have the highest draft numbers of the people who played. After the second minute passes Lin and Meihong will keep playing since they only played one minute so far and it's Wai and Purav who have to sit out.

Finally after the third minute Lin and Maihong go back to the bench and all the players currently playing again are: Purav Slawek Wai Weiyan


*/

struct  student {
    student(string n, int h=0, int p=0) : name(n), height(h), per(p), st(0), pt(0), num(0)
    {}
    void print()
    {
        cout << name << " ";
    }
    string name;
    int num;
    int height;
    int per;
    int st;
    int pt;
};

bool pred_p(student& a, student& b) {
    if (b.pt > a.pt)
        return true;
    else if (b.pt == a.pt) {
        if (b.num > a.num)
            return true;
        else
            return false;
    }
    else return false;
}

bool pred_s(student& a, student& b) {
    if (b.st > a.st)
        return true;
    else if (b.st == a.st) {
        if (b.num < a.num)
            return true;
        else
            return false;
    }
    else return false;
}


void process_q(vector<student>& h1p, vector<student>& h1s,
               vector<student>& h2p, vector<student>& h2s)
{
    for (auto& e: h1p)
        e.pt += 1;
    for (auto& e: h2p)
        e.pt += 1;
    for (auto& e: h1s)
        e.st += 1;
    for (auto& e: h2s)
        e.st += 1;

    pop_heap(h1p.begin(), h1p.end(), pred_p);
    h1s.push_back(h1p.back());
    push_heap(h1s.begin(), h1s.end(), pred_s);
    h1p.pop_back();
    pop_heap(h1s.begin(), h1s.end(), pred_s);
    h1p.push_back(h1s.back());
    push_heap(h1p.begin(), h1p.end(), pred_p);
    h1s.pop_back();

    pop_heap(h2p.begin(), h2p.end(), pred_p);
    h2s.push_back(h2p.back());
    push_heap(h2s.begin(), h2s.end(), pred_s);
    h2p.pop_back();
    pop_heap(h2s.begin(), h2s.end(), pred_s);
    h2p.push_back(h2s.back());
    push_heap(h2p.begin(), h2p.end(), pred_p);
    h2s.pop_back();
}

void basketball()
{
    int t, n, m, p;
    cin >> t;
    cin >> n >> m >> p;

    auto pred = [&](student& a, student &b) {
        if (a.per < b.per)
            return true;
        else if (a.per == b.per) {
            if (a.height < b.height)
                return true;
            else
                return false;
        }
        else
            return false;
    };

    for (int i = 0; i < t; ++i) {
        vector<student> vs;
        for (int j = 0; j < n; ++j) {
            string s;
            int h, p;
            cin >> s >> h >> p;
            vs.push_back(student(s, h, p));
        }

        sort(vs.begin(), vs.end(), pred);

        vector<student> h1p;
        vector<student> h1s;
        vector<student> h2p;
        vector<student> h2s;

        for (int j = 0; j < vs.size(); j += 2)
        {
            vs[j].num = j + 1;
            vs[j + 1].num = j + 2;
            h1s.push_back(vs[j]);
            h2s.push_back(vs[j + 1]);
        }

        make_heap(h1s.begin(), h1s.end(), pred_s);
        make_heap(h2s.begin(), h2s.end(), pred_s);

        pop_heap(h1s.begin(), h1s.end(), pred_s);
        h1p.push_back(h1s.back());
        h1s.pop_back();
        pop_heap(h2s.begin(), h2s.end(), pred_s);
        h2p.push_back(h2s.back());
        h2s.pop_back();

        make_heap(h1p.begin(), h1p.end(), pred_p);
        make_heap(h2p.begin(), h2p.end(), pred_p);

        for (int j = 0; j < m; ++j)
            process_q(h1p, h1s, h2p, h2s);

        for (auto&e : h1p)
            e.print();
        for (auto&e : h2p)
            e.print();
    }
}

void test_basketball()
{
    int p = 2;
    int m = 3;
    vector<student>vs;
    vs.push_back(student("Wai"));
    vs.push_back(student("Pur"));
    vs.push_back(student("Wei"));
    vs.push_back(student("Sla"));
    vs.push_back(student("Lin"));
    vs.push_back(student("Mei"));

    vector<student> h1p;
    vector<student> h1s;
    vector<student> h2p;
    vector<student> h2s;

    for (int j = 0; j < vs.size(); j += 2)
    {
        vs[j].num = j + 1;
        vs[j + 1].num = j + 2;
        h1s.push_back(vs[j]);
        h2s.push_back(vs[j + 1]);
    }

    make_heap(h1s.begin(), h1s.end(), pred_s);
    make_heap(h2s.begin(), h2s.end(), pred_s);

    pop_heap(h1s.begin(), h1s.end(), pred_s);
    h1p.push_back(h1s.back());
    h1s.pop_back();
    pop_heap(h1s.begin(), h1s.end(), pred_s);
    h1p.push_back(h1s.back());
    h1s.pop_back();
    pop_heap(h2s.begin(), h2s.end(), pred_s);
    h2p.push_back(h2s.back());
    h2s.pop_back();
    pop_heap(h2s.begin(), h2s.end(), pred_s);
    h2p.push_back(h2s.back());
    h2s.pop_back();

    make_heap(h1p.begin(), h1p.end(), pred_p);
    make_heap(h2p.begin(), h2p.end(), pred_p);

    for (int j = 0; j < m; ++j)
    {
        cout << endl << "-----------" << endl;
        process_q(h1p, h1s, h2p, h2s);

        for (auto&e : h1p)
            e.print();
        for (auto&e : h2p)
            e.print();
        cout << endl << "-----------" << endl;
    }
}


struct jobs2m {
    jobs2m(int i, int j, int k) :index(i), a(j), b(k)
    {
    }

    bool operator<(const jobs2m &other) const
    {
        if (index < other.index)
            return true;
        else if (index == other.index) {
            if (a < other.a)
                return true;
            else if (a == other.a) {
                if (b < other.b)
                    return true;
                else return false;
            }
            else return false;
        }
        else return false;
    }

int index;
    int a;
    int b;
};

map<jobs2m, int> jobs2m_map;

int process_jobs2m(int idx, vector<int>& a, vector<int>& b, int ka, int kb, int k)
{

    // todo: I think this is not right. This implementation just returns minimum
    // process time, not the time taken to complete all the jobs.
    if (idx == a.size())
        return 0;

    // todo: we can use 2 parameters instead of two.
    jobs2m t(idx, ka, kb);
    if (jobs2m_map.find(t) != jobs2m_map.end())
        return jobs2m_map[t];

    int r;

    if (ka == 0)
    {
        r = b[idx] + process_jobs2m(idx + 1, a, b, k, kb - 1, k);
    }
    else if (kb == 0)
    {
        r = a[idx] + process_jobs2m(idx + 1, a, b, ka - 1, k, k);
    }
    else
    {
        r =  min(a[idx] + process_jobs2m(idx + 1, a, b, ka - 1, k, k),
                 b[idx] + process_jobs2m(idx + 1, a, b, k, kb - 1, k));
    }

    jobs2m_map[t] = r;
    return r;
}


/*
You are given 2 machines. There are N jobs you have to perform. Job i takes Ai time to perform on machine A and Bi time to perform on machine B. Each job should be done either on machine A or B. The jobs should be performed in order. Given the arrays A and B and an integer K, find the minimum time required to complete the jobs, given that you cannot do more than K jobs on the same machine continuously. This can be done in O(N K)space and time. This can be improved to O(N K) time and O(N ) space and further to O(N logN ) time.
*/
void two_machine_n_jobs() //jj
{

    int n, k;
    cin >> n >> k;

    int t;
    vector<int> a, b;

    for (int i = 0; i < n; ++i)
    {
        cin >> t;
        a.push_back(t);
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> t;
        b.push_back(t);
    }


    // recursive call to find the optimal solution.
    int r = process_jobs2m(0, a, b, k, k, k);

    cout << "the result is " << r << endl;

    // we can also find optimal solution by first sorting the diff between
    // the two machine, and select from the beggest gap first al the way
    // to the end of the job list. For any index i in the array, if selecting
    // small valued machine makes more than k consecutive, then select the other
    // machineways

    r = 0;
    using elem = pair<int, int>;
    vector<elem> d;
    for (int i = 0; i < n; ++i)
    {
        d.push_back(elem(abs(a[i] - b[i]), i));
    }

    sort(d.begin(), d.end(), [](elem&a, elem&b) { return a.first < b.first; });

    vector<int> vr(n);

    for (int i = n - 1; i >= 0; --i)
    {
        int idx = d[i].second;
        int t = 0;

        if (a[idx] > b[idx])
            t = -1;
        else if (a[idx] < b[idx])
            t = 1;
        else {
            r += a[idx];
            continue;
        }

        int cnt = 1;
        for (int j = idx - 1; j >= 0; --j)
        {
            if (vr[j] != t)
                break;
            ++cnt;
        }
        for (int j = idx + 1; j <= n - 1; ++j)
        {
            if (vr[j] != t)
                break;
            ++cnt;
        }

        if (cnt > k)
            t = -t;

        vr[idx] = t;

        if (t > 0)
            r += a[idx];
        else
            r += b[idx];
    }

    cout << "the result is " << r << endl;
}


// 1. start with finding staff that has the same sum
// 2. then find (from the result of 1) the weight staff
vector<int> find_staff(vector<int>& v, int i, int len)
{
    int sum = v[i + len] - v[i];

    vector<int> r;

    for (int j = i + len; j < v.size() - len; ++j)
    {
        int t = v[j + len] - v[j];
        if (t == sum)
            r.push_back(j);
    }

    return r;
}

vector<int> find_match_staff(vector<int>& v, int i, int len, vector<int>& r)
{
    vector<int> rr;

    return rr;
}


void staff() //jj
{
    string s;

    cin >> s;

    vector<int> v;
    vector<char> vc(s.begin(), s.end());

    for (auto& e: vc)
        v.push_back(int(e - '0'));

    int m_max = 0;
    vector<int> vs;
    vs[0] = v[0];
    for (int i = 1; i < v.size(); ++i)
    {
        vs[i] = v[i] + vs[i - 1];
    }

    int max_len = v.size() / 2;

    // start with max_len first, as we will stop if we find
    // the longest staff
    bool found = false;
    for (int len = max_len; len >= 1 ; --len)
    {
        for (int i = 0; i + len < v.size(); ++i)
        {
            vector<int>r = find_staff(vs, i, len);
            vector<int> rr = find_match_staff(v, i, len, r);
            if (rr.size() > 0)
            {
                found = true;
// we found it;
            }
        }

        if (found)
            break;
    }
}


struct bt_node {
    bt_node(int v) : val(v), left(nullptr), right(nullptr) {}
    bt_node* left;
    bt_node* right;
    int val;
};

void  find_first_left(bt_node* n, stack<bt_node*> &ls)
{
    ls.push(n);
    if (n->left)
    {
        return find_first_left(n->left, ls);
    }
    else
    {
        return;
    }
}

bt_node* get_next_left(stack<bt_node*> &ls)
{
    if (ls.empty())
        return nullptr;
    bt_node* n = ls.top();
    ls.pop();
    if (n->right)
        find_first_left(n->right, ls);
    return n;
}

void find_first_right(bt_node* n, stack<bt_node*> &rs)
{
    rs.push(n);
    if (n->right)
    {
        return find_first_right(n->right, rs);
    }
    else
    {
        return;
    }
}

bt_node* get_next_right(stack<bt_node*> &rs)
{
    if (rs.empty())
        return nullptr;
    bt_node* n = rs.top();
    rs.pop();
    if (n->left)
        find_first_right(n->left, rs);
    return n;
}

void find_match_sum_bintree() //jj
{
    bt_node a(6);
    bt_node b(3);
    bt_node c(8);
    a.left = &b;
    a.right = &c;

    bt_node d(1);
    bt_node e(4);
    b.left = &d;
    b.right = &e;

    bt_node f(7);
    bt_node g(12);
    c.left = &f;
    c.right = &g;

    stack<bt_node*> ls, rs;

    find_first_left(&a, ls);
    find_first_right(&a, rs);

    bt_node* left = ls.top();ls.pop();
    bt_node* right = rs.top();rs.pop();

    int match = 16;

    while (left->val < right->val) {
        // cout << "left is " << left->val << " and right is " << right->val << endl;
        if (left->val + right->val < match)
            left = get_next_left(ls);
        else if (left->val + right->val > match)
            right = get_next_right(rs);
        else
        {
            cout << "found " << left->val << " " << right->val << endl;
            left = get_next_left(ls);
            right = get_next_right(rs);
        }
    }
}

//
// How to save bst and retrieve it? how to serialise and reconstruct?
//

vector<int> serialise_bst(bt_node* n)
{
    vector<int> a;

    if (!n)
        return a;

    a.push_back(n->val);

    if (n->left)
    {
        vector<int> l = serialise_bst(n->left);
        copy(l.begin(), l.end(), back_inserter(a));
    }
    if (n->right)
    {
        vector<int> l = serialise_bst(n->right);
        copy(l.begin(), l.end(), back_inserter(a));
    }

    return a;
}

vector<int> left_tree(vector<int>& v)
{

    vector<int> r;
    if (v.size() == 0)
        return r;

    int m = v[0];

    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i] > m)
            break;
        r.push_back(v[i]);
    }
    return r;
}


bt_node* construct_bst(vector<int>& v)
{
    bt_node* n = nullptr;

    if (v.size() == 0)
        return n;

    n = new bt_node(v[0]);
    vector<int> l = left_tree(v);
    n->left = construct_bst(l);
    vector<int> r(v.begin() + l.size() + 1, v.end());
    n->right = construct_bst(r);

    return n;
}


void test_save_reconstruct_bst() //jj
{
    bt_node a(6);
    bt_node b(3);
    bt_node c(8);
    a.left = &b;
    a.right = &c;

    bt_node d(1);
    bt_node e(4);
    b.left = &d;
    b.right = &e;

    bt_node f(7);
    bt_node g(12);
    c.left = &f;
    c.right = &g;

    vector<int> r = serialise_bst(&a);
    cout << "before" << endl;
    for (auto e: r)
        cout << e << " ";
    cout << endl;

    bt_node* n = construct_bst(r);

    r = serialise_bst(n);
    cout << "after" << endl;
    for (auto e: r)
        cout << e << " ";
    cout << endl;
}

/*
Convert a doubly linked list to a Binary Search Tree
Given a sorted doubly linked list, create a BST which
is balanced and not skewed. */
bt_node* make_tree(list<int>& l)
{
    if (l.begin() == l.end())
        return nullptr;

    // find middle

    auto first = l.begin();
    auto last = l.end();
    while (first != last)
    {
        --last;
        if (first == last)
            break;
        ++first;
    }

    bt_node* n {new bt_node(*first)};
    list<int> left {l.begin(), first};
    auto next = first;
    ++next;
    list<int> right {next, l.end()};
    n->left = make_tree(left);
    n->right = make_tree(right);

    return n;
}


void print(bt_node* r)
{
    if (!r)
    {
        cout << "null" << endl;
        return;
    }

    cout << r->val << endl;
    print(r->left);
    print(r->right);
}


void test_bst_from_list() //jj
{
    // find middle and divide and conquer, call make_tree
    //
    // shared_ptr<node> m{new node(middle->val)};
    // m->left = make_tree(begin, middle->left);
    // m->right = make_tree(middle->right, end);

    int n;

    cin >> n;

    list<int> l;
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        l.push_back(t);
    }

    bt_node* r = make_tree(l);

    cout << " The result is " << endl;

    print(r);
}


// construct binary tree from the traverse of
// its post order and pre order.
// For example,
// a b c d e f g (left is root, bfs),
// a b d e c f g (pre order)
// d e b f g c a (post order)
vector<int> left_tree(vector<int>& va, vector<int>& vb)
{
    set<int> a;
    set<int> b;

    for (int i = 0; i + 1 < va.size(); ++i)
    {
        a.insert(va[i + 1]);
        b.insert(vb[i]);
        if (a == b)
            break;
    }

    return vector<int>(va.begin() + 1, va.begin() + 1 + a.size());
}


bt_node* make_tree(vector<int> va, vector<int> vb)
{
    bt_node* n = nullptr;
    if (va.size() == 0 || vb.size() == 0)
        return n;

    n = new bt_node(va[0]);

    vector<int> l = left_tree(va, vb);
    n->left = make_tree(l, vector<int>(vb.begin(), vb.begin() + l.size()));
    vector<int> r(va.begin() + l.size() + 1, va.end());
    n->right = make_tree(r, vector<int>(vb.begin() + l.size(), vb.end() - 1));

    return n;
}

void construct_binarytree_from_post_and_pre_order_traverse() //jj
{
    int n;
    cin >> n;
    vector<int> va, vb;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        va.push_back(t);
    }

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        vb.push_back(t);
    }

    bt_node* node = make_tree(va, vb);
    vector<int> r = serialise_bst(node);
    cout << "after" << endl;
    for (auto e: r)
        cout << e << " ";
    cout << endl;

}


//
// binary tree (not bst), find whether node b is in between the path from a to c
//
bool search_topdown_path(bt_node* n, list<bt_node*> l)
{
    if (l.empty())
        return true;

    if (!n)
        return false;

    bt_node* t = l.front();

    if (n == t) {
        l.pop_front();
        if (l.empty())
            return true;
    }

    bool r = false;
    // l is copied, so no need to worry about the
    // changes in the subtree
    // if we want to consider pre-order traversal,
    // then l should be reference type.

    r = search_topdown_path(n->left, l);
    if (r)
        return true;

    r = search_topdown_path(n->right, l);
    if (r)
        return true;

    return false;
}


void test_search_node_path() //jj
{
    bt_node a(6);
    bt_node b(3);
    bt_node c(8);
    a.left = &b;
    a.right = &c;

    bt_node d(1);
    bt_node e(4);
    b.left = &d;
    b.right = &e;

    bt_node f(7);
    bt_node g(12);
    c.left = &f;
    c.right = &g;

    bt_node h(100);
    bt_node i(120);
    f.left = &h;
    g.right = &i;

    list<bt_node*> l = {&a, &c, &i};
    if (search_topdown_path(&a, l))
        cout << "yes1" << endl;

    l = {&a, &c, &h};
    if (search_topdown_path(&a, l))
        cout << "yes2" << endl;

    l = {&a, &b, &i};
    if (search_topdown_path(&a, l))
        cout << "no1" << endl;

    l = {&a, &i, &h};
    if (search_topdown_path(&a, l))
        cout << "no2" << endl;
}





/*

The beauty of a number X is the number of 1s in the binary representation of X.

Two players are plaing a game. There is number n written on a black board. The game is played as following:

Each time a player chooses an integer number (0 <= k) so that 2^k is less than n and (n-2^k) has as much beauty as n. Next he removes n from blackboard and writes n-2^k instead. The player that can not continue the game (there is no such k that satisfies the constrains) looses the game.

The First player starts the game and they play in turns alternatively. Knowing that both two players play optimally you have to specify the winner.

Input:

First line of the Input contains an integer T, the number of testcase. 0 <= T <= 5.

Then follow T lines, each containing an integer n.

n more than 0 and less than 10^9 +1.

Output

For each testcase print "First Player" if first player can win the game and "Second Player" otherwise.

Sample Input

7 1 2 8 16 42 1000 123

Sample Output

Second Player First Player First Player Second Player Second Player First Player Second Player

Explanation

In the first example n is 1 and first player can't change it so the winner is the second player.

In the second example n is 2, so the first player subtracts 1 (2^0) from n and the second player looses the game.

 */


int get_ones(int x)
{
    int i = 0;
    while (x > 0)
    {
        x = x & (x - 1);
        i += 1;
    }

    return i;
}



int get_btr(int r)
{
    int i = 1;
    int num = get_ones(r);
    while (r > i)
    {
        int x = get_ones(r - i);
        if (x == num)
            return (r - i);
        i = i * 2;
    }

    return -1;
}

/*

The beauty of a number X is the number of 1s in the binary representation of X.
Two players are plaing a game. There is number n written on a black board. The game is played as following:

Each time a player chooses an integer number (0 <= k) so that 2^k is less than n and (n-2^k) has as much beauty as n. Next he removes n from blackboard and writes n-2^k instead. The player that can not continue the game (there is no such k that satisfies the constrains) looses the game.

The First player starts the game and they play in turns alternatively. Knowing that both two players play optimally you have to specify the winner.
*/

void beauty_number() //jj
{
    int x;
    cin >> x;

    int user = 0;
    while (x > 0)
    {
        cout << "before " << x;
        x = get_btr(x);
        cout << " and after " << x << endl;
        if (x == -1)
            break;

        user += 1;
    }

    string winner;
    if ((user % 2) == 1)
        winner = "user1";
    else
        winner = "user2";

    cout <<"winner is " << winner << endl;
}


// get maximum number i where i is 1, 2, 4, 8, ...
int get_dum(int x, int y)
{
    if (x < y)
        return 0;

    int i = 1;
    while (x >= y * i * 2)
        i *= 2;

    return i;
}



// this can be implemented using get_dum.
void div_using_mul(int x, int y) //jj
{
    int r = 0;
    while (x >= y)
    {
        int k = 1;
        // actually it can be done without multiplication.
        // we can just use bit >> or <<
        while (x >= 2 * k * y)
            k *= 2;

        x -= k * y;
        r += k;
    }

    cout << " the result is " << r << " and " << x << endl;
}

void test_div_using_mul()
{
    int x, y;
    cin >> x >> y;

    div_using_mul(x, y);
}


// leetcode 441
// You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.
//   Given n, find the total number of full staircase rows that can be formed.
//   n is a non-negative integer and fits within the range of a 32-bit signed integer.
//   Example 1:
//   n = 5
int arrangeCoins(int n)
{
  long long low=0,high=n;
  long long ans=0;

  while(low<=high)
    {
      long long mid=low+(high-low)/2;
      long long s=mid*(mid+1)/2;
      if(s==n) return mid;
      else if(s<n) {ans=mid; low=mid+1;}
      else high=mid-1;
    }

  return ans; // or just h or l - 1 is all the same

}


/*
Your task is to decode messages that are encoded with substitution ciphers. In a substitution cipher, all occurrences of a character are replaced by a different character. For example, in a cipher that replaces "a" with "d" and "b" with "e", the message "abb" is encoded as "dee".

The exact character mappings that are used in the substitution ciphers will not be known to you. However, the dictionary of words that were used will be given. You will be given multiple encoded messages to decode (one per line) and they may use different substitution ciphers. The same substitution cipher is used on all of the words in a particular message.

For each scrambled message in the input, your program should output a line with the input line, followed by the string " = " (without the quotes), followed by the decoded message.

Example:

input file:

//dict

hello

there

yello

thorns

//secret

12334 51272

12334 514678

output:

12334 51272 = hello there

12334 514678 = hello thorns
*/


struct dcpr {
    dcpr(const char* m) : msg(m), visited(false) {}
    string msg;
    bool visited;
};

bool dcpr_match(dcpr& a, dcpr&b, map<char, char>& cmap)
{
    // cout << "match " << a.msg << " " << b.msg << " ";
    if (a.msg.size() != b.msg.size()) {
        // cout << "false 1" << endl;
           return false;
    }

    for (int i = 0; i < a.msg.size(); ++i)
    {
        char c = a.msg[i];
        if (cmap.find(c) != cmap.end())
        {
            if (cmap[c] != b.msg[i])
            {
                // cout << "false 2" << endl;
                return false;
            }
        }
    }

    return true;
}

map<char, char> update_map(dcpr& a, dcpr&b, map<char, char> cmap)
{
    // update cmap
    for (int i = 0; i < a.msg.size(); ++i)
    {
        char c = a.msg[i];
        cmap[c] = b.msg[i];
    }

    // cout << "true" << endl;
    return cmap;
}

void proc_dcpr(int i, vector<dcpr>& vb, vector<dcpr>& va, map<char, char>& cmap)
{
    // cout << "proc with i " << i << endl;
    if (i == vb.size())
    {
        cout << "found" << endl;
        for (auto& ee : vb)
        {
            cout << ee.msg << " = " ;
            string ss;
            for (int k = 0; k < ee.msg.size(); ++k)
                ss.push_back(cmap[ee.msg[k]]);
            cout << ss << endl;
        }
        return;
    }

    for (auto& e : vb)
    {
        if (e.visited)
            continue;
        e.visited = true;

        for (auto& a : va)
        {
            if (a.visited)
                continue;
            if (!dcpr_match(e, a, cmap))
                continue;
            a.visited = true;
            auto mmap = update_map(e, a, cmap);
            proc_dcpr(i + 1, vb, va, mmap);
            a.visited = false;
        }
        e.visited = false;
    }

}

void decipher() //jj
{
    vector<dcpr> va = {"hello", "there", "yello", "thorns"};
    vector<dcpr> vb1 = {"12334", "51272"};
    vector<dcpr> vb2 = {"12334", "514678"};

    map<char, char> cmap;

    proc_dcpr(0, vb1, va, cmap);

    cmap.clear();
    proc_dcpr(0, vb2, va, cmap);
}


/*

  remove unnecessary parenthesis from an explression

  (((( a + b)) c )) -> (a + b) c
  ((a) + (b)) -> a + b

*/


string remove_parenthesis(string str) //jj
{
    stack<string> stk;

    for (auto c : str)
    {

        if (c != ')')
        {
            string ss(1, c);
            stk.push(ss);
        }
        else
        {
            string s;
            int count = 0;

            while (stk.top() != "(")
            {
                s += stk.top();
                count++;
                stk.pop();
            }

            // remove '('
            stk.pop();

            if (count == 0)
                continue;

            if (count > 1)
                s = "(" + s + ")";

            stk.push(s);
        }

    }

    string r = string(stk.top().begin() + 1, stk.top().end() - 1);
    return r;
}


void test_remove_par()
{
    string s;
    cin >> s;

    string r = remove_parenthesis(s);

    cout << "the result is " << r << endl;

}

// Given a string with alpha-numeric characters and parentheses,
// return a string with balanced parentheses by removing the fewest characters possible.
// You cannot add anything to the string.
void test_remove_unbalanced_par()
{
    //sol: step 1: from left to right, if there is a mismatching ')' then delete it from the string.
    // step 2: from right to lefti, if there is a mismatching '(', then delete it from the string.

    string s;
    cin >> s;

    int par = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(')
        {
            ++par;
        }
        else if (s[i] == ')')
        {
            if (par > 0)
            {
                --par;
            }
            else
            {
                s.erase(s.begin() + i);
                --i;
            }
        }
    }

    cout << "the result is " << s << endl;
    par = 0;
    for (int i = s.size() - 1; i >= 0; --i)
    {
        if (s[i] == ')')
        {
            ++par;
        }
        else if (s[i] == '(')
        {
            if (par > 0)
            {
                --par;
            }
            else
            {
                s.erase(s.begin() + i);
            }
        }
    }

    cout << "the result is " << s << endl;
}

// leetcode 301
// Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
// Note: The input string may contain letters other than the parentheses ( and ).
//     Example 1:
//       Input: "()())()"
//       Output: ["()()()", "(())()"]
// https://leetcode.com/problems/remove-invalid-parentheses/discuss/498070/Python-100
/* python code
def removeInvalidParentheses(self, s: str) -> List[str]:
   def valid(s):
        count = 0
        for i in s:
            if i == "(": count += 1;
            elif i == ")": count -= 1;
            if count < 0: return False;
        return count == 0;
   def bfs(s):
        queue = [s]
        visited = {}
        res = []
        found = False
        while queue:
            temp = queue.pop(0)
            if temp in visited:
                continue;
            visited[temp] = True
            if valid(temp):
                found = True
                res.append(temp)
            if found: continue
            for i in range(len(temp)):
                if temp[i] == "(" or temp[i] == ")":
                    new = temp[:i] + temp[i+1:]
                    queue.append(new)
        return res
   return bfs(s)
*/
void test_reverse_sum() //jj
{
    string a, b;
    cin >> a >> b;

    int len = max(a.size(), b.size());
    string r;
    int carry = 0;

    for (int i = 0; i < len; ++i)
    {
        int x = 0, y = 0;

        if (i < a.size())
            x = a[i] - '0';
        if (i < b.size())
            y = b[i] - '0';

        int sum = x + y + carry;
        carry = (sum >= 10)? 1 : 0;
        sum = sum % 10;

        r.push_back('0' + sum);
    }

    if (carry == 1)
        r.push_back('1');

    int i;
    for (i = 0; i < r.size(); ++i)
    {
        if (r[i] != '0')
            break;
    }

    string t = r.substr(i);
    cout << " the result is "  << t << endl;
}
int gget (string& s, int idx)
{
    if (idx >= s.size())
        return 0;

    return s[s.size() - 1 - idx] - '0';
}

string bin_add(string& s1, string& s2) //jj
{
    int len = max(s1.size(), s2.size());
    string s3;
    int carry = 0;

    for (int i = 0; i < len; ++i)
    {
        int t = carry + gget(s1, i) + gget(s2, i);
        carry = t / 2;
        string r = (t % 2)? "1" : "0";
        s3 = r + s3;
    }

    // this is important. always check the last element.
    if (carry)
        s3 = "1" + s3;

    return s3;
}


void bin_string_add()
{
    string s1, s2;
    cin >> s1 >> s2;

    string r = bin_add(s1, s2);

    cout << r << endl;

    // sol2: reverse it first
    // search test_reverse_sum
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());

    int carry = 0;
    string r2;

    auto first1 = s1.begin();
    auto last1 = s1.end();
    auto first2 = s2.begin();
    auto last2 = s2.end();

    while (carry || first1 != last1 || first2 != last2)
    {
        int a = (first1 == last1)? 0: *first1++ - '0';
        int b = (first2 == last2)? 0: *first2++ - '0';

        int sum = carry + a + b;
        carry = sum / 2;
        r2 += (sum % 2) + '0';
    }


    reverse(r2.begin(), r2.end());
    cout << r2 << endl;

}

/*
  u are given an array containing 0s and 1s. Give an O(n) time algorithm to
find the maximum contiguous sub sequence which has equal number of 1s and 0s.

Examples

1) 10101010

The longest contiguous sub sequence that satisfies the problem is the input itself

2)1101000

The longest sub sequence that satisfies the problem is 110100
*/

int gmbs_get(vector<int>& vs, int beg, int len)
{
    if (len == 0)
        return 0;
    int j = beg + len - 1;

    if (beg == 0)
        return vs[j];
    else
        return vs[j] - vs[beg - 1];
}


pair<int, int> max_p(pair<int, int> a, pair<int, int> b)
{
    if (a.first > b.first)
        return a;
    return b;
}

pair<int, int> gmbs_rec(vector<int>&vs, int beg, int len)
{
    if (gmbs_get(vs, beg, len) * 2 == len)
    {
        return pair<int, int>(len, beg);
    }
    else
    {
        return max_p(gmbs_rec(vs, beg, len - 1),
                     gmbs_rec(vs, beg + 1, len - 1));
    }
}

// iteration
pair<int, int> gmbs_iter(vector<int>&vs, int beg, int size)
{
    int len = size - size % 2; // same number of 0's and 1's means that it is even number.
    while (len > 0)
    {
        for (int i = beg; i + len <= size; ++i)
        {
            if (gmbs_get(vs, i, len) * 2 == len)
            {
                return pair<int, int>(len, i);
            }

        }
        len = len - 2;
    }

    return pair<int, int>(0, 0);
}

// sum_to_k
// get max binary sequence
// linear
// same problem as longest subarray sum to zero or sum to x
// similar to largest sum
pair<int, int> gmbs_linear(vector<int>& v)
{
    int len = 0;
    int sum = 0;
    int index = -1;
    unordered_map<int, int> m;
    m[0] = -1;

    for (int i = 0; i < v.size(); ++i)
    {
        sum += (v[i] == 0)? -1 : 1;

        if (m.find(sum) != m.end()) // searching for k? then sum - k
        {
            if (len < i - m[sum]) // here as well, sum -k
            {
                len = i - m[sum]; // sum - k
                index = i;
            }
        }
        if (m.find(sum) == m.end()) // if sum to zero, this if stmt can be replaced with just else of above if-stmt, but if sum to k (which is not zero) then we need this, as the map function should find sum - k above.
        {
            m[sum] = i;
        }
    }

    return pair<int, int>(len, index - len + 1);
}

pair<int, int> gmbs(vector<int>& v)
{
    vector<int> vs(v.size());
    vs[0] = v[0];
    for (int i = 1; i < v.size(); ++i)
    {
        vs[i] = vs[i - 1] + v[i];
    }

    return gmbs_rec(vs, 0, vs.size());
}

pair<int, int> gmbs2(vector<int>& v)
{
    vector<int> vs(v.size());
    vs[0] = v[0];
    for (int i = 1; i < v.size(); ++i)
    {
        vs[i] = vs[i - 1] + v[i];
    }

    return gmbs_iter(vs, 0, vs.size());
}

void get_max_bin_subsequence()
{
    vector<int> v1;

    int n;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v1.push_back(t);
    }

    pair<int, int> r;

    r = gmbs(v1);
    cout << r.first << " " << r.second << endl;

    r = gmbs2(v1);
    cout << r.first << " " << r.second << endl;

    r = gmbs_linear(v1);
    cout << r.first << " " << r.second << endl;
}


// find largest equal binary sequence of two
int find_lcs_dp(string s1, string s2)
{
    int n = s1.size() + 1;
    int m = s2.size() + 1;

    vector<vector<int>> v(n, vector<int>(m, 0));

    int max_len = 0;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                v[i][j] = v[i - 1][j - 1] + 1;
                max_len = max(max_len, v[i][j]);
            }
            else
            {
                v[i][j] = 0;
            }
        }
    }

    return max_len;
}

void get_eq_bin_subsequence()
{
    string s1, s2;

    cin >> s1 >> s2;

    int result = find_lcs_dp(s1, s2);

    cout << "the result is " << result << endl;
}

void add_without_plus() //jj
{
    int a, b;
    cin >> a >> b;

    unsigned int carry = 0; // if it is int, then 1 - 1 gives wrong answer

    do {
        carry = a & b;
        b = a ^ b;
        a = carry << 1;
    } while (carry != 0);

    cout << "the  result is " << b;

}

void test_set()
{
    set<set<int>> ss;

    set<int> s1 = {1, 2};
    set<int> s2 = {1, 2};

    ss.insert(s1);
    ss.insert(s2);

    assert(1 == ss.size());


    set<vector<int>> ls;

    vector<int> l1 = {1, 2};
    vector<int> l2 = {1, 2};

    ls.insert(l1);
    ls.insert(l2);

    assert(1 == ls.size());
}


int lsna(int i, vector<int>& v)
{
    if (i >= v.size())
        return 0;

    return max(v[i] + lsna(i + 2, v),
               lsna(i + 1, v));
}

int lsna_table(vector<int>& v)
{
    vector<int> t(v.size());
    int size = t.size();
    if (size == 0)
        return 0;
    if (size == 1)
        return v[0];

    t[size - 1] = v[size - 1];
    t[size - 2] = max(v[size - 1], v[size - 2]);

    for (int i = size - 3; i >= 0; --i)
    {
        t[i] = max(t[i + 1], v[i] + t[i + 2]);
    }

    return t[0];
}


void largest_sum_no_adjcent() //jj
{

    int n;
    vector<int> v;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;

        v.push_back(t);
    }

    int r = lsna(0, v);
    cout << r << endl;
    r = lsna_table(v);
    cout << r << endl;
}


int fnre(vector<int>& vi, int i, int j)
{
    if (i > j)
        return -1; // did not find one

    int m = i + (j - i) / 2;

    if ((vi[m - 1] != vi[m]) &&
        vi[m + 1] != vi[m])
        return vi[m];

    if (m % 2)
    {
        if (vi[m] == vi[m - 1])
            return fnre(vi, m + 1, j);
        else
            return fnre(vi, i, m - 1);
    }
    else
    {
        if (vi[m] == vi[m - 1])
            return fnre(vi, i, m - 1);
        else
            return fnre(vi, m + 1, j);
    }

}

// all elements are repeated except one. Find it as quick as possible.
void test_find_non_repeated_elem() //jj
{
    int n;
    vector<int> vi;

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        vi.push_back(t);
    }

    cout << fnre(vi, 0, vi.size() - 1) << endl;
}

void test_find_longest_repeated_char() //jj
{
    string s;
    cin >> s;

    char prev = s[0];
    int count = 1;
    int max = 0;
    list <char> l;

    for (int i = 1; i < s.size(); ++i)
    {
        if (prev != s[i])
        {
            if (count > max)
            {
                max = count;
                l.clear();
                // sometimes interviewer wants other data structure than map
                l.push_back(prev);
            }
            else if (count == max)
            {
                l.push_back(prev);
            }

            prev = s[i];
            count = 1;
        }
        else
        {
            ++count;
        }
    }

    // don' forget the condition after exit (i.e., carry)
    if (count > max)
    {
        max = count;
        l.clear();
        l.push_back(prev);
    }
    else if (count == max)
    {
        l.push_back(prev);
    }

    for (auto& e: l)
        cout << e << " ";
    cout << endl;
}

void test_first_unrepeated_char() //jj
{
    string s;
    cin >> s;

    char prev = s[0];
    int count = 1;

    for (int i = 1; i < s.size(); ++i)
    {
        if (prev != s[i])
        {
            if (count == 1)
                break;

            prev = s[i];
            count = 1;
        }
        else
        {
            ++count;
        }
    }

    if (count == 1)
        cout << "the result is " << prev << endl;
}

// Find the first repeated word in a string
// Given a string, Find the 1st repeated word in a string
//                 Input : "Ravi had been saying that he had been there"
//                 Output : had

//                 Input : "Ravi had been saying that"
//                 Output : No Repetition
void test_first_repeated_word_in_a_string()
{
    // sol: use istringstream to tokenise the string, and use map to count occurence.

    string s;
    cin >> s;
    istringstream iss(s);
    string token;

    // hashmap for storing word and its count
    // in sentence
    unordered_map<string, int> setOfWords;

    // store all the words of string
    // and the count of word in hashmap

    while (getline(iss, token, ' ')) {
        setOfWords[token] += 1;
    }

    // do the rest
}


void test_find_a_missing_number_in_4_billion_number_in_a_file() //jj
{
    // You have a file in which there are supposed to be 4 billion numbers,
    // starting from 1 to 4,000,000,000 but unfortunately one number is missing,
    // i.e there are only 3,999,999,999 numbers, You need to find the missing number.

    // it is s^32
    // sol 1: first 16 bit of the integer can be bucket, and the next 16 bit can be index.
    // for each number x in the file, count[x >> 16]++ then for each c in count check if
    // c is less then 2^16. If it is, that means that bucket has missing number.
    // Then pass the the file again, use a bitset<2^16> bs, and for each number x
    // check if x is in the bucket. If it is, then bs.set(x & (1<<16 - 1).
    // Finally, for each bs[i] check if it is 0. If it is, then that is the missing number
    // solution 2: n (n + 1) / 2 = 1 + 2 + ... + n, so
    // missing number = n ( n + 1) / 2 - sum
    // but it may take too long time to keep adding very big value
}

void test_searching_words_in_a_very_big_file() //jj
{
    // Given a large file, how will you store the words in the file so that
    // searching of a word can be done in constant time? Also how will you find
    // the 10 most frequently occurring word.


    // sol 1: trie, each end node has the list of the positions
    //        in the file. After constructing the trie, scan the
    // trie to create map<int, list<string>> where int is the number of occurences
    // and list<stirng> is string that occurs int times in the file.

    // sol 2: multiple hash, as single hash may create hash corriding.
}



// find the biggest '+' mark in a sparse matrix (0 and 1).
// left, right, top, down wing should be same length of '1's. So
// if left has two '1' and the rest has one '1' then we should take one.
// also remember this is sparse matrix
// leetcode 764 using DP
void find_biggest_plus(vector<string>& v)
{
    using elem = pair<int, int>;

    auto adj = [&] (int i, int j, int depth) {
        if ((v[i][j] == '1') &&
            (i - depth >= 0) &&
            (i + depth < v.size()) &&
            (j - depth >= 0) &&
            (j + depth < v[0].size()) &&
            (v[i + depth][j] == '1') &&
            (v[i - depth][j] == '1') &&
            (v[i][j - depth] == '1') &&
            (v[i][j + depth] == '1'))
        {
            return true;
        }

        return false;
    };

    list<elem> l;
    elem r(-1, -1);
    int depth = 1;

    for (int i = 1; i < v.size() - 1; ++i)
    {
        for (int j = 1; j < v[0].size() - 1; ++j)
        {
            if (adj(i, j, depth))
            {
                l.emplace_back(elem(i, j));
            }
        }
    }
    l.emplace_back(r);


    list<elem> k;
    while(!l.empty())
    {
        elem e = l.front();
        l.pop_front();

        if (e.first == -1)
        {
            if (l.empty())
            {
                if (k.empty())
                {
                    cout << "found nothing" << endl;
                }
                else
                {
                    elem e = k.front();
                    cout << "the result is " << e.first << " " << e.second << " " << depth << endl;
                }
            }
            else
            {
                ++depth;
                l.emplace_back(e);
                k.clear();
            }
        }
        else
        {
            if (adj(e.first, e.second, depth + 1))
            {
                l.emplace_back(e);
            }
            k.emplace_back(e);
        }
    }
}

void test_find_biggest_plus() //jj
{
    vector<string> v = {"0010010",
                        "1010101",
                        "1111111",
                        "0010000",
                        "0000000"}; // result: (2, 2, 1)

    find_biggest_plus(v);
}


// You have N toffee packets, each containing different number of toffees. The number of toffees contained in the ith packet is denoted by ci. You need to put these toffee packets in 5 boxes such that each box contains at least one toffee packet, and the maximum number of toffees in a box is minimum. You can only choose consecutive toffee packets to put in a box.

// using DP?
// leetcode 410
// toffee in the below implementation is not optimal. Please take a look at splitarray implementation below which is
// actually same as toffee problem
int toffee(int sum, int begin, int count, vector<int>& v)
{
    if (count == 0)
    {
        return sum + accumulate(v.begin() + begin, v.end(), 0);
    }

    if (count == (v.size() - begin))
    {
        auto a = *max_element(v.begin() + begin, v.end());
        return max(a, sum);
    }

    int a = toffee(sum + v[begin], begin + 1, count, v);
    int b = max(sum + v[begin], toffee(0, begin + 1, count - 1, v));

    return min(a, b);
}

void test_toffee()
{
    int n, k; // n is size of toffee packet, k is size of box
    cin >> n >> k;

    vector<int> v;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.emplace_back(t);
    }

    auto r = toffee(0, 0, k - 1, v);

    cout << "the result is " << r << endl;
}


// leetcode 410, same as toffee above
// Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

//                                      Input:
//                                      nums = [7,2,5,10,8]
//                                      m = 2

//                                      Output:
//                                      18

int foo(vector<int>& nums, int idx, int m, vector<long long>& v, vector<vector<int>>& mm);
int splitArray(vector<int>& nums, int m) {

    vector<long long> v(nums.size());
    v[0] = nums[0];
    for (int i = 1; i < nums.size(); ++i)
    {
        v[i] = nums[i] + v[i - 1];
    }

    vector<vector<int>> mm(nums.size() + 1, vector<int>(m + 1, -1));
    return foo(nums, 0, m, v, mm);

}

int foo(vector<int>& nums, int idx, int m, vector<long long>& v, vector<vector<int>>& mm)
{
    if (mm[idx][m] != -1)
        return mm[idx][m];

    if (m == 1)
    {
        int res = (idx == 0) ? v[nums.size() - 1] : v[nums.size() - 1] - v[idx - 1];
        mm[idx][m] = res;
        return res;
    }


    int r = INT_MAX;

    for (int i = idx; nums.size() - i >= m; ++i)
    {
        int a = (idx == 0) ? v[i] : v[i] - v[idx - 1];
        if (a > r)
            break;
        int b = foo(nums, i + 1, m - 1, v, mm);
        int mmax = max(a, b);
        r = min(mmax, r);
    }

    mm[idx][m] = r;
    return r;
}


// Given an array of Integers, find out how many combinations in the array, satisfy the equation x+y+z=w, where x,y,z and w belong to the array and idx(x)<idx(y)<idx(z)<idx(w). Elements are unique.
// 1 0 1 2 0 -1 4 -> 2
int find_3_numbers_sum_to_w(int sum, int idx, int cnt, vector<int>& v, unordered_map<int, int>& m)
{
    // todo: how to cache?
    // sol1: 2 dimensional array (sum, idx + cnt*v.size()) -> val)
    // sol2: map(obj) -> val where obj is a struct of (int, int, int).
    if (cnt == 0)
    {
      // todo: delete this sol as this is wrong. are there any duplicate?
        if ((m.find(sum) != m.end()) && (m[sum] >= idx))
        {
            return 1;
        }

        return 0;
    }

    // this
    int r = 0;
    for (int i = idx; i < v.size(); ++i)
    {
        r += find_3_numbers_sum_to_w(sum + v[i], i + 1, cnt - 1, v, m);
    }
    return r;

    // or this
    // if (idx == v.size()) return 0;
    // int a = find_3_numbers_sum_to_w(sum, idx + 1, cnt, v, m);
    // int b = find_3_numbers_sum_to_w(sum + v[idx], idx + 1, cnt - 1, v, m);
    // return a + b;

}

int find_3_numbers_sum_to_w_2(vector<int>& v)
{
    int cnt = 0;
    unordered_map<int, int> s1;
    for (int i = 1; i < v.size() - 2; ++i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            s1[v[i] + v[j]]++;
        }

        for (int j = i + 2; j < v.size(); ++j)
        {
            if(s1.find(v[j] - v[i + 1]) != s1.end())
            {
                cnt += s1[v[j] - v[i + 1]];
            }
        }
    }

    return cnt;
}

void test_find_3_numbers_sum_to_w()
{
    int n;
    vector<int> v;
    unordered_map<int, int> m;

    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.emplace_back(t);
        m[t] = i;
    }

    int r = find_3_numbers_sum_to_w(0, 0, 3, v, m);
    cout << " the result is " << r << endl;

    r = find_3_numbers_sum_to_w_2(v);
    cout << " the result is " << r << endl;
}


// find all numbers the sum of cube of each digits is the number itself
// ex:153=1^3+5^3+3^3
// todo: from cube of each number, get the combination of numbers and see if it is the number itself? reverse order?
void test_find_numbers_xyz_equal_cube_of_all_digit()
{
    int n;
    cin >> n;

    vector<int> vvv;
    for (int i = 0; i < 10; ++i)
    {
        vvv.emplace_back(pow(i, 3));
    }

    auto get_sum = [&](int x) {
        int sum = 0;

        while (x > 0)
        {
            int t = x % 10;
            x = x / 10;
            sum += vvv[t];
        }

        return sum;
    };

    for (int i = 0; i < n; ++i)
    {
        if (i == get_sum(i))
        {
            cout << " found at " << i << endl;
        }
    }
}

vector<char> parse(string& t, unordered_map<char, int>& m)
{
    stack<char> rator;
    vector<char> rand;

    auto CE = [](){ cout << "Compilation Error" << endl; };

    string keyword = "+-/*";

    for (int i = 0; i < t.size(); ++i)
    {
        if (isspace(t[i]))
        {
            continue;
        }

        if (m.find(t[i]) == m.end() &&
            find(keyword.begin(), keyword.end(), t[i]) == keyword.end())
        {
            CE(); return {};
        }

        if (isalpha(t[i]))
        {
            if (rator.empty())
            {
                if (!rand.empty())
                {
                    CE(); return {};
                }
                rand.emplace_back(t[i]);
            }
            else
            {
                if (rator.top() == '*' || rator.top() == '/')
                {
                    rand.emplace_back(t[i]);
                    rand.emplace_back(rator.top());
                    rator.pop();
                }
                else
                {
                    rand.emplace_back(t[i]);
                }
            }
        }
        else
        {
            if (rand.empty())
            {
                CE(); return {};
            }
            else if (t[i] == '*' || t[i] == '/')
            {
                rator.push(t[i]);
            }
            else
            {
                if (!rator.empty() && (rator.top() == '+' || rator.top() == '-'))
                {
                    rand.emplace_back(rator.top());
                    rator.pop();
                }
                rator.push(t[i]);
            }
        }
    }

    if (!rator.empty())
    {
        rand.emplace_back(rator.top());
    }

    return rand;
}

int interpret(vector<char>& v, unordered_map<char, int>& m)
{
    stack<int> s;

    auto compute = [](char op, int b, int a){
        if (op == '+') {return a + b;}
        else if (op == '-') {return a - b;}
        else if (op == '*') {return a * b;}
        else {return a / b;}
    };

    for(int i = 0; i < v.size(); ++i)
    {
        if (isalpha(v[i]))
        {
            s.push(m[v[i]]);
        }
        else
        {
            auto a = s.top(); s.pop();
            auto b = s.top(); s.pop();
            s.push(compute(v[i], a, b));
        }
    }

    return s.top();
}

// leetcode 224, 227
void test_interpret_using_postfix()
{
// How to evaluate a mathematical expression by compiler design. The program will ask the user to input a value (say n). Then user will input n lines of input each of which contains an identifier and its corresponding value. Then program will ask the user again to input a value (say m). Then user will input m lines of expressions. Calculate the final value for each of the given expression using first n lines of input. If you can't evaluate any expression from given numbers of identifiers then output 'Compilation Error'. Allowed mathematical operators are +(add), -(subtract), x(multiply), /(divide).

// Example: a = 1
// b = 2
// c = 2


// a x b + a x c + b x c output 8
// a x c - b / c + c x c out put 5


// g = 2
// p = 3
// t = 1
// w = 2

// g + p x t - w x p output -1
// t - g + t - w output -2
// e + t x t - m output compilation error


    // sol1: similar to sol1, but instead of compute x and % in first scan, push them in operand stack (i.e., a x b -> a b x), and make operand stack as a postfix expressions, then compute it.

    // sol2: using operator stack and operand stack, first scan compute x and %, then compute + and - using values in operator stack and operand stack. stack is for char, so the result of * or / should be stored as a temporary var. Finally, operand stack should have 1 value, and operator stack should be empty. When computing operator, if there is just one operand, then it is a compilation error too. But it is hard to maintain temporary var.
    int n;
    cin >> n;

    unordered_map<char, int> m;
    for (int i = 0; i < n; ++i)
    {
        char c;
        int t;
        cin >> c >> t;

        m[c] = t;
    }

    string s;
    getline(cin, s);
    getline(cin, s);

    // most parsing error should be caught by parse
    vector<char> p = parse(s, m);

    if (!p.empty())
    {
        for (int i = 0; i < p.size(); ++i)
            cout << p[i] << ' ';
        cout << endl;
        int r = interpret(p, m);
        cout << " the result is " << r << endl;
    }

}

void test_zig()
{
    vector<vector<int>> v {{1, 2}, {3, 4, 5, 6}};
    int i = -1;
    list<int> l; // instead of integer, we can use iterator for each of vector

    auto get = [&](int i) {
                   if (v[0].size() > i)
                       l.push_back(v[0][i]);
                   if (v[1].size() > i)
                       l.push_back(v[1][i]);
               };

    auto hasNext = [&]() {
                       if (!l.empty())
                           return true;
                       get(++i);
                       if (l.empty())
                           return false;
                       return true;
                   };

    auto getNext = [&]() {
                       int a = l.front();
                       l.pop_front();
                       return a;
                   };


    while (hasNext())
        cout << getNext() << " ";

    cout << endl;
}


/*
  In a row of trees, the i-th tree produces fruit with type tree[i].
  You start at any tree of your choice, then repeatedly perform the following steps:

  1. Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
  2. Move to the next tree to the right of the current tree.  If there is no tree to the right, stop.
  Note that you do not have any choice after the initial choice of starting tree: you must perform step 1, then step 2, then back to step 1, then step 2, and so on until you stop.

  You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.

  What is the total amount of fruit you can collect with this procedure?

  Input: [3,3,3,1,2,1,1,2,3,3,4]
  Output: 5
  Explanation: We can collect [1,2,1,1,2].
  If we started at the first tree or the eighth tree, we would only collect 4 fruits.
 */
int totalFruit(vector<int>& tree) {

    int prev = tree[0];
    unordered_map<int, int> m;
    m[prev] = 0;
    int begin = 0;
    int max_t = 1;

    for (int i = 1; i < tree.size(); ++i)
    {
        if (m.find(tree[i]) != m.end())
        {
            if (prev != tree[i])
                m[tree[i]] = i;
        }
        else
        {
            if (m.size() == 2)
            {
                max_t = max(max_t, i - begin);
                begin = m[prev];
                m.clear();
                m[prev] = begin;
            }
            m[tree[i]] = i;
        }

        prev = tree[i];
    }

    max_t = max(max_t, int(tree.size() - begin));
    return max_t;
}


/*
  leetcode 974
Input: A = [4,5,0,-2,-3,1], K = 5
    Output: 7
    Explanation: There are 7 subarrays with a sum divisible by K = 5:
    [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
*/
int subarraysDivByK(vector<int>& A, int K) {

    int sum = 0, cnt = 0;

    map<int, int> m;

    m[0] = 1;

    for (int i = 0; i < A.size(); ++i)
    {
        sum += A[i];

        if (m.find(sum % K) != m.end())
        {
            cnt += m[sum % K];
        }
        if (m.find((sum % K) - K) != m.end()) // if sum is plus, but there would be minus to consider (i.e., [-1, 2, 9], K = 2)
        {
            cnt += m[(sum % K) - K];
        }
        if (m.find((sum % K) + K) != m.end()) // if sum is minus, but there would be plus to consider
        {
            cnt += m[(sum % K) + K];
        }


        m[sum % K]++;

    }
    return cnt;
}


class RegexMatcher {
public:
    // bool isMatch(string s, string p) {

    //     return isMatch(s, 0, p, 0);
    //  }

    bool isMatch(string s, string p) {

        vector<vector<bool>> v(s.size() + 1, vector<bool>(p.size() + 1, false));
        v.back().back() = true;

        for (int i = s.size(); i >= 0; --i)
        {
            for (int j = p.size() - 1; j >= 0; --j)
            {
                bool match = (i < s.size() && ((p[j] == s[i]) || (p[j] == '.')));
                if (j + 1 < p.size() && p[j + 1] == '*')
                {
                    auto a = v[i][j + 2];
                    auto b = match && v[i + 1][j];
                    v[i][j] =  a | b;
                }
                else
                {
                    v[i][j] = match && v[i + 1][j + 1];
                }
            }
        }

        return v[0][0];
    }

    bool isMatch(string s, int i, string p, int j)
    {
        if (i == s.size())
        {
            if(j == p.size())
            {
                return true;
            }
        }

        if (j == p.size())
        {
            if (i < s.size())
            {
                return false;
            }
        }

        if (p[j] == '.')
        {
            if (j + 1 < p.size() && p[j + 1] == '*')
            {
                auto a = isMatch(s, i, p, j + 2);
                auto b = (i >= s.size()) ? false : isMatch(s, i + 1, p, j);
                return a | b;
            }
            else
            {
                return isMatch(s, i + 1, p, j + 1);
            }

        }
        else if (isalpha(p[j]))
        {
            if (j + 1 < p.size() && p[j + 1] == '*')
            {
                auto a = isMatch(s, i, p, j + 2);
                auto b = (i <= s.size() && s[i] == p[j])? isMatch(s, i + 1, p, j) : false;
                return a | b;
            }
            else
            {
                return (s[i] == p[j]) && isMatch(s, i + 1, p, j + 1);
            }
        }

        return false;
    }

};

void test_sign()
{
    unsigned int x = -2147483648;
    unsigned int y = -1;
    int x1 = abs(-2147483648);
    int y1 = abs(-1);
    cout << x1 << " " << y1 << endl;
}


/*
  in an array of integer, each number has the number of bigger numbers on the right.
  For example, [2, 3, 1, 7, 6], 2 has 3, 3 has 2, 1 has 2, 7 has0, 6 has 0.
  This problem should return the index of the number which has the most, in this case index 0 (for number 2).
 */
 // leetcode 315


struct anode {
    anode() : left(-1), right(-1), cnt_right(0) {};
    int left;
    int right;
    int cnt_right;
};

int push_tree(vector<int>& v, vector<anode>& t, int i)
{
    int idx = v.size() - 1;
    if (idx == i)
    {
        return 0;
    }

    int x = 0;
    while (idx != i)
    {
        if (v[idx] > v[i])
        {
            if (t[idx].left == -1)
                t[idx].left = i;
            x += 1 + t[idx].cnt_right;
            idx = t[idx].left;
        }
        else
        {
            if (t[idx].right == -1)
                t[idx].right = i;
            t[idx].cnt_right++;
            idx = t[idx].right;
        }
    }

    return x;
}


// merge a (start), m (middle), e (end)
void merge(vector<vector<int>>& v, int a, int m, int e)
{
  // cout << "enter merge" << endl;
  vector<vector<int>> v1{v.begin() + a, v.begin() + m + 1};
  vector<vector<int>> v2{v.begin() + m + 1, v.begin() + e + 1};

  int a1 = 0, a2 = 0;
  int e1 = v1.size(), e2 = v2.size();

  // cout << "enter loop" << endl;
  while (true)
    {
      if (a1 == e1)
      {
        // cout << "step 1" << endl;
        copy(v2.begin() + a2, v2.end(), v.begin() + a);
        break;
      }
      if (a2 == e2)
        {
          // cout << "step 2" << endl;
          copy(v1.begin() + a1, v1.end(), v.begin() + a);
          break;
        }
      v[a++] = v1[a1][0] > v2[a2][0] ? v2[a2++] : v1[a1++];
    }

  // cout << "leave merge" << endl;
}

// call find_most_bigger_numbers_right(v, 0, nums.size() - 1, vi)
// and then find the index of biggest element in vi, return it.
void find_most_bigger_numbers_right(vector<vector<int>>& v, int a, int e, unordered_map<int, int>& m)
{
  if (a >= e)
    return;

  int mid = (a + e) / 2;
  find_most_bigger_numbers_right(v, a, mid, m);
  find_most_bigger_numbers_right(v, mid + 1, e, m);

  for (int i = a; i <= mid; ++i)
    {
      int cnt = 0;
      for (int j = e; j > mid && v[i][0] < v[j][0]; --j)
        {
          ++cnt;
        }
      m[v[i][1]] += cnt;

    }

  merge(v, a, mid, e);
}

int sol4_find_max_right_idx(vector<int>& v)
{
  unordered_map<int, int> m;
  vector<vector<int>> vi (v.size(), vector<int>(2, 0));

  for (int i = 0; i < v.size(); ++i)
    {
      vi[i][0] = v[i];
      vi[i][1] = i;
    }

  find_most_bigger_numbers_right(vi, 0, v.size() - 1, m);

  int r = 0;
  for (auto& e : m)
    {
      r = max(r, e.second);
    }

  return r;
}


void test_find_number_which_has_the_most_bigger_numbers_on_the_right()
{
    int n;
    cin >> n;

    vector<int> v;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    int x = 0;
    vector<anode> tr(v.size());

    // sol1: using binary search tree (as shown below), but worst time complexity is O(n*n)
    // sol2: using binary search tree (using upper_bound), keep right side sorted. upper_bound runs in O(log(n)), but you need to shift the rest of the numbers to make it sorted, which is O(n), so using upper_bound is O(n * n) as well. We should use upper_bound because lower_bound returns the begining of the same numbers.
    // sol3: using stack. read from right, keep pop stack until top of the stack is bigger number. Then push all the poped numbers on to stack. O(n * n)
    // sol4: using merge sort.


    // this is sol1
    for (int i = v.size() - 1; i >= 0; --i)
    {
        int t = push_tree(v, tr, i);
        x = max(x, t);
    }
    cout << "the result of sol1 is " << x << endl;

    cout << "the result of sol4 is " << sol4_find_max_right_idx(v) << endl;
}


/*
  Given a non-empty binary tree, find the maximum path sum.

  For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.
 */
struct TreeNode {
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    int val;
    TreeNode* left;
    TreeNode* right;
};

class MaxPathSum {
public:
    int m{INT_MIN};

    int maxPathSum(TreeNode* root) {
        if (root == nullptr)
            return 0;

        foo(root);

        return m;
    }

    int foo(TreeNode* n)
    {
        if (n == nullptr)
            return 0;

        int l = foo(n->left);
        int r = foo(n->right);

        if (l < 0 && r < 0)
        {
            m = max(m, n->val);
            return n->val;
        }
        else if (l < 0)
        {
            m = max(m, n->val + r);
            return n->val + r;
        }
        else if (r < 0)
        {
            m = max(m, n->val + l);
            return n->val + l;
        }
        else
        {
            m = max(m, n->val + l + r);
            return n->val + max(l, r);
        }
    }
};


// find max gap
// Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
// Return 0 if the array contains less than 2 elements.
// BIN sort (radix sort)
int maximumGap(vector<int>& nums)
{

    if (nums.empty() || nums.size() < 2)
        return 0;

    int maxVal = *max_element(nums.begin(), nums.end());

    int exp = 1;                                 // 1, 10, 100, 1000 ...
    int radix = 10;                              // base 10 system

    vector<int> aux(nums.size());

    /* LSD Radix Sort */
    while (maxVal / exp > 0) {                   // Go through all digits from LSD to MSD
        vector<int> count(radix, 0);

        for (int i = 0; i < nums.size(); i++)    // Counting sort
            count[(nums[i] / exp) % 10]++;

        for (int i = 1; i < count.size(); i++)   // you could also use partial_sum()
            count[i] += count[i - 1];

        for (int i = nums.size() - 1; i >= 0; i--)
            aux[--count[(nums[i] / exp) % 10]] = nums[i];

        for (int i = 0; i < nums.size(); i++)
            nums[i] = aux[i];

        exp *= 10;
    }

    int maxGap = 0;

    for (int i = 0; i < nums.size() - 1; i++)
        maxGap = max(nums[i + 1] - nums[i], maxGap);

    return maxGap;
}

// maxgap with buckets and pigeonhole principle
class Bucket {
public:
    bool used = false;
    int minval = numeric_limits<int>::max();        // same as INT_MAX
    int maxval = numeric_limits<int>::min();        // same as INT_MIN
};
int maximumGap2(vector<int>& nums)
{
    if (nums.empty() || nums.size() < 2)
        return 0;

    int mini = *min_element(nums.begin(), nums.end()),
        maxi = *max_element(nums.begin(), nums.end());

    int bucketSize = max(1, (maxi - mini) / ((int)nums.size() - 1));        // bucket size or capacity
    int bucketNum = (maxi - mini) / bucketSize + 1;                         // number of buckets
    vector<Bucket> buckets(bucketNum);

    for (auto&& num : nums) {
        int bucketIdx = (num - mini) / bucketSize;                          // locating correct bucket
        buckets[bucketIdx].used = true;
        buckets[bucketIdx].minval = min(num, buckets[bucketIdx].minval);
        buckets[bucketIdx].maxval = max(num, buckets[bucketIdx].maxval);
    }

    int prevBucketMax = mini, maxGap = 0;
    for (auto&& bucket : buckets) {
        if (!bucket.used)
            continue;

        maxGap = max(maxGap, bucket.minval - prevBucketMax);
        prevBucketMax = bucket.maxval;
    }

    return maxGap;
}


// Knight is at (0, 0), Princess is at bottom right. Knight should rescue princess.
// in order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.
//     Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

//leet code 174, 741
int CalcMinHealth_DP(vector<vector<int>>& d)
{
    int row = d.size();
    int col = d[0].size();
    int A[row][col];
    A[row - 1][col - 1] = d[row - 1][col - 1];

    for (int i = row - 2; i >= 0; --i)
    {
        int x = d[i][col - 1];
        if (A[i + 1][col - 1] < 0)
            x = x + A[i + 1][col - 1];
        A[i][col - 1] = x;
    }

    for (int j = col - 2; j >= 0; --j)
    {
        int y = d[row - 1][j];
        if (A[row - 1][j + 1] < 0)
            y = y + A[row - 1][j + 1];
        A[row - 1][j] = y;
    }

    for (int i = row - 2; i >= 0; --i)
    {
        for (int j = col - 2; j >= 0; --j)
        {
            int x = max(A[i + 1][j], A[i][j + 1]);
            int y = d[i][j];
            if (x < 0)
                y = y + x;
            A[i][j] = y;
        }
    }

    if (A[0][0] <= 0)
        return 1 - A[0][0];
    else
        return 1;
}

/*
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.
Input: "2*3-4*5"
Output: [-34, -14, -10, -10, 10]
Explanation:
(2*(3-(4*5))) = -34
    ((2*3)-(4*5)) = -14
    ((2*(3-4))*5) = -10
    (2*((3-4)*5)) = -10
    (((2*3)-4)*5) = 10
*/
class diffway{
public:
    vector<int> diffWaysToCompute(string input) {

        int idx = 0;
        vector<int> rand;
        vector<char> rator;

        while (idx < input.size())
        {
            int j = 0;
            while (isdigit(input[idx + j]))
            {
                ++j;
                if (idx + j == input.size())
                    break;
            }
            rand.push_back(stoi(input.substr(idx, j)));
            idx = idx + j;

            if (idx < input.size() && (input[idx] == '+' || input[idx] == '*' || input[idx] == '-'))
            {
                rator.push_back(input[idx]);
                idx++;
            }
        }


        int size = rand.size();

        vector<vector<vector<int>>> v(size, vector<vector<int>>(size, vector<int>()));

        for (int i = 0; i < size; ++i)
        {
            v[i][i].push_back(rand[i]);
        }

        for (int t = 1; t < size; ++t)
        {
            for (int i = 0; i + t < size; ++i)
            {
                // for each operator
                for (int j = i; j < i + t; ++j)
                {
                    for (auto& e1 : v[i][j])
                    {
                        for (auto& e2 : v[j + 1][i + t])
                        {
                            int r = compute(rator[j], e1, e2);
                            v[i][i + t].push_back(r);
                        }
                    }
                }
            }
        }

        return v[0][size - 1];
    }

    int compute(char c, int x, int y)
    {
        if (c == '*')
            return x * y;
        else if (c == '+')
            return x + y;
        else
            return x - y;
    }
};

/*
  Write a program to find the nth super ugly number.

  Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

  Example:

  Input: n = 12, primes = [2,7,13,19]
  Output: 32
  Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
  super ugly numbers given primes = [2,7,13,19] of size 4.
 */
int nthSuperUglyNumber(int n, vector<int>& primes) {
    vector<int> k(primes.size(), 0);
    vector<int> v(n, 0);
    v[0] = 1;

    for (int i = 1; i < n; ++i)
    {
        int m = INT_MAX;
        for (int j = 0; j < primes.size(); ++j)
        {
            int val = primes[j] * v[k[j]];
            m = min(val, m);
        }

        v[i] = m;
        for (int j = 0; j < primes.size(); ++j)
        {
            if (m == primes[j] * v[k[j]])
                ++k[j];
        }
    }

    return v[n - 1];
    }

/* leetcode 316
  Given a string which contains only lowercase letters, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

  Example 1:

  Input: "bcabc"
  Output: "abc"
  Example 2:

  Input: "cbacdcbc"
  Output: "acdb"
 */
// using stack
// also see leetcode 907
string removeDuplicateLetters(string s) {
    string res;
    vector<int>cnt(26,0);   // arr to store cnt of each character
    vector<bool>visited(26,0);   //To check if char is already added to res string
    for(char &i : s) cnt[i-'a']++;
    int unique=0;   // no of unique chars
    for(int i=0;i<26;i++) unique+=(cnt[i]>0);
    for(char &c : s)
    {

        cnt[c-'a']--;
        if(visited[c-'a']) continue;
        while(!res.empty() && c<res.back() && cnt[res.back()-'a']>0)       // It means we have added
            //bigger char to the res string before the smaller current char where as we can even get the bigger char later also but still added so pop chars until they are bigger than current and we can find them later
        {
            visited[res.back()-'a']=0;
            res.pop_back();
        }
        visited[c-'a']=1;
        res+=c;
        if(res.size()==unique) break;      // If we have find all the unique chars already simply break no need to traverse more
    }
    return res;
}


/*
  leetcode 402
  Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

  Note:
  The length of num is less than 10002 and will be ≥ k.
  The given num does not contain any leading zero.
  Example 1:

  Input: num = "1432219", k = 3
  Output: "1219"
  Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
  Example 2:

  Input: num = "10200", k = 1
  Output: "200"
  Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
  Example 3:

  Input: num = "10", k = 2
  Output: "0"
  Explanation: Remove all the digits from the number and it is left with nothing which is 0.
 */

string removeKdigits(string num, int k) {
    string res;
    int kinit = k;

    if (k >= num.size()) return "0";

    for (char c : num) {
        while(k > 0 && !res.empty() && res.back() > c) {
            res.pop_back();
            k--;
        }
        if (!(res.empty() && c == '0')) res.push_back(c);
    }

    return res.empty() ? "0" : res.substr(0,num.size()-kinit);
}

/*
  Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
  Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.
  Input: nums = [-2,5,-1], lower = -2, upper = 2,
  Output: 3
  Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2

  leetcode 327 using mergesort
*/
class CountOfRangeSum {
public:
    int lo, up;
    vector<long long> s;

    int countSum(int l, int r) {
        if (l >= r) return 0;
        if (r - l + 1 == 2) {
            return (s[r] - s[l] >= lo && s[r] - s[l] <= up);
        }
        int m = (l + r) / 2;
        int ret = countSum(l, m) + countSum(m + 1, r);
        vector<long long> a;
        for(int i = l; i <= m; ++i) a.push_back(s[i]);
        sort(a.begin(), a.end());
        for(int i = m+1; i <= r; ++i) {
            ret += distance(lower_bound(a.begin(), a.end(), s[i] - up), upper_bound(a.begin(), a.end(), s[i] - lo));
        }
        return ret;
    }
    int countRangeSum(vector<int>& a, int lower, int upper) {
        lo = lower; up = upper;
        int n = a.size();
        s.assign(n+1, 0);
        for(int i = 1; i <= n; ++i) s[i] = s[i-1] + a[i-1];
        return countSum(0, n);
    }
};

/*
leetcode 395
Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 */
int sub(const string& s, int k, int l, int r) {
    if (r -l < k) return 0;
    int a[26] = {0,};
    for (int i = l; i < r; ++i) {
        ++a[s[i]-'a'];
    }
    int start = l;
    int ret = 0;
    for (int i = l; i < r; ++i) {
        if (a[s[i]-'a'] < k) {
            ret = max(ret, sub(s, k, start, i));
            start = i+1;
        }
    }
    if (start == l) {
        return r - l;
    }
    return max(ret, sub(s, k, start, r));
}

int longestSubstring(string s, int k) {
    return sub(s, k , 0, s.size());
}

//leetcode 480 median of sliding window
// Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
//   Examples:
//   [2,3,4] , the median is 3

//     [2,3], the median is (2 + 3) / 2 = 2.5
// sol1 : use binary search tree
// sol2 : binary search tree using lower bound (below)
vector<double> medianSlidingWindow(vector<int>& nums, int k) {

  vector<double> res;
  vector<long long> med;

  for(int i= 0; i<k; i++)
    med.insert(lower_bound(med.begin(),med.end(),nums[i]),nums[i]);
  if(k%2==0)
    res.push_back((double)(med[k/2]+med[k/2-1])/2 );
  else
    res.push_back((double)med[k/2]);


  for(int i=k; i<nums.size(); i++)
    {
      med.erase(lower_bound(med.begin(),med.end(),nums[i-k]));
      med.insert(lower_bound(med.begin(),med.end(),nums[i]),nums[i]);
      if(k%2==0)
        res.push_back((double)(med[k/2]+med[k/2-1])/2 );
      else
        res.push_back((double)med[k/2]);
    }
  return res;
    }

/**
You are given an array of integers nums, 
there is a sliding window of size k which is moving from the very left of the array to the very right. 
You can only see the k numbers in the window. 
Each time the sliding window moves right by one position.
Return the max sliding window.
*/
class leetcode239 {
public:
    vector<int> maxSlidingWindow1(vector<int>& nums, int k) {
        multiset<int> s;

        vector<int> r;

        for (int i = 0; i < nums.size(); ++i)
        {
            if (s.size() == k)
            {
                s.erase(s.find(nums[i - k]));
            }
            s.insert(nums[i]);
            if (s.size() == k)
                r.push_back(*s.rbegin());
        }

        return r;
    }

    // faster
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> v(nums.size());
        vector<int> r;

        if (nums.size() == 0)
            return r;

        v[0] = nums[0];
        for (int i = 1; i < k; ++i)
        {
            v[i] = nums[i];
            for (int j = i - 1; j >= 0; --j)
            {
                if (v[j] >= v[i])
                    break;
                else
                    v[j] = v[i];
            }
        }

        r.push_back(v[0]);

        for (int i = k; i < nums.size(); ++i)
        {
            v[i] = nums[i];
            for (int j = i - 1; i - j < k ; --j)
            {
                if (v[j] >= nums[i])
                    break;
                else
                    v[j] = nums[i];
            }

            r.push_back(v[i - k + 1]);
        }

        return r;
    }
};


// leetcode 464
// In the "100 game" two players take turns adding, to a running total, any integer from 1 to 10. The player who first causes the running total to reach or exceed 100 wins.

//   What if we change the game so that players cannot re-use integers?

//   For example, two players might take turns drawing from a common pool of numbers from 1 to 15 without replacement until they reach a total >= 100.

//   Given two integers maxChoosableInteger and desiredTotal, return true if the first player to move can force a win, otherwise return false. Assume both players play optimally.

// 10 11 -> false, 10 0 -> true, 10 1 -> true, 10 40 -> false
bool canIWin(int maxChoosableInteger, int desiredTotal) {
  if (desiredTotal <= 0) return true;

  const int sum = maxChoosableInteger * (maxChoosableInteger + 1) / 2;
  if (sum < desiredTotal) return false;

  unordered_map<int, bool> memo;  // true: can win, false: can't win

  // state: record integers that have been chosen
  function<bool(int, int)> dp = [&](int total, int state) {
                                  if (total <= 0) return false;
                                  if (memo.count(state)) return memo[state];

                                  for (int i = 1; i <= maxChoosableInteger; ++i) {
                                    if (state & (1 << i)) continue;  // integer i is used
                                    if (!dp(total - i, state | (1 << i))) return true;
                                  }

                                  return memo[state] = false;
                                };

  return dp(desiredTotal, 0);
}


// leetcode 488
/*
Think about Zuma Game. You have a row of balls on the table, colored red(R), yellow(Y), blue(B), green(G), and white(W). You also have several balls in your hand.

Each time, you may choose a ball in your hand, and insert it into the row (including the leftmost place and rightmost place). Then, if there is a group of 3 or more balls in the same color touching, remove these balls. Keep doing this until no more balls can be removed.

Find the minimal balls you have to insert to remove all the balls on the table. If you cannot remove all the balls, output -1.

Example 1:

Input: board = "WRRBBW", hand = "RB"
Output: -1
Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW
Example 2:

Input: board = "WWRRBBWW", hand = "WRBRW"
Output: 2
Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty
Example 3:

Input: board = "G", hand = "GGGGG"
Output: 2
Explanation: G -> G[G] -> GG[G] -> empty
Example 4:

Input: board = "RBYYBBRRB", hand = "YRBGB"
Output: 3
Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty
*/

class zuma_game {
public:
    //from discussion
    unordered_map<char,int> m;

    int findMinStep(string board, string hand) {
        if(board.size()==0) return 0;
        vector<int> handcnt(5,0);
        for(auto& h:hand){
            if(h=='R') handcnt[0]++;
            else if(h=='Y') handcnt[1]++;
            else if(h=='B') handcnt[2]++;
            else if(h=='G') handcnt[3]++;
            else if(h=='W') handcnt[4]++;
        }
        m['R']=0;
        m['Y']=1;
        m['B']=2;
        m['G']=3;
        m['W']=4;

        auto res=dfs(board,handcnt,0);

        return res==(INT_MAX>>1)?-1:res;
    }

    int dfs(const string& board, const vector<int>& hand,int idx){
        if(idx==board.size()) return 0;


        int res=(INT_MAX>>1);
        //insert on the left
        for(int i=idx;i<board.size();++i){
            if(i==0||board[i]!=board[i-1]){
                int cnt=0,j=i;
                while(j<board.size()&&board[j]==board[i])cnt++,j++;
                int need=3-cnt;
                if(need<0) need=0;
                if(hand[m[board[i]]]<need) continue;

                vector<int> newhand(hand);
                newhand[m[board[i]]]-=need;
                string newboard=board.substr(0,i)+board.substr(j);

                res=min(res,need+dfs(newboard,newhand,0));
                //cout<<res<<","<<newboard<<"!"<<board<<endl;
            }
        }

        return res;
    }
};


// leetcode 502
// Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources, it can only finish at most k distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.

// You are given several projects. For each project i, it has a pure profit Pi and a minimum capital of Ci is needed to start the corresponding project. Initially, you have W capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.

// To sum up, pick a list of at most k distinct projects from given projects to maximize your final capital, and output your final maximized capital.

// Example 1:
// Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

// Output: 4

int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {

  int n = Profits.size();

  vector<pair<int,int>> v(n);
  for(int i = 0; i < n; i++){
    v[i] = {Capital[i], Profits[i]};
  }

  sort(v.begin(), v.end());

  priority_queue<int> pq;

  int cur = W, i = 0;
  for(i = 0; i < n && v[i].first <= W; i++){
    pq.push(v[i].second);
  }

  while(!pq.empty() && k){
    cur += pq.top();
    pq.pop();
    k--;

    while(i < n && v[i].first <= cur)
      pq.push(v[i].second), i++;
  }

  return cur;
    }


// leetcode 424
/*
  Given a string s that consists of only uppercase English letters, you can perform at most k operations on that string.
  In one operation, you can choose any character of the string and change it to any other uppercase English character.
  Find the length of the longest sub-string containing all repeating letters you can get after performing the above operations.

  Note:
  Both the string's length and k will not exceed 104.

  Example 1:

  Input:
  s = "ABAB", k = 2

  Output:
  4

  Explanation:
  Replace the two 'A's with two 'B's or vice versa.
*
 */
int characterReplacement(string s, int k) {

  vector<vector<int>> v(26, vector<int>());

  for (int i = 0; i < s.size(); ++i)
    {
      int idx = s[i] - 'A';
      v[idx].push_back(i);
    }

  int mmax = 0;
  int max_size = s.size();

  for (int i = 0; i < 26; ++i)
    {
      if (v[i].empty())
        continue;

      int l = 0, r = 0;

      while (r < v[i].size())
        {
          int cnt = r - l + 1;
          int size = v[i][r] - v[i][l] + 1;
          int cap = cnt + k - size;

          if (cap >= 0)
            {
              size = min(size + cap, max_size);
              mmax = max(mmax, size);

              ++r;
            }
          else
            {
              ++l;
            }
        }
    }

  return mmax;
}


// leetcode 352
// Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.
//   Implement the SummaryRanges class:
//   SummaryRanges() Initializes the object with an empty stream.
//   void addNum(int val) Adds the integer val to the stream.
//   int[][] getIntervals() Returns a summary of the integers in the stream currently as a list of disjoint intervals [starti, endi].

class SummaryRanges {

  map<int, int> mp;

  // if test is needed, then probably need to take am interface to get the time, as  an  interface.


  void addNum(int val) {
    if(mp.count(val)) {
      return;
    }
    mp[val] = val;
    int minn = val, maxx = val;
    if(mp.count(val - 1)) {
      minn = mp[val - 1];
    }
    if(mp.count(val + 1)) {
      maxx = mp[val + 1];
    }
    mp[minn] = maxx;
    mp[maxx] = minn;
  }

  vector<vector<int>> getIntervals() {
    vector<vector<int>>ans;
    auto it = mp.begin();
    while(it != mp.end()) {
      ans.push_back({it -> first, it -> second});
      it = mp.upper_bound(it -> second);
    }
    return ans;
  }
};


//leetcode 220
// Given an integer array nums and two integers k and t, return true if there are two distinct indices i and j in the array such that abs(nums[i] - nums[j]) <= t and abs(i - j) <= k.
//   Input: nums = [1,2,3,1], k = 3, t = 0
//   Output: true

class ContainsDuplicate3 {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        multiset<int> v;

        for (int i = 0; i < nums.size(); ++i)
        {
            if (v.size() == k + 1)
            {
                v.erase(v.find(nums[i - k - 1]));
            }

            auto it = v.insert(nums[i]);

            if (next(it) != v.end())
            {
                long long a = *next(it);
                long long b = nums[i];
                if (t >= abs(a - b))
                {
                    return true;
                }
            }
            if (it != v.begin())
            {
                long long a = nums[i];
                long long b = *prev(it);
                if (t >= abs(a - b))
                {
                    return true;
                }
            }

        }

        return false;
    }
};

// leetcode 546
// You are given several boxes with different colors represented by different positive numbers.
// You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), remove them and get k * k points.
// Return the maximum points you can get.


class leetcode546 {
    // time limit exceeded
    int removeBoxes(vector<int>& boxes) {
        vector <pair<int, int>>  v;
        
        int prev = boxes[0];
        int cnt = 1;
        for (int i = 1; i < boxes.size(); ++i) {
           if (prev == boxes[i])  {
               ++cnt;
           } else {
               v.push_back({prev, cnt});
               prev = boxes[i];
               cnt = 1;
           }
        }
        v.push_back({prev, cnt});
        return foo(v);
    }
    
    int foo(vector<pair<int, int>>& v) {
        int r = 0;
        
        for (int i = 0; i < v.size(); ++i) {
            auto vv = v;
            vv.erase(vv.begin() + i);
            if (i != 0 && (i != (v.size() - 1))) {
               if (vv[i - 1].first == vv[i].first) {
                  // merge if the color is the same
                  vv[i - 1].second = vv[i - 1].second + vv[i].second; 
                  vv.erase(vv.begin() + i);
               }
            }
            
            int x = v[i].second * v[i].second + foo(vv);
            r = max(r, x);
        }
        
        return r;
    } 

    int solve(int l, int r,int mx, vector<int>& b ,vector<vector<vector<int>>> &dp)
    {
        if(l>r)
            return 0;
        if(dp[l][r][mx]!=-1)
            return dp[l][r][mx];
                  
        int val = solve(l+1,r,0,b,dp) + (mx+1) * (mx+1) ;
        for(int i=l+1;i<=r;i++)
        {
            if(b[l]==b[i])
            {
                val = max({val,solve(l+1,i-1,0,b,dp)+solve(i,r,mx+1,b,dp)});
            }
        }
        
        return dp[l][r][mx] = val;
    }
    // from discussion using DP
    int removeBoxes1(vector<int>& b) {
        int n  = b.size();
        vector<vector<vector<int>>> dp(n,vector<vector<int>>(n,vector<int>(n, -1)));
        int ans  = solve(0,n-1,0,b,dp);
        return ans;
    }
        
};


// leetcode 97
// Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
class Interleave {
public:
    bool isInterleave(string s1, string s2, string s3) {

        int size1 = s1.size();
        int size2 = s2.size();
        if (size1 + size2 != s3.size())
            return false;
        
        vector<vector<bool>> v(size1 + 1, vector<bool>(size2 + 1, false));
        
        for (int i = size1 ; i >= 0; --i)
        {
            for (int j = size2 ; j >= 0; --j)
            {
                if (i == size1 && j == size2) {
                    v[i][j] = true;
                } else if (i == size1) {
                    v[i][j] = s2[j] == s3[i + j] && v[i][j + 1];
                } else if (j == size2) {
                    v[i][j] = s1[i] == s3[i + j] && v[i + 1][j];
                } else {
                    auto a = v[i + 1][j] && (s1[i] == s3[i + j]);
                    auto b = v[i][j + 1] && (s2[j] == s3[i + j]);
                    v[i][j] = a || b;
                }
            }
        }
        
        return v[0][0];
     }
};

// leetcode 115
// Given two strings s and t, return the number of distinct subsequences of s which equals t.
class Distinct {
public:
    int numDistinct(string s, string t) {
        return foo3(s, t);
    }
    
    int foo3(string& s, string& t)
    {
        int sz1 = s.size();
        int sz2 = t.size();
        
        vector<vector<double>> v(sz1 + 1, vector<double>(sz2 + 1, 0));
        
        for (int i = sz1; i >= 0; --i)
        {
            for (int j = sz2; j >= 0; --j)
            {
                if (j == sz2)
                    v[i][j] = 1;
                else if (i == sz1)
                    v[i][j] = 0;
                else
                {
                    double a = (s[i] == t[j]) ? v[i + 1][j + 1] : 0;
                    double b = v[i + 1][j];
                    v[i][j] = a + b;
                }
            }
        }
        
        return v.front().front();
    }
};

int main()
{
    // when test your algorithm which takes a string,
    // consider 'a', 'ab', 'aba', 'aaa'.
    // Consider also the case the loop of your algorithm is not taken.
    // such as, 가장 많이 consecutive한 스트링 찾을 때 'a'가 인풋인 경우.
    // test_denom();

    // int* a[10];
    // cout << "size of a is " << sizeof(a) << endl;

  test_find_number_which_has_the_most_bigger_numbers_on_the_right();
}


/*
start: get an idea by examples, design, implement next, optimize or debug last
end: if there is a loop, then check end condition - what happens at the end of
of the loop. If carry is left at the end of the loop?
*/
