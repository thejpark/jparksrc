/*
 *
 * Accelerated C++
 *
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <ios>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <stdexcept>
#include <cctype>
#include <numeric>
#include <fstream>
#include <memory>

using namespace std;


int t1()
{

    std::cout << "Please enter your name:  " ;

    std::string name;
    std::cin >> name;

    std::cout << "Hello, " << name << "!" << std::endl;

    return 0;
}

int t2()
{

    std::cout << "Please enter your first name: ";
    std::string name;
    std::cin >> name;

    const std::string greeting = "* Hello " + name + "! *";
    const std::string spaces(greeting.size() - 2, ' ');
    const std::string second = "*" + spaces + "*";
    const std::string first(second.size(), '*');

    std::cout << std::endl;
    std::cout << first << std::endl;
    std::cout << second << std::endl;
    std::cout << greeting << std::endl;
    std::cout << second << std::endl;
    std::cout << first << std::endl;

    
}

int t3()
{
    const string hello = "Hello";
    const string world = hello + " World" + "!";

    cout << world << endl;

}


#if 0
int t4()
{
    const string exclaim = "!";
    const string message = "hello" +  ", World" + exclaim; // string_literal + string_literal causes error

    cout << message << endl;

}
#endif

int t5()
{
    {
        const string a = "a string";
        cout << a << endl;
    }
    
    
    {
        const string a = "another string";
        cout << a << endl;
    } 
    
}


int t6()
{

    const int pad = 1;
    int rows, cols;

    string name;

    cout << "What is you name? ";
    cin >> name;
    
    string greeting = "Hello " + name;

    rows = pad * 2 + 3;
    cols = greeting.size() + pad * 2 + 2;
    string first(cols, '*');
    
    
    for(int i = 0; i < rows; i++) {
        if (i == 0 || i == rows - 1) {
            cout << first << endl;
        } else if (i == pad + 1) {
            cout << '*';
            for (int j = 0; j < pad; j++) {
                cout << ' ';
            }
            cout << greeting;
            for (int j = 0; j < pad; j++) {
                cout << ' ';
            }
            cout << '*' << endl;
            
        } else {
            string pads(greeting.size() + pad * 2, ' ');
            cout << '*' << pads << '*' << endl;
        }
    }
}


int t7()
{

    int row, col;

    cout << "Enter row ";    
    cin >> row;

    
    for (int i = 0; i < row; i++) {
        int k = row - i + 1;
        int j = i * 2 + 1;
        string pad(k, ' ');
        string star(j, '*');
        cout << pad << star << endl;
    }
}


/* use appropriate types. Sometimes you need to use double instead of int. */
int t8()
{
    string name;
    cout << "What is your name? ";
    cin >> name;


    double midterm, final;

    cout << "Enter your midterm grade ";
    // if I enter non-number, it will 
    // be an error. and cin will not work after that, so you probably
    // need to clear the stream.
    cin >> midterm;


    cout << "Enter your final term grade ";
    cin >> final;

    cout << "Enter homework: ";

    int count = 0;
    double sum = 0, x;
    
    while (cin >> x) {
        count++;
        sum += x;
        // C-d means end of stream
    }

    streamsize prec = cout.precision();

    cout << "Your final grade is " << setprecision(3)
         << 0.2 * midterm + 0.3 * final + 0.5 * sum / count
         << setprecision(prec) << endl;
    return 0;
    
    
}

/* use appropriate types. Sometimes you need to use double instead of int. */
/* in the array or vector, check whether the index you want is correct. */
int t9()
{
    string name;
    cout << "What is your name? ";
    cin >> name;

    double midterm, final;

    cout << "Enter your midterm grade ";
    cin >> midterm;
    cout << "Enter your final term grade ";
    cin >> final;

    cout << "Enter homework: ";

    int x;
    vector<int> xv;
    
    while (cin >> x) {
        xv.push_back(x);
    }

    sort(xv.begin(), xv.end());
    double median;

    median = ((xv.size() % 2) == 1)? xv[xv.size()/2] : (xv[xv.size()/2 - 1] + xv[xv.size()/2])/2;

    cout << "Meding value is " << median << endl;
    
    streamsize prec = cout.precision();

    
    cout << "Your final grade is " << setprecision(3)
         << 0.2 * midterm + 0.3 * final + 0.5 * median
         << setprecision(prec) << endl;
    return 0;
    
    
}


int find_biggest()
{


}

int find_smallest()
{


}


// what is quartiles? how to calculte it?
// do not use size and index at the same time. try to use one (i.e., index).

double get_mid(const vector<double> &xv, int i, int j)
{
    int idx = i + (j - i) / 2;

    if ((j - i + 1) % 2 == 1)  {
        return xv[idx];
    } else {
        return (xv[idx] + xv[idx + 1]) / 2.0; // 2.0
    }
    
}


int t10()
{
    cout << "Enter numbers: ";

    double x;
    vector<double> xv;
    
    while (cin >> x) {
        xv.push_back(x);
    }

    sort(xv.begin(), xv.end());

    int idx = (xv.size() - 1) / 2;
    double median = get_mid(xv, 0, xv.size() - 1);
    double median_low, median_hi;

    if ((xv.size() % 2) == 1) {
        median_low = get_mid(xv, 0, idx);
        median_hi = get_mid(xv, idx, xv.size() - 1);
    } else {
        median_low = get_mid(xv, 0, idx);
        median_hi = get_mid(xv, idx + 1, xv.size() - 1);
    }

    cout << " the result is " << median_low << " : " << median << " : " << median_hi << endl;
    
    return 0;
    
}

int t11() 
{
    string s;
    
    map<string, int> counter;

    while (cin >> s) {
        counter[s]++;
    }

    for (map<string, int>::const_iterator it = counter.begin();
                 it != counter.end(); ++it) {

        cout << it->first << " : " << it->second << endl; // the output is sorted in alphabetical order. why?
    }
}

int t12()
{

    string s;
    vector<string> vs;
    

    cout << "Enter strings ";
    
    while (cin >> s) {
        vs.push_back(s);
    }

    // this is another world
    int max, min;

    max = min = 0;
    
    for (int i = 1; i < vs.size(); i++) {

        if (vs[max].size() < vs[i].size()) {
            max = i;
        }

        if (vs[min].size() > vs[i].size()) {
            min = i;
        }
    }

    cout << "max string is " << vs[max] << " and min string is " << vs[min] << endl;
}

double median(vector<double> vi) // if the vector is used for sort, it should not be defined as const. sort changes data.
// so we did not used reference, vector<double>& vi 
{
    vector<double>::size_type size;
    
    sort(vi.begin(), vi.end());
    size = vi.size();

    int med = (size - 1) / 2;

    if ((size % 2 == 1)) return vi[med];
    else return (vi[med] + vi[med + 1]) / 2;
}

// if the data is not frequently added or erased e
// at random position, list is not the right data structure.
// list is just for the data randomly deleted as vector incurs too
// much overheads

double median(list<double>& vi) 
{
    list<double>::size_type size, med;
    
    vi.sort();
    size = vi.size();

    med = size / 2;


    list<double>::size_type i = 0;
    double t1, t2;
    
    for (list<double>::const_iterator it = vi.begin();
         it != vi.end();
         ++it, ++i) {

        if (i == med)
            t1 = *it;
        else if (i == med + 1) {
            t2 = *it;
            break;

        }
    }

    if ((size % 2 == 1)) return t1;
    else return (t1 + t2) / 2;

}


// grade should be not be int as it should be multilied by 0.X

double grade(double midterm, double final, double hw_median)
{

    return (0.2 * midterm + 0.3 * final + 0.5 * hw_median);

}

double grade(double midterm,
        double final,
        const vector<double>& hw)
{

    if (hw.size() == 0)
          throw domain_error("student has done no homework");

    return grade(midterm, final, median(hw)); // median() takes vector<double> using call by value, so it is ok. It should be problem if it takes
    // the arguments by references.
    
}

double grade(double midterm,
        double final,
        list<double>& hw)
{

    if (hw.size() == 0)
        throw domain_error("student has done no homework");

    return grade(midterm, final, median(hw));
    
}

istream& read_hw(istream& is, vector<double>& hw)
{
    double x;

    if (is) {

        hw.clear();

        while(is >> x) {

            hw.push_back(x);
        }

        is.clear(); // clear the error status of the stream so that input continue.
    }

    return is;
}

istream& read_hw(istream& is, list<double>& hw)
{
    double x;

    if (is) {

        hw.clear();

        while(is >> x) {

            hw.push_back(x);
        }

        is.clear(); // clear the error status of the stream so that input continue.
    }

    return is;
}

struct student_info 
{
    string name;
    double midterm;
    double final;
    vector<double> hw;
};


istream& read(istream& is, student_info& s)
{
    is >> s.name >> s.midterm >> s.final;

    read_hw(is, s.hw);

    return is;
}

double grade(const struct student_info& s)
{
    return grade(s.midterm, s.final, s.hw);
}


