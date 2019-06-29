#ifndef DEFAULT_GAME_HPP
#define DEFAULT_GAME_HPP

#include <stdlib.h>
#include "Game.hpp"
#include "GamePlayer.hpp"

class DefaultGame : public Game {
public:
    DefaultGame(GamePlayer& computer, GamePlayer& human) : c(computer), h(human) {}

    void Play() {
        ShowHowto();
        h.Play(*this);
        c.Play(*this);
    }

    void SendRequest(GamePlayer& player, Kind k) override {
        if (player.GetId() == h.GetId()) {
            h_result = k;
            count++;
        }
        else {
            c_result = k;
            count++;
        }

        if (count == 2)
        {
            ShowResult();
            count = 0;
        }
    }

private:
    GamePlayer& h;
    GamePlayer& c;
    Kind h_result;
    Kind c_result;
    int count = 0;

    virtual void ShowHowto() {
        cout << "enter 0, 1, or 2 (0 for rock, 1 for paper, 2 for scissor)" << endl;
    }

    virtual void ShowResult() {
        string result = "Draw";
        if (h_result == rock)
        {
            if (c_result == paper)
                result = "You Lose";
            else if (c_result == scissor)
                result = "You Win";
        }
        else if (h_result == scissor)
        {
            if (c_result == rock)
                result = "You Lose";
            else if (c_result == paper)
                result = "You Win";
        }
        else
        {
            if (c_result == scissor)
                result = "You Lose";
            else if (c_result == rock)
                result = "You Win";
        }

        cout << result << ": Computer is " << c_result << endl;
    }
};
#endif
