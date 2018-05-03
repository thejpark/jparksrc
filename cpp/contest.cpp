/*
http://web.stanford.edu/class/cs97si/
*/

#include <assert.h>
#include <iostream>
#include <vector>
#include <string>
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

void test_denom()
{
    cout << makeChange(16, 25) << endl;

    vector<int> a {25, 10,  5, 1};
    vector<int> b {1, 5, 10, 25};

    cout << makeChange(a, 0, 16) << endl;
    cout << makeChange(b, 0, 16) << endl;
    cout << makeChangeDP(b, 16) << endl;
    cout << makeMinChange(a, 0, 0, 16) << endl;
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


// http://poj.org/problem?id=2033
void alphacode() //jj
{

  string s;
  vector<int> v;

  cin >> s;

  int size = s.size();
  for (int i = 0; i < size; i++)
    v.push_back(s[i] - '0');

  vector<int> d(v.size());

  // I should stick to simple algorithm. And I should go a phase which check if input is healthy or not.
  // for example, if there is more than 1 consecutive 0 in the input, then input is error.
  // So implement happy case, then extend.

  // error check
  for (int i = 0; i < v.size(); ++i) {
      if (i == 0 && v[i] == 0) {
        cout << " error input " << endl;
        return;
      }
      else if (i > 0 && v[i] == 0 && v[i - 1] > 2) {
        cout << " error input " << endl;
        return;
      }
  }

  d[size - 1] = 1;
  if ((v[size - 2] == 1 || v[size - 2] == 2) && (v[size - 1] > 0 && v[size - 1] < 7))
  {
      d[size - 2] = 2;
  }
  else
  {
      d[size - 2] = 1;
  }

  for (int i = size - 3; i >= 0; --i)
  {
    if ((v[i] == 1 || v[i] == 2) && (v[i + 1] > 0 && v[i + 1] < 7))
      {
          d[i] = d[i + 1] + d[i + 2];
      }
      else
      {
          d[i] = d[i + 1];
      }
  }

  cout << "the result is " << d[0] << endl;
}

int acode1(string s)
{
    if (s.size() == 0)
        return 1;
    if (s.size() == 1)
    {
        if (s[0] == '0')
            return 0;
        return acode1(s.substr(1));
    }
    if (s[0] == '1' || s[0] == '2')
    {
        if (s[1] == '0')
            return acode1(s.substr(2));
        if (s[1] > '0' && s[1] < '7')
            return acode1(s.substr(1)) + acode1(s.substr(2));
    }

    return acode1(s.substr(1));
}


void alphacode2() //j
{

    string s;
    cin >> s;

    int r = acode1(s);

    cout << " the result is " << r << endl;
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

  vector<int> d(n + 1);

  for (int i = 1; i <= n; i++)
    d[i] = 10000000;

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
  auto min_comp = [&](pair<int, int>& a, pair<int, int>& b)
      {
          return a.second > b.second;
      };

  map<int, list<pair<int, int> > > mm;
  set<int> s, v;

  for (int i = 0; i < m; i++) {

    int a, b, len;
    cin >> a >> b >> len;

    mm[a].push_back(pair<int, int>(b, len));
    mm[b].push_back(pair<int, int>(a, len));
    v.insert(a);
    v.insert(b);
  }

  /* minimal spanning tree */
  int x = *(v.begin());
  cout << "first is " << x << " and the size of v is " << v.size() << endl;
  s.insert(x);
  v.erase(x);

  vector<pair<int, int> > vd{mm[x].begin(), mm[x].end()};
  make_heap(vd.begin(), vd.end(), min_comp);

  int t_max = -1;

  while (v.size() > 0) {
      auto w = vd.front();
      s.insert(w.first);
      v.erase(w.first);
      cout << w.first << " and distance is " << w.second << endl;

      t_max = max(t_max, w.second);
      pop_heap(vd.begin(), vd.end(), min_comp);
      vd.pop_back();

      for (auto e: mm[w.first])
      {
          if (s.find(e.first) != s.end())
              continue;
          vd.push_back(e);
          push_heap(vd.begin(), vd.end(), min_comp);
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
    }
    cout << i << " " << j << endl;
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
    /*************
    Sample Input
    7 a/7 b/6 c/5 d/4 e/3 f/2 g/1
    7 a/1 b/2 c/3 d/4 e/5 f/6 g/7
    7 a/3 b/6 c/4 d/7 e/2 f/5 g/1
    0
    Sample Output
    (a/7(b/6(c/5(d/4(e/3(f/2(g/1)))))))
    (((((((a/1)b/2)c/3)d/4)e/5)f/6)g/7)
    (((a/3)b/6(c/4))d/7((e/2)f/5(g/1)))
    ****************/

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

#else
        int ssum = sum(leaf.size() - 1) + x;
        ssum -= sum(size - (size & -size));
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

    if (idx == a.size())
        return 0;

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
    // machine.

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

    // update cmap
    for (int i = 0; i < a.msg.size(); ++i)
    {
        char c = a.msg[i];
        cmap[c] = b.msg[i];
    }

    // cout << "true" << endl;
    return true;
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
            proc_dcpr(i + 1, vb, va, cmap);
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

pair<int, int> gmbs_iter(vector<int>&vs, int beg, int size)
{
    int len = size;
    while (len > 0)
    {
        for (int i = beg; i + len <= size; ++i)
        {
            if (gmbs_get(vs, i, len) * 2 == len)
            {
                return pair<int, int>(len, i);
            }

        }
        --len;
    }

    return pair<int, int>(0, 0);
}

pair<int, int> gmbs_linear(vector<int>&vs, vector<int>& v, int beg, int size) //jj
{
    int len = size;
    while (len > 0)
    {
        int t = gmbs_get(vs, beg, len) * 2;

        if (t == len)
        {
            return pair<int, int>(len, beg);
        }
        else if (t < len)
        {
            if (v[beg] == 0)
            {
                ++beg;
            }
        }
        else
        {
            if (v[beg] == 1)
            {
                ++beg;
            }
        }
        --len;
    }

    return pair<int, int>(0, 0);
}


pair<int, int> gmbs3(vector<int>& v)
{
    vector<int> vs(v.size());
    vs[0] = v[0];
    for (int i = 1; i < v.size(); ++i)
    {
        vs[i] = vs[i - 1] + v[i];
    }

    return gmbs_linear(vs, v, 0, vs.size());
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


pair<int, int> gebs_iter(vector<int>&vs1, vector<int>& vs2, int beg, int size)
{
  int len = size;
  while (len > 0)
    {
      for (int i = beg; i + len <= size; ++i)
        {
          if (gmbs_get(vs1, i, len) == gmbs_get(vs2, i, len))
            {
              return pair<int, int>(len, i);
            }

        }
      --len;
    }

  return pair<int, int>(0, 0);
}


pair<int, int> gebs(vector<int>& v1, vector<int>& v2) //jj
{
    vector<int> vs1(v1.size());
    vs1[0] = v1[0];
    for (int i = 1; i < v1.size(); ++i)
    {
        vs1[i] = vs1[i - 1] + v1[i];
    }

    vector<int> vs2(v2.size());
    vs2[0] = v2[0];
    for (int i = 1; i < v2.size(); ++i)
    {
        vs2[i] = vs2[i - 1] + v2[i];
    }

    return gebs_iter(vs1, vs2, 0, vs1.size());
}


void get_eq_bin_subsequence()
{
    vector<int> v1;
    vector<int> v2;

    int n;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v1.push_back(t);
    }

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v2.push_back(t);
    }

    pair<int, int> r;

    r = gebs(v1, v2);
    cout << r.first << " " << r.second << endl;
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

    r = gmbs3(v1);
    cout << r.first << " " << r.second << endl;
}



void add_without_plus() //jj
{
    int a, b;
    cin >> a >> b;

    int carry = 0;

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

struct splus {
    int x, y, size;
};


int find_more(pair<int, int>& n, set<pair<int, int>>& m, map<pair<int, int>, int>& t_m, int direction)
{
    auto it = t_m.find(n);
    if (it != t_m.end())
        return it->second;

    pair<int, int> next;

    switch(direction) {
    case 0: next = pair<int, int> (n.first - 1, n.second);
        break;
    case 1: next = pair<int, int> (n.first + 1, n.second);
        break;
    case 2: next = pair<int, int> (n.first, n.second - 1);
        break;
    case 3: next = pair<int, int> (n.first, n.second + 1);
        break;

    }

    auto next_len = (m.find(next) == m.end()) ? 0: 1 + find_more(next, m, t_m, direction);

    t_m[n] = next_len;
    return next_len;
}


int find_plus(pair<int, int>& n,
              set<pair<int, int>>& m,
              map<pair<int, int>, int>& t_m,
              map<pair<int, int>, int>& b_m,
              map<pair<int, int>, int>& l_m,
              map<pair<int, int>, int>& r_m)
{
    auto top = pair<int, int> (n.first - 1, n.second);
    auto bot = pair<int, int> (n.first + 1, n.second);
    auto left = pair<int, int> (n.first, n.second - 1);
    auto right = pair<int, int> (n.first, n.second + 1);

    auto top_len = (m.find(top) == m.end()) ? 0: 1 + find_more(top, m, t_m, 0);
    auto bot_len = (m.find(bot) == m.end()) ? 0: 1 + find_more(bot, m, b_m, 1);
    auto left_len = (m.find(left) == m.end()) ? 0: 1 + find_more(left, m, l_m, 2);
    auto right_len = (m.find(right) == m.end()) ? 0: 1 + find_more(right, m, r_m, 3);

    auto r1 = min(bot_len, top_len);
    auto r2 = min(right_len, left_len);
    auto r = min(r1, r2);

    return r;
}


splus find_biggest_plus(set<pair<int, int>>& m)
{
    splus t;
    // for each elem in the list, do dfs
    map<pair<int, int>, int> t_m;
    map<pair<int, int>, int> b_m;
    map<pair<int, int>, int> l_m;
    map<pair<int, int>, int> r_m;

    for (auto e: m)
    {
        int r = find_plus(e, m, t_m, b_m, l_m, r_m);
        if (r > t.size)
        {
            t.size = r;
            t.x = e.first;
            t.y = e.second;
        }
    }

    return t;
}

void test_find_biggest_plus() //jj
{
}


int main()
{
    // when test your algorithm which takes a string,
    // consider 'a', 'ab', 'aba', 'aaa'.
    // Consider also the case the loop of your algorithm is not taken.
    // such as, 가장 많이 consecutive한 스트링 찾을 때 'a'가 인풋인 경우.
 test_bit();
}


/*
start: get an idea by examples, design, implement next, optimize or debug last
end: if there is a loop, then check end condition - what happens at the end of
of the loop. If carry is left at the end of the loop?
*/
