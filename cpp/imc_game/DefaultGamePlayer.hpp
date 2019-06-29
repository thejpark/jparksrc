#ifndef DEFAULT_GAME_PLAYER_HPP
#define DEFAULT_GAME_PLAYER_HPP

#include <functional>
#include <stdlib.h>
#include <time.h>
#include "GamePlayer.hpp"
#include "Game.hpp"

int DefaultGameAlgo(const GamePlayer& g) {
    srand (time(NULL));
    return rand() % 3;
}

using namespace std;

class DefaultComputerPlayer : public GamePlayer {
public:
    DefaultComputerPlayer(string gameId, GameAlgoFunc strategy = DefaultGameAlgo) :
        algo(strategy) {
        id = gameId;
    }

    void Play(Game& g) override {
        int res = algo(*this);
        g.SendRequest(*this, static_cast<Kind>(res));
    }

private:
    GameAlgoFunc algo;
};

class DefaultHumanPlayer : public GamePlayer {
public:
    explicit DefaultHumanPlayer(string gameId) { id = gameId;}

    void Play(Game& g) override {
        int t = GetUserInput();
        g.SendRequest(*this, static_cast<Kind>(t));
    }

private:
    virtual int GetUserInput()
    {
        cout << "user: ";
        int t;
        cin >> t;
        return t;
    }
};
#endif
