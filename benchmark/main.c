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
#include "html2html_lib.h"

// link lib -lhubbub -lparserutils -liconv -ldom -lwapcaplet
//#include "hubbub/parser.h"
//#include "hubbub/tree.h"
//
//#include "dom/dom.h"
//#include "dom/bindings/hubbub/parser.h"

void benchmark_myhtml_single(const char *filename, const char *html, size_t size, struct benchmark_ctx *ctx)
{
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_PARSE_MODE_SINGLE, 1, 0);
    
    // first tree init
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    myhtml_parse(tree, MyHTML_ENCODING_UTF_8, html, size);
    
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
}

void benchmark_myhtml(const char *filename, const char *html, size_t size, struct benchmark_ctx *ctx)
{
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    // first tree init
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    myhtml_parse(tree, MyHTML_ENCODING_UTF_8, html, size);
    
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
}

void benchmark_myhtml_single_real_live(const char *filename, const char *html, size_t size, struct benchmark_ctx *ctx)
{
    if(ctx->data == NULL)
    {
        myhtml_t* myhtml = myhtml_create();
        myhtml_init(myhtml, MyHTML_OPTIONS_PARSE_MODE_SINGLE, 1, 0);
        
        // first tree init
        myhtml_tree_t* tree = myhtml_tree_create();
        myhtml_tree_init(tree, myhtml);
        
        ctx->data = tree;
    }
    
    myhtml_parse(ctx->data, MyHTML_ENCODING_UTF_8, html, size);
}

void benchmark_myhtml_real_live(const char *filename, const char *html, size_t size, struct benchmark_ctx *ctx)
{
    if(ctx->data == NULL)
    {
        myhtml_t* myhtml = myhtml_create();
        myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
        
        // first tree init
        myhtml_tree_t* tree = myhtml_tree_create();
        myhtml_tree_init(tree, myhtml);
        
        ctx->data = tree;
    }
    
    myhtml_parse(ctx->data, MyHTML_ENCODING_UTF_8, html, size);
}

void benchmark_gumbo(const char *filename, const char *html, size_t size, struct benchmark_ctx *ctx)
{
    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, html, size);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void benchmark_html5ever(const char *filename, const char *html, size_t size, struct benchmark_ctx *ctx)
{
    parse_document(html, size, 0);
}

//void benchmark_hubbub_real_live_dom(const char *filename, const char *html, size_t size, struct benchmark_ctx *ctx)
//{
//    if(ctx->data == NULL)
//    {
//        dom_hubbub_parser_params params;
//        memset(&params, 0, sizeof(dom_hubbub_parser_params));
//        
//        dom_document *doc;
//        dom_hubbub_parser *parser = NULL;
//        dom_hubbub_parser_create(&params, &parser, &doc);
//        
//        ctx->data = parser;
//        ctx->ctx  = doc;
//    }
//    
//    dom_hubbub_error status = dom_hubbub_parser_parse_chunk(ctx->data, (const unsigned char*)html, size);
//    status = dom_hubbub_parser_completed(ctx->data);
//}
//
//void benchmark_hubbub_real_live(const char *filename, const char *html, size_t size, struct benchmark_ctx *ctx)
//{
//    if(ctx->data == NULL)
//    {
//        hubbub_parser *parser = NULL;
//        hubbub_parser_create("UTF-8", true, &parser);
//        
//        ctx->data = parser;
//    }
//    
//    hubbub_error status = hubbub_parser_parse_chunk(ctx->data, (const uint8_t*)html, size);
//    status = hubbub_parser_completed(ctx->data);
//}

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

double bentchmark(const char *dirpath, const char *filename, benchmark_work_callback_f callback)
{
    FILE *fh = NULL;
    
    if(filename) {
        fh = fopen(filename, "w");
        if (fh == NULL) {
            printf("Error opening file: %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    
    struct benchmark_ctx ctx = {0, 0, NULL, 0};
    benchmark_work_readdir(dirpath, &ctx, callback, fh);
    
    if(fh)
        fclose(fh);
    
    return ctx.sum;
}

void bentchmark_real(const char *dirpath, benchmark_work_callback_f callback)
{
    size_t mem_start = proc_stat_getCurrentRSS();
    double time = bentchmark(dirpath, NULL, callback);
    size_t mem_end = proc_stat_getPeakRSS();
    
    size_t mem_used = mem_end - mem_start;
    
    printf("Time: %0.5f; Mem start: %zu; Mem end: %zu; Mem after work: %zu\n", time, mem_start, mem_end, mem_used);
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
    
    bentchmark(argv[1], "result/myhtml_single_object.csv", benchmark_myhtml_real_live);
    bentchmark(argv[1], "result/myhtml_single_single_object.csv", benchmark_myhtml_single_real_live);
    
    bentchmark_fork(argv[1], "result/myhtml_single.csv", benchmark_myhtml_single);
    bentchmark_fork(argv[1], "result/myhtml.csv", benchmark_myhtml);
    bentchmark_fork(argv[1], "result/html5ever.csv", benchmark_html5ever);
    bentchmark_fork(argv[1], "result/gumbo.csv", benchmark_gumbo);
    
    return 0;
}

//int main(int argc, char** argv)
//{
//    if (argc != 2) {
//        usage();
//        DIE("Invalid number of arguments\n");
//    }
//    
//    bentchmark_real(argv[1], benchmark_hubbub_real_live);
//    return 0;
//}

//int main(int argc, char** argv)
//{
//    if (argc != 2) {
//        usage();
//        DIE("Invalid number of arguments\n");
//    }
//    
//    bentchmark_real(argv[1], benchmark_myhtml_real_live);
//    return 0;
//}

//int main(int argc, char** argv)
//{
//    if (argc != 2) {
//        usage();
//        DIE("Invalid number of arguments\n");
//    }
//    
//    bentchmark_real(argv[1], benchmark_myhtml_single_real_live);
//    return 0;
//}

//int main(int argc, const char * argv[])
//{
//    if (argc != 2) {
//        usage();
//        DIE("Invalid number of arguments\n");
//    }
//    
//    bentchmark_real(argv[1], benchmark_html5ever);
//    return 0;
//}

//int main(int argc, const char * argv[])
//{
//    if (argc != 2) {
//        usage();
//        DIE("Invalid number of arguments\n");
//    }
//    
//    bentchmark_real(argv[1], benchmark_gumbo);
//    return 0;
//}

//int main(int argc, const char * argv[]) {
//    // insert code here...
//    struct timespec tw = {1,0};
//    
//    uint64_t start = myhtml_hperf_clock();
//    nanosleep (&tw, NULL);
//    uint64_t end = myhtml_hperf_clock();
//    
//    double work_time = myhtml_absolute_difference(start, end);
//    printf("Time: %0.5f\n", work_time);
//    
//    return 0;
//}
