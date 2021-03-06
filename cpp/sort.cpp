#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int>
msort(vector<int>::iterator beg, vector<int>::iterator end)
{
    if (end - beg <= 1)
        return vector<int>(beg, end);

    auto i = beg + (end - beg) / 2;

    vector<int> ra = msort(beg, i);
    vector<int> rb = msort(i, end);
    vector<int> r;
    merge(ra.begin(), ra.end(), rb.begin(), rb.end(), back_inserter(r));

    return r;
}

void msort2(vector<int>::iterator beg, vector<int>::iterator end)
{
    if (end - beg <= 1)
        return;

    auto i = beg + (end - beg) / 2;

    msort2(beg, i);
    msort2(i, end);
    inplace_merge(beg, i, end);
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


void heapify(vector<int>& va, int i)
{
    if (i == 0)
        return;

    int p = (i - 1) / 2;

    while (p >= 0)
    {
        if (va[i] > va[p])
        {
            swap(va[i], va[p]);
            i = p;
            p = (p - 1) / 2;
        }
        else
            break;
    }
}

void heap_push(vector<int>& va, int idx)
{
    if (idx == 0)
        return;

    int i = 0;
    while (i <= (idx - 1) / 2)
    {
        int l = i * 2 + 1;
        int r = i * 2 + 2;

        if (r > idx || va[l] >= va[r])
        {
            if (va[i] < va[l])
            {
                swap(va[i], va[l]);
                i = l;
            }
            else
                break;
        }
        else
        {
            if (va[i] <va[r])
            {
                swap(va[i], va[r]);
                i = r;
            }
            else
                break;
        }
    }
}

void heapsort(vector<int>& va)
{
    for (int i = 0; i < va.size(); ++i)
    {
        heapify(va, i);
    }

    for (int i = va.size() - 1; i > 0; --i)
    {
        swap(va[0], va[i]);
        heap_push(va, i - 1);
    }
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
    vector<int> va = {5, 1, 2, 6, 7, 3, 4, 8, 10, 9};

    cout << "before:" << endl;
    for (int i = 0; i < va.size(); i++)
        cout << " " << va[i];
    cout << endl;

    
    msort2(va.begin(), va.end());

    cout << "after:" << endl;
    for (int i = 0; i < va.size(); i++)
        cout << " " << va[i];
 
    cout << endl;
}
