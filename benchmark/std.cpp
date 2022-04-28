#include "common.h"
#include <cstdlib>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <stdint.h>
#include <stdio.h>
#include <unordered_map>
#include <vector>

static void run_map_insert(size_t n) {
    std::map<uint32_t, uint32_t> m;

    for (size_t i = 0; i < NUM_ELEMENTS_MAP; ++i) {
        m[(i * 19) % n] = i;
        m[(i * 53) % n] = i;
        m[(i * 257) % n] = i;
    }

    print(m.size());
}

static void run_map_iterate() {
    std::map<uint32_t, uint32_t> m;

    for (size_t i = 0; i < NUM_ELEMENTS_MAP; ++i) {
        m[i] = i;
    }

    for (size_t i = 0; i < NUM_REPEATS_MAP_ITERATE; ++i) {
        size_t sum = 0;
        for (const auto& el : m) {
            sum += el.second;
        }
        print(sum);
    }

    print(m.size());
}

static void run_unordered_map_insert(size_t n) {
    std::unordered_map<uint32_t, uint32_t> m;

    for (size_t i = 0; i < NUM_ELEMENTS_UNORDERED_MAP; ++i) {
        m[(i * 19) % n] = i;
        m[(i * 53) % n] = i;
        m[(i * 257) % n] = i;
    }

    print(m.size());
}

static void run_unordered_map_iterate() {
    std::unordered_map<uint32_t, uint32_t> m;

    for (size_t i = 0; i < NUM_ELEMENTS_UNORDERED_MAP; ++i) {
        m[i] = i;
    }

    for (size_t i = 0; i < NUM_REPEATS_UNORDERED_MAP_ITERATE; ++i) {
        size_t sum = 0;
        for (const auto& el : m) {
            sum += el.second;
        }
        print(sum);
    }

    print(m.size());
}

static void run_vector_iterate() {
    std::vector<uint32_t> v;

    for (size_t i = 0; i < NUM_ELEMENTS_VECTOR; ++i) {
        v.push_back(i);
    }

    for (size_t i = 0; i < NUM_REPEATS_VECTOR_ITERATE; ++i) {
        size_t sum = 0;
        for (const auto& el : v) {
            sum += el;
        }
        print(sum);
    }

    print(v.size());
}

static void run_deque_insert(size_t n) {
    for (size_t j = 0; j < NUM_TOTAL_INSERTS_DEQUE / n; ++j) {
        std::deque<uint32_t> d;

        for (size_t i = 0; i < n; ++i) {
            size_t delta = d.size() / 20;
            d.insert(d.begin() + delta, i);
            d.insert(d.end() - delta, i);
        }

        print(d.size());
    }
}

static void run_deque_iterate() {
    std::deque<uint32_t> d;

    for (size_t i = 0; i < NUM_ELEMENTS_DEQUE; ++i) {
        d.push_back(i);
    }

    for (size_t i = 0; i < NUM_REPEATS_DEQUE_ITERATE; ++i) {
        size_t sum = 0;
        for (const auto& el : d) {
            sum += el;
        }
        print(sum);
    }

    print(d.size());
}

static void run_unordered_map_of_vectors_insert(void) {
    std::unordered_map<uint32_t, std::vector<uint32_t>> m;

    for (size_t j = 0; j < NUM_REPEATS_UNORDERED_MAP_OF_VECTORS_INSERT; ++j) {
        for (size_t i = 0; i < NUM_ELEMENTS_MAP; ++i) {
            m[(i * 19) % 1000].push_back(i);
            m[(i * 53) % 1000].push_back(i);
            m[(i * 257) % 1000].push_back(i);
        }
        print(m.size());
    }

    print(m.size());
}

static void run_priority_queue_push_pop(size_t n) {
    std::priority_queue<uint32_t> p;

    for (size_t j = 0; j < NUM_TOTAL_INSERTS_PRIORIRTY_QUEUE / n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            p.push((i * 19) % 1000);
            p.push((i * 53) % 1000);
            p.push((i * 257) % 1000);
        }

        print(p.size());

        while (!p.empty()) {
            p.pop();
        }
        print(p.size());
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    int benchmark = atoi(argv[1]);
    switch (benchmark) {
    case map_insert_10:
        run_map_insert(10);
        break;
    case map_insert_1000:
        run_map_insert(1000);
        break;
    case map_insert_100000:
        run_map_insert(100000);
        break;
    case map_iterate:
        run_map_iterate();
        break;
    case unordered_map_insert_10:
        run_unordered_map_insert(10);
        break;
    case unordered_map_insert_1000:
        run_unordered_map_insert(1000);
        break;
    case unordered_map_insert_100000:
        run_unordered_map_insert(100000);
        break;
    case unordered_map_iterate:
        run_unordered_map_iterate();
        break;
    case vector_iterate:
        run_vector_iterate();
        break;
    case deque_insert_100:
        run_deque_insert(100);
        break;
    case deque_insert_100000:
        run_deque_insert(100000);
        break;
    case deque_iterate:
        run_deque_iterate();
        break;
    case unordered_map_of_vectors_insert:
        run_unordered_map_of_vectors_insert();
        break;
    case priority_queue_push_pop_100:
        run_priority_queue_push_pop(100);
        break;
    case priority_queue_push_pop_100000:
        run_priority_queue_push_pop(100000);
        break;
    };
    return 0;
}
