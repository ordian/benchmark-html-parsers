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

 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#ifndef work_h
#define work_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "perf.h"
#include "proc_stat.h"

#define DIE(msg, ...) do { fprintf(stderr, msg, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)

typedef void (*benchmark_work_callback_f)(const char* filename, const char* html, size_t html_size);

void benchmark_work_readdir_fork(const char *dirpath, benchmark_work_callback_f callback, FILE *out_fh);

#endif /* work_h */
