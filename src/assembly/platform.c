#include "platform.h"
#include <stdio.h>
#include <string.h>

const char *platform_symbol(const char *name) {
    static char buf[256];
#if defined(PLATFORM_MACOS)
    snprintf(buf, sizeof(buf), "_%s", name);
#else
    snprintf(buf, sizeof(buf), "%s", name);
#endif
    return buf;
}

void platform_print_info(void) {
#if defined(PLATFORM_MACOS)
    printf("Target platform: macOS (Mach-O ABI)\n");
#elif defined(PLATFORM_WINDOWS)
    printf("Target platform: Windows (PE/COFF ABI)\n");
#else
    printf("Target platform: Linux/ELF (SysV ABI)\n");
#endif
}
