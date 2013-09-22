#include "student_info.h"

using namespace std;

extern double grade(double, double, const vector<double>&);
extern double grade(double, double);
extern istream& read_hw(istream&, vector<double>&);

bool Student_compare(const Student_info& x, const Student_info& y)
{
    // inside the name() function, const Student& is passed. So
    // name should be const function. Otherwise error.
    // 9-2
    return x.name() < y.name();
}

double
Student_info::grade() const
{
#ifdef exercise_9_1
    return _grade;
#else
    return ::grade(midterm, final, homework);
#endif
    // instead of return ::grade(midterm, final, homework);
    //_grade is calcualted in read() function.
    // 9-1
}


//9-5
bool
Student_info::pass() const
{
    double final_grade = 0.5 * midterm + 0.5 * final;

    if (final_grade >= 60) {
        return true;
    } else {
        return false;
    }
}



istream&
Student_info::read(istream& in)
{
    in >> n >> midterm >> final;
    ::read_hw(in, homework);
#ifdef exercise_9_1
    _grade = ::grade(midterm, final, homework);
#endif
    // grade is expanded to Student_info::grade
    return in;
}

Student_info::Student_info(istream& is)
{
    read(is);
    new_instance();
}

Student_info::Student_info() : midterm(0), final(0)
{
    new_instance();
}

Student_info::Student_info(const Student_info& s) : midterm(s.midterm), final(s.final), n(s.n), homework(s.homework)
{
    new_instance();
}

Student_info::~Student_info()
{
    del_instance();
}

Student_info &
Student_info::operator=(const Student_info& s)
{
    midterm = s.midterm;
    final = s.final;
    n = s.n;
    homework = s.homework;

    cout << " assigned " << endl;
    
    return *this;
}

