#include <vector>
#include <string>
#include <iostream>

class Student_info 
{

public:
    std::string name() const
    {
        return n;
    }
    bool valid() const 
    {
        return !homework.empty();
    }
    std::istream& read(std::istream&);
    double grade() const;
    Student_info();
    Student_info(std::istream&);
    Student_info(const Student_info&);
    bool pass() const;
    Student_info& operator=(const Student_info& s);
    ~Student_info();
    
private:
    std::string n;
    double midterm, final, _grade;
    std::vector<double> homework;
    void new_instance()
    {
        std::cout << "instance created " <<  std::endl;
    }
    void del_instance()
    {
        std::cout << "instance deleted " <<  std::endl;
    }
    
};

bool Student_compare(const Student_info&, const Student_info&);
