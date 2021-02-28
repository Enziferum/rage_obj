//
// Created by Alexraag on 2/28/21.
//

#pragma once
#include "obj_math.h"

///////////////////// obj_parser api //////////////////////

struct obj_mesh{

};

struct obj_model{

};

//loading obj file to obj_model
const obj_model* obj_load(const char* path, obj_model* model);

//returns str repr of error
const char* obj_err();
///////////////////// obj_parser api //////////////////////