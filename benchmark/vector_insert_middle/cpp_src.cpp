#include <vector>
#include <fstream>

#define INPUT_FILE "input.txt"

static void meassure(size_t num_of_elements)
{
	std::vector<int> v;

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		v.insert(v.begin() + v.size() / 2, i);
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
