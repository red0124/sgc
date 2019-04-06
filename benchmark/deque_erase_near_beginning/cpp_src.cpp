#include <deque>
#include <fstream>

#define INPUT_FILE "input.txt"

static void meassure(size_t num_of_elements)
{
	std::deque<int> d;
	for(size_t i = 0; i < num_of_elements; ++i)
	{
		d.push_back(i);
	}

	while(!d.empty())
	{
		d.erase(d.begin() + d.size() / 3);
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
