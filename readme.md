# rage_obj

 - Simple parser of .obj file. 
 - Component of [rage engine](https://github.com/Enziferum/rage) collection.

## requirements
 - C 99 compiler
 - cmake  

## How - to
 - build:
    ```shell
        git clone
        mkdir build && cd build
        cmake .. -G 
    ```
 - add
   - copy to libs folder in project
   - ```cmake
        add_subdirectory(ext_libs/rage_obj)
        target_link_libraries(${PROJECT_NAME} rage_obj)
     ``` 
 - use
    ```c++
        #include "rage_obj/obj_parser.h"
            
        const char* path = "PATH_TO_FILE";
        rage_obj_model model;
        
        int error = rage_obj_load(path, &model);
        
        if( error != 0 ) {
            const char* str_err = rage_obj_err(error);
            printf/std::cout str_err;
        }    
   ```
 - docs
   - will be added soon