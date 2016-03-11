//
//  work.h
//  benchmark
//
//  Created by Alexander Borisov on 06.03.16.
//  Copyright © 2016 Alexander Borisov. All rights reserved.
//

#ifndef work_h
#define work_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "perf.h"
#include "proc_stat.h"

#define DIE(msg, ...) fprintf(stderr, msg, ##__VA_ARGS__); exit(EXIT_FAILURE);

struct benchmark_ctx {
    size_t count;
    double sum;
    void  *data;
    
    size_t start_mem;
    size_t total_file_size;
};

typedef void (*benchmark_work_callback_f)(const char* filename, const char* html, size_t html_size, struct benchmark_ctx *ctx);
void benchmark_work_readdir(const char *dirpath, struct benchmark_ctx *ctx, benchmark_work_callback_f callback, FILE *out_fh);
void benchmark_work_readdir_fork(const char *dirpath, benchmark_work_callback_f callback, FILE *out_fh);
void benchmark_work(const char *filepath, const char *filename, benchmark_work_callback_f callback, struct benchmark_ctx *ctx, FILE *out_fh);
void benchmark_work_print_total(struct benchmark_ctx *ctx, FILE *fh);

#endif /* work_h */
