/*
http://web.stanford.edu/class/cs97si/
*/

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
using namespace std;


void add()
{
  int a, b;
  cin >> a >> b;
  cout << a << " + " << b << " = " << a + b << endl;
}

void finance()
{
  int i;
  double a[12];
  double sum = 0, average;
  unsigned int tmp;

  for (i = 0; i < 12; i++) {
    cin >> a[i];
    sum += a[i];

  }

  average = sum / 12;
  
  tmp = average * 100;
  average = double(tmp) / 100;
  

  cout << average;
    
}


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


// nlog(n)
void dna_sorting2()
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
void herd_sum2()
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

    vector<int> vi2(vi.size());

    vi2[0] = vi[0];
    for (int i = 1; i < vi2.size(); ++i)
    {
        vi2[i] = vi2[i - 1] + vi[i];
    }

    
    unordered_map<int, int> mi;
    mi[0]++;
    for (int i = 0; i < vi2.size(); ++i)
    {
        mi[vi2[i]]++;
        mi[vi2[i] - mmatch]++;
    }

    int r = 0;
    for (int i = 0; i < vi2.size(); ++i)
    {
        if (mi[vi2[i] - mmatch] == 2)
        {
            ++r;
        }
    }
    if (r == 0)
        cout << "no sequences found" << endl;
    cout << r << endl;
}



int revert(int n)
{
  int r = 0;
  
  while(1) {
    r += n % 10;
    n = n / 10;
    if (n == 0)
	break;
    else 
      r = r * 10;
  }
  
  return r;
}



