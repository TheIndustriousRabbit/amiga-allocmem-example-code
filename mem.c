#include <proto/exec.h>
#include <proto/dos.h>
#include <exec/exec.h>
#include <clib/exec_protos.h>
#include <clib/graphics_protos.h>

#include <hardware/dmabits.h>
#include <hardware/custom.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE (100)

extern struct Custom custom;

UBYTE *buffer;
UBYTE *target;

void cleanUp() {
  if (buffer) FreeMem(buffer, MEMORY_SIZE);
  if (target) FreeMem(target, MEMORY_SIZE);
}

int main() {
  atexit(cleanUp);

  buffer = AllocMem(MEMORY_SIZE, MEMF_CLEAR);
  target = AllocMem(MEMORY_SIZE, MEMF_CLEAR);

  strcpy((char*)buffer, "Agnus copied me since I am in Chip RAM. Thanks, Agnus!");
  strcpy((char*)target, "Oh no, the blitter can't work with me since I'm in Fast RAM (or Slow RAM).");

  // Agnus blitter stuff
  OwnBlitter(); WaitBlit(); // Wait for the blitter to finish up its current operation.
  custom.bltcon0 = 0x09f0;
  custom.bltcon1 = 0;
  custom.bltapt = buffer;
  custom.bltdpt = target;
  custom.bltamod = 0;
  custom.bltdmod = 0;
  custom.bltafwm = 0xffff;
  custom.bltalwm = 0xffff;
  // Setting bltsize starts the blitter operation
  custom.bltsize = (1 * 64) + (MEMORY_SIZE / 2); // 1 "row", convert byte width to words
  DisownBlitter(); WaitBlit(); // Wait before we do anything else with the Chip RAM we (might) have.
    
  printf("\n%s\n\n", target);

  if (buffer) FreeMem(buffer, MEMORY_SIZE);
  if (target) FreeMem(target, MEMORY_SIZE);

  buffer = 0;
  target = 0;
}

