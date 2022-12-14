# define LOCALHOST "127.0.0.1"

# include "Core/Core.hpp"
# include "Http/Http.hpp"
# include "Parser/ConfigFile.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage:\n\t.d/run {config__file}.cfg\n";
		exit(EXIT_FAILURE); 
	}
	Core 	core(argv[1]);

	core.setUpWebServers();
	core.runWebServers();
}