#ifndef DEFINE_DEBUG_ONCE
#define DEFINE_DEBUG_ONCE

#if DEBUG
	#include <stdio.h>

	#define debug(x, ...) { \
		fprintf(stderr, "%s:%s(%u): \n" x "\n", \
		__FILE__, __PRETTY_FUNCTION__, __LINE__, \
		##__VA_ARGS__); } 

	#define logout(x, ...) { \
		fprintf(stdout, x "\n", ##__VA_ARGS__); }

	#define sdl_debug(x, ...) { \
		fprintf(stderr, x " : %s\n", ##__VA_ARGS__, SDL_GetError()); }


#else
	#define debug(x, ...)
	#define logout(x, ...)
	#define sdl_debug(x, ...)
#endif

#endif
