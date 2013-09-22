#include <vector>
#include <iostream>

using namespace std;



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

vector<int>
msort(vector<int> va)
{
    if (va.size() <= 1)
        return va;

    typedef vector<int>::iterator iter;

    iter i = va.begin() + (va.end() - va.begin()) / 2;

    vector<int> a(va.begin(), i);
    vector<int> b(i, va.end()); // it should be i, not i + 1. 

    vector<int> ra = msort(a);
    vector<int> rb = msort(b);
    vector<int> r = merge(ra,rb);

    return r;
}

vector<int>
quick(vector<int> va)
{
    if (va.size() <= 1)
        return va;

    vector<int> left;
    vector<int> right;
    int pivot = va[0];
    for (vector<int>::size_type i = 1; i < va.size() ; i++) {
        if (va[i] > pivot)
            right.push_back(va[i]);
        else
            left.push_back(va[i]);
    }

    vector<int> r;
    left = quick(left);
    right = quick(right);
    copy(left.begin(), left.end(), back_inserter(r));
    r.push_back(pivot);
    copy(right.begin(), right.end(), back_inserter(r));
    return r;
}

/* 3 2 1 */

vector<int> bubble(vector<int> va)
{
    vector<int>::size_type i = 0, j = 0; // this is unsigned type, so if i == 0, then -1 is very big number.

    for (i = va.size() - 1; i > 0; i--) { // if condition is i >= 0, then i might be very big number at the final stage.
        for (j = 0; j < i; j++) {
            if (va[j] > va[j + 1])
                swap(va[j + 1], va[j]);
        }
    }

    return va;
}

int insertion()
{



}

vector<int>
selection(vector<int> va)    
{
    vector<int>::size_type i, j;
    int max;

    for (i = va.size() - 1; i > 0; i--) {
        max = 0;
        for (j = 0; j < i; j++) {
            if (va[max] < va[j])
                max = j;
        }
        if (va[i] < va[max])
            swap(va[i], va[max]);
    }

    return va;
}


vector<int> heap(vector<int> va)
{



}


int
getdigit(int x, int n)
{
 int div = 1;
 for (int i = 1; i < n; i++)
     div = div * 10;

 x = x / div;

 return x % 10;
}       
// sort ages, assume ages less than 100
vector<int> binsort(vector<int> va)
{

    vector<vector<int> > bin(10);
    for (int digit = 1; digit <= 2; digit++) {
        for (vector<int>::size_type i = 0; i < va.size(); i++) {
            bin[getdigit(va[i], digit)].push_back(va[i]);
        }
        va.clear();
        for (int j = 0; j < 10; j++) {
            copy(bin[j].begin(), bin[j].end(), back_inserter(va));
            bin[j].clear();
        }
    }
    
    return va;
}
  
// merge sort and quick sort: comparison depends on the size of the data set.
// http://stackoverflow.com/questions/680541/quick-sort-vs-merge-sort


int main()
{

    vector<int> va;

    for (int i = 10; i > 0; i--)
        va.push_back(i);

    cout << "before:" << endl;
    for (int i = 0; i < va.size(); i++)
        cout << " " << va[i];
    cout << endl;

    
    vector<int> r = binsort(va);

    cout << "after:" << endl;
    for (int i = 0; i < r.size(); i++)
        cout << " " << r[i];
 
    cout << endl;

}