void reversed_sum()
{


  int num;

  cin >> num;

  int *a = new int[num];
  int *b = new int[num];
  int *c = new int[num];

  int l, m, r;

  for (int i = 0; i < num; i++) {
    cin >> a[i] >> b[i];
    l = revert(a[i]);
    m = revert(b[i]);
    r = l + m;
    c[i] = revert(r);
  }

  for (int i = 0; i < num; i++) {

    cout << c[i] << endl;

  }
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

#if 0

void get(vector<char> &v, int idx, char *a, char *b)
{
  int size;

  *a = v[idx];
  size = v.size();
  
  for (i = 0; i < size; i++) {
    if (v[i] == '.') 
      break;
  }

  *b = i - idx;

} 


void mul(char a, char b, char c, char d, char *e, char *f)
{
  *e = a * c;
  *f = b * d;
}
 

 
void mul(vector<char> &v1, vector<char> &v2, vetor<char> &v3)
{
 
  /* iterate v1 and v2, get a value from both v1 and v2, multiply it and store to result in a vector. */
  /* result of the multiply is added to the result which is a vector.*/
 
}


void exponentiation()
{
  
  string s;
  int n;
  double r = 1;


  cin >> s >> n;

  vector<char> v1;
  vector<char> v11;
  vector<char> v2;

  get_vector(s, v1);
  v11 = v1;

  for (int i = n; i > 1; i = i / 2) {
    
    mult(v1, v1, v2);
    v1 = v2;

  } 

  if (n % 2)
    mult(v1, v11, v2); 

  
}
#endif




#if 0

//we can use vector.erase(i) function.

void minus(vector<char> &ret, vector<char> &v, char c)
{
  for (int i = 0; i < v.size(); i++) {
    if (v[i] != c)
      ret.push_back(v[i]);
  }
  
}

#endif



void vcprint(vector<char> &v)
{
  for (int i = 0; i < v.size(); i++) {
    cout << v[i];
  }
  cout << endl;
}


void merge(vector<vector<char> *> &ret, char c, vector<vector<char> *> &v)
{
  int size = v.size();

  if (size == 0) {
    vector<char> *tmp = new vector<char>;
    tmp->push_back(c);
    ret.push_back(tmp);

  }

  else { 
    for (int i = 0; i < size; i++) {

      vector<char> *tmp = new vector<char>;
      
      tmp->push_back(c);
      
      vector<char> *tmp2 = v[i];

      for (int j = 0; j < tmp2->size(); j++) {
	tmp->push_back(tmp2->at(j));
      }

      ret.push_back(tmp);
      delete tmp2;
    }
  }

  return;
}


void perm(vector<vector<char> *> &ret, vector<char> &vc)
{


  if (vc.size() == 0) 
    return;
 
  for (int i = 0; i < vc.size(); i++) {

    vector<char> vc_1 = vc; 
    vc_1.erase(vc_1.begin() + i);

    vector<vector<char> *> ret_1;
    perm(ret_1, vc_1); 
    merge(ret, vc[i], ret_1);
    
  }

}


void permutation()
{

  vector<vector<char> *> ret;
  vector<char> v;

  v.push_back('a');
  v.push_back('b');
  v.push_back('c');
  v.push_back('d');

  perm(ret, v);

  for (int i = 0; i < ret.size(); i++) {

    vcprint(*ret[i]);
  }

}


void foo()
{
  int x;
  while  (cin >> x) {

    cout << x << endl;
  }

}


void map_test_word_count()
{

  string s;
  map<string, int> wc;

  while (cin >> s) {
    ++wc[s];
  }

  for(map<string, int>::const_iterator it = wc.begin(); it != wc.end(); ++it) {
    cout << it->first << ":" << it->second << endl;
  }


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

void tree_count()
{


  map<string, int> tc;
  string str;
  
  while (cin >> str) {
    ++tc[str];
  } 

  for (map<string, int>::const_iterator it = tc.begin(); it != tc.end(); it++) {

    cout << it->first << " is " << it->second << endl;

  } 

}


bool is_in(int a, vector<int> &b)
{

  for (int i = 0; i < b.size(); i++) {
    if (a == b[i])
      return true;
  }
  
  return false;
} 


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


void nearest_common_ancestor()
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

#if 0
// method 1. compare all parents to all parents
    for (int k = 0; k < a.size(); k++) {

      if (is_in(a[k], b)) {
          res.push_back(a[k]);
          break;
      }
    }


#endif
#if 1
// method 2. compare at the same level.
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
  

#endif
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
void exp_replace_stack_queue()
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
void navi()
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

// /*

// Do not keep the sum in the tree node, as the modified value in the left tree can affects 
// the values in the right. So, in level 3 from the top, the node in the middle is updated twice,
// first for the first node in level two, second for the second node in level two.

// */



// /*
  
//  Instead of function call, store the computed value to an array will be better for
// dynamic programming.

// */
// // http://poj.org/problem?id=1163
void tri_sum()
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
void dp_triangle_test()
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


void init_combination(vector<int> &vi, int n, int k)
{
  for (int i = 0; i < k; i++)
    vi.push_back(i);
  
}


int get_next_combination(vector<int> &vi, int n, int k)
{
  int size = vi.size();
  int i = 1;

  while (i > 0) {

    if (vi[size - i] >= n - i) {
      vi[size - i] = 0;
      i++;
      if (i > k) break;
      
    } else {

      if (i < k)
	if (vi[size - i] < vi[size - i - 1])
	  vi[size - i] = vi[size - i - 1];

      vi[size - i]++;
      i--;
    }
    
  }

  if (i > k)
    return 0;

  return 1;
}



void compute_matrix(vector<vector<int> > &vii, vector<int> &vi)
{

  int n = vi.size();
  vii.resize(vi.size());

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {

      vii[i].push_back(abs(vi[i] - vi[j]));

    }
  }

}


int dp_post_office(vector<vector<int> > &vii, vector<int> &vi)
{

  int r = 0;
  int idx = 0;
  int i = 0;

  while (i <= vi[idx])
    r += vii[i++][vi[idx]];
    
  while (i <= vi[vi.size() - 1])  {

    r += min(vii[i][vi[idx]], vii[i][vi[idx + 1]]);
    i++;
    if (i > vi[idx + 1])
      ++idx;
  }

  while (i < vii.size())
    r += vii[i++][vi[idx]];

  return r;
    
}

// http://poj.org/problem?id=1160
void post_office()
{

  int num_v, num_p;
  vector<int> vi;
  int t, min_t, r;
  vector<vector<int> > vii;
  vector<int> vi2;

  cin >> num_v >> num_p;


  for(int i = 0; i < num_v; i++) {
    cin >> t;
    vi.push_back(t);
  }

  compute_matrix(vii, vi);

  init_combination(vi2, num_v, num_p);

  min_t = - 1;
  while (1) {

    t = dp_post_office(vii, vi2);
    if (min_t == -1)
      min_t = t;
    else if (min_t > t)
      min_t = t;

    r = get_next_combination(vi2, num_v, num_p);
    if (!r) break;
  }

  cout <<  "the result is " << min_t << endl;

}


int get_min(vector<int> vi, int left, int right)
{
    if (left == -1 && right == -1)
    {
        int min_t = 10000;
        for (int i = 0; i < vi.size(); ++i)
        {
            int sum = 0;
            for (int j = 0; j < vi.size(); ++j)
            {
                sum += abs(vi[i] - vi[j]);
            }

            if (sum < min_t)
                min_t = sum;
        }
        return min_t;
                
    }
    else if (right == -1)
    {
        int min_t = 10000;
        for (int i = 0; i < vi.size(); ++i)
        {
            int sum = 0;
            for (int j = 0; j < vi.size(); ++j)
            {
                sum += min(abs(left - vi[j]),
                           abs(vi[i] - vi[j]));
            }

            if (sum < min_t)
                min_t = sum;
        }
        return min_t;
     }
    else if (left == -1)
    {
        int sum = 0;
        for (int i = 0; i < vi.size(); ++i)
        {
            sum += abs(right - vi[i]);
        }

        return sum;
     }
    else
    {
        int sum = 0;
        for (int i = 0; i < vi.size(); ++i)
        {
            sum += min(abs(right - vi[i]),
                       abs(left - vi[i]));
        }

        return sum;
       
    }
}


int get_min_pv(vector<int>vi, int num_p, int left, int right)
{
    int r, min_t = 10000; // assume it would be max number
    
    if (num_p == 1)
    {
        min_t = get_min(vi, left, right);
    }
    else
    {
        for (int i = 0; i <= vi.size() - num_p; ++i)
        {
            r = get_min(vector<int>(vi.begin(), vi.begin() + i + 1), left, vi[i]) +
                get_min_pv(vector<int>(vi.begin() + i + 1, vi.end()), num_p - 1, vi[i], right);
            if (min_t > r)
                min_t = r;
        }
    }

    return min_t;
}

void post_office2()
{

  int num_v, num_p;
  vector<int> vi;
  int t, min_t;
  vector<int> vi2;

  cin >> num_v >> num_p;

  for(int i = 0; i < num_v; i++) {
    cin >> t;
    vi.push_back(t);
  }


  min_t = get_min_pv(vi, num_p, -1, -1);

  cout << "The result is " << min_t << endl;
}

// http://poj.org/problem?id=2033
void alphacode()
{
  
  string s;
  vector<int> vi, d;
  
  cin >> s;
  int size = s.size() + 1;

  vi.push_back(0);
  for (int i = 0; i < size; i++)
    vi.push_back(s[i] - '0');

  d.resize(size + 1);


  d[0] = 1;
  d[1] = 1;

  for (int i = 2; i <= size; i++) {
    if (vi[i] < 7 && (vi[i - 1] == 1 || vi[i - 1] == 2))
      d[i] = d[i - 1] + d[i - 2];
    else 
      d[i] = d[i - 1];

  }

  cout << "the result is " << d[size - 1] << endl;

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
void hay()
{

  int n, m;
  cin >> n >> m;

  vector<vector<int> > vt;

  vt.resize(n + 1);
  for (int i = 0; i < vt.size(); i++) {
    vt[i].resize(n + 1);

  }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      vt[i][j] = 10000000;
  
  for (int i = 0; i < m; i++) {

    int a, b, len;
    cin >> a >> b >> len;
    
    vt[a][b] = len;
  }

  /* shortest path algorithm by Dikstra */

  vector<int> d;

  d.resize(n + 1);
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



int min_elem2(vector<vector<int> > &vi, set<int> &s, set<int> &v, int *r)
{
  int min = 10000000;
  int res = 0;
 
  for (set<int>::const_iterator it = s.begin(); it != s.end(); it++) {
    for (set<int>::const_iterator iit = v.begin(); iit != v.end(); iit++) {
      if (min > vi[*it][*iit]) {
          min = vi[*it][*iit];
          *r = min;
          res= *iit;
      }
    }
  }
  
  return res;
}

void hay2()
{
  int n, m;
  cin >> n >> m;

  vector<vector<int> > vt;

  vt.resize(n + 1);
  for (int i = 0; i < vt.size(); i++) {
    vt[i].resize(n + 1);

  }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      vt[i][j] = 10000000;
  
  for (int i = 0; i < m; i++) {

    int a, b, len;
    cin >> a >> b >> len;
    
    vt[a][b] = len;
    vt[b][a] = len;

  }

  /* minimal spanning tree */

  set<int> s, v;
  s.insert(1);

  for (int i = 2; i <= n; i++) {
    v.insert(i);
  }
  
  int res, max = -1;
  while (v.size() > 0) {
    int w = min_elem2(vt, s, v, &res);
    s.insert(w);
    v.erase(w);
    cout << w << " and distance is " << res << endl;
    if (max < res)
      max = res;
  }

  cout << max << endl;

}

void hay3()
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

void knight_move()
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



// worm hole seems to be just a shortest path starting from itself. Or a network
// flow from source to dest?
// http://poj.org/problem?id=3259


// http://poj.org/problem?id=1945
// single line with a single integer that is the minimum number of operations it requires to compute the power.
// given two variables (or store) to save temporary variable 
// for example, for input 31, output is 6
// we can either multiply or divide.
// (x, 1), (x, x^2), ..., (x, x^32), (x, x^31)
// (1, 0), (1, 2),   ..., (1, 32), (1, 31).
// so, input is (1, 0), and output is either should (31, k) or (k, 31) for some
// k. so, the problem is to construct a graph, and dfs to find the depth, search for the min depth. each node is a pair of integer.

 
// http://poj.org/problem?id=3169
// layout.




// perfect stall
// http://poj.org/problem?id=1274

int find_perfect_stall(map<int, int>& allocated,
                       map<int, int>& visited,
                       map<int, list<int>>& cow)
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
void all_in_all()
{
    string s, t;
    cin >> s >> t;

    if (aia(s, t))
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

void largest_sum()
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
        cout << vi2[i] << " ";
    }
    cout << endl;

    
    unordered_map<int, int> mi;
    mi[0]++;
    for (int i = 0; i < vi2.size(); ++i)
    {
        mi[vi2[i]]++;
        mi[vi2[i] - mmatch]++;
    }

    for (int i = 0; i < vi2.size(); ++i)
    {
        if (mi[vi2[i] - mmatch] == 2)
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

void match_sum2()
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


bool find_match_sum(vector<int>& vi, int i, int target) // i ==0 -> size -1
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

   
void test_bin_search_heap()
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

void test_cube_stack()
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
    //  for (int i = 0; i < num_cube; ++i)
    // {
    //     cout << vc[i].grp << " " << vc[i].leaf << endl;
    // }
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


void test_find_and_catch()
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
        
        // x -= (x & -x); // clear left most 1 
        // so, (x & -x) is right most bit

        int size = leaf.size();
        int ssum = 0;
        for (int i = size - (size & -size); i < size; ++i)
        {
            ssum += leaf[i];
        }

        inner.push_back(ssum);
        // cout << ">> " << ssum << endl;
    }

    void update(int i, int x)
    {
        leaf[i] += x;

        int size = leaf.size();
        while (i <= size){
            inner[i - 1] += x;
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

private:
    vector<int> leaf;
    vector<int> inner;
};


void test_bit()
{
    BIT b;
    for (int i = 1; i <= 10; ++i)
        b.push_back(i);

    b.update(2, -1);

    cout << " the result should be 55 and " << b.sum(3) << " " << b.sum(10) << endl;
    // assert(b.sum(10) == 55);
    cout << "test_bit passed" << endl;
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
                                                              

int get_kth_number(int n, int k, vector<vector<int>>& v)
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
        
        // for (auto&e : v) {
        //     for (auto ee: e) {
        //         cout << ee << " ";
        //     }
        //     cout << endl;
        // }


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
    
    if (ka == 0)
        return (b[idx] + process_jobs2m(idx + 1, a, b, k, kb - 1, k));
    if (kb == 0)
        return (a[idx] + process_jobs2m(idx + 1, a, b, ka - 1, k, k)); 

    int r =  min(a[idx] + process_jobs2m(idx + 1, a, b, ka - 1, k, k),
               b[idx] + process_jobs2m(idx + 1, a, b, k, kb - 1, k));

    jobs2m_map[t] = r;
    return r;
}


void two_machine_n_jobs()
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


    int r = process_jobs2m(0, a, b, k, k, k);

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


void staff()
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

void find_match_sum_bintree()
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


void beauty_number()
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
    cout << "match " << a.msg << " " << b.msg << " ";
    if (a.msg.size() != b.msg.size()) {
        cout << "false 1" << endl; 
           return false;
    }
    
    for (int i = 0; i < a.msg.size(); ++i)
    {
        char c = a.msg[i];
        if (cmap.find(c) != cmap.end())
        {
            if (cmap[c] != b.msg[i])
            {
                cout << "false 2" << endl; 
                return false;
            }
        }
        else
        {
            cmap[c] = b.msg[i];
        }

    }

                
    cout << "true" << endl; 
    return true;
}

void proc_dcpr(int i, vector<dcpr>& vb, vector<dcpr>& va, map<char, char>& cmap)
{
    cout << "proc with i " << i << endl;
    if (i == vb.size())
    {
        cout << "found" << endl;
        for (auto& ee : vb)
        {
            cout << ee.msg << " = " ;
            for (int k = 0; k < ee.msg.size(); ++k)
                ee.msg[k] = cmap[ee.msg[k]];
            cout << ee.msg << endl;
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

void decipher()
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


struct stk_node {
    stk_node(string ss) : s(ss) {}
    string s;
};


string remove_parenthesis(string str)
{
    stack<stk_node> stk;
    vector<stk_node> vs;

    for (auto c : str)
    {

        if (c != ')')
        {
            string ss(1, c);
            stk.push(stk_node(ss));
        }
        else
        {
            string s;
            int count = 0;

            while (stk.top().s != "(")
            {
                stk_node sn = stk.top();
                s += sn.s;
                count++;
                stk.pop();
            }

            // remove '('
            stk.pop();

            if (count == 0)
                continue;
                  
            if (count > 1)
                s = "(" + s + ")";
                
            stk_node sn(s);
            stk.push(sn);
        }

    }

    string r = string(stk.top().s.begin() + 1, stk.top().s.end() - 1);
    return r;
}



void test_remove_par()
{
    string s;
    cin >> s;

    string r = remove_parenthesis(s);

    cout << "the result is " << r << endl;

}



    
int main()
{
    test_remove_par();
}


/*
start: get an idea by examples, design, implement next, optimize or debug last
*/
