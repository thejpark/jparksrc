#include <iostream>
#include <string>
#include <random>
#include "DefaultGamePlayer.hpp"
#include "DefaultGame.hpp"

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
    cout << "Enter how many games to play: ";
    cin >> n;

    NewGameAlgo newAlgo;
    DefaultComputerPlayer computer("computer1", newAlgo);
    DefaultHumanPlayer human("human1");

    DefaultGame game(computer, human);
    for (int i = 0; i < n; ++i)
    {
        game.Play();
    }
}
