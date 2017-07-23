#ifndef _HTML2HTML_LIB_H_
#define _HTML2HTML_LIB_H_

#ifdef __cplusplus
extern "C"
{
#endif

    enum parse_status
    {
        RES_OK = 0,
        RES_ERR_INVALID_PARAMETER = 1,
    };

    enum parse_status html5ever_parse_document(const char *html, size_t html_size, int use_arena);

#ifdef __cplusplus
}
#endif

#endif /* _HTML2HTML_LIB_H_ */
