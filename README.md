# ccontainers
Generic containers for **C** using macros 

## Usage 
The containers used are similar to the **C++ STL** containers with little 
difference.

First add the **generic_container.h** file into your program.

Since there are no generic functions in C, we manually have to 
init the container using the **INIT_CONTAINER(type)** macro.
The **type** has to be a single word (use typedef).
The macro will generate the structures and functions of the
container you wanted, adding **_type** at the end of 
every structure and function to separate them because function
overload does not exist in C.

When using a container we also have to initialize it manually since
there are no default values in C. Either use the function
 __void container_init_type(struct container_type*)__ or 
**struct container_type container_new_type()**

The container destruction has to be done manualy too using the
__void container_free_type(struct container*)__ function

If the type of the container has memory alocated dynamically a
function can be given to the container that will take care of
the destruction of all the elements when the container is freed.
__void container_set_free_type(struct container_type*, void(_*destroy_)(type*))__
This is similar to the *C++* destruction of an object where **delete** calls
the destructors of the container type.

The way elements are added to the container is determined by the **copy**
function in the container, which by default is a flat copy using **memcpy** 
*(create new element, copy every bit of data from the source)*, 
an array will not be copied the element in the container 
will just point to the same array. 
The **copy** function can be changed using the
__void container_set_copy_type(struct container_type*, void (_*copy_)(type*, const T*))__
function.

The equality condition of the elements is given by the **equ** function in the 
container which by default is a flat compare using **memcmp**.
The **equ** function can be changed using the
__void container_set_equ_type(struct container_type*, int (_*equ_)(const type*, const type*))__
function.

Same goes for the sort condition used for the elements if needed
__void container_set_comp_type(struct container_type*, int (_*comp_)(const void* ,const void*))__
Be careful sine this functions take _void*_ as parameters, and have to be made
similar to the **C qsort** compare functions, and **memcmp** is used by default.

An easy way to operate through each of the elements of a container is using the
__void container_operate_type(struct container_type*, void (_*operate_)(T*))__
function. There is also an inverted version of this function.

Getting certain data from the container can be done using the
**container_operate_to_type** function, and so on.
The functions provided by the container are given in the 
**generic_container_headers.h** file

Those containers can be compiled separately by adding every structure we want to
use into the **generic_types.h** file, then init them into the 
**generic_container.c** files and used by adding the **generic_container_header.h**
file into your program so it can be linked later on.

## Examples
# Vector

![GitHub Logo](/vector.png)
Format: ![Alt Text](url)
