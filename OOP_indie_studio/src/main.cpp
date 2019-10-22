/*
** EPITECH PROJECT, 2019
** BOMBERMAN
** File description:
** Main
*/

#include <exception>
#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include "bomberman.hpp"
#include "Board.hpp"
#include "Bomb.hpp"
#include "Display.hpp"
#include "Sound.hpp"

int load_game(Display &display, std::unique_ptr<Board> &board, Sound &soundBox)
{

    if (display.getNbSave() == 0)
        board.reset(new Board(display.getScene(), display.getDriver(), display.getMeta(), soundBox, display.getPlayers()));
    else {
        board.reset(new Board(display.getSaves(display.getNbSave()), display.getScene(), display.getDriver(), display.getMeta(), soundBox));
    }
    for (int j = 0; j < MAXY; j++) {
        for (int i = 0; i < MAXX; i++) {
            printf("%d", (*board)(i, j).getEntity());
        }
        printf("\n");
    }
    if (board->_playerCounted == 1 && display.getPlayers() == 2) {
        display.displayLittleMessage(L"Bad number of players", L"sorry, but you try to lunch a 1 player save with 2 players.");
        display.setState(START_MENU);
    } else if (board->_playerCounted == 2 && display.getPlayers() == 1) {
        display.displayLittleMessage(L"Bad number of players", L"sorry, but you try to lunch a 2 player save with 1 players.");
        display.setState(START_MENU);
    } else {
        display.setOpt();
        display.setCam();
        display.setState(GAME);
    }
    return (NORMAL);
}

int main(int argc, char **argv)
{
    Sound soundBox;
    soundBox.music(MUSIC);

    Display display;
    std::unique_ptr<Board> board;

    display.setState(CREDIT);
    try {
    while (display.isRunning()) {
        if (display.getState() == START_MENU)
            display.displayStartMenu();
        else if (display.getState() == START_GAME)
            load_game(display, board, soundBox);
        else if (display.getState() == GAME)
            display.displayAll(*board);
        else if (display.getState() == PAUSE)
            display.displayPause();
        else if (display.getState() == CREDIT)
            display.displayCredit();
        else if (display.getState() == SAVE)
            display.displaySave(*board);
    }
    soundBox.stop();
    }
    catch(std::exception &e) {
        std::cerr << e.what();
    }
    return (0);
}