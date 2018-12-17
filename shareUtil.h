#pragma once
#ifndef _SSUTIL_H_
#define _SSUTIL_H_

#include <stdlib.h>
#include <stdint.h>

static char *randString(char *, size_t);
static uint32_t rdtsc();

#include "shareUtil.c"

#endif