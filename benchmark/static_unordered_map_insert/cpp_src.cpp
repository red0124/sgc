#include <unordered_map>
#include <fstream>

#define STATIC_MAX 400000
#define INPUT_FILE "input.txt"

static void meassure(size_t num_of_elements)
{
	for(size_t i = 0; i < 9; ++i)
	{
		std::unordered_map<int, int> m;
		m.reserve(STATIC_MAX);

		for(size_t i = 0; i < num_of_elements; ++i)
		{
			m.insert(std::pair<int, int>(i, i));
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
