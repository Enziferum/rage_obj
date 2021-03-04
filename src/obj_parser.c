/*********************************************************************
(c) Alex Raag 2021
https://github.com/Enziferum
rage_obj - Zlib license.
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.
2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

////// C standard libraries //////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
////// C standard libraries //////


#include "rage_obj/obj_parser.h"


#ifndef RAGE_OBJ_REALLOC
#define RAGE_OBJ_REALLOC realloc
#endif

#ifndef RAGE_OBJ_FREE
#define RAGE_OBJ_FREE free
#endif


#define BUFFER_SZ 65536

#ifndef RAGE_OBJ_UINT_TYPE
#define RAGE_OBJ_UINT_TYPE unsigned int
#endif

typedef RAGE_OBJ_UINT_TYPE rage_uint8;


void*
rage_memory_realloc(void* ptr, const size_t sz){
    return RAGE_OBJ_REALLOC(ptr, sz);
}

void
rage_memory_dealloc(void* buffer){
    RAGE_OBJ_FREE(buffer);
}


////// array api //////

////// array api //////

////// str api //////
char*
string_copy(const char* src, const char* dst){
    char* copy;

    size_t sz;
    sz = (size_t)(dst - src);
    //nothing to copy
    if(sz < 0)
        return NULL;
    copy = (char*)(realloc(0, sz+1));
    if(copy){
        memcpy(copy, src, sz);
        copy[sz] = '\0';
    }
    return copy;
}

char*
string_substr(const char* str, size_t offset, size_t len){
    return string_copy(str + offset, str + offset + len);
}

////// str api //////


/////// file api //////
FILE*
rage_open_file(const char* path){
    return fopen(path, "r");
}

void
rage_close_file(void* file){
    FILE* p_file;
    p_file = (FILE*)(file);
    fclose(file);
}

size_t
rage_read_file(void* src, void* dst, size_t size){
    FILE* file = (FILE*)(src);
    return fread(dst, 1, size, file);
}

/////// file api //////


typedef struct {
    rage_obj_model* model;
    // group ?
    rage_uint8 material;
    rage_uint8 line_it;
    char* base_path;
}rage_parse_data;



void
parse_buffer(rage_parse_data* data, const char* ptr, const char* end){
    printf("%s", "Ji!");
}

const int
rage_obj_load(const char* path, rage_obj_model* model){
    void* file;
    char* buffer;
    char* start;
    char* end;
    char* last;
    rage_uint8 read;
    rage_uint8 bytes;

    rage_parse_data parse_data;
    parse_data.model = model;
    parse_data.material = 0;
    parse_data.line_it = 0;
    parse_data.base_path = NULL;

    model->materials = 0;
    model->groups = 0;
    model->normals = 0;
    model->positions = 0;
    model->texture = 0;
    model->face_materials = 0;
    model->face_vertices = 0;


    file = rage_open_file(path);
    if(!file)
        return 1;

    {
        const char* sep1;
        const char* sep2;
        const char* sep;
        if(sep)
            parse_data.base_path = string_substr(path, 0, sep - path + 1);
    }

    buffer = (char*)(rage_memory_realloc(0, 2 * BUFFER_SZ * sizeof(char)));
    if(buffer == NULL)
        return 2;

    start = buffer;

    for(;;){
        read = (rage_uint8)(rage_read_file(file, start, sizeof(buffer)));
        if(read == 0 && start == buffer)
            break;

        if(read < BUFFER_SZ){
            if (read == 0 || start[read - 1] != '\n')
                start[read++] = '\n';
        }

        end = start + read;
        if (end == buffer)
            break;

        last = end;
        while (last > buffer)
        {
            last--;
            if (*last == '\n')
                break;
        }

        if (*last != '\n')
            break;

        last++;


        parse_buffer(&parse_data, buffer, last);

        bytes = (rage_uint8)(end - last);
        // move buffer pointer in memory
        memmove(buffer, last, bytes);
        start = buffer + bytes;
    }


    rage_memory_dealloc(buffer);
    rage_memory_dealloc(parse_data.base_path);
    rage_close_file(file);

    return 0;
}


int
rage_obj_load_custom(const char* path, rage_obj_model* model, custom_buffer_parser parser){
    void* file;
    char* buffer;
    char* start;
    char* end;
    char* last;
    rage_uint8 read;
    rage_uint8 bytes;

    rage_parse_data parse_data;
    parse_data.model = model;
    parse_data.material = 0;
    parse_data.line_it = 0;
    parse_data.base_path = NULL;

    model->materials = 0;
    model->groups = 0;
    model->normals = 0;
    model->positions = 0;
    model->texture = 0;
    model->face_materials = 0;
    model->face_vertices = 0;


    file = rage_open_file(path);
    if(!file)
        return 1;

//    {
//        const char* sep1;
//        const char* sep2;
//        const char* sep;
//        if(sep)
//            parse_data.base_path = string_substr(path, 0, sep - path + 1);
//    }

    buffer = (char*)(rage_memory_realloc(0, 2 * BUFFER_SZ * sizeof(char)));
    if(buffer == NULL)
        return 2;

    start = buffer;

    for(;;){
        read = (rage_uint8)(rage_read_file(file, start, BUFFER_SZ));
        if(read == 0 && start == buffer)
            break;

        if(read < BUFFER_SZ){
            if (read == 0 || start[read - 1] != '\n')
                start[read++] = '\n';
        }

        end = start + read;
        if (end == buffer)
            break;

        last = end;
        while (last > buffer)
        {
            last--;
            if (*last == '\n')
                break;
        }

        if (*last != '\n')
            break;

        last++;


        parser(&parse_data, buffer, last);

        bytes = (rage_uint8)(end - last);
        // move buffer pointer in memory
        memmove(buffer, last, bytes);
        start = buffer + bytes;
    }


    rage_memory_dealloc(buffer);
    rage_memory_dealloc(parse_data.base_path);
    rage_close_file(file);

    return 0;
}

const char*
rage_obj_err(const int code){
    if(code == 0)
        return "success load";
    if(code == 1)
        return "error to open file";
    if(code == 2)
        return "can't alloc memory to buffer";
    return 0;
}
