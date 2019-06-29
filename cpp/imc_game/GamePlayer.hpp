#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <functional>
#include <stdlib.h>
#include <time.h>

class GamePlayer;

int defaultGameAlgo(const GamePlayer& g) {
    srand (time(NULL));
    return rand() % 3;
}

class GamePlayer {
public:
    using GameAlgoFunc = std::function<int(const GamePlayer&)>;
    explicit GamePlayer(GameAlgoFunc gc = defaultGameAlgo) : gameAlgo(gc) {}
    int GetValue() { return gameAlgo(*this); }

private:
    GameAlgoFunc gameAlgo;
};
#endif
