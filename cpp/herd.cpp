
#include <string>
#include <iostream>

using namespace std;

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

int main()
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
