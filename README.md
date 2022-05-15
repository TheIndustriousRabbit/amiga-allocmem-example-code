# Amiga AllocMem Example Code

The C program used in "What the Heck is NoFastMem?" to show how AllocMem works.
View the video here: https://www.youtube.com/watch?v=CDUtoaqKkkk

## Compiling

You'll need [vbcc](http://sun.hasenbraten.de/vbcc/) with the m68k target and the appropriate Native
Development Kit headers installed:

```
vc -lauto -lamiga -c99 +kick13 -o mem mem.c
```

`mem` included in this repo is built with the above command and
should run on AmigaOS 1.3 and higher.

## Running

Open a Shell on an Amiga with Fast RAM and run:

```
mem
run nofastmem
mem
run nofastmem
mem
```
