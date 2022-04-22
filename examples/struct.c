#include <sgc/deque.h>
#include <stdio.h>

struct student {
    char name[32];
    int age;
    int grade;
};

// initializes init, copy and free functions for student
// student_init will do a memset to 0
// student_free will do nothing but it is mandatory for sgc
// student_copy will to a raw struct copy
// will also make a typedef
SGC_INIT_PRIMITIVE_STRUCT(struct student, student)

SGC_INIT(DEQUE, student, deq)

int main(void) {
    deq d;
    deq_init(&d);

    student s = {.name = "batiatus", .age = 21, .grade = 9};
    deq_push_back(&d, s);

    for_each(i IN d AS deq) {
        printf("%s %d %d\n", i->name, i->age, i->grade);
    }

    deq_free(&d);
    return 0;
}
