#include <list>
#include <fstream>

#define INPUT_FILE "input.txt"

static void meassure(size_t num_of_elements)
{
	std::list<int> l;

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		l.push_back(i % 100);
	}
	l.sort();

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