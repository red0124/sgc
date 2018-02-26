# ccontainers
Generic containers for **C** using macros 

## Usage 
The containers used are simular to the **C++ STL** containers with little 
difference.

First add the **generic_container.h** file into your program.

Since there are no generic functions in C we manuali have to 
init the container using the **INIT_CONTAINER(type)** macro.
The **type_name** has to be a single word (use typedef).
The macro will generate the structures and functions of the
container you wanted, adding **_type** at the end of 
every structure and function to seperate them because function
overload does not exist in C.

When using a container we also have to initialize it manualy since
there are no default values in C. Either use the function
 **void container_init_type(struct container_type*)** or 
**struct container_type container_new_type()**

The container destruction has to be done manualy too using the
**void container_free_type(struct container*)** function

If the type of the container has memory alocated dinamicly a
function can be given to the container that will take care of
the destruction of all the elements when the container is freed.
**void container_set_free_type(struct container_type*, void(*destroy)(type*))**
This is sumular to the *C++* destruction of an object where **delete** calls
the destructors of the container type.

The way elements are added to the container is determened by the **copy**
function in the container, whitch by default is a flat copy using **memcpy** 
(create new element, copy every bit of data from the source)*, 
an array will not be copied the element in the container 
will just point to the same array. 
The **copy** function can be changed using the
**void container_set_copy_type(struct container_type*, void (*copy)(type*, const T*))**
function.

The equivalation of the elements is given by the **equ** function in the 
container which by default is a flat compare using **memcmp**.
The **equ** function can be changed using the
**void container_set_equ_type(struct container_type*, int (*equ)(const type*, const type*))**
function.

Same goes for the sort condition used for the elements if needed
**void container_set_comp_type(struct container_type*, int (*comp)(const void*, const void*))**
Be carefull sine this functions take *void* as parameters, and have to be made
simular to the **C qsort** compare functions, and **memcmp** is used by default.

An easy way to operate through each of the elements of a container is using the
**void container_operate_type(struct container_type*, void (*operate)(T*))**
function. There is also an inverted version of this function.

Geting certain data from the container can be done using the
**container_operate_to_type** function, and so on.
The functions provided by the container are given in the 
**generic_container_headers.h** file

Those containers can be compiled separatly by adding every structure we want to
use into the **generic_types.h** file, then init them into the 
**generic_container.c** files and used by adding the **generic_container_header.h**
file into your program so it can be linked later on.
