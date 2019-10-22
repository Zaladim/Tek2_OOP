/*
** EPITECH PROJECT, 2019
** PLAZZA
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

int Kitchen::_knum = 0;

static void *timerThread(Kitchen *k)
{
	k->clock();
	return (NULL);
}

static void *restockThread(Kitchen *k)
{
	k->restockClock();
	return (NULL);
}

Kitchen::Kitchen(std::string &name, int nb_cook, float mult_cook_time, int restock) : 
	_name(name),
	_nb_cook(nb_cook),
	_max_pizza(2 * nb_cook),
	_mult_cook_time(mult_cook_time),
	_restock_time(restock)
{
	for(int i = 0; i < LOVE; i++) {
		_ingredients.push_back(5);
	}

	_cookManager = std::unique_ptr<CookManager> (new CookManager());
	_pipe = std::unique_ptr<Pipe> (new Pipe(name));
	_processingLock = std::unique_ptr<std::mutex> (new std::mutex);

	initRequest();

	initCook();
}

Kitchen::~Kitchen()
{
	std::string path = "./tmp/" + _name;
	fs::path p(path);
	remove(p.c_str());
	_cookManager->stop();
	for (std::unique_ptr<std::thread> &t : _working)
		t->join();
}

void Kitchen::restockClock()
{
	Timer t;

	while (_running) {
		if (t.getElapsedTime() >= _restock_time) {
			t.reset();
			_cookManager->refill(1);
		}
	}
}

void Kitchen::clock()
{
	Timer t;

	while (_running) {
		t.reset();
		while (!_cookManager->getWorking()) {
			if (t.getElapsedTime() >= 5000) {
				_running = false;
				_pipe->write("r: quit");
				break;
			}
		}
	}
}

void Kitchen::initRequest()
{
	_request["nbAwaiting"] = &Kitchen::requestCook;
	_request["status"] = &Kitchen::requestStatus;
	_request["quit"] = &Kitchen::requestQuit;
}

void Kitchen::initCook()
{
	for(int i = 0; i < _nb_cook; i++){
		_working.push_back(std::unique_ptr<std::thread> (new std::thread(&CookManager::cook, _cookManager.get(), _mult_cook_time)));
	}
}

// === REQUEST ===
void Kitchen::requestCook(std::string &req)
{
	int tmp = 0;
	std::stringstream convert;

	_processingLock->lock();
    tmp = _cookManager->getSize();
	_processingLock->unlock();
	convert << tmp;
	_pipe->write(convert.str());
}

void Kitchen::requestStatus(std::string &req)
{
	_processingLock->lock();

	std::cout << "Cook status : " << _cookManager->getCooking() << "/" << _nb_cook << " working" << std::endl;
	std::cout << "Pizza status : " << _cookManager->getWaiting() << " commands" << std::endl;
	std::cout << "Ingredients status : " << std::endl;
	for (auto &ingr : _cookManager->getIngredients()) {
		std::cout << "\t" << ingrName[ingr.first] << " : " << ingr.second << std::endl;
	}


	_processingLock->unlock();

	_pipe->write("done");
}

void Kitchen::requestQuit(std::string &req)
{
	_cookManager->stop();
	quit();
}

void Kitchen::quit()
{
	_running = false;
	std::string path = "./tmp/" + _name;
	fs::path p(path);
	remove(p.c_str());
	for (std::unique_ptr<std::thread> &t : _working)
		t->join();
}

int Kitchen::getNbPizza()
{
	return _nb_pizza;
}

void Kitchen::newPizza()
{
	_nb_pizza ++;
}

int Kitchen::run()
{
	_running = true;
	std::string tmp;
	tmp.clear();
	_tTimer.push_back(std::unique_ptr<std::thread> (new std::thread(timerThread, this)));
	_tTimer.push_back(std::unique_ptr<std::thread> (new std::thread(restockThread, this)));

	while (_pipe->read(tmp) && _running) {
		if (tmp != "") {
			handleMessages(tmp);
			tmp.clear();
		}
	}
	std::cout<< _name << " : closing" << std::endl;
	for (auto &t : _tTimer) {
		t->join();
	}
	return EXIT_SUCCESS;
}

bool Kitchen::checkError(std::string &str)
{
	std::string tmp = str;
	std::string tmp2 = tmp.substr(0, 3);
	int n = 0;

	if (tmp2 != "c: " && tmp2 != "r: ")
		return (false);
	tmp.erase(0, 3);
	n = std::count(tmp.begin(), tmp.end(), ' ');
	if (n > 1)
		return (false);
	return (true);
}

void Kitchen::handleMessages(std::string &str)
{
	size_t tmp = std::string::npos;
	if (!checkError(str)) {
		_pipe->write("ERROR");
	}
	tmp = str.find("c:");
	if (tmp != std::string::npos) {
		return (handleCommand(str));
	}
	return (handleRequest(str));
}

void Kitchen::handleCommand(std::string &cmd)
{
	_processingLock->lock();
	std::cout << "COMMAND : " << cmd << std::endl;
	std::string tmp = cmd.substr(3);
	_cookManager->push(tmp);
	_pipe->write("OK");
	_processingLock->unlock();
}

void Kitchen::handleRequest(std::string &req)
{
	void (Kitchen::*ptr)(std::string &);
	std::string tmp = req.substr(3);
	ptr = _request[tmp];
	(this->*ptr)(tmp);
}