#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

#define INPUT_FILE "input.txt"
#define REPEAT(N) for(size_t _i = 0; _i < N; ++_i)

#define STATIC_MAX 400000

/*
   ===========================
      function to measure
   ===========================
*/

#define MEASURE test_vector_push_back

/*
   ===========================
   ===========================
*/

void test_pqueue_pop(size_t num_el, size_t num_rep)
{
        std::priority_queue<int> p;

        REPEAT(num_rep)
        {
                for(size_t i = 0; i < num_el; ++i)
                {
                        p.push(i);
                }

                while(!p.empty())
                {
                        p.pop();
                }
        }
}

void test_pqueue_push(size_t num_el, size_t num_rep)
{
        std::priority_queue<int> p;

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                p.push(i);
        }
}

void test_list_iterate(size_t num_el, size_t num_rep)
{
        std::list<int> l;

        for(size_t i = 0; i < num_el; ++i)
        {
                l.push_back(i);
        }

        REPEAT(num_rep)
        for(auto &i : l)
        {
                ++i;
        }
}

void test_list_push_back(size_t num_el, size_t num_rep)
{
        std::list<int> l;

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                l.push_back(i);
        }
}

void test_map_insert(size_t num_el, size_t num_rep)
{
        std::map<int, int> m;

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                m.emplace(i * 9999, i);
        }
}

void test_map_iterate(size_t num_el, size_t num_rep)
{
        std::map<int, int> m;

        for(size_t i = 0; i < num_el; ++i)
        {
                m.emplace(i * 9999, i);
        }

        REPEAT(num_rep)
        for(auto &i : m)
        {
                ++i.second;
        }
}

void test_map_fetch(size_t num_el, size_t num_rep)
{
        std::map<int, int> m;

        for(size_t i = 0; i < num_el; ++i)
        {
                m.emplace(i * 9999, i);
        }

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                ++m[i * 9999];
        }
}

void test_sumap_iterate(size_t num_el, size_t num_rep)
{
        std::unordered_map<int, int> m;
        m.reserve(STATIC_MAX);

        for(size_t i = 0; i < num_el; ++i)
        {
                m.emplace(i * 9999, i);
        }

        REPEAT(num_rep)
        for(auto &i : m)
        {
                ++i.second;
        }
}

void test_sumap_insert(size_t num_el, size_t num_rep)
{
        std::unordered_map<int, int> m;
        m.reserve(STATIC_MAX);

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                m.emplace(i * 9999, i);
        }
}

void test_sumap_fetch(size_t num_el, size_t num_rep)
{
        std::unordered_map<int, int> m;
        m.reserve(STATIC_MAX);

        for(size_t i = 0; i < num_el; ++i)
        {
                m.emplace(i * 9999, i);
        }

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                ++m[i * 9999];
        }
}

void test_umap_iterate(size_t num_el, size_t num_rep)
{
        std::unordered_map<int, int> m;

        for(size_t i = 0; i < num_el; ++i)
        {
                m.emplace(i * 9999, i);
        }

        REPEAT(num_rep)
        for(auto &i : m)
        {
                ++i.second;
        }
}

void test_umap_insert(size_t num_el, size_t num_rep)
{
        std::unordered_map<int, int> m;

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                m.emplace(i * 9999, i);
        }
}

void test_umap_fetch(size_t num_el, size_t num_rep)
{
        std::unordered_map<int, int> m;

        for(size_t i = 0; i < num_el; ++i)
        {
                m.emplace(i * 9999, i);
        }

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                ++m[i * 9999];
        }
}

void test_vector_fetch(size_t num_el, size_t num_rep)
{
        std::vector<int> v;

        for(size_t i = 0; i < num_el; ++i)
        {
                v.push_back(i);
        }

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                ++v[i];
        }
}

void test_vector_push_back(size_t num_el, size_t num_rep)
{
        std::vector<int> v;

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                v.push_back(i);
        }
}

int main(int argc, char *argv[])
{
        std::ifstream in(INPUT_FILE);
        std::string tmp;

        in >> tmp;
        size_t num_of_elements = stoi(tmp);

        in >> tmp;
        size_t num_of_repetitions = stoi(tmp);

        in.close();

        MEASURE(num_of_elements, num_of_repetitions);

        return 0;
}
