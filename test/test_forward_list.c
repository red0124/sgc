#include "test_common.h"
#include <sgc/forward_list.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_FORWARD_LIST(int, list)

const int* list_at(list* l, size_t at) {
    list_it curr = list_begin(l);

    while (list_it_valid(curr)) {
        if (at == 0) {
            return list_it_data(curr);
        }
        list_it_go_next(&curr);
        --at;
    }

    if (at == 0) {
        return list_it_data(curr);
    }

    return NULL;
}

void list_set(list* l, size_t at, int el) {
    int* curr_el = (int*)list_at(l, at);
    if (curr_el != NULL) {
        *curr_el = el;
    }
}

void list_insert(list* l, int at, int el) {
    if (at > (int)list_size(l)) {
        return;
    }

    list new_list;
    list_init(&new_list);

    for (list_it curr = list_begin(l); list_it_valid(curr);
         list_it_go_next(&curr)) {
        if (at == 0) {
            list_push_back(&new_list, el);
        }
        list_push_back(&new_list, *list_it_data(curr));
        --at;
    }

    if (at == 0) {
        list_push_back(&new_list, el);
    }

    list_free(l);
    *l = new_list;
}

void list_erase(list* l, int at) {
    if (at >= (int)list_size(l)) {
        return;
    }

    list new_list;
    list_init(&new_list);

    for (list_it curr = list_begin(l); list_it_valid(curr);
         list_it_go_next(&curr)) {
        if (at != 0) {
            list_push_back(&new_list, *list_it_data(curr));
        }
        --at;
    }

    list_free(l);
    *l = new_list;
}

void list_pop_back(list* l) {
    if (!list_empty(l)) {
        list_erase(l, list_size(l) - 1);
    }
}

void list_it_go_prev(list_it* it) {
    struct _p_list_node* curr = it->head_;
    if(curr == it->curr_) {
        it->curr_ = NULL;
        return;
    }
    while (curr->next_ && curr->next_ != it->curr_) {
        curr = curr->next_;
    }
    it->curr_ = curr;
}

void test_list_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(list);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_insert_erase_combinations);
    return UNITY_END();
}
