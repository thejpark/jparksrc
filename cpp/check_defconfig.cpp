#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void map_test()
{

    string s;
    
    map<string, int> wc;

    while(cin >> s) {
        ++wc[s];
    }

    for(map<string, int>::const_iterator it = wc.begin(); it != wc.end(); ++it) {

        cout << it->first << ":" << it->second << endl;

    }
    
}


int main()
{

    ifstream f1("def1");
    ifstream f2("def2");
    string line;
    

    map<string, int> wc;
    
    if (f1.is_open())
    {

        while (f1.good() )
        {

            getline (f1,line);
            ++wc[line];
        }

        f1.close();

    }

    
    if (f2.is_open())
    {

        while (f2.good() )
        {

            getline (f2,line);

            if ((wc[line] == 0) && (line[0] != '#')) {
                cout << line << endl;
            }
            
                
        }

        f2.close();

    }

}





