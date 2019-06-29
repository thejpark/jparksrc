#include <iostream>
#include <string>
#include <random>
#include "GamePlayer.hpp"

using namespace std;

int NewGameAlgo (const GamePlayer& g) {
        default_random_engine seed((random_device())()); // random num generator
        return uniform_int_distribution<int>{0, 2}(seed);
}

int main()
{
    GamePlayer gp(NewGameAlgo);
    cout << "result is : " << gp.GetValue() << endl;

}
