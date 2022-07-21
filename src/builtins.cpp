#include "common.hpp"
#include <unordered_map>
#include <cstdio>
#include <fs>

std::unordered_map<std::string, Builtin> builtins;

static void exit(std::Args& args) {
	IGNORE(args);
	std::exit();
}

static void pwd(std::Args& args) {
	IGNORE(args);
	std::printf("%s\n", env["PWD"].c_str());
}

static void clear(std::Args& args) {
	IGNORE(args);
	std::clearTerm();
}

static void cd(std::Args& args) {
	std::string pwd = env["PWD"];
	pwd += "/";
	pwd += args[0];
	pwd = std::simplifyPath(pwd);

	size_t err = std::_fs_select(pwd);
	if(err != std::FS_OK) {
		std::printf("cd: %s: %s\n",
					std::VFS::errStr(err),
					pwd.c_str());
		return;
	}

	if(!std::isDir(pwd)) {
		std::printf("cd: not a directory: %s\n",
					pwd.c_str());
		return;
	}

	env["PWD"] = pwd;
}

static void lev(std::Args& args) {
	IGNORE(args);
	std::printf("%d\n", lastExitValue);
}

void initBuiltins() {
	builtins["exit"] = exit;
	builtins["pwd"] = pwd;
	builtins["clear"] = clear;
	builtins["cd"] = cd;
	builtins["lev"] = lev;
}
