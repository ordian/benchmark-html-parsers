/*
 Copyright 2016 Alexander Borisov
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 Authors: lex.borisov@gmail.com (Alexander Borisov)
*/

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
