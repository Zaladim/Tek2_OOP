/*
** EPITECH PROJECT, 2019
** ARCADE
** File description:
** Allegro lib
*/

#include "Allegro.hpp"

extern "C" ILib *start()
{
	return new Allegro;
}

Allegro::Allegro()
{
}

Allegro::~Allegro()
{
}

// === START ===
int Allegro::open(std::vector<std::string> libs)
{
	if(!al_init()) {
    	fprintf(stderr, "failed to initialize allegro!\n");
    	return COMMAND_EXIT;
   	}
	al_get_display_mode(al_get_num_display_modes() - 1, &_dm);

	al_set_new_display_flags(ALLEGRO_FRAMELESS);
	_main = al_create_display(_dm.width, _dm.height);
	if(!_main) {
    	fprintf(stderr, "failed to initialize allegro!\n");
    	return COMMAND_EXIT;
   	}
	if(!al_install_keyboard()) {
     	fprintf(stderr, "failed to initialize the keyboard!\n");
      	return COMMAND_EXIT;
  	}
	_timer = al_create_timer(0.05);
   	if(!_timer) {
      fprintf(stderr, "failed to create timer!\n");
      return COMMAND_EXIT;
   	}
	if(!al_init_image_addon()) {
     	fprintf(stderr, "failed to initialize images!\n");
      	return COMMAND_EXIT;
  	}
	if(!al_init_primitives_addon()) {
     	fprintf(stderr, "failed to initialize primitives!\n");
      	return COMMAND_EXIT;
  	}
	if(!al_init_font_addon()) {
     	fprintf(stderr, "failed to initialize fonts!\n");
      	return COMMAND_EXIT;
  	}
	if(!al_init_ttf_addon()) {
     	fprintf(stderr, "failed to initialize ttf!\n");
      	return COMMAND_EXIT;
  	}
	
	_font = al_load_ttf_font("lib/allegro/font.ttf", 24, 0);
	if (!_font){
      	fprintf(stderr, "Could not load 'font.ttf'.\n");
      	return -1;
   	}

	for (std::string &elem : libs) {
		elem = elem.erase(0, 13);
		elem = elem.substr(0, elem.size() - 3);
		_libText += elem;
		_libText += "     ";
	}


	return COMMAND_CONTINUE;
}

void Allegro::close()
{
	al_destroy_display(_main);
}

int Allegro::run(std::vector<std::string> libs, std::vector<std::vector<int>> board, int score)
{
	ALLEGRO_EVENT_QUEUE *events = al_create_event_queue();
	if(!events) {
		fprintf(stderr, "failed to create event_queue!\n");
		return COMMAND_EXIT;
   	}
	al_register_event_source(events, al_get_keyboard_event_source());
	al_register_event_source(events, al_get_timer_event_source(_timer));

	al_clear_to_color(al_map_rgb(0,0,0));
	displayGame(board);
	printLib(libs);
	printName();
	printScore(score);
 	al_flip_display();

	al_start_timer(_timer);

	ALLEGRO_EVENT ev;
	al_wait_for_event(events, &ev);
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		if (_moving[UP]) {
			return COMMAND_UP;
		}
		if (_moving[DOWN]) {
			return COMMAND_DOWN;
		}
		if (_moving[LEFT]) {
			return COMMAND_LEFT;
		}
		if (_moving[RIGHT]) {
			return COMMAND_RIGHT;
		}
	}

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				return COMMAND_EXIT;
			case ALLEGRO_KEY_LEFT:
				return COMMAND_PREV_LIB;
			case ALLEGRO_KEY_RIGHT:
				return COMMAND_NEXT_LIB;
			case ALLEGRO_KEY_UP:
				return COMMAND_NEXT_GAME;
			case ALLEGRO_KEY_DOWN:
				return COMMAND_PREV_GAME;
			case ALLEGRO_KEY_ENTER:
				al_clear_to_color(al_map_rgb(0,0,0));
				printLib(libs);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
				printLib(libs);
				return setName(events);
			case ALLEGRO_KEY_R:
				return COMMAND_PLAY;
			case ALLEGRO_KEY_Z:
				_moving[UP] = true;
				_moving[DOWN] = false;
				_moving[LEFT] = false;
				_moving[RIGHT] = false;
				break;
			case ALLEGRO_KEY_S:
				_moving[UP] = false;
				_moving[DOWN] = true;
				_moving[LEFT] = false;
				_moving[RIGHT] = false;
				break;
			case ALLEGRO_KEY_Q:
				_moving[UP] = false;
				_moving[DOWN] = false;
				_moving[LEFT] = true;
				_moving[RIGHT] = false;
				break;
			case ALLEGRO_KEY_D:
				_moving[UP] = false;
				_moving[DOWN] = false;
				_moving[LEFT] = false;
				_moving[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				return COMMAND_ACTION;
		}
	}

	if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_Z:
				_moving[UP] = false;
				break;
			case ALLEGRO_KEY_S:
				_moving[DOWN] = false;
				break;
			case ALLEGRO_KEY_Q:
				_moving[LEFT] = false;
				break;
			case ALLEGRO_KEY_D:
				_moving[RIGHT] = false;
				break;
		}
	}
	

	return COMMAND_CONTINUE;
}

// === TEXT ===
void Allegro::printLib(std::vector<std::string> libs)
{
	al_draw_text(_font, red, 0, 0, 0, _libText.c_str());
}

void Allegro::printScore(int score)
{
	_score = score;
	std::string textScore = "Score : " + std::to_string(score);
	al_draw_text(_font, red, _dm.width - textScore.length() * 21,  _dm.height - 50, ALLEGRO_ALIGN_LEFT, textScore.c_str());
}

int Allegro::setName(ALLEGRO_EVENT_QUEUE *events)
{
	ALLEGRO_EVENT ev;
	bool write = true;

	while (write) {
		al_clear_to_color(al_map_rgb(0,0,0));
		displayPause();
		printName();
 		al_flip_display();
		al_wait_for_event(events, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER :
					write = false;
					break;
				case ALLEGRO_KEY_BACKSPACE:	
					break;
				case ALLEGRO_KEY_ESCAPE:
					return COMMAND_EXIT;
			}
		} 
		if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					break;
				case ALLEGRO_KEY_BACKSPACE:
					if (_nameText.length() > 0) {
						_nameText.pop_back();
					}	
					break;
				default:
					_nameText += ev.keyboard.unichar;
			}
		}
	}
	return COMMAND_CONTINUE;
}

void Allegro::printName()
{
	al_draw_text(_font, red, 0, _dm.height - 50, 0, ("Name : " + _nameText).c_str());
}

// === GAME ===
void Allegro::displayGame(std::vector<std::vector<int>> board)
{
	int w = (_dm.width - board.size()*10)/2;
	int h = (_dm.height - board[0].size()*10)/2;
	ALLEGRO_COLOR tmp;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			switch(board[j][i]){
				case 0:
					tmp = white;
					break;
				case 1:
					tmp = purple;
					break;
				case 2:
					tmp = blue;
					break;
				case 3:
					tmp = red;
					break;
				case 4:
					tmp = black;
					break;
				case 5:
					tmp = green;
					break;
			}
			al_draw_filled_rectangle(i*10+w-10, j*10+h-10, i*10+w, j*10+h, tmp);
		}
	}
}

void Allegro::displayPause()
{
	al_draw_text(_font, red, _dm.width/2, _dm.height/2, ALLEGRO_ALIGN_CENTER, "Pause");
}