bool compare(const struct student_info& s1,
        const struct student_info& s2)
{
    return s1.name < s2.name;
}

    
//page.64

int t13()
{
    vector<struct student_info> vs;
    struct student_info si;

    string::size_type maxlen = 0;
    
    while (read(cin, si)) {

        vs.push_back(si); // push_back copies contents.
        maxlen = max(si.name.size(), maxlen);
    }

    sort(vs.begin(), vs.end(), compare);
    
    for (vector<struct student_info>::size_type i = 0;
         i != vs.size(); ++i) {

        cout << vs[i].name << string(maxlen - vs[i].name.size(), '*');

        try {
            double final_grade = grade(vs[i]);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec);

        }
        catch (domain_error e) {

            cout << e.what();

        }

        cout << endl;

    }

    return 0;

}

static double* f()
{

    double d[3];
    
    d[0] = d[1] = d[2] = 3;

    return d; // address of local variable d is returned, which may make system crash.
}

int t14()
{

    for (int i = 1; i <= 100; i++) {

        cout << setw(5) << i << " : " << setw(5) << i * i << endl;

    }
    double d = f()[2];
    cout << d << endl;
    
}

int int_width(int x)
{
    int len = 0;

    while (x >= 1) {
        x = x / 10;
        ++len;
    }
    
    return len;
}


int t15()
{
    int maxlen = 0;
    
    for (int i = 1; i <= 100; i++) {

        maxlen = max(maxlen, int_width(i * i));
    }

    for (int i = 1; i <= 100; i++) {

        cout << setw(maxlen) << i << " : " << setw(maxlen) << i * i << endl;

    }

}

int double_width(double x, int n)
{
    int len = n; // decimal places sosujeom 

    while (x >= 1) { // it should not be ' > 0' as double 0.32  > 0.
        x = x / 10;
        ++len;
    }
    
    return len;
}

int t16()
{
    double max_base = 99.9;

    int max_base_width = double_width(max_base, 1);

    int max_result_width = double_width(max_base * max_base, 2);

    cout << "*** : " << max_base_width << " " << max_result_width << endl;

    int dd;
    
    cin >> dd;
    

    for (double i = 0; i < max_base; i += .1) {

        cout << setw(max_base_width + 2) << setprecision(max_base_width) << i <<
                setw(max_result_width + 2) << setprecision(max_result_width) << i * i << endl;
        
    }
    
}

int t17()
{

    string s;
    map<string, int> mc;

    while (cin >> s) {
        mc[s]++;
    }
    

    for (map<string, int>::const_iterator it = mc.begin();
         it != mc.end(); ++it) {

        cout << it->first << " " << it->second << endl;
        
    }
    
         
}

// find number of words occurences

int t18()
{
    string s;
    vector<string> vs;


    while(cin >> s)
    {
        vs.push_back(s);

    }

    cout << "the number of words are " << vs.size() << endl;

    for (int i = 0; i < vs.size(); i++) {

        int count = 0;

        for (int j = 0; j < vs.size(); j++) {

            if (vs[i] == vs[j]) {

                if (j < i) // if this word exists before current word
                    goto out;
                count++;
            }
            

        }

        cout << vs[i] << " : " << count << endl;

    out:
        ;
        

    }

}

// same, but with sort.
int t19()
{

    string s;
    vector<string> vs;


    while(cin >> s)
    {
        vs.push_back(s);

    }

    cout << "the number of words are " << vs.size() << endl;

    sort(vs.begin(), vs.end()); // string does not need comparer
    

    for (int i = 0; i < vs.size();) {
        int count = 0;
        int j;

        //for (j = i; (vs[i] == vs[j]) && (j < vs.size()); j++) --> when j == vs.size() vs[j] causes segmentation fault.
        // ((j < vs.size()) && vs[i] == vs[j]) should work fine: && operator evaluate left side first and if it is true evaluate right.
        for (j = i; j < vs.size(); j++) {
            if (vs[i] != vs[j])
                break;
            count++;
        }

        cout << vs[i] << " : " << count << endl;
        i = j;
    }
    
}

/*
begin = x.begin();
for(auto i = x.begin(); i != x.end(); ++i)
 {
     if (*i == *begin)
         ++count;
     else
     {
         cout << *begin << " : " << count;
         begin = i;
     }
 }
*/

//chap5

bool fgrade(const student_info& s)
{
    return grade(s) < 60;
}

bool pgrade(const student_info& s)
{
    return !fgrade(s);
}


vector<student_info> extract_fail_1(vector<student_info>& vs)
{

    vector<student_info> fail;
    vector<student_info> succ;
    vector<student_info>::size_type i = 0;
    
    while (i != vs.size()) {
        if (fgrade(vs[i]))
            fail.push_back(vs[i]);
        else
            succ.push_back(vs[i]);

        i++;
    }
    
    vs = succ;

    return fail;

}

vector<student_info> extract_fail_2(vector<student_info>& vs)
{

    vector<student_info> fail;

    vector<student_info>::size_type i = 0;
    
    while (i != vs.size()) {
        if (fgrade(vs[i])) {
            fail.push_back(vs[i]);
            vs.erase(vs.begin() + i);
        }
        else
            i++;
    }
    
    return fail;

}

vector<student_info> extract_fail_3(vector<student_info>& vs)
{

    vector<student_info> fail;

    for (vector<student_info>::iterator it = vs.begin();
                 it != vs.end();) {
        if (fgrade(*it)) {
            fail.push_back(*it);
            vs.erase(it);
        }
        else
            ++it;
    }
    
    return fail;

}


vector<student_info> extract_fail_4(list<student_info>& ls)
{

    vector<student_info> fail;

    for (list<student_info>::iterator it = ls.begin();
                 it != ls.end();) {
        if (fgrade(*it)) {
            fail.push_back(*it);
            ls.erase(it);
        }
        else
            ++it;
    }
    
    return fail;

}

vector<string> split(const string& s)
{


    string::size_type i;
    vector<string> ret;

    i = 0;

    while (i != s.size()) {

        while (i != s.size() && isspace(s[i]))
            i++;

        string::size_type j = i;
        while (j != s.size() && !isspace(s[j]) )
            j++;
                
        if (i != j)
            ret.push_back(s.substr(i,  j - i));

        i = j;

    }
    return ret;
    
}
    
int t20()
{

    string s;
    
    while (getline(cin, s)) {

        vector<string> vs = split(s);

        for (vector<string>::const_iterator it = vs.begin();
             it != vs.end(); ++it) {

            cout << *it << endl;

        }
        
    }

}

//interesting!!

int t21()
{
    string s;
    while (cin >> s) {

        cout << s << endl;
    }
    
}


string::size_type width(const vector<string>&);

    
vector<string> hcat(const vector<string>& a, const vector<string>& b)
{

    string::size_type i, j, max_len, max_len_2;
    vector<string> ret;

    j = i = 0;

    max_len = width(a);
    max_len_2 = width(b);
    
    while (! (i == a.size() && j == b.size())) {
        string s;
        
        if (i != a.size()) {
            s = a[i];
            ++i;
        }

        if (j != b.size()) {
            s += string(max_len - s.size(), ' ');
            s += b[j];
            s += string(max_len_2 - b[j].size(), ' ');
            ++j;
        }
        ret.push_back(s);
    }
    return ret;
    // if you finished a function,
    // alway remember that we should return something!!!!
    
}

vector<string>
hcat2(const vector<string>& a, const vector<string>& b) //hcat with iterator
{

    typedef vector<string>::const_iterator iter;
    vector<string> ret;

    iter i = a.begin();
    iter j = b.begin();

    string::size_type max_len, max_len_2;
    max_len = width(a);
    max_len_2 = width(b);

    while (! (i == a.end() && j == b.end())) {
        string s;
        
        if (i != a.end()) {
            s = *i;
            ++i;
        }

        if (j != b.end()) {
            s += string(max_len - s.size(), ' ');
            s += *j;
            s += string(max_len_2 - j->size(), ' ');
            ++j;
        }
        ret.push_back(s);
    }
    return ret;
    // if you finished a function,
    // alway remember that we should return something!!!!
    
}


string::size_type width(const vector<string>& s)
{

    string::size_type max_len = 0; // defalt value is not 0
    
    for (vector<string>::size_type i = 0; i != s.size(); ++i) {

        max_len = max(max_len, s[i].size());
        
    }
    return max_len;
}


int t22()
{
    vector<string> a;
    vector<string> b;
    
    string line;
    string::size_type max_len;
    

    // while (cin >> s) ....
    // while (cin >> s) ....
    // this two line cannot work if ctrl+d butten is pressed. I have no idea how to clear, as cin.clear() does not clear ctrl+d.
    getline(cin, line);
    a = split(line);

    /*
     * test for split works fine 
    for(vector<string>::size_type i = 0; i != a.size(); ++i)
        cout << a[i];
    */
    getline(cin, line);
    b = split(line);

    /* test for split works fine
     for(vector<string>::size_type i = 0; i != b.size(); ++i)
     cout << b[i] << endl;
    */

     cout << " Result is " << endl;



     vector<string> ret = hcat(a, b);
     max_len = width(ret);
     string border(max_len + 4, '*');
     cout <<  border << endl;
     for(vector<string>::size_type i = 0; i != ret.size(); ++i)
         cout << "* " << ret[i] << " *" << endl;;

     cout <<  border << endl;
}

