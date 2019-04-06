#include <list>
#include <fstream>

#define INPUT_FILE "input.txt"

static void meassure(size_t num_of_elements)
{
	std::list<int> l;

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		l.push_back(i);
	}

	while(!l.empty())
	{
		auto it = l.end();
		for(size_t i = 0; i < 1 + l.size() / 3; ++i)
		{
			--it;
		}
		l.erase(it);
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
