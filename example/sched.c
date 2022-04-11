#include <stdio.h>
#include <string.h>

#include <SGC/fs_vector.h>
#include <SGC/fs_priority_queue.h>

struct task
{
	void (*fun)(void);
	int priority;
	int initital_priority;
};

int task_compare(const struct task* first,
		 const struct task* second)
{
	return first->priority - second->priority;
}

#define MAX_TASKS 32

SGC_INIT_STATIC(STRUCT, struct task, task);
SGC_INIT_STATIC(PRIORITY_QUEUE, task, MAX_TASKS, pqueue);
SGC_INIT_STATIC(VECTOR, task, MAX_TASKS, vector);

pqueue sched_pqueue;
vector sched_vector;

void sched_init(void)
{
	pqueue_init(&sched_pqueue);
	vector_init(&sched_vector);
}

void sched_add(void (*fun)(void), int priority)
{
	pqueue_push(&sched_pqueue, (task){fun, priority, priority});
}

void sched_run(void)
{
	if(pqueue_empty(&sched_pqueue))
	{
		return;
	}
	while(1)
	{
		task curr = *pqueue_top(&sched_pqueue);
		pqueue_pop(&sched_pqueue);

		curr.fun();
		--curr.priority;

		if(curr.priority <= 0)
		{
			curr.priority = curr.initital_priority;
			vector_push_back(&sched_vector, curr);
		}
		else
		{
			pqueue_push(&sched_pqueue, curr);
		}

		if(pqueue_empty(&sched_pqueue))
		{
			for_each(i in sched_vector as vector)
			{
				pqueue_push(&sched_pqueue, *i);
			}
			// should write a function to clean the containers
			vector_init(&sched_vector);
		}
	}
}

void foo(void)
{
	printf("foo\n");
}

void bar(void)
{
	printf("bar\n");
}

void tar(void)
{
	printf("tar\n");
}

int main(void)
{
	sched_init();

	sched_add(foo, 10);
	sched_add(bar, 5);
	sched_add(tar, 1);

	sched_run();
	return 0;
}

