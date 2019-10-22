/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Worm
*/

#ifndef WORM_HPP_
#define WORM_HPP_

#include "Object.hpp"
#include "Bodypart.hpp"

class Worm : public Object {
    public:
        Worm();
        Worm(int x, int y, int dir, int lenght, std::vector<Bodypart> bodyParts);
        ~Worm();

        int isThere(int x, int y) override;
        int getDir() const;
        int getLenght() const;
        void setDir(int dir);
        void swarm(int x, int y, std::vector<std::vector<int>> &board);
        int cut(int lenght);
        std::vector<Bodypart> *getBody(int lenght);

    protected:
    private:
        int _lenght;
        int _dir;
        std::vector<Bodypart> _parts;
};

#endif /* !WORM_HPP_ */
