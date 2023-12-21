#include "dev.h"
#include "devices/Keyboard/kb.h"
#include "devices/PIT/pit.h"

void dev_init() {
    pit_init();
    kb_init();
}