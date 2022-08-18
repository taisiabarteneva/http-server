#include "Core.hpp"
#include "../Parser/config_file.hpp"

Core::Core(char *config)
{
    ConfigFile  cfg;

    cfg.openConfigFile(config);
    servers = cfg.getAllServers();

    // vector<Server>::iterator it = servers.begin();
    // while (it != servers.end())
    // {
    //     cout << "server's ip_port: " << it->getAddress() << endl;
    //     vector<Location> locations = it->getLocations();
    //     cout << "locations.size: " << locations.size() << endl;
    //     vector<Location>::iterator ite = locations.begin();
    //     while (ite != locations.end()) {
    //         ite->printLocationInfo();
    //         cout << endl;
    //         ++ite;
    //     }
    //     ++it;
    // }

    for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++)
    {
        std::cout << "setting up server at " << it->getAddress() << std::endl;
        it->setupServer();
        it->run();
    }
    servers[0].setupServer(); servers[0].run(); // 
}

Core::Core(const Core & rhs) 
{
    *this = rhs;
}

const Core & Core::operator=(const Core & rhs)
{
    if (this != &rhs) {}

    return *this;
}

Core::~Core() {}