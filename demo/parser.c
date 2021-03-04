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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rage_obj/obj_parser.h"
#include "parser.h"


typedef unsigned int uint8;

typedef struct{

}obj_model;

typedef struct{
    rage_obj_model* model;
    uint8 material;
    uint8 line_it;
    char* base_path;
}rage_parser_data;

int
is_digit(char c){
    return (c >= '0' && c <= '9');
}

int
is_newline(char c){
    return (c == '\n');
}

int
is_whitespace(char c){
    return (c == ' ' || c == '\t' || c == '\r');
}

const char*
rage_skip_line(const char* ptr){
    while (!is_newline(*ptr++))
        ;
    return ptr;
}

const char*
rage_skip_whitespace(const char* ptr){
    while(is_whitespace(*ptr))
        ptr++;
    return ptr;
}

const char*
rage_parse_int(const char* ptr, int* value){
    int sign;

    ptr = rage_skip_whitespace(ptr);

    switch (*ptr) {
        case '+':
            sign = 1;
        case '-':
            sign = -1;
        default:
            sign = 1;
    }

    int num = 0;
    while (is_digit(*ptr))
        num = 10 * num + (int)(*ptr++ - '0');

    *value = num;
    return ptr;
}

const char*
rage_parse_float(const char* ptr, float* value){
    double sign;
    ptr = rage_skip_whitespace(ptr);

    switch (*ptr) {
        case '+':
            sign = 1.0;
            ptr++;
            break;
        case '-':
            sign = -1.0;
            ptr++;
            break;
        default:
            sign = 1.0;
    }

    double num = 0.0;
    while (is_digit(*ptr))
        num = 10 * num + (double)(*ptr++ - '0');

    if(*ptr == '.')
        ptr++;

    //now we are work on fraction
    double frac = 0.0;
    double div = 1.0;

    while (is_digit(*ptr)){
        frac = 10.0 * frac + (double)(*ptr++ - '0');
        div *= 10.0;
    }

    num += frac / div;

    //todo if exponent ??


    *value = (float)(sign * num);


    return ptr;
}

const char*
rage_parse_vertex(rage_parser_data* data, const char* ptr){
    float value;

    printf("%s", "vertex info := ");
    for(uint8 it = 0; it < 3; ++it){
        ptr = rage_parse_float(ptr, &value);
        printf("%f ", value);
    }

    printf("\n");
    return ptr;
}

const char*
rage_parse_texcoord(rage_parser_data* data, const char* ptr){
    printf("%s", "texcoord info := ");
    for(short it = 0; it < 2; ++it){
        float value;
        ptr = rage_parse_float(ptr, &value);
        printf("%f ", value);
    }
    printf("\n");
    return ptr;
}

const char*
rage_parse_normal(rage_parser_data* data, const char* ptr){
    printf("%s", "normal info := ");
    for(uint8 it = 0; it < 3; ++it){
        float value;
        ptr = rage_parse_float(ptr, &value);
        printf("%f ", value);
    }
    printf("\n");
    return ptr;
}


const char*
rage_parse_face(rage_parser_data* data, const char* ptr){
    ptr = rage_skip_whitespace(ptr);
    int count = 0;

    while (!is_newline(*ptr)){

        //process

        count++;
        ptr = rage_skip_whitespace(ptr);
    }
    return ptr;
}

const char*
rage_parse_mtllib(rage_parser_data* data, const char* ptr){
    ptr = rage_skip_whitespace(ptr);
    const char* start = ptr;
    ptr = rage_skip_line(ptr);

    size_t dist = (size_t)(ptr - start - 1);
    char* mtllib_name = (char*)(malloc(dist+1));
    mtllib_name[dist] = '\0';
    memcpy(mtllib_name, start, dist);

    //open file
    return ptr;
}

//here we are line by line
void
rage_obj_custom_parser(void* data, const char* buffer, const char* end){
    rage_parser_data* parser_data = (rage_parser_data*)(data);
    const char* ptr;
    ptr = buffer;

    while (ptr != end){
        ptr = rage_skip_whitespace(ptr);
        switch(*ptr){
            case 'v':
                ptr++;
                switch (*ptr++) {
                    case ' ':
                    case '\t':
                        ptr = rage_parse_vertex(parser_data, ptr);
                        break;

                    case 't':
                        ptr = rage_parse_texcoord(parser_data, ptr);
                        break;

                    case 'n':
                        ptr = rage_parse_normal(parser_data, ptr);
                        break;

                    default:
                        ptr--; /* roll p++ back in case *p was a newline */
                }
                break;
            case 'f':
                ptr++;

            case 'u':
                break;
            case 'm':
                if(ptr[1] == 't'
                    && ptr[2] == 'l'
                    && ptr[3] == 'l'
                    && ptr[4] == 'i'
                    && ptr[5] == 'b')
                {
                    ptr += 6;
                    rage_parse_mtllib(parser_data, ptr);
                }
                break;
            case '#':
                break;
        }
        //we not parse something usefull skip it

        ptr = rage_skip_line(ptr);
        parser_data->line_it++;
    }
}