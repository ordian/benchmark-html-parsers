//
//  proc_stat.h
//  proc_stat
//
//  Created by Alexander Borisov on 05.03.16.
//  Copyright © 2016 Alexander Borisov. All rights reserved.
//

#ifndef proc_stat_h
#define proc_stat_h
#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

double proc_stat_getCPUTime(void);
size_t proc_stat_getPeakRSS(void);
size_t proc_stat_getCurrentRSS(void);
void proc_stat_print_rss(const char *name, size_t x, size_t y, FILE *fh);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* proc_stat_h */
