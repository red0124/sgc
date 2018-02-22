to make a compiled list add every tipe you want a list of into the
'generic_types.h' file, the type name must be a single word (use typedef)
initialize the lists in the 'generic_list.c' file using the 
'INIT_LIST(<TYPE_NAME>)' macro so it can be compiled seperatly
to use the list simply add the 'generic_list_headers.h' file into 
your program and initialize the progotypes using the
'INIT_LIST_HEADERS(<TYPE NAME>)' macro so it can be linked with the
compiled lists

to use the list uncompiled just add the 'generic_list.h' file 
into your program

if used with a type that has memory alocated dinamicly a type_free and a
type_copy function has to be added into the list

some functions also require a type_equal function in order to execute
(list_find, list_erase, etc...)
