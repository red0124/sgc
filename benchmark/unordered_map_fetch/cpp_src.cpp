#include <unordered_map>
#include <fstream>

#define INPUT_FILE "input.txt"

static void meassure(size_t num_of_elements)
{
	std::unordered_map<int, int> m;

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		// i * 9999 to get some identical hashes
		m.insert(std::pair<int, int>(i * 9999, i));
	}

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		for(size_t j = 0; j < 9; ++j)
		{
			++m[i * 9999];
		}
	}
}

int main(int argc, char* argv[])
{
	std::ifstream in(INPUT_FILE);
	std::string tmp;
	in >> tmp;

	size_t num_of_elements = stoi(tmp);
	meassure(num_of_elements);

	return 0;
}
