#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <unordered_map>
#include <tasks>

char getChar();
std::string getLine();

void initBuiltins();

extern std::Env env;

typedef void (*Builtin)(std::Args&);
extern std::unordered_map<std::string, Builtin> builtins;

#endif
