#include <iostream>
#include <string>
#include <random>
#include "GamePlayer.hpp"

using namespace std;

struct NewGameAlgo {
    int operator() (const GamePlayer& g) {
        default_random_engine seed((random_device())());
        return uniform_int_distribution<int>{0, 2}(seed);
    }
};

int main()
{
    int n;
    cin >> n;

    NewGameAlgo algo;
    DefaultGamePlayer gp(algo);

    for (int i = 0; i < n; ++i)
    {
        int user;
        cout << "enter 0, 1, or 2 (0 for rock, 1 for paper, 2 for scissor)" << endl;
        cout << "user: ";
        cin >> user;
        int computer = gp.GetValue();
        cout << "computer: " << computer << endl;
    }

}
