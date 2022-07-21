#include "common.hpp"
#include <userspace/keyboard.hpp>
#include <rpc>
#include <cstdio>

std::PID keyboard = 0;

char getChar() {
	if(!keyboard)
		while(!(keyboard = std::resolve("keyboard")));

	return std::rpc(keyboard, std::keyboard::GET_CHAR);
}

std::string getLine() {
	std::string ret;

	while(true) {
		char c = getChar();
		if(!c) {
			std::printf("shell: could not read from keyboard\n");
			std::printf("Hint: does this user have the KEYBOARD permission?\n");
			std::exit(100);
		}

		if(c == '\b') {
			if(ret.size()) {
				std::printf("\b \b");
				ret.pop_back();
			}
		} else if(c == '\n') {
			std::printf("\n");
			break;
		} else {
			ret.push_back(c);
			std::printf("%c", c);
		}

		std::flushTerm();
	}

	return ret;
}
