#include <iostream>

using namespace std;

class self_del 
{

public:
#if TEST_VIRTUAL_CONSTRUCTOR
    virtual /* this causes compile error */
#endif
    self_del() 
    {
        cout << "construct" << endl;
    }

    ~self_del() 
    {
        cout << "destruct" << endl;
    }

    void self_del_try()
    {
        cout << "try delete this at " << this << endl;
        delete this;
        cout << "after delete this" << endl;
    }
    
};

    

int main()
{
    self_del a;

    a.self_del_try();
    cout << "this is the end" << endl;
}