int t23()
{
    list<student_info> ls;
    student_info si;

    string::size_type maxlen = 0;
    
    while (read(cin, si)) {

        ls.push_back(si);
        maxlen = max(si.name.size(), maxlen);
    }

    ls.sort(compare);
    
    for (list<student_info>::iterator it = ls.begin(); // it should not be const_iterator as in the grade() function takes non-const argument.
         it != ls.end(); ++it) {

        cout << it->name << string(maxlen - it->name.size(), '*');

        try {
            double final_grade = grade(*it); // this function takes non-const arguments.
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec);

        }
        catch (domain_error e) {

            cout << e.what();

        }

        cout << endl;

    }

    return 0;

}

//use typedef
int t24()
{

    // typedef seems not be in the if-then-else part.

#ifdef ACC_USE_LIST 
    typedef list<student_info> student_list;
#else
    typedef vector<student_info> student_list;
#endif

    student_list ls;
    student_info si;
    string::size_type maxlen = 0;

    
    while (read(cin, si)) {

        ls.push_back(si);
        maxlen = max(si.name.size(), maxlen);
    }

#ifdef ACC_USE_LIST
    ls.sort(compare);
#else
    sort(ls.begin(), ls.end(), compare);
#endif
    
    for (student_list::iterator it = ls.begin(); // it should not be const_iterator as in the grade() function takes non-const argument.
         it != ls.end(); ++it) {

        cout << it->name << string(maxlen - it->name.size(), '*');

        try {
            double final_grade = grade(*it); // this function takes non-const arguments.
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec);

        }
        catch (domain_error e) {

            cout << e.what();

        }

        cout << endl;

    }

    return 0;

}


int t25()
{

    vector<string> vs;
    vector<string> vs2;
    

    vs.push_back(string("this"));
    vs.push_back("is");

    vs2.push_back("new");
    vs2.push_back("world");

    vs.insert(vs.end(), vs2.begin(), vs2.end());

    for (vector<string>::const_iterator it = vs.begin();
         it != vs.end();
         ++it) {
        cout << *it << endl;
    }
    
}

// interesting!!
bool is_palindrome(const string&s)
{

    return equal(s.begin(), s.end(), s.rbegin());
}


static bool
space(char c)
{
    return isspace(c); // overloaded function
}

static bool
not_space(char c)
{
    return !isspace(c);
}

//interesting!!
vector<string> split2(const string& str)
{

    vector<string> ret;
    string::const_iterator b = str.begin(), e = str.end();

    while (b != e) {
        b = find_if(b, e, not_space);
        if (b != e) {
            string::const_iterator k;
            k = find_if(b, e, space);
            ret.push_back(string(b, k));
            b = k;
        }
    }
    return ret;
}

bool
not_url_char(char c)
{
    static const string url_char = "~;/?:@=&$-_.+!*'(),";

    return !(isalnum(c) ||
            find(url_char.begin(), url_char.end(), c) != url_char.end());
}


string::const_iterator
url_begin(string::const_iterator b, string::const_iterator e)
{

    static const string sep = "://";
    typedef string::const_iterator iter;
    

    iter i = b;
    while (i != e) {
         i = search(i, e, sep.begin(), sep.end());

         if (i != e && i != b  && i + sep.size() != e) {

             iter beg = i;

             while (beg != b && isalpha(beg[-1]))
                 beg--;

             if (beg != i && !not_url_char(i[sep.size()]))
                 return beg;
         }

         i += sep.size();
         
    }

    return e;
    /* same as return i */
}


string::const_iterator
url_end(string::const_iterator b, string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}


vector<string>
find_url(const string& s)
{
    vector<string> ret;

    string::const_iterator b = s.begin();
    string::const_iterator e = s.end();
    
    while (b != e) {

        b = url_begin(b, e);
        if (b != e) {
            
            string::const_iterator k = url_end(b, e);
            ret.push_back(string(b, k));
            b = k;
        }
    }
    return ret;

}

int t26()
{
    vector<string> urls = find_url("this is the address of amazon http://www.amazon.dom");

    vector<string>::const_iterator b = urls.begin();
    
    while (b != urls.end())
        {
            cout << *b;
            b++;
        }
    cout << endl;
    
            

}

bool
did_all_hw(const student_info& s)
{
    return (find(s.hw.begin(), s.hw.end(), 0) == s.hw.end());
}

double
grade_aux(const student_info& s) // grade(student_info s) -> we can call 'grade (a)' if a is type 'const student_info &'
{
    try {
        return grade(s);
    } catch (domain_error){
        return grade(s.midterm, s.final, 0);
    }
}


double
median_analysis(const vector<student_info> &si)
{
    vector<double> grades;

    transform(si.begin(), si.end(), back_inserter(grades), grade_aux); // std::back_inserter

    return median(grades);
}

double
average(const vector<double> &v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double
average_grade(const student_info& s)
{
    return grade(s.midterm, s.final, average(s.hw));
}


double
average_analysis(const vector<student_info> &si)
{
    vector<double> grades;

    transform(si.begin(), si.end(), back_inserter(grades), average_grade);

    return median(grades);
}

double
opt_median(const student_info& si)
{
    vector<double> nonzero;

    remove_copy(si.hw.begin(), si.hw.end(), back_inserter(nonzero), 0);

    if (nonzero.empty())
        return grade(si.midterm, si.final, 0);
    else
        return grade(si.midterm, si.final, median(nonzero));
}

double
opt_median_analysis(const vector<student_info> &si)
{
    vector<double> grades;

    transform(si.begin(), si.end(), back_inserter(grades), opt_median);

    return median(grades);
}

/* merge of above three analysis method */
double
do_analysis(const vector<student_info>& si, double method(const student_info&))
{
    vector<double> grades;

    transform(si.begin(), si.end(), back_inserter(grades), method);

    return median(grades);
}


void
write_analysis(ostream &out, const string name,
        double analysis(const vector<student_info> &),
        const vector<student_info> &did,
        const vector<student_info> &didnt)
{
    out << name << ": (did) = " << analysis(did) <<
            ", (didnt) = " << analysis(didnt) << endl;
}

int
t27()
{
    vector<student_info> did, didnt;

    student_info s;

    while (read(cin, s)){
        if(did_all_hw(s))
            did.push_back(s);
        else
            didnt.push_back(s);
        }

    if (did.empty()) {
        cout << "No student did all the homework" << endl;
        return 1;
        }
    if (didnt.empty()) {
        cout << "All students did all the homework" << endl;
        return 1;
        }

    write_analysis(cout, "median", median_analysis, did, didnt);
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "opt median", opt_median_analysis, did, didnt);
}

vector<student_info>
extract_fail_5(vector<student_info>& si)
{
    vector<student_info> fail;

    remove_copy_if(si.begin(), si.end(), back_inserter(fail), pgrade);

    si.erase(remove_if(si.begin(), si.end(), fgrade), si.end()); /* erase function does not take const_iterator type. */

    return fail;

}

vector<student_info>
extract_fail_6(vector<student_info>& si)
{
    vector<student_info>::iterator iter = /* const_iterator does not work. */
            stable_partition(si.begin(), si.end(), pgrade);
    vector<student_info> fail(iter, si.end());
    si.erase(iter, si.end());
    return fail;
}


int t28()
{

    vector<double> vd(10);
    cout << "The size of vd is " << vd.size() << endl;
    vd.resize(100);
    cout << "The size of vd after resize is " << vd.size() << endl;

}
    

int t29()
{

    vector<string> vs;
    string s;
    string ret;
    
    
    while (cin >> s) {
        vs.push_back(s);
        
    }
    

    for (vector<string>::const_iterator it = vs.begin();
         it != vs.end(); it++) {
        remove_copy(it->begin(), it->end(), back_inserter(ret), 0);
    
    }
    

    cout << ret << endl;
}

// vector<inxt>::size_type i;
// i = 0; i--;
// cout << i
// print very big number.



/* chap 7 */
int t30()
{

    string s;
    map<string, int> mc;

    while(cin >> s) {
        mc[s]++;
    }
    

    for(map<string, int>::const_iterator it = mc.begin();
        it != mc.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }
    
}


map<string, vector<int> >
xref(istream& in, vector<string> find_words(const string&) = split)
{

    string line;
    int line_number = 0;

    map<string, vector<int> > ret;

    while(getline(in, line)) {
        ++line_number;

        vector<string> words = find_words(line);
        for(vector<string>::const_iterator it = words.begin();
            it != words.end(); ++it) {

            ret[*it].push_back(line_number);
        }
    }
    return ret;
    
}



typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

Grammar
read_grammar(istream& in)
{

        Grammar ret;

        string line;

        while(getline(in, line)) {

            vector<string> entry = split(line);

            if (!entry.empty()) {

                ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));

            }

        }

        return ret;

}



bool
bracketed(const string& str)
{
    return ((str.size() > 1) && (str[0] == '<') && (str[str.size() - 1] == '>'));
}



// interestng... 
int
nrand(int n)
{

    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");

    const int bucket_size = RAND_MAX / n;
    int r;
    do r = rand() / bucket_size;
    while (r >= n);

    return r;
}


void
gen_aux(const Grammar& g, const string& word, vector<string>& ret)
{


    if (!bracketed(word))
        ret.push_back(word);

    else {

        Grammar::const_iterator it = g.find(word);

        if (it == g.end())
            throw logic_error("empty rules");

        const Rule_collection rc = it->second;

        const Rule r = rc[nrand(rc.size())];

        for (Rule::const_iterator i = r.begin();
             i != r.end(); ++i) {
            gen_aux(g, *i, ret);
            
        }
        
    }
}


vector<string>
gen_sentences(const Grammar& g)
{
    vector<string>ret;
    gen_aux(g, "<sentence>", ret);

    return ret;
}




// 7-1 using vector
int t31()
{
    string s;
    map<string, int> mc;
    vector<vector<string> >  mc2;
    int max = 0;
    
    while(cin >> s) {
        mc[s]++;
    }
    
    for(map<string, int>::const_iterator it = mc.begin();
        it != mc.end(); it++) {
        if (max < it->second)
            max = it->second;
    }

    mc2.resize(max + 1);
    
    for(map<string, int>::const_iterator it = mc.begin();
        it != mc.end(); it++) {
        mc2[it->second].push_back(it->first);
    }
    
    for (vector<vector<string> >::const_iterator it = mc2.begin();
         it != mc2.end(); it++) {
        cout << endl << "*******" << endl;

        for (vector<string>::const_iterator iter = it->begin();
             iter != it->end(); iter++) {

            cout << " " << *iter;
        }
        
    }
    
}

//7-1 using map
int t32()
{
    string s;
    map<string, int> mc;
    map<int, vector<string> >  mc2;
    
    while (cin >> s) {
        mc[s]++;
    }
    
    for (map<string, int>::const_iterator it = mc.begin();
        it != mc.end(); it++) {
        mc2[it->second].push_back(it->first);
    }
    
    
    for (map<int, vector<string> >::const_iterator it = mc2.begin();
         it != mc2.end(); it++) {
        cout << endl << "*******" << endl;

        for (vector<string>::const_iterator iter = it->second.begin();
             iter != it->second.end(); iter++) {

            cout << " " << *iter;
        }
        cout << endl;
    }
}


int t33()
{
    vector<struct student_info> vs;
    struct student_info si;
    map<char, int> gmap;
    
    while (read(cin, si)) {

        vs.push_back(si);
    }

    for (vector<struct student_info>::size_type i = 0;
         i != vs.size(); ++i) {

        try {
            double final_grade = grade(vs[i]);
            int x =  final_grade / 10;
            cout << "final grade is " << final_grade << " : " << x << endl;
            
            switch (x){
            case 10:
            case 9:
                gmap['A']++;
                break;
            case 8:
                gmap['B']++;
                break;
                
            case 7:
                gmap['C']++;
                break;
            case 6:
                gmap['D']++;
                break;
                
            default:
                gmap['F']++;
                
                break;
            }
            
                
        }
        catch (domain_error e) {
            cout << e.what();
        }

    }

    
    for (map<char, int>::const_iterator it = gmap.begin();
         it != gmap.end(); ++it) {

        
        cout << it->first << " : " << it->second << endl;

    }

    return 0;

}

//7-3

map<string, vector<int> >
xref2(istream& in, vector<string> find_words(const string&) = split)
{

    string line;
    int line_number = 0;

    map<string, vector<int> > ret;

    while(getline(in, line)) {
        ++line_number;

        vector<string> words = find_words(line);
        for(vector<string>::iterator it = words.begin();
            it != words.end(); ++it) {
            
            if(find(it + 1, words.end(), *it) != words.end()) /* add line number only once. no duplicate line number. */
                /* find() does not need const_iterator as its first argument. iterator + 1 should mean next item */
                ret[*it].push_back(line_number);
        }
    }
    return ret;
}

int t34()
{
    vector<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);


    vector<int>::iterator it = a.begin();

    cout << "a is " << *it << endl;
    cout << "b is " << *(it + 1) << endl;
}


//7-5 using list

void
gen_aux(const Grammar& g, const string& word, list<string>& ret)
{


    if (!bracketed(word))
        ret.push_back(word);

    else {

        Grammar::const_iterator it = g.find(word);

        if (it == g.end())
            throw logic_error("empty rules");

        const Rule_collection rc = it->second;

        const Rule r = rc[nrand(rc.size())];

        for (Rule::const_iterator i = r.begin();
             i != r.end(); ++i) {
            gen_aux(g, *i, ret);
            
        }
        
    }
}


list<string>
gen_sentences_list(const Grammar& g)
{
    list<string> ret;
    gen_aux(g, "<sentence>", ret);

    return ret;
}

//7-6 non-recursive gen_sentences
void
gen_aux(const Grammar& g, vector<string>& ret, vector<string>& stk)
{
    while (!stk.empty()) {
        string word = stk[stk.size() - 1];
        stk.pop_back();

        if (!bracketed(word))
            ret.push_back(word);

        else {
            
            Grammar::const_iterator it = g.find(word);

            if (it == g.end())
                throw logic_error("empty rules");

            const Rule_collection rc = it->second;

            const Rule r = rc[nrand(rc.size())]; // remember this is const

            for (Rule::const_reverse_iterator i = r.rbegin(); /* used rbegin and rend as stk is used as a stk. */
                 // so this should also be const_reverse_iterator
                 i != r.rend(); ++i) {
                stk.push_back(*i);
            }
        }
    }
}


vector<string>
gen_sentences_iterative(const Grammar& g)
{
    vector<string> ret;
    vector<string> stk;
    stk.push_back("<sentence>");
    
    gen_aux(g, ret, stk);

    return ret;
}


int t35()
{

    vector<string> sentence = gen_sentences_iterative(read_grammar(cin));

    vector<string>::const_iterator it = sentence.begin();
    if(!sentence.empty()) {
        cout << *it ;
        ++it;
    }
    while (it != sentence.end()) {

        cout << " " << *it;

        ++it;
    }

    cout << endl;

    return 0;
}


//7-9: is it right?

int
nrand2(int n)
{
    if (n <= RAND_MAX) {
        return nrand(n);
    } else {
        int bucket_number = n / RAND_MAX;
#if 0
        // I think we don't need this...
        int bucket_remain = n % RAND_MAX;

        if (bucket_remain > 0)
            ++bucket_number;
#endif        
        int r;
        
        do r = nrand2(bucket_number) * RAND_MAX + nrand2(RAND_MAX);
        while (r >= n);
        return r;
    }    
}

//chap 8

//p 141
template <class T>
T medianT(vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz; // used typename

    vec_sz size = v.size();
    if (size == 0)
        throw domain_error("median of an empty vector");

    sort(v.begin(), v.end());

    vec_sz mid = size / 2;

    return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
    
}

//p 143.
//

template <class T>
T max2(const T& left, const T& right)
{
    return left > right? left : right;

}


int t36()
{
    string name("myname");
    
    string::size_type maxlen = 0;
    maxlen = max2(maxlen, name.size()); // two arguments should have the same type

}

//p148
template <class BidIt>
void
reverse (BidIt begin, BidIt end)
{
    while (begin != end) {
        --end;
        if (begin != end)
            swap (*begin++, *end);
    }
    
}



//p152, split with template
template <class Out>
void split3(const string& s, Out os) 
{

    typedef string::const_iterator iter;

    iter beg = s.begin();
    
    while (beg != s.end()) {

        beg = find_if(beg, s.end(), not_space);
        iter j = find_if(beg, s.end(), space);
        if (beg != s.end())
            *os++ = string(beg, j);
        
        beg = j;
    }
    

}

int t37()
{
    string s;
    while (getline(cin, s)) {

        split3(s, ostream_iterator<string>(cout, "\n"));

        return 0;

    }
    
}

// 8-1: template can be used not just a class but a function as well.
template <class T>
double
do_test(vector<double>& si, T& t)
{
    vector<double> grades;

    transform(si.begin(), si.end(), back_inserter(grades), t);

    return median(grades);
}

double plus1(double x)
{
    return x + 1;
}

double plus10(double x)
{
    return x + 10;
}

double plus100(double x)
{
    return x + 100;
}

   
int t38()
{
    double x;
    vector<double> si;
    
    while (cin >> x)
        si.push_back(x);

    cout << "test 1: " << do_test(si, plus1) << endl;
    cout << "test 2: " << do_test(si, plus10) << endl;
    cout << "test 3: " << do_test(si, plus100) << endl;


}

//8-2

template <class InIter1, class InIter2>
bool
equal2(InIter1 first1, InIter1 last1, InIter2 first2) // we should not use & (reference) as we change first1 in the body
{
    while (first1 != last1) {

        if (!(*first1) == (*first2))
            return false;

        ++first1;
        ++first2;
    }
    return true;
}

template <class InIter, class T>
InIter
find2(InIter first, InIter last, const T& t)
{
    while (first != last) {

        if ((*first) == t)
            return first;

        ++first;
    }
    return first;
}

template <class InIter1, class InIter2>
InIter2
copy2(InIter1 first1, InIter1 last1, InIter2 first2)
{
    while (first1 != last1) {

        *first2 = *first1;
        ++first1;
        ++first2;
    }
    return first2;
}

template <class InIter1, class InIter2, class UnaryPred>
InIter2
remove_copy_if2(InIter1 first1, InIter1 last1, InIter2 first2, UnaryPred pred)
{
    while (first1 != last1) {

        if (!pred(*first1))
            *first2++ = *first1;
        ++first1;
    }
    return first2;
}

template <class InIter1, class InIter2, class T>
InIter2
remove_copy2(InIter1 first1, InIter1 last1, InIter2 first2, const T& t)
{
    while (first1 != last1) {

        if (*first1 != t)
            *first2++ = *first1;
        ++first1;
    }
    return first2;
}


template <class FwdInIter1, class T>
FwdInIter1
remove(FwdInIter1 first1, FwdInIter1 last1, const T& t)
{
    FwdInIter1 ret = first1;
    
    while (first1 != last1) {

        if (*first1 != t) {
            *ret = *first1;
            ++ret;
        }
            
        ++first1;
    }
    return ret;
}



template <class InIter1, class InIter2, class UnaryPred>
InIter2
transform2(InIter1 first1, InIter1 last1, InIter2 first2, UnaryPred pred)
{
    while (first1 != last1) {

        *first2 = pred(*first1);
        ++first1;
        ++first2;
    }
    return first2;
}

template <class InIter1, class T>
T
accumulate2(InIter1 first1, InIter1 last1, T t)
{
    while (first1 != last1) {
        t += *first1++;
    }
    return t;
}

template <class FwdInIter1, class FwdInIter2>
FwdInIter1
search2(FwdInIter1 first1, FwdInIter1 last1, FwdInIter2 first2, FwdInIter2 last2)
{

    if (first2 == last2)
        return first1;
    
    while (first1 != last1) {
        FwdInIter1 i = first1;
        FwdInIter2 j = first2;

        while(j != last2 && i != last1) {
            if (*j != *i)
                break;
            j++;
            i++;
        }

        if (j == last2)
            return first1;
        if (i == last1)
            return last1;
        
        ++first1;
    }
    return first1;
}

// there are also methods like:
// count, count_if
//


template <class InIter, class Pred>
InIter
find_if2(InIter first, InIter last, Pred op)
{
    while (first != last) {

        if (op(*first))
            return first;

        ++first;
    }
    return first;
}

template <class BidInIter, class Pred>
BidInIter partition2 (BidInIter first, BidInIter last, Pred op)
{
    while (first != last) {

        while (op(*first)) {
            ++first;
            if (first == last)
                return first;
        }

        do { // last points to one past the last element, so I used do-while.
            --last;
            if (last == first)
                return first;
        } while (!op(*last));
        
        swap(*first, *last);
        ++first;
    }
    return first;
}


//8-3

template <class InIter>
InIter median2(InIter beg, InIter end)
{
    
    InIter it = beg;
    
    if (beg == end)
        throw domain_error("median of an empty vector");

    cout << endl;
    while (it != end)
        cout << *it++ << " ";

    cout << endl;
    sort(beg, end); // sort changes value pointed by iterator, so I need to copy it. So, it does not make make any difference.
    // also, we do not know whether the iterator is a vector/array or list, so we should visit all the elements. So it is not
    // very efficiet.

    while (beg != end)
        cout << *beg++ << " ";
        
}

int t49()
{
    int x[] = {1, 5, 2, 4, 3};
    median2(x, x + 5);

    vector<int> xv(x, x + 5);
    // xv.push_back(1);
    // xv.push_back(5);
    // xv.push_back(2);
    // xv.push_back(4);
    // xv.push_back(3);
    median2(xv.begin(), xv.end());
}


//8-4

template <class T>
void
swap2(T& a, T& b)
{
    T c(a);
    a = b;
    b = c;
}


int t39()
{

    vector<int> aa;
    
    aa.push_back(1);
    aa.push_back(2);

    vector<int>::iterator a = aa.begin();
    vector<int>::iterator b = a + 1;

#if 0
    swap2(*a, *b);
#else
    int c = *b; // we have to know the type of a and b if we want to expand the swap function.
    *b = *a;    // 
    *a = c;
#endif
    
    cout << "a is " << *a << " and b is " << *b << endl;

}

int t40()
{
    cout << "random number with RAND_MAX is " << RAND_MAX  << endl;

    int c = 10;

    while (c-- > 0) {
        
        int k = nrand2(10000);
        cout << " " << k << endl;
    }
}

//8-6

int t41()
{
    map<int, string> ms;
    vector<pair<int, string> > vs;
    

    ms[1] = string("new world");
    ms[3] = string(" has come");

    copy(ms.begin(), ms.end(), back_inserter(vs));

    cout << "first is " << vs[0].second << " and second is " << vs[1].second << endl;
    
}

//HEADUP
// using iterator might be problematic if you are using insert/erase.
// update iterator if you use erase.
// insert is more problematic. It does not return iterator but iterator after this might be invalidated. So..
// enough space should be reserved before. ctci 1.5
//  check out http://www.cplusplus.com/reference/vector/vector/insert/



int t42()
{
    map<int, string> ms;
    vector<pair<int, string> > vs;
    
    // map does not have push_back, so it cannot be used as an argument of back_inserter
    #if 0
    ms.push_back(pair<int, string>(1, string("new world")));
    ms.push_back(pair<int, string>(3, string(" has come")));
    #endif
    vs.push_back(pair<int, string>(1, string("new world")));
    vs.push_back(pair<int, string>(3, string(" has come")));
}


//chap 9

#include "student_info.h"

int t43()
{
    vector<Student_info> students;

    Student_info record;

    string::size_type maxlen = 0;

    // read and store data
    while(record.read(cin)) {

        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    sort(students.begin(), students.end(), Student_compare);

    for (vector<Student_info>::size_type i = 0;
         i != students.size(); ++i) {
        cout << students[i].name()
             << string(maxlen + 1 - students[i].name().size(), ' ');

        try {
            double final_grade = students[i].grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;

        } catch (domain_error e) {
            cout << e.what() << endl;

        }

    }

    return 0;
    
}


//9-3, 9-4
int t44()
{
    Student_info s;
    if (s.valid()) {
        double d = s.grade();
        cout << d;
    }
    else cout << "end" << endl;
}


//9-5
int t45()
{
    vector<Student_info> students;

    Student_info record;

    string::size_type maxlen = 0;

    // read and store data
    while(record.read(cin)) {
        // because we need maxlen, we did 2 phase: reading (computing) maxlen, and print.
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    sort(students.begin(), students.end(), Student_compare);

    for (vector<Student_info>::size_type i = 0;
         i != students.size(); ++i) {
        cout << students[i].name()
             << string(maxlen + 1 - students[i].name().size(), ' ');

        if (students[i].pass()) {
            cout << " PASS " << endl;
        } else {
            cout << " FAIL " << endl;
        }
        
    }

    return 0;
}

bool pass_9_6(const Student_info& s)
{
    return s.pass();
}

//9-6
int t46()
{
    vector<Student_info> students;

    Student_info record;

    string::size_type maxlen = 0;

    // read and store data
    while(record.read(cin)) {

        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    partition(students.begin(), students.end(), pass_9_6);
    

    for (vector<Student_info>::size_type i = 0;
         i != students.size(); ++i) {
        cout << students[i].name()
             << string(maxlen + 1 - students[i].name().size(), ' ');

        if (students[i].pass()) {
            cout << " PASS " << endl;
        } else {
            cout << " FAIL " << endl;
        }
        
    }

    return 0;
}

//chap 10
// interesting code. If switch/if was used, then it would be more confusing.
string
letter_grade(double grade)
{

    static const double numbers[] = {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
        };
    static const char* const letters[] = {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
        };
    static const size_t ngrade = sizeof(numbers) / sizeof(*numbers);

    for (size_t i = 0; i < ngrade; ++i) {
        if (grade >= numbers[i])
            return letters[i];
    }

    return "?\?\?";
}

int t47()
{
    ifstream infile(string("in").c_str());
    ofstream outfile("out");

    string s;

    while (getline(infile, s))
        outfile << s << endl;

    return 0;

}

char *
duplicate_chars(const char* p)
{

    size_t length = strlen(p) + 1;
    char* result = new char[length];

#if 0
    copy(p, p + length, result); // copy can take pointer as well as iterator.
#endif
    remove_copy(p, p + length, result, 'l'); // remove_copy also does not need iterator. pointer is enough.

    return result;
}

int t48()
{
    cout << endl << duplicate_chars("duplicate") << endl;
}

//10-2
// I have no idea how to make a median function for both vector and array.

template <class T>
T
median3(T* beg, T* end)
{
    size_t size = (end - beg); // pointer arithmatic unit is the size of the element
    void* addr = beg + size * sizeof(*beg); // pointer arithmatic unit is still the size of the element, so it is not what you expect.
    cout << endl << beg << " : " << end << " size is " << size << " and sizeof(*beg) is " << sizeof(*beg) << " and addr is " << addr << endl;

    if (size == 0)
        throw domain_error("median of an empty vector");

    T* result = new T[size];
    
    copy(beg, end, result);
    
    sort(result, result + size);

    size_t  mid = size / 2;
    cout << endl << "mid is " << mid << endl; 

    return size % 2 == 0 ? (result[mid] + result[mid - 1]) / 2 : result[mid];
    
}


int t50()
{

    int i[] = {5, 1, 2, 4, 3};

    double r = median3(i, i + 5);

    cout << "the result is " << r << endl;

    size_t cnt = 5;
    for (int j = 0; j < cnt; j++)
        cout << " " << i[j];
    cout << endl;

    vector<double> vi;
    vi.push_back(5);
    vi.push_back(6);
    vi.push_back(1);
    vi.push_back(3);
    vi.push_back(2);
    vi.push_back(4);

    r = medianT(vi);
    
    cout << "the result is " << r << endl;
    cnt = 6;
    for (int j = 0; j < cnt; j++)
        cout << " " << i[j];
    cout << endl;
    
    
}

// test erase before and after with vector: erased one and elements after that are invalidated, but in real implementation it seems just work.
// but inserting is really problematic. it may invalidate everything.
int t51()
{
    vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);
    vi.push_back(4);

    vector<int>::iterator it = vi.begin();
    vector<int>::iterator it2 = it + 1;

    cout << " " << *it << " " << *it2 << endl;
    vi.erase(it); // use it = vi.erase(it) if possible
    
    cout << "after  " << *it << " " << *it2 << endl;
    

}


//10-4 ~ 10-7

class String_list
{
public:
    void push_back(string s) 
    {
        sl.push_back(s);

    }
    typedef list<string>::const_iterator const_iterator;
    typedef list<string>::iterator iterator;

    iterator begin()
    {
        return sl.begin();
        
    }

    iterator end()
    {
        return sl.end();

    }

    const_iterator begin() const
    {
        return sl.begin();
    }

    const_iterator end() const
    {
        return sl.end();
    }
    
    
private:
    list<string> sl;
};


int t52()
{

    String_list st;

    st.push_back("this");
    st.push_back("is");
    st.push_back("a new world!");

    typedef String_list::const_iterator iter;

    iter a = st.begin();

    cout << endl;
    
    while (a != st.end()) {

        cout << *a++ << " " ;
    }
    
    cout << endl;
    

}


int t53()
{
    cout << ptrdiff_t(1) << endl; // 1 

}


//chap 11

template <class T>
class Vec {
 
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;

    Vec() 
    {
        create();
    }

    explicit Vec(size_type n, const T& t = T()) 
    {
        create(n, t);
    }
    Vec(const Vec& v)
    {
        create(v.begin(), v.end());
    }
    Vec& operator=(const Vec&);
    ~Vec() 
    {
        uncreate();
    }

    T& operator[](size_type i)
    {
        return data[i];
    }

    const T& operator[](size_type i) const
    {
        return data[i];
    }

    void push_back(const T& t)
    {
        if (avail == limit)
            grow();
        unchecked_append(t);
    }
    size_type size() 
    {
        return avail - data;
    }
    size_type size() const
    {
        return avail - data;
    }
    iterator begin() 
    {
        return data;
    }
    const_iterator begin () const 
    {
        return data;

    }
    iterator end()
    {
        return avail;
    }
    const_iterator end() const 
    {
        return avail;
    }

    iterator erase(iterator);
    void clear();
    

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();
    void grow();
    void unchecked_append(const T&);
    
    
};

template <class T>
void
Vec<T>::create()
{
    data = avail = limit = 0;
}

template <class T>
void
Vec<T>::create(size_type n, const T& val) 
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

template <class T>
void
Vec<T>::create(const_iterator i, const_iterator j) 
{
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}

template <class T>
void
Vec<T>::uncreate()
{
    if (data) {
        iterator it = avail;
        while (it != data) {
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit - data);
    }

    data = limit = avail = 0;
}

template <class T>
void
Vec<T>::grow()
{
    size_type new_size = max(2 * (avail - data), ptrdiff_t(1));

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);
    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T>
void
Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}


/* if I want to use iterator instead of T*, I may have to define this function in the declaration */
template <class T>
T*
Vec<T>::erase(iterator i)
{
    iterator new_avail = uninitialized_copy(i + 1, avail, i);
    avail = new_avail;
    return i;
}

template <class T>
void
Vec<T>::clear()
{
    uncreate();
}

template <class T>
Vec<T>&
Vec<T>::operator=(const Vec& rhs)
{
    if (&rhs != this) {
        uncreate();
        create(rhs.begin(), rhs.end());
    
    }
    return *this;
}
    

int t54()
{
    Student_info a;
    Student_info b(a);
    b = a;
}

int t55()
{
    Vec<int> xv;
    cout << " the size is " << xv.size() << endl;
    xv.push_back(1);
    cout << " the size is now " << xv.size() << endl;
    xv.push_back(2);
    cout << " the size is now " << xv.size() << endl;
    xv.push_back(3);
    cout << " the size is now " << xv.size() << endl;

    for (Vec<int>::iterator it = xv.begin();
         it != xv.end();) {
        cout << *it << " " ;

        if (*it == 1)
            it = xv.erase(it);
        else
            ++it;
    }

    cout << endl;
    cout << " the size is now " << xv.size() << endl;

    for (Vec<int>::const_iterator it = xv.begin();
         it != xv.end(); ++it) {
        cout << *it << " " ;
    }
    cout << endl;

    xv.clear();
    cout << " the size is now " << xv.size() << endl;
    
}

//11-8

template <class T>
class List {
public:
    
    class ListItem
    {
    public:
        ListItem()
        {

        }
        
        ListItem(const T& t): data(t) 
        {
            
        }
        ListItem* prev;
        ListItem* next;
        T data;
    };

    typedef ListItem ListItemT;

    class Iterator 
    {
    public:
        Iterator(ListItemT* l) : ls(l) 
        {
        }

        Iterator(const Iterator& x) : ls(x.ls) 
        {
        }
        Iterator& operator++()
        {
            ls = ls->next;
            return *this;
        }
        T& operator*()
        {
            return ls->data;
        }
        bool operator!=(const Iterator& x) 
        {
            return (ls != x.ls);
        }

    private:
        ListItemT * ls;
    };
    
    typedef Iterator iterator;
    typedef const Iterator const_iterator;

        
    void push_back(const T& val) 
    {
        ListItemT* t = new ListItemT(val);

        if (first == last){
            first = t;
            first->prev = last;
            first->next = last;
            last->prev = first;
            last->next = first;
        } else {
            last->prev->next = t;
            t->prev = last->prev; //be careful in setting pointer
            last->prev = t;
            t->next = last;
        }
    }
    
    iterator begin() 
    {
        return Iterator(first);
    }

    iterator end()
    {
        return Iterator(last);
    }

    const_iterator begin() const
    {
        return Iterator(first);
    }
    
    const_iterator end() const
    {
        return Iterator(last);
    }

    List() 
    {
        first = last = new ListItemT;
        first->prev = last;
        last->next = first;
    }
    ~List()
    {
        while (first != last) {
            ListItemT* it = first;
            first = first->next;
            delete it;
        }

        delete last;
    }

private:
 
    ListItemT* first;
    ListItemT* last;
};


int t56()
{
    List<int> li;

    li.push_back(1);
    li.push_back(2);
    li.push_back(3);

    for (List<int>::iterator it = li.begin();
         it != li.end();
         ++it)
    {
        cout << " element is " ;
        cout << *it << " " ;
    }

    cout << endl;
    
}

int t57()
{
    const string s("hello ");
    const string w("world");
    cout << s + w + " !" + " !! "  << endl; // "hello " + "world" fails because operator+ does not accept it.
    // but + is left associative, so s + w + " !" is string, and string + "!!" also works fine. "hello" + "world" does...
}


class A {

    public:
    A(): k(0) {
        cout << "default" << endl;
    }
    A(const A& a): k(a.k) {
        cout << "copy" << endl;
        
    }
    A(int x) : k(x) {
        cout << " A(int) is called" << endl;
    }
    ~A() {
        cout << "destructor" << endl;
    }
    A& operator=(const A& a){
        cout << "assign" << endl;
        k = a.k;
    }
    
    int k;
};


class B : public A {

public:
    B() {
        cout << "B() is called" << endl;
    }

    B(int x) : A(x) {
        cout << "B(int) is called" << endl;
    }
    
    ~B() {
        cout << "~B() is called" << endl;
    }


};

int t58()
{

    A a;
    cout << " a is created" << endl;
    A b;
    cout << " b is created" << endl;
    A c = a;
    cout << " c is created" << endl;
    b = a;
    cout << " b is assignd" << endl;

    B e(1);
}

class Str {

public:

    friend std::istream& operator>>(std::istream&, Str&);
    friend int compare(const Str&, const Str&);
    typedef Vec<char>::size_type size_type;
    Str() { cout << "** default Str ctr " << endl; }
#if 1
    Str(const Str& s) : data(s.data)
    {
        //std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        cout << "** copy Str ctr: " + s.size() << endl;
    }
#endif
    Str(size_type n, char c): data(n, c) { }

    Str(const char* cp) {
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
        cout << "Str(char*) ctr" << endl;
    }


    template<class In>
    Str(In b, In e) {
        std::copy(b, e, std::back_inserter(data));
    }
    size_type size() const { return data.size();}
    char& operator[](size_type i) { return data[i];}
    const char& operator[](size_type i) const { return data[i];}

    char* c_str() {
        // this implementation is not good as it may not be called in const object.
        // this function should be just a reader
      _c_str = new char[size() + 1];
#if 1
      for (size_type i = 0; i != size(); i++) // if ret++ is used, then we cannot return ret as ret does point to the last element.
          _c_str[i] = data[i];
#else
      /* it also works */
      std::copy(data.begin(), data.end(), _c_str);
#endif
      _c_str[size()] = 0;
      return _c_str;
    }

    Str& operator+=(const Str& s)
    {
        std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        //delete _c_str;
        cout << " += is called " << endl;
        return *this;
    }

    operator bool(){
        return size();
    }
private:
    Vec<char> data;
    char * _c_str; /* this should be invalidated if the data is changed */
};

std::ostream&
operator<<(ostream& os, const Str& s)
{
    for (Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}

std::istream&
operator>>(istream& is, Str& s)
{
    s.data.clear();

    char c;
    while (is.get(c) && isspace(c))
        ;

    if (is) {
        do s.data.push_back(c);
        while (is.get(c) && !isspace(c));

        if (is)
            is.unget();
        
    }
    return is;
}

Str
operator+(const Str& s, const Str& t)
{
    Str r = s;
    r += t;
    return r;
}


// 12-2, only c_str() implemented
int t59()
{
    Str s("this");
    Str t(" is new world");

    Str n = s + t;
    
    cout << s << t << endl;
    
    //cout << " the size of n is " << n.size() << n.c_str() << endl;

    Str greeting = Str("Hello") + n + Str("!");

    Str &a = greeting; // reference should be initialised when it is declared.

    cout << endl << greeting << endl;
    

}

//12-3, 12-4


int
compare(const Str& a, const Str& b)
{

    Str::size_type i = 0;
    Str::size_type j = 0;

    while (i != a.size() && j != b.size()) {

        if (a.data[i] > b.data[j]) {
            return 1;
        }
        else if (a.data[i] < b.data[j]) {
            return -1;
        }
        else {
            j++;i++;
        }
    }

    if (i == a.size() && j == b.size())
        return 0;
    else if (i == a.size())
        return -1;
    else return 1;

}

bool
operator>(const Str& a, const Str& b)
{
    return (compare(a, b) > 0);
}

bool
operator<(const Str& a, const Str& b)
{
    return (compare(a, b) < 0);
}


bool
operator==(const Str& a, const Str& b)
{
    return (compare(a, b) == 0);
}

bool
operator!=(const Str& a, const Str& b)
{
    return (compare(a, b) != 0);
}

int t60()
{

    Str a("this");
    Str b("that");
    Str c("the");
    Str e("the ");

    if (a > b)
        cout << "a is bigger than b" << endl;
    else
        cout << "a is not bigger than b" << endl;

    if (a > c)
        cout << "a is bigger than c" << endl;
    else
        cout << "a is not bigger than c" << endl;

    if (c > b)
        cout << "c is bigger than b" << endl;
    else
        cout << "c is not bigger than b" << endl;

    if (c == e)
        cout << " c is equal with e" << endl;
    else if (c > e)
        cout << "c is greater than e" << endl;
    else
        cout << "e is greater than c" << endl;
    
}

// 12 - 6

int t61()
{
    Str a;
    Str b(" ");

    if (!a)
        cout << "a is empty" << endl;
    if (!b)
        cout << "b is empty" << endl;
}



//chap 13
class Core {

public:
    friend class Student_info_h;
    Core() : midterm(0), final(0) { }
    Core(std::istream& is) { read(is); }
    std::string name() const;
    virtual std::istream& read(std::istream&);
    virtual double grade() const;
    virtual  ~Core() { }
    virtual Core* clone() const { return new Core(*this); }

protected:
    std::istream& read_common(std::istream&);
    double midterm, final;
    std::vector<double> homework;

private:
    std::string n;
};

class Grad: public Core {

public:
    Grad() : thesis(0) {}
    Grad(std::istream& is) { read(is); }

    double grade() const; // virtual function should be declared and defined. inheritance does not work.
    std::istream& read(std::istream&);
    Grad* clone() const { return new Grad(*this); }
private:
    double thesis;
        
};

string
Core::name() const
{
    return n;
}

istream&
Core::read_common(istream& in)
{
    in >> n >> midterm >> final;
}

istream&
Core::read(istream& in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

istream&
Grad::read(istream& in)
{
    read_common(in);
    in >> thesis;
    read_hw(in, homework);
    return in;
}

double
Core::grade() const
{
    return ::grade(midterm, final, homework);
}

double
Grad::grade() const
{
    return min(Core::grade(), thesis);
}


class Student_info_h {
public:
    Student_info_h() : cp(0) {}
    Student_info_h(std::istream& is) : cp(0) { read(is); }
    Student_info_h(const Student_info_h&);
    ~Student_info_h() { delete cp; }
    Student_info_h& operator=(const Student_info_h&);


    std::istream& read(std::istream&);
    std::string name() const
    { // don't need to return const type
        if (cp)
            return cp->name();
        else
            throw std::runtime_error("uninitialized student");
    }
    
    double grade() const
    { // don't need to return const type
        if (cp)
            return cp->grade();
        else
            throw std::runtime_error("uninitialized student");
    }

    static bool compare(const Student_info_h& s1, const Student_info_h& s2)
    {
        return (s1.name() < s2.name());
    }
    
private:
    Core *cp;
};

std::istream&
Student_info_h::read(istream& is)
{
    delete cp;

    char ch;
    is >> ch;

    if (ch == 'U')
        cp = new Core(is);
    else
        cp = new Grad(is);

    return is;
}

Student_info_h::Student_info_h(const Student_info_h& s) : cp(0)
{
    if (s.cp) cp = s.cp->clone();
}

#if 0

void Core::regrade (double d) { final = d; }
void Grad::regrade (double d1, double d2) { final = d1; thesis = d2;}

if r reference to Core then;

r.regrade(100); // ok
r.regrade(100, 100); // compile error

else if r reference to Grad then:

r.regrade(100); // compile error
r.regrade(100, 100); // ok

/* this is becuase overriding */
r.Core::regrade(100) // ok
/*  
or you should define using virtual function */

virtual void Core::regrade(double d, double = 0) { final = d ;}


#endif


class test_static {

public:
    friend class ts_derived; // this is needed so that ts_derived can use ts_int type.
    static int x;
    int y;
    void foo () {
        cout << "x is " << x << endl;
        cout << "y is " << y << endl;
    }
    static void foos() {
        cout << "x is " << x << endl;
#if 0
        // this is not allowd as static function does not access to any object.
        cout << "y is " << y << endl;
#endif
    }
private:
    typedef int ts_int; // this is defined in the private:, so are not inherited by 
};

class ts_derived: public test_static {

public:
    ts_int j;
};

int test_static::x = 0; // dont forget to put type 'int'.

int t62()
{
    test_static ts;
    ts.foo();
    ts.foos();
}


//chap 14

template <class T>
T* clone(const T* tp)
{
    return tp->clone();
}

// specialization
template<>
Vec<char>* clone(const Vec<char>* vp)
{
    return new Vec<char>(*vp);
}

template <class T>
class Ptr {

public:
    void make_unique() {
        if (*refptr != 1) {
            --*refptr;
            refptr = new size_t(1);
            p = p? clone(p):0;

            }
        }
    Ptr(): p(0), refptr(new size_t(1)) { }
    Ptr(T* t): p(t), refptr(new size_t(1)) { }
    Ptr(const Ptr& h): p(h.p), refptr(h.refptr) { ++*refptr; }

    Ptr& operator=(const Ptr&);
    ~Ptr();
    operator bool() const {
        return p;
    }
    T& operator*() const {
        if (p)
            return *p;
        throw std::runtime_error("unbound Ref_handler");
    }

    T* operator->() const {
        if (p)
            return p;
        throw std::runtime_error("unbound Ref_handler");
    }
private:
    T* p;
    std::size_t* refptr;
};

template <class T>
Ptr<T>::~Ptr()
{
    if (--*refptr == 0) {
        delete p;
        delete refptr;
    }
}

template <class T>
Ptr<T>&
Ptr<T>::operator=(const Ptr& rhs)
{
    ++*rhs.refptr;
    if (--*refptr == 0) {
        delete refptr;
        delete p;
    }

    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}


// Str using Ptr
class Str2 {

    friend std::istream& operator>>(std::istream&, Str2&);
public:

    Str2& operator+=(const Str2& s) {
        data.make_unique();
        std::copy(s.data->begin(), s.data->end(), back_inserter(*data));
        return *this;
    }
    typedef Vec<char>::size_type size_type;

    Str2(): data(new Vec<char>) { }
    Str2(size_type n, char c): data(new Vec<char>(n, c)) { }

    Str2(const char* cp): data(new Vec<char>) {
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(*data)); 
    }


    template<class In>
    Str2(In b, In e): data(new Vec<char>) {
        std::copy(b, e, std::back_inserter(*data));
    }
    size_type size() const { return data->size();}
    char& operator[](size_type i) {
        data.make_unique();
        return (*data)[i];
    }

    // in this function, if we return non const then it does not bring compile error (just for clearing confusion)
    const char& operator[](size_type i) const {
        return (*data)[i];
    }

private:
    Ptr<Vec<char> > data;
};

std::ostream&
operator<<(ostream& os, const Str2& s)
{
    for (Str2::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}


int t63()
{
    Str2 s("this is new world");
    const Str2 s2(s);

    cout << endl << s2 << " : " << s2[2] << endl;
    cout << endl << s << " : " << s[2] << endl;
}

int t63_1()
{
    Ptr<vector<int> > x = new vector<int>(); // c+= allows new vector<int>, that means only type name. Java needs '()' as well.
    x->push_back(1);
    x->push_back(2);
    x->push_back(3);

    for(vector<int>::iterator it = x->begin(); it != x->end(); ++it) {
        cout << * it << endl;
    }
    cout << endl << (*x)[1] << endl;
}

//chap15

class Picture;

class Pic_base {

    friend std::ostream& operator<<(std::ostream&, const Picture&);
    friend class Frame_pic;
    friend class HCat_pic;
    friend class VCat_pic;
    friend class String_pic;

    typedef std::vector<string>::size_type ht_sz;
    typedef std::string::size_type wd_sz;

    virtual wd_sz width() const = 0;
    virtual ht_sz height() const = 0;
    virtual void display(std::ostream&, ht_sz, bool) const = 0;

public:
    virtual ~Pic_base() {}

protected:
    static void pad(std::ostream&, wd_sz, wd_sz);
};

void
Pic_base::pad(std::ostream& os, wd_sz beg, wd_sz end)
{
    while (beg != end) {
        cout << " ";
        ++beg;
    }
}

class String_pic : public Pic_base {

    friend class Picture;
    std::vector<string> data;
    String_pic(const std::vector<std::string>& v): data(v) { }

    ht_sz height() const { return data.size(); }
    wd_sz width() const;
    void display(std::ostream&, ht_sz, bool) const;

};

Pic_base::wd_sz          /* wd_sz is private, but is accessible to the friends. It cannot be be used outside */
String_pic::width() const
{
    Pic_base::wd_sz n = 0;
    for (Pic_base::ht_sz i = 0; i != data.size(); ++i)
        n = std::max(n, data[i].size());
    return n;
}

void
String_pic::display(std::ostream& os, ht_sz row, bool do_pad) const
{
    wd_sz start = 0;

    if (row < height()) {
        os << data[row];
        start = data[row].size();
    }

    if (do_pad) {
        pad(os, start, width());
    }
}

class VCat_pic: public Pic_base {
    friend Picture vcat(const Picture&, const Picture&);
    Ptr<Pic_base> top, bottom;
    VCat_pic(const Ptr<Pic_base>& t, const Ptr<Pic_base>& b): top(t), bottom(b) {}
    wd_sz width() const {
        return std::max(top->width(), bottom->width());
    }
    ht_sz height() const {
        return top->height() + bottom->height();
    }
    void display(std::ostream&, ht_sz, bool) const;

};

void
VCat_pic::display(std::ostream& os, ht_sz row, bool do_pad) const
{
    wd_sz w = 0;
    if (row < top->height()) {
        top->display(os, row, do_pad);
        w = top->width();
    } else if (row < height()) {
        bottom->display(os, row, do_pad);
        w = bottom->width();
    }
    if (do_pad) {
        pad(os, w, width());
    }

}

class HCat_pic: public Pic_base {

    friend Picture hcat(const Picture&, const Picture&);
    Ptr<Pic_base> left, right;
    HCat_pic(const Ptr<Pic_base>& l, const Ptr<Pic_base>& r) :left(l), right(r) { }
    wd_sz width() const { return left->width() + right->width(); }
    ht_sz height() const { return max(left->height(), right->height()); }
    void display(std::ostream&, ht_sz, bool) const;
};

void
HCat_pic::display(std::ostream& os, ht_sz row, bool do_pad) const
{
left->display(os, row, do_pad || row < right->height());
right->display(os, row, do_pad);
}

class Frame_pic: public Pic_base {
    friend Picture frame(const Picture&);
    Ptr<Pic_base> p;
    Frame_pic(const Ptr<Pic_base>& pic): p(pic) { }
    wd_sz width() const { return p->width() + 4; }
    ht_sz height() const { return p->height() + 4; }
    void display(std::ostream&, ht_sz, bool) const;

};

void
Frame_pic::display(std::ostream &os, ht_sz row, bool do_pad) const
{
    if (row >= height()) {
        if (do_pad)
            pad(os, 0, width());
    } else {
        if (row == 0 || row == height() - 1) {
            os << string(width(), '*');
        } else if (row == 1 || row == height() - 2) {
            os << "*";
            pad(os, 1, width() - 1);
            os << "*";
        } else {
            os << "* ";
            p->display(os, row - 2, true);
            os << " *";
        }
    }
}

class Picture {
    friend std::ostream& operator<<(std::ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture hcat(const  Picture&, const  Picture&);
    friend Picture vcat(const Picture&, const  Picture&);

public:
    Picture(const std::vector<std::string>& =
            std::vector<std::string>());
private:
    Picture(Pic_base* ptr) : p(ptr) { }
    Ptr<Pic_base> p;
};

Picture::Picture(const std::vector<std::string>& v) : p(new String_pic(v)) { }

Picture frame(const Picture& pic)
{
    return new Frame_pic(pic.p);
}
Picture hcat(const  Picture& left, const  Picture& right)
{
    return new HCat_pic(left.p, right.p);
}
Picture vcat(const Picture& top, const  Picture& bottom)
{
    return new VCat_pic(top.p, bottom.p);
}
std::ostream& operator<<(std::ostream& os, const Picture& pic)
{
    const Pic_base::ht_sz ht = pic.p->height();
    for (Pic_base::ht_sz i = 0; i != ht; ++i) {
        pic.p->display(os, i, false);
    }
    return os;
}



int t64()
{

    vector<string> s;
    s.push_back("this is");
    s.push_back("new world");
    Picture p(s);
    Picture q = frame(p);
    Picture r = hcat(p, q);
    Picture t = vcat(q, r);

    cout << frame(hcat(t, vcat(r, q))) << endl;

}



vector<int>
merge(const vector<int>& a, const vector<int>& b)
{
    typedef vector<int>::const_iterator iter;
    iter ia = a.begin();
    iter ib = b.begin();
    vector<int> res;

    while (ia != a.end() && ib != b.end()) {
        if (*ia > *ib)
            res.push_back(*ib++);
        else if (*ia < *ib)
            res.push_back(*ia++);
        else {
            res.push_back(*ia++);
            res.push_back(*ib++);
        }
    }

    if (ia == a.end())
        copy(ib, b.end(), back_inserter(res));
    else if (ib == b.end())
        copy(ia, a.end(), back_inserter(res));
    
    return res;
}
int t65()
{
    vector<int> a, b;

    a.push_back(1);
    a.push_back(3);
    a.push_back(6);
    a.push_back(7);
    b.push_back(2);
    b.push_back(4);
    b.push_back(5);

    vector<int> c = merge(a, b);

    for(vector<int>::const_iterator it = c.begin(); it != c.end(); ++it)
        cout << *it;

    cout << endl;
}

// median: how can we find median if the size of data is too big? 1) check all elem 2) random sampling


int main(int argc, char * argv[])
{
	t61(); 
}



