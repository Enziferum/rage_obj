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

#include <iostream>
#include <assert.h>

#include "rage_obj/obj_parser.h"
#include "parser.h"

void print_material_info(const rage_obj_material* material){

}

void print_model_info(const rage_obj_model* model){

    //print material info
    rage_obj_material* material_it = model->materials;
    for(int it = 0; it < model->material_sz; ++it){
        print_material_info(material_it);
        material_it++;
    }

    std::cout << "Positions found" <<std::endl;

}


char*
string_copy(const char* src, const char* dst){
    char* copy;
    size_t sz;

    sz = size_t(dst - src);
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


void substring_test(){
    const char* msg = "Hello world";
    char* sub_str = string_substr(msg, 6, 5);
    //output should be world
    printf("%s", sub_str);
    //free because we allocate memory
    free(sub_str);
}

void model_test(){
    const char* path = "res/demo/test.obj";
    rage_obj_model model;
    int code = rage_obj_load_custom(path, &model, rage_obj_custom_parser);

    std::cout << rage_obj_err(code) << std::endl;
    print_model_info(&model);
}


#pragma pack(push, 1)
typedef struct{
    size_t elems;
    size_t elem_sz;
    size_t reverse_sz;
    size_t capelems_sz;
    unsigned char* buffer;
}rage_array;
#pragma pack(pop)

rage_array*
rage_array_new(size_t elem_sz){
    rage_array* arr = (rage_array*)(malloc(sizeof(rage_array)));
    if(!arr)
        return NULL;
    arr->elems = 0;
    arr->elem_sz = elem_sz;
    //1kb of memory
    arr->reverse_sz = 1024;
    arr->capelems_sz = arr->reverse_sz;
    arr->buffer = (unsigned char*)(malloc(arr->capelems_sz * arr->elem_sz));
    if(!arr->buffer)
        return NULL;

    return arr;
}

void
rage_array_free(rage_array* arr){
    free(arr->buffer);
    free(arr);
}

void
rage_array_grow(rage_array* arr){
    unsigned char* mem = (unsigned char*)(malloc((arr->reverse_sz
            + arr->capelems_sz) * arr->elem_sz));
    memcpy(mem, arr->buffer, arr->elems * arr->elem_sz);
    free(arr->buffer);
    arr->buffer = mem;
    arr->capelems_sz += arr->reverse_sz;
}

void
rage_array_push(rage_array* arr, void* value, size_t value_sz){
    assert(value_sz == arr->elem_sz);
    if(arr->elems == arr->capelems_sz)
        rage_array_grow(arr);
    memcpy(arr->buffer + (arr->elem_sz * arr->elems),
           (unsigned char*)(value), value_sz);
    arr->elems++;
}

size_t
rage_array_sz(rage_array* arr){
    return arr->elem_sz;
}

void*
rage_array_get(rage_array* arr, size_t idx){
    assert(idx < arr->elem_sz);
    return (void*)(arr->buffer + (idx * arr->elem_sz));
}


void
array_test(){
    //init array with float type
    rage_array* array = rage_array_new(sizeof(float));
    if(array == NULL)
        return;
    float val = 10.f;

    rage_array_push(array, &val, sizeof(float));
    float* positions;



    rage_array_free(array);
}


int main() {
    array_test();
    return 0;
}


