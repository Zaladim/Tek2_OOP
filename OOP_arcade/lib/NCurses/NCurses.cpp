/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** nCurses library
*/

#include "NCurses.hpp"
#include <iostream>

extern "C" ILib *start()
{
	return new NCurses;
}

NCurses::NCurses() :
	ALib()
{
}

NCurses::~NCurses()
{
}

std::vector<int> &NCurses::getGameSize()
{
	int maxX;
	int maxY;

	getmaxyx(_game, maxX, maxY);
	std::vector<int> *size = new std::vector<int>(maxX, maxY);
	return *size;
}

int NCurses::run(std::vector<std::string> libs, std::vector<std::vector<int>> board, int score)
{
	if (_game) {
		int event;

		if (_name )
		clear();
		printLib(libs);
		displayGame(board);
		if (score >= 0)
			_scoreval = score;
		printScore(_scoreval);
		printName();
		event = getch();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		switch (event) {
			case 27:
				return (COMMAND_EXIT);
			case KEY_LEFT:
				return (COMMAND_PREV_LIB);
			case KEY_RIGHT:
				return (COMMAND_NEXT_LIB);
			case KEY_UP:
				return COMMAND_NEXT_GAME;
			case KEY_DOWN:
				return COMMAND_PREV_GAME;
			case 'r':
				return COMMAND_PLAY;
			case 'z':
				return COMMAND_UP;
			case 's':
				return COMMAND_DOWN;
			case 'q':
				return COMMAND_LEFT;
			case 'd':
				return COMMAND_RIGHT;
			case 32:
				return COMMAND_ACTION;
			case 10:
				return setName();
			default:
				return COMMAND_CONTINUE;
		}
	}
	return COMMAND_CONTINUE;
}

int NCurses::open(std::vector<std::string> libs)
{
	int xGame, yGame, startXGame, startYGame;
	int xLib, yLib, startXLib, startYLib;
	int xScore, yScore, startXScore, startYScore;
	int xName, yName, startXName, startYName;
	int ch;
	initscr();
	noecho();
	curs_set(FALSE);
	cbreak();
	nodelay(stdscr, true);
	keypad(stdscr, TRUE);

	refresh();
	startXGame = 3;
	startYGame = COLS/4;
	xGame = 50;
	yGame = 100;
	_game = create_newwin(xGame, yGame, startXGame, startYGame);
	startXLib = 0;
	startYLib = 0;
	xLib = 3;
	yLib = COLS;
	_lib = create_newwin(xLib, yLib, startXLib, startYLib);
	startXScore = LINES - 3;
	startYScore = 0;
	xScore = 3;
	yScore = COLS / 2;
	_score = create_newwin(xScore, yScore, startXScore, startYScore);
	startXName = LINES - 3;
	startYName = COLS / 2;
	xName = 3;
	yName = (COLS + 1) / 2;
	_name = create_newwin(xName, yName, startXName, startYName);

	return (COMMAND_CONTINUE);
}

void NCurses::close()
{
	destroy_win(_game);
	destroy_win(_lib);
	destroy_win(_score);
	destroy_win(_name);
	endwin();
	clear();
}

void NCurses::displayGame(std::vector<std::vector<int>> board)
{
	wclear(_game);
	int maxX = board[0].size();
	int maxY = board.size();
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);

	for (int x = 0; x < maxX; x++) {
		for (int y = 0; y < maxY; y++) {
			switch(board[x][y]) {
				case WALKABLE:
					mvwprintw(_game, x, y*2, " ");
					break;
				case UNWALKABLE:
					mvwprintw(_game, x, y*2, "*");
					break;
				case PLAYER:
					wattron(_game, COLOR_PAIR(4));
					mvwprintw(_game, x, y*2, "o");
					wattroff(_game, COLOR_PAIR(4));
					break;
				case SHOT:
					wattron(_game, COLOR_PAIR(5));
					mvwprintw(_game, x, y*2, " ");
					wattroff(_game, COLOR_PAIR(5));
					break;
				case ENNEMY:
					wattron(_game, COLOR_PAIR(3));
					mvwprintw(_game, x, y*2, "@");
					wattroff(_game, COLOR_PAIR(3));
					break;
				case EAT:
					wattron(_game, COLOR_PAIR(4));
					mvwprintw(_game, x, y*2, "#");
					wattroff(_game, COLOR_PAIR(4));
					break;
			}
		}
	}
	refresh();
	wrefresh(_game);
}

int NCurses::setName()
{
	bool writing = true;
	int event;

	displayPause();
	while (writing) {
		event = getch();
		if (event == KEY_BACKSPACE && _playerName.length() > 0) {
			_playerName.pop_back();
		} else if (event == 10) {
			writing = false;
		}else if (event == 27) {
			return COMMAND_EXIT;
		}
		else if (event >= 33 && event <= 126) {
			_playerName += event;
		}
	}
	return COMMAND_CONTINUE;
}

void NCurses::printLib(std::vector<std::string> libs)
{
	start_color();
	int ind = 1;
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_WHITE);

	if(has_colors() == FALSE)
	{	
		endwin();
		printf("Your terminal does not support color\n");
		exit(84);
	}
	for (auto &elem : libs) {
		elem = elem.erase(0, 13);
		elem = elem.substr(0, elem.size() - 3);

		if (elem.compare("nCurses")) {
			wattron(_lib, COLOR_PAIR(1));
			mvwprintw(_lib, 1, ind, elem.c_str());
			wattroff(_lib, COLOR_PAIR(1));
		} else {
			wattron(_lib, COLOR_PAIR(2));
			mvwprintw(_lib, 1, ind, elem.c_str());
			wattroff(_lib, COLOR_PAIR(2));
		}
		ind += elem.length() + 1;
	}
	refresh();
	wrefresh(_lib);
}

void NCurses::printScore(int score)
{
	std::cout << _scoreval << std::endl;
}

void NCurses::printName()
{
	std::cout << _playerName << std::endl;
}

void NCurses::displayPause()
{
	std::cout << "write your name and press enter" << std::endl;
}


WINDOW *NCurses::create_newwin(int height, int width, int startY, int startX)
{
	WINDOW *local_win;
	local_win = newwin(height, width, startY, startX);

	wrefresh(local_win);
	return local_win;
}

void NCurses::destroy_win(WINDOW *local_win)
{	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}