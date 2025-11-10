#ifndef PLATFORM_H
#define PLATFORM_H

#if defined(__APPLE__)
#  define PLATFORM_MACOS 1
#elif defined(_WIN32)
#  define PLATFORM_WINDOWS 1
#else
#  define PLATFORM_LINUX 1
#endif

const char *platform_symbol(const char *name);

void platform_print_info(void);

#endif
