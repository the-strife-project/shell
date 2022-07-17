#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <unordered_map>

char getChar();
std::string getLine();

void initBuiltins();

extern std::unordered_map<std::string, std::string> env;

typedef std::vector<std::string> Args;
typedef void (*Builtin)(const Args&);
extern std::unordered_map<std::string, Builtin> builtins;

#endif
