#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <string>

class Game;
class GamePlayer {
public:
    using GameAlgoFunc = std::function<int(const GamePlayer&)>;
    virtual ~GamePlayer() {}
    virtual void Play(Game&) = 0;
    std::string GetId() { return id; }

protected:
    std::string id;
};
#endif
