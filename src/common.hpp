#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <unordered_map>
#include <tasks>
#include <kkill>

char getChar();
std::string getLine();

void initBuiltins();
void printKR(size_t pid, size_t kr);

extern std::Env env;
extern size_t lastExitValue;

typedef void (*Builtin)(std::Args&);
extern std::unordered_map<std::string, Builtin> builtins;

#endif
