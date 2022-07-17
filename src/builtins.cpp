#include "common.hpp"
#include <unordered_map>
#include <cstdio>

std::unordered_map<std::string, Builtin> builtins;

static void exit(const Args& args) {
	IGNORE(args);
	std::exit(0);
}

static void pwd(const Args& args) {
	IGNORE(args);
	std::printf("%s\n", env["PWD"].c_str());
}

static void clear(const Args& args) {
	IGNORE(args);
	std::clearTerm();
}

void initBuiltins() {
	builtins["exit"] = exit;
	builtins["pwd"] = pwd;
	builtins["clear"] = clear;
}
