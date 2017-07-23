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

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "perf.h"
#include "proc_stat.h"
#include "work.h"

#include "myhtml/api.h"

#include "gumbo.h"
#include "html5ever_parse_capi.h"

void benchmark_myhtml_single(const char *filename, const char *html, size_t size)
{
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_PARSE_MODE_SINGLE, 1, 0);

    // first tree init
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    myhtml_parse(tree, MyENCODING_UTF_8, html, size);

    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
}

void benchmark_myhtml(const char *filename, const char *html, size_t size)
{
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    // first tree init
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);

    myhtml_parse(tree, MyENCODING_UTF_8, html, size);

    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
}

void benchmark_gumbo(const char *filename, const char *html, size_t size)
{
    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, html, size);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void benchmark_html5ever_rc(const char *filename, const char *html, size_t size)
{
    html5ever_parse_document(html, size, 0);
}

void benchmark_html5ever_arena(const char *filename, const char *html, size_t size)
{
    html5ever_parse_document(html, size, 1);
}


void bentchmark_fork(const char *dirpath, const char *filename, benchmark_work_callback_f callback)
{
    FILE *fh = fopen(filename, "w");
    if (fh == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    benchmark_work_readdir_fork(dirpath, callback, fh);

    fclose(fh);
}

static void usage(void)
{
    fprintf(stderr, "benchmark <dirpath to HTML files>\n");
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        usage();
        DIE("Invalid number of arguments\n");
    }

    struct stat st = {0};

    if (stat("result", &st) == -1) {
        if(mkdir("result", 0700)) {
            DIE("Can't create directory: result\n");
        }
    }

    bentchmark_fork(argv[1], "result/myhtml_single.csv", benchmark_myhtml_single);
    bentchmark_fork(argv[1], "result/myhtml.csv", benchmark_myhtml);
    bentchmark_fork(argv[1], "result/html5ever_rc.csv", benchmark_html5ever_rc);
    bentchmark_fork(argv[1], "result/html5ever_arena.csv", benchmark_html5ever_arena);
    bentchmark_fork(argv[1], "result/gumbo.csv", benchmark_gumbo);

    return 0;
}

