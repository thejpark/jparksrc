
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

#include <fstream>
#include <string>

using namespace std;
int main()
{
    ifstream f1("cx2.xml");
    string int_num = "number=";

     map<int, int> wc;
    
     if (f1.is_open())
         {
             {
                 getline (f1,line);

                 //            cout << " 1 ... "  << line.size() << endl;

                 int size = line.size();


                 //              cout << " 2 ... " << i << " " << line
                 // << endl; cout << i << " " << int_num.size() << " "
                 // << line[i] << endl;
                 if (line.compare(i, int_num.size(), int_num) == 0) {

                     // cout << " 3 ... " << endl;
                    i += int_num.size() + 1;
                    int k = 0;
                    
                    while(line[i] != '\"') {
                        k = k * 10;
                        k += line[i] - '0';
                        i++;
                        //   cout << " 4 ... " << endl;
                    }
                    // cout << " 5 ... " << endl;
                    ++wc[k];                            
                    break;
             
                }
                
            }

        }

        f1.close();
    }


    for (int i = 32 ; i < 200; i++) {

        if (wc[i] != 0)
            cout << "interrupt " << i << " is installed" << endl;
        
    }
    
}





