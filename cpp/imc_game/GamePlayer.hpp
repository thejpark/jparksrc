#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <functional>
#include <stdlib.h>
#include <time.h>

enum class Kind {rock, paper, scissor};

class GamePlayer {
public:
    using GameAlgoFunc = std::function<int(const GamePlayer&)>;
    virtual int GetValue() = 0;
};

int DefaultGameAlgo(const GamePlayer& g) {
    srand (time(NULL));
    return rand() % 3;
}

class DefaultGamePlayer : public GamePlayer {
public:
    explicit DefaultGamePlayer(GameAlgoFunc gc = DefaultGameAlgo) : gameAlgo(gc) {}
    int GetValue() override { return gameAlgo(*this); }

private:
    GameAlgoFunc gameAlgo;
};
#endif
