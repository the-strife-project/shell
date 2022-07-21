#include "common.hpp"
#include <cstdio>
#include <unordered_map>
#include <fs>
#include <tasks>
#include <users>

static const char* prompt = "\033\x0E[\033\x0C%s\033\x0E %s] $ \033\x0A";

std::unordered_map<std::string, std::string> env;
size_t lastExitValue = 0;

extern "C" void _start() {
	// Who am I?
	auto info = std::info(std::getPID());
	auto user = std::uidToName(info.uid);
	const char* username = user.c_str();

	env["PWD"] = "/";
	env["PATH"] = "/cd/bin";
	initBuiltins();

	while(true) {
		std::printf(prompt, username, env["PWD"].c_str());
		std::flushTerm();

		auto line = getLine();

		// Split and strip
		auto parts_ = line.split(' ');
		std::vector<std::string> parts;
		for(auto const& x : parts_)
			if(x.size())
				parts.push_back(x);

		if(!parts.size())
			continue;

		auto program = parts[0];
		parts.pop_front(); // args

		if(builtins.has(program)) {
			builtins[program](parts);
			continue;
		}

		// It's not a builtin

		bool isPath = false;
		for(size_t i=0; i<program.size(); ++i) {
			if(program[i] == '/') {
				isPath = true;
				break;
			}
		}

		if(isPath) {
			// TODO
			continue;
		}

		// Reachable via $PATH?
		bool reached = false;
		auto paths = env["PATH"].split(':');
		for(auto const& x : paths) {
			if(!x.size())
				continue;

			std::string path = x + "/" + program;
			if(std::isFile(path)) {
				reached = true;
				std::PID pid = std::run(path, parts, env);
				auto lerr = std::getLastLoaderError();
				if(lerr) {
					std::printf("shell: %s: invalid ELF: error %d\n", program.c_str(), lerr);
					break;
				}

				std::wait(pid);
				size_t kr = std::getKillReason(pid);
				if(kr == std::kkill::OK)
					lastExitValue = std::getExitValue(pid);
				else
					printKR(pid, kr);
				break;
			}
		}

		if(reached)
			continue;

		std::printf("shell: command not found: %s\n", program.c_str());
	}

	std::exit(0);
}
