/*
 * Desktop entry: init SDL, then jump into CORE_ENTRY (app_main_pce).
 */

#include <stdio.h>
#include <stdlib.h>

#include "host_compat.h"
#include "host_platform.h"

#ifndef HOST_SCALE
#define HOST_SCALE 2
#endif

#ifndef HOST_APP_MAIN
#define HOST_APP_MAIN app_main
#endif

extern int HOST_APP_MAIN(uint8_t load_state, uint8_t start_paused, int8_t save_slot);

int main(int argc, char **argv)
{
    const char *title = "PC Engine / PCE-CD (host)";
    const char *rom = getenv("HOST_ROM");
    int rc;

    if (argc > 1 && argv[1] && argv[1][0])
        rom = argv[1];

    if (host_platform_init(title, HOST_SCALE) != 0)
        return 1;

    gw_core_bridge_init();
    if (rom)
        host_set_rom_path(rom);

    printf("host: Esc or close window to quit\n");
    printf("host: Arrows=D-pad  Z=B  X=A  Enter=Start  Shift=Select\n");
    printf("host: F1=save state  F2=load state  (./host_saves/)\n");
    printf("host: PCE-CD needs HOST_SD with bios/pce/syscard3.pce\n");
    if (rom)
        printf("host: ROM %s\n", rom);

    rc = HOST_APP_MAIN(0, 0, -1);

    host_platform_shutdown();
    return rc != 0 ? 1 : 0;
}
