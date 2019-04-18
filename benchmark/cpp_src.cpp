#include <vector>
#include <unordered_map>
#include <fstream>

#define INPUT_FILE "input.txt"
#define REPEAT(N) for(size_t _i = 0; _i < N; ++_i)

#define STATIC_MAX 400000

/*
   ===========================
      function to meassure
   ===========================
*/

#define MEASSURE test_sumap_fetch

/*
   ===========================
   ===========================
*/

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

void test_vector_push_back(size_t num_el, size_t num_rep)
{
	std::vector<int> v;

	REPEAT(num_rep)
	for(size_t i = 0; i < num_el; ++i)
	{
		v.push_back(i);
	}
}

int main(int argc, char* argv[])
{
	std::ifstream in(INPUT_FILE);
	std::string tmp;

	in >> tmp;
	size_t num_of_elements = stoi(tmp);

	in >> tmp;
	size_t num_of_repetitions = stoi(tmp);

	in.close();

	MEASSURE(num_of_elements, num_of_repetitions);

	return 0;
}
