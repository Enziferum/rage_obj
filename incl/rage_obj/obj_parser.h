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

#ifndef OBJ_PARSER
#define OBJ_PARSER


#define RAGE_OBJ_MAJOR_VERSION 0
#define RAGE_OBJ_MAJOR_MINOR 1

///////////////////// obj_parser structs //////////////////////

typedef struct {
    //name of structure
    char* name;

    //path to structure
    char* path;

}rage_obj_texture;


//todo parse model
typedef struct {

    rage_obj_texture* t1;
    rage_obj_texture* t2;
    rage_obj_texture* t3;

}rage_obj_material;

typedef struct{
    char* name;

    unsigned int faces_sz;

    unsigned int faces_offset;

    unsigned int index_offset;
}rage_obj_group;


typedef struct {
    unsigned int p;
    unsigned int t;
    unsigned int n;
} rage_obj_index;


typedef struct {
    unsigned int position_sz;
    float* positions;

    unsigned int texture_sz;
    float* texture;

    unsigned int normals_sz;
    float* normals;

    unsigned int face_count;
    unsigned int* face_vertices;
    unsigned int* face_materials;

    rage_obj_index* indexs;

    unsigned int material_sz;
    rage_obj_material* materials;

    unsigned int group_sz;
    rage_obj_group* groups;

}rage_obj_model;
///////////////////// obj_parser structs //////////////////////


///////////////////// obj_parser api //////////////////////

#ifdef __cplusplus
extern "C"{
#endif

typedef void(*custom_buffer_parser)(void*, const char*, const char*);

//loading obj file to obj_model
const int
rage_obj_load(const char* path, rage_obj_model* model);

//loading model using custom parser
int
rage_obj_load_custom(const char* path, rage_obj_model* model, custom_buffer_parser parser);

//returns str repr of error
const char*
rage_obj_err(const int code);

#ifdef __cplusplus
}
#endif
///////////////////// obj_parser api //////////////////////
#endif