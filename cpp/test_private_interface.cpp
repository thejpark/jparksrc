#include <iostream>


class iface1 {
public: 
    void foo() {
        std::cout << "foo" << std::endl;
    }
};

class iface2 {
public:
    void bar() 
    {
        std::cout << "bar" << std::endl;
    }

};


class inst1: public iface1, private iface2 {

public:
    iface2* getxxx()
    {

        // I can get the private interfae using this.
        return this;
        // but if I try to get the private interface from outside,
        // such as iface2* x = new inst1, it will fail as it tried to
        // to access private interface from outsie.
    }
};


class inst2 {

public:
    void zoo(iface1& if1) 
    {
        if1.foo();        
    }
    
};


int main()
{
    inst1 a;
    inst2 b;
    b.zoo(a);
    iface2* x = a.getxxx();
    x->bar();

    // but this causes error
    a.bar();
}
