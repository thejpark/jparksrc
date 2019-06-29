#ifndef GAME_HPP
#define GAME_HPP

enum Kind {rock = 0, paper, scissor};

class GamePlayer;
class Game {
public:
    virtual ~Game() {}
    virtual void Notify(GamePlayer&, Kind) = 0;
};
#endif
