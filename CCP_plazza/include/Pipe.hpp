/*
** EPITECH PROJECT, 2019
** PLAZZA
** File description:
** Pipe IPC
*/

#ifndef PIPE_HPP_
#define PIPE_HPP_

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>
#include <fstream>
#include <iostream>
#include <string>	

class Pipe {
	public:
		Pipe(std::string name);
		~Pipe();

		std::string getName() const;

		bool read(std::string &msg) const;
		bool write(const std::string &msg) const;
		void destroy();

	protected:
	private:
		const std::string _name;
		const std::string _file;
		int _fd;
};

#endif /* !PIPE_HPP_ */
