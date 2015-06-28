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
#include <list>
#include <set>
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

    for (int k = 0; k < a.size(); k++) {

      if (is_in(a[k], b)) {
	res.push_back(a[k]);
	break;
      }
    }

  }

  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << endl;

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


/*


Hash function: std::tr1::unordered_map<>
I think the rest of them is same with map.

#include <unordered_map>

http://en.wikipedia.org/wiki/Unordered_associative_containers_(C%2B%2B)

*/


/*

 #include <stack>
 stack<int> mystack;
 mystack.push(x)
 y = mystack.top()
 mystack.pop()
 if(mystack.empty())

*/


/*

// queue::push/pop
#include <iostream>
#include <queue>
using namespace std;

int main ()
{
  queue<int> myqueue;
  int myint;

  cout << "Please enter some integers (enter 0 to end):\n";

  do {
  cin >> myint;
    myqueue.push (myint);
  } while (myint);

  cout << "myqueue contains: ";
  while (!myqueue.empty())
  {
  cout << " " << myqueue.front();
    myqueue.pop();
  }

  return 0;
}



*/


/*

 //set::find returns set.end() is there is no elements in the set.

// set::find
#include <iostream>
#include <set>
using namespace std;

int main ()
{
  set<int> myset;
  set<int>::iterator it;

  // set some initial values:
  for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

  it=myset.find(20);
  myset.erase (it);
  myset.erase (myset.find(40));

  cout << "myset contains:";
  for (it=myset.begin(); it!=myset.end(); it++)
  cout << " " << *it;
  cout << endl;

  return 0;
}

*/


struct farm {
  int x;
  int y;
  int  grp;
};


int find(vector<struct farm> &vi, int x)
{

  while(vi[x].grp != 0)
    x = vi[x].grp;

  return x;
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


/*

Do not keep the sum in the tree node, as the modified value in the left tree can affects 
the values in the right. So, in level 3 from the top, the node in the middle is updated twice,
first for the first node in level two, second for the second node in level two.

*/



/*
  
 Instead of function call, store the computed value to an array will be better for
dynamic programming.

*/

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

int main()
{
    alphacode();
}


/*
start: get an idea by examples, design, implement next, optimize or debug last
*/
