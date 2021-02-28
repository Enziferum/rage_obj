//
// Created by Alexraag on 2/28/21.
//

#include <vector>
#include <string>

#include "obj_parser.h"

enum obj_codes{};

enum class obj_token{
    comment, object, mtllib
};



class obj_reader{
public:
    const obj_model* load_obj(const char* path);

private:
    void get_token(const std::string& line);
    bool load_file(const char* path);
private:
    obj_model m_model;
    obj_token m_token;
    std::vector<std::string> m_file;
};

void obj_reader::get_token(const std::string& line) {
    std::string raw_token;
    for(size_t it = 0; it < line.size(); ++it){
        if(!std::isspace(line[it]))
            raw_token += line[it];
    }

    if(raw_token == "o")
        m_token = obj_token::object;
    if(raw_token == "#")
        m_token = obj_token::comment;
    if(raw_token == "mtllib")
        m_token = obj_token::mtllib;
}

const obj_model* obj_reader::load_obj(const char* path) {
    if(!load_file(path))
        return nullptr;

    bool parse_obj = false;
    for(auto& it: m_file){
        get_token(it);
        if(m_token == obj_token::comment)
            continue;
        if(m_token == obj_token::mtllib){
            //load mtllib file
        }
        if(m_token == obj_token::object){
            if(!parse_obj){
                //get object name
                parse_obj = true;
            }
            else{

            }

        }

    }

    return &m_model;
}

int g_err = 0;

const obj_model* obj_load(const char* path, obj_model* model){

}

const char* obj_err(){
    switch (g_err) {
        default:
            return "success load";
    }
}