/*
 * Example client program that uses thread pool.
 */
#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"

#define NCHAR 256
#define NTASK 32
#define NPOOH 62

//hex variable to print out winne the pooh using special characters
char *p[NPOOH] = {
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x2E\x2E\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x57\x24\x24\x24\x24\x24\x75",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x46\x2A\x2A\x2B\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x6F\x57\x24\x24\x24\x65\x75",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x2E\x75\x65\x65\x65\x57\x65\x65\x6F\x2E\x2E\x20\x20\x20\x20\x20\x20\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x65\x57\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x62\x2D\x20\x64\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x57",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2C\x2C\x2C\x2C\x2C\x2C\x2C\x75\x65\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x48\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x7E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3A\x65\x6F\x43\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x43\x22\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x54\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x2A\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x69\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3F\x66\x22\x21\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x75\x64\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2A\x43\x6F",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x20\x20\x20\x6F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x21\x21\x21\x6D\x2E\x2A\x65\x65\x65\x57\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x66\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x55",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x21\x21\x21\x21\x21\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x54\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2A\x21\x21\x2A\x2E\x6F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x2C\x64\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x3A",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x65\x65\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x43",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x62\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2A\x2A\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x54\x62\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2A\x75\x4C\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x6F\x2E\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22\x20\x75\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x65\x6E\x20\x60\x60\x60\x20\x20\x20\x20\x2E\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x42\x2A\x20\x20\x3D\x2A\x22\x3F\x2E\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x57\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x6F\x23\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x52\x3A\x20\x3F\x24\x24\x24\x57\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22\x20\x3A\x21\x69\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x21\x6E\x2E\x3F\x24\x3F\x3F\x3F\x22\x22\x60\x60\x2E\x2E\x2E\x2E\x2E\x2E\x2E\x2C\x60\x60\x60\x60\x60\x60\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x60\x60\x20\x20\x20\x2E\x2E\x2E\x2B\x21\x21\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x2A\x20\x2C\x2B\x3A\x3A\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2A\x60",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x21\x3F\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x7E\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x7E\x60",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2B\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x3F\x21\x60",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x27\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2C\x20\x21\x21\x21\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3A\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x27\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x60\x21\x21\x3A",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x2B\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x7E\x7E\x21\x21\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x21\x21\x21\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3A\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2E\x60\x3A\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x3A\x3A\x20\x60\x21\x21\x2B",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x7E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2E\x7E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2E\x60\x21\x21\x3A",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7E\x7E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x3B\x21\x21\x21\x21\x7E\x60\x20\x2E\x2E\x65\x65\x65\x65\x65\x65\x6F\x2E\x60\x2B\x21\x2E\x21\x21\x21\x21\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3A\x2E\x2E\x20\x20\x20\x20\x60\x2B\x7E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x3A\x21\x3B\x60\x2E\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x75\x20\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x62\x65\x65\x65\x75\x2E\x2E\x20\x20\x60\x60\x60\x60\x60\x7E\x2B\x7E\x7E\x7E\x7E\x7E\x22\x20\x60\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x62",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x55\x55\x24\x55\x24\x24\x24\x24\x24\x20\x7E\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x24\x6F",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2E\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x7E\x20\x24\x24\x24\x75",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x38\x24\x24\x24\x24\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x58\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x60\x75\x24\x24\x24\x24\x24\x57",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22\x2E\x24\x24\x24\x24\x24\x24\x24\x3A",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x2E\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x66\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x27\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x69\x62\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x62\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22\x6F\x24\x24\x24\x62\x2E\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x65\x2E\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x64\x24\x24\x24\x24\x24\x24\x6F\x2E\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x48\x20\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x57\x2E\x60\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x2E\x20\x22\x3F\x3F\x24\x24\x24\x66\x20\x2E\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x64\x24\x24\x24\x24\x24\x24\x6F\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x65\x65\x65\x65\x65\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x62\x75\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x33\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2A\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x64\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x2E\x20\x22\x3F\x24\x24\x24\x24\x24\x3A\x60\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x38",
"\x20\x20\x20\x20\x20\x20\x20\x65\x24\x24\x65\x2E\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2B\x20\x20\x22\x3F\x3F\x66\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x63",
"\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x6F\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x60\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x62\x2E",
"\x20\x20\x20\x20\x20\x4D\x24\x24\x24\x24\x24\x24\x24\x24\x55\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x75",
"\x20\x20\x20\x20\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x75",
"\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x6F",
"\x20\x20\x20\x20\x20\x20\x20\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x3F\x3F\x24\x24\x24\x24\x24\x24\x24\x46\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x22\x3F\x33\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x75\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x60\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x22\x3F\x3F\x3F\x3F\x3F\x22\x22"
};

//structure declared to use variables for compuation
struct data
{
    int a;
    int b;
};

//simple function to add two variables 
void add(void *param)
{
    struct data *temp;

    temp = (struct data*)param;
    printf("I add two values %d and %d result = %d\n",
           temp->a, temp->b, temp->a + temp->b);
}

void number(void *param)
{
    int i, num;
    
    num = *(int *)param;
    for (i = 0; i < NCHAR; ++i)
        printf("%d", num);
    printf("<%d>", num);
}

void donothing(void *param)
{
    /* do nothing */;
}

//function to print winne the pooh
void pooh(void *param)
{
    int i;
    
    printf("\n");
    for (i = 0; i < NPOOH; ++i)
        printf("%s\n", p[i]);
}

int main(void)
{
    int i, num[NTASK];
    struct data work;

    // initialize the thread pool
    pool_init();

    // 1st test
    work.a = 5;
    work.b = 10;
    pool_submit(add, &work);
    
    // 2nd test
    for (i = 0; i < NTASK; ++i) {
        num[i] = i;
        if (pool_submit(number, num+i)) //since pool_submit returns 1 if task is not added to queue
            fprintf(stderr, "%d: Queue is full.\n", i);
    }
    
    // wait for free slots in the task queue
    sleep(1);

    // 3rd test
    pool_submit(donothing, NULL);
    pool_submit(donothing, NULL);
    pool_submit(pooh, NULL);

    pool_shutdown(); //closes the thread pool
    return 0;
}
