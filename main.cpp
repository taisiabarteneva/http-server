# define LOCALHOST "127.0.0.1"

// # include "Core/Core.hpp"
# include "Http/Http.hpp"
# include "Parser/ConfigFile.hpp"
# include "Net/Net.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage:\n\t./run {config__file}.cfg\n";
		exit(EXIT_FAILURE); 
	}
	Core 	core(argv[1]);

	// core.printInfo();
	std::cout << "Desпыsbudsвdddddsssвssfssfыssdfsssssssfsssssshsssssssdsssssdsdsswsdsssssssssssssddsssssdsddgssssssdddsdasdfssssssssdssfsdddпfdвssddыыjsdddsdddgd\n" << std::endl;
	core.setUpWebServers();
	core.runWebServers();
}