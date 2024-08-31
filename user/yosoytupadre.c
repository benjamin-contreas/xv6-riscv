#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int ppid = getppid();
    printf("Yo soy tu padre - dijo el proceso %d\n", ppid);
    exit(0);
}