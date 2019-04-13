#include <vector>
#include <unordered_map>
#include <fstream>

#define INPUT_FILE "input.txt"
#define REPEAT(N) for(size_t _i = 0; _i < N; ++_i)

/*
   ===========================
      function to meassure
   ===========================
*/

#define MEASSURE test_umap_fetch

/*
   ===========================
   ===========================
*/

void test_umap_fetch(size_t num_el, size_t num_rep)
{
	std::unordered_map<int, int> m;

	for(size_t i = 0; i < num_el; ++i)
	{
		m.emplace(i, i);
	}

	REPEAT(num_rep)
	for(size_t i = 0; i < num_el; ++i)
	{
		++m[i];
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
