#include <common.hpp>
#include <cstdio>

void printKR(size_t pid, size_t kr) {
	std::printf("Killed PID %d. Reason: %d\n", pid, kr);
}
