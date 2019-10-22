/*
** EPITECH PROJECT, 2019
** PLAZZA
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <memory>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <thread>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <exception>
#include <algorithm>
#include "Plazza.hpp"
#include "Pipe.hpp"
#include "Timer.hpp"
#include "CookManager.hpp"
#include "Pizza.hpp"

namespace fs = std::filesystem;

class Kitchen {
	public:
		Kitchen(std::string &name, int nb_cook, float mult_cook_time, int restock);
		~Kitchen();

		int getNbPizza(void);

		int run();
		void restockClock();
		void clock();
		void newPizza();
	protected:
	private:
		void initRequest(); // Initialize function ptr _request tab
		void initCook(); // Initialize thread pool

		// === REQUEST ===
		std::unordered_map<std::string , void(Kitchen::*)(std::string &)>  _request;
		void requestCook(std::string &req); // Send info on cooks
		void requestStatus(std::string &req); //Display status
		void requestQuit(std::string &req);
		void quit(); // Close kitchen

		// === HANDLER ===
		bool checkError(std::string &str); // Check for error in pipe file
		void handleMessages(std::string &str); // Redirect message
		void handleCommand(std::string &cmd); // From string command create appropriate pizza
		void handleRequest(std::string &req); // From string resquest, send back appropriate info


		// === MUTEX ===
		std::unique_ptr<std::mutex> _processingLock;

		// === PIPE ===
		std::unique_ptr<Pipe> _pipe;

		// === THREAD ===
		std::vector<std::unique_ptr<std::thread>> _tTimer;

		// === COOKS ===
		std::unique_ptr<CookManager> _cookManager;
		std::vector<std::unique_ptr<std::thread>> _working;

		std::string _name;
		bool _running;
		int _nb_cook;
		int _max_pizza;
		int _nb_pizza;
		float _mult_cook_time;
		int _restock_time;

		std::vector<int> _ingredients;

		static int _knum;
		int _pid;
};

#endif /* !KITCHEN_HPP_ */
