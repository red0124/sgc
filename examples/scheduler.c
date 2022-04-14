#include <sgc/priority_queue.h>
#include <stdio.h>

struct task {
    void (*fun)(void);
    int priority;
};

SGC_INIT_PRIMITIVE_STRUCT(struct task, task)

int task_compare(const task* t1, const task* t2) {
    return t1->priority - t2->priority;
}

SGC_INIT(PRIORITY_QUEUE, task, pqueue)

void fun1(void) {
    printf("fun1\n");
}

void fun2(void) {
    printf("fun2\n");
}

int main(void) {
    pqueue p;
    pqueue_init(&p);

    task t1 = {fun1, 2};
    task t2 = {fun2, 3};
    task t3 = {fun2, 1};

    pqueue_push(&p, t1);
    pqueue_push(&p, t2);
    pqueue_push(&p, t3);

    while (!pqueue_empty(&p)) {
        const task* t = pqueue_top(&p);
        printf("Priority %d\n", t->priority);
        t->fun();
        pqueue_pop(&p);
    }

    pqueue_free(&p);
    return 0;
}
