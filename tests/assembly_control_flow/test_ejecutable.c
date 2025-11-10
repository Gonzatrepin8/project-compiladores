#include <stdio.h>
#include <stdlib.h>

int main(void) {
    struct {
        int input;
        int expected;
    } tests[] = {
        {1, 1},
        {2, 6},
        {3, 24},
        {4, 1},
        {5, 9},
        {6, 10},
        {99, 0}
    };

    int total = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < total; i++) {
        char cmd[128];
        snprintf(cmd, sizeof(cmd), "echo %d | ./ascf", tests[i].input);

        FILE *fp = popen(cmd, "r");
        if (!fp) {
            perror("popen");
            return 1;
        }

        int output;
        if (fscanf(fp, "%d", &output) != 1) {
            printf("❌ Sin salida legible para input=%d\n", tests[i].input);
            pclose(fp);
            continue;
        }

        pclose(fp);

        if (output == tests[i].expected) {
            printf("✅ input=%d → %d (OK)\n", tests[i].input, output);
            passed++;
        } else {
            printf("❌ input=%d → %d (esperado %d)\n",
                   tests[i].input, output, tests[i].expected);
        }
    }

    printf("\nResumen: %d/%d pasaron.\n", passed, total);
    return passed == total ? 0 : 1;
}
