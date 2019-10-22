/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** SDL lib
*/

#include "SDL.hpp"

extern "C" ILib *start()
{
	return new SDL;
}

SDL::SDL() : 
	ALib(),
	_run(false),
	_textColor({0, 255, 0}),
	_playerName("")
{
}

SDL::~SDL()
{
}

int SDL::run(std::vector<std::string> libs, std::vector<std::vector<int>> board, int score)
{
	if (_main) {
		SDL_Event event;

		SDL_RenderClear (_mainRenderer);
			
		displayGame(board);
		_libs.render(_mainRenderer, 0, 5);
		if (score >= 0)
			_score = score;
		printScore(_score);
		printName();
	
		SDL_RenderPresent(_mainRenderer);
			
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						return (COMMAND_EXIT);
					case SDLK_LEFT:
						return (COMMAND_PREV_LIB);
					case SDLK_RIGHT:
						return (COMMAND_NEXT_LIB);
					case SDLK_UP:
						return COMMAND_NEXT_GAME;
					case SDLK_DOWN:
						return COMMAND_PREV_GAME;
					case SDLK_RETURN:
						return setName();
					case SDLK_r:
						return COMMAND_PLAY;
					case SDLK_z:
						return COMMAND_UP;
					case SDLK_s:
						return COMMAND_DOWN;
					case SDLK_q:
						return COMMAND_LEFT;
					case SDLK_d:
						return COMMAND_RIGHT;
					case SDLK_SPACE:
						return COMMAND_ACTION;
				}
			}
		}
	}
	return COMMAND_CONTINUE;
}

int SDL::open(std::vector<std::string> libs)
{
	if (TTF_Init() == -1) {
		fprintf(stderr,"Unable to initialize TTF (%s)\n",TTF_GetError());
		return COMMAND_ERROR;
	}
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stderr,"Unable to initialize SDL (%s)\n",SDL_GetError());
		return COMMAND_ERROR;
    }
	
	_font = TTF_OpenFont("lib/sdl/font.ttf", 40);
	if (_font == NULL) {
		fprintf(stderr,"Unable to initialize TTF_font (%s)\n",TTF_GetError());
		return COMMAND_ERROR;
	}


	SDL_GetCurrentDisplayMode(0, &_dm);

	_main = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, \
                                    SDL_WINDOWPOS_UNDEFINED, \
                                    _dm.w, \
                                    _dm.h, \
                                    SDL_WINDOW_FULLSCREEN_DESKTOP);


	_mainRenderer = SDL_CreateRenderer(_main, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor( _mainRenderer , 0, 0, 0, 0);
	printLib(libs);

	return (COMMAND_CONTINUE);
}

void SDL::close()
{
	SDL_DestroyWindow(_main);
	SDL_Quit();
	TTF_CloseFont(_font);
	TTF_Quit();
}

void SDL::printLib(std::vector<std::string> libs)
{
	std::string text;

	for (std::string &elem : libs) {
		elem = elem.erase(0, 13);
		elem = elem.substr(0, elem.size() - 3);
		text += "Thy Olde ";
		text += elem;
		text += "      ";
	}
	_libs.loadFromText(_font, text, _textColor, _mainRenderer);
}

void SDL::printScore(int score)
{
		_textScore = "Thy Olde Scoring : ";

		_textScore += std::to_string(score);

		_scoring.loadFromText(_font, _textScore, _textColor, _mainRenderer);
		_scoring.render(_mainRenderer, _dm.w - (_textScore.length() * 15), _dm.h - 40);
		_score = score;
}

int SDL::setName()
{
	bool writing = true;
	SDL_Event event;

	SDL_StartTextInput();
	while (writing) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_BACKSPACE && _playerName.length() > 0) {
					_playerName.pop_back();
				} else if (event.key.keysym.sym == SDLK_RETURN) {
					writing = false;
				}else if (event.key.keysym.sym == SDLK_ESCAPE) {
					return COMMAND_EXIT;
				}
			} else if (event.type == SDL_TEXTINPUT) {
				_playerName += event.text.text;
			}
		}
		SDL_RenderClear(_mainRenderer);
		_libs.render(_mainRenderer, 0, 5);
		printScore(_score);
		printName();
		displayPause();
		SDL_RenderPresent(_mainRenderer);
	}
	return COMMAND_CONTINUE;
}

void SDL::printName()
{
	_name.loadFromText(_font, "Thy Olde Name : " + _playerName, _textColor, _mainRenderer);
	_name.render(_mainRenderer, 0, _dm.h - 40);
}

void SDL::displayGame(std::vector<std::vector<int>> board)
{
	SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

	//Tiles Texture
	Texture tileTexture;

	//Tile offsets
	int x = 0;
	int y = 0;

	//Tiles number
	int tilesNB = board.size() * board[0].size();

	Tile *tiles[board.size()][board[0].size()];

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			tiles[i][j] = new Tile(x, y, board[i][j]);
			x += TILE_WIDTH;
		}
		x = 0;
		y += TILE_HEIGHT;
	}

	gTileClips[ TILE_RED ].x = 0;
	gTileClips[ TILE_RED ].y = 0;
	gTileClips[ TILE_RED ].w = TILE_WIDTH;
	gTileClips[ TILE_RED ].h = TILE_HEIGHT;
	
	gTileClips[ TILE_GREEN ].x = 0;
	gTileClips[ TILE_GREEN ].y = 40;
	gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
	gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

	gTileClips[ TILE_BLUE ].x = 0;
	gTileClips[ TILE_BLUE ].y = 80;
	gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
	gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;

	gTileClips[ TILE_TOPLEFT ].x = 40;
	gTileClips[ TILE_TOPLEFT ].y = 0;
	gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
	gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

	gTileClips[ TILE_LEFT ].x = 40;
	gTileClips[ TILE_LEFT ].y = 40;
	gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
	gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;

	gTileClips[ TILE_BOTTOMLEFT ].x = 40;
	gTileClips[ TILE_BOTTOMLEFT ].y = 80;
	gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
	gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

	gTileClips[ TILE_TOP ].x = 80;
	gTileClips[ TILE_TOP ].y = 0;
	gTileClips[ TILE_TOP ].w = TILE_WIDTH;
	gTileClips[ TILE_TOP ].h = TILE_HEIGHT;

	gTileClips[ TILE_CENTER ].x = 80;
	gTileClips[ TILE_CENTER ].y = 40;
	gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
	gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;

	gTileClips[ TILE_BOTTOM ].x = 80;
	gTileClips[ TILE_BOTTOM ].y = 80;
	gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
	gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

	gTileClips[ TILE_TOPRIGHT ].x = 120;
	gTileClips[ TILE_TOPRIGHT ].y = 0;
	gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
	gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

	gTileClips[ TILE_RIGHT ].x = 120;
	gTileClips[ TILE_RIGHT ].y = 40;
	gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
	gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

	gTileClips[ TILE_BOTTOMRIGHT ].x = 120;
	gTileClips[ TILE_BOTTOMRIGHT ].y = 80;
	gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
	gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;

	tileTexture.loadFromFile("lib/sdl/tiles.png", _mainRenderer);

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			tiles[i][j]->render(_mainRenderer, &tileTexture, _dm, gTileClips, board.size()*TILE_WIDTH, board[0].size()*TILE_HEIGHT);
		}
	}
}

void SDL::displayPause()
{
	std::string pause = "Thy Olde Pause";
	_name.loadFromText(_font, pause, _textColor, _mainRenderer);
	_name.render(_mainRenderer, (_dm.w - (pause.length() * 15)) / 2, (_dm.h / 2));
}