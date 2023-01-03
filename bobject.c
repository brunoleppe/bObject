#include "bobject.h"
#include <stdio.h>

static bType type_id = 0;
static bObjectClass class;

static void destructor(bObject* obj){
    b_type_free(obj,obj->type);
    DEBUG_PRINT("Eliminando el objeto\n");
}

static void bObject_class_initialize(bObjectClass* class){
    class->destructor = destructor;
}
static void bObject_instance_initialize(bObject* obj){
    obj->type = type_id;
    DEBUG_PRINT("inicializando bObject\n");
}

static void bOject_initialize(){
    static bool initialized = false;
    if(initialized)
        return;
    type_id = b_type_object_initialize(
        sizeof(bObject),
        (void (*)(void*))bObject_instance_initialize,
        sizeof(bObjectClass),
        (void (*)(void*))bObject_class_initialize,
        &class);

    initialized = true;
    INFO_PRINT("Objecto inicializado\n");
    

}

bObject* b_object_new(bType type)
{
    bObject* obj = b_type_instantiate(type);
    if(obj == NULL)
        return NULL;
    obj->type = type;
    return obj;
}


void b_object_delete(bObject* obj)
{
    bObjectClass* class = b_type_class_get(obj->type);
    class->destructor(obj);
}

bType b_object_get_type(){
    bOject_initialize();
    return type_id;
}