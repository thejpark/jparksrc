#include <iostream>
#include <string>

using std::cout;
using namespace std;

bool compare_nocase(const string &a, const string &b)
{

    string::size_type i;

    i = 0;
    while(i != a.size() && i != b.size()) {
        if (toupper(a[i]) < toupper(b[i]))
            return true;
        else if (toupper(a[i]) > toupper(b[i]))
            return false;
        i++;
    }

    if (i == a.size())
        return true;
    else /* (i == b.size())*/
        return false;
}



int main()
{

    string s = "this is new world";

    cout << s << " " << s.length() << std::endl;

    // if the argument is const liternal, than type should be const string
    if (compare_nocase("thisis", "thatis"))
        cout << "yes" << endl;

    else
        cout << "no" << endl;
}
