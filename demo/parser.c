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

#include "rage_obj/obj_parser.h"
#include "parser.h"


typedef unsigned int uint8;

typedef struct{
    rage_obj_model* model;
    uint8 material;
    uint8 line_it;
    char* base_path;
}rage_parser_data;


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
    while(!is_whitespace(*ptr))
        ptr++;
    return ptr;
}

const char*
rage_parse_float(const char* ptr, float* value){

    return ptr;
}

const char*
rage_parse_vertex(rage_parser_data* data, const char* ptr){

    for(uint8 it = 0; it < 3; ++it){
        float value;
        ptr = rage_parse_float(ptr, &value);

    }

    return ptr;
}

const char*
rage_parse_texcoord(rage_parser_data* data, const char* ptr){

    for(short it = 0; it < 2; ++it){
        float value;
        ptr = rage_parse_float(ptr, &value);
    }

    return ptr;
}

const char* rage_parse_normal(rage_parser_data* data, const char* ptr){
    for(uint8 it = 0; it < 3; ++it){
        float value;
        ptr = rage_parse_float(ptr, &value);

    }
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
                break;
            case 'u':
                break;
            case 'm':
                break;
            case 'o':
                break;
            case '#':
                break;
        }
        //we not parse something usefull skip it

        ptr = rage_skip_line(ptr);
        parser_data->line_it++;
    }
}