#include "Core.hpp"
#include "../Parser/ConfigFile.hpp"

Core::Core(char *config)
{
    ConfigFile  cfg;

    cfg.openConfigFile(config);
    servers = cfg.getAllServers();
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

void Core::setWebServers(void)
{
    for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++)
    {
        std::cout << "Setting up server at " << it->getAddress() << std::endl;
        it->setupServer();
        it->run();
    }
}

void Core::printInfo(void)
{
    vector<Server>::iterator it = servers.begin();
    while (it != servers.end())
    {
        cout << "Server's address: " << it->getAddress() << endl;
        vector<Location> locations = it->getLocations();
        cout << "Locations' size: " << locations.size() << endl;
        vector<Location>::iterator iter = locations.begin();
        while (iter != locations.end()) 
        {
            iter->printLocationInfo();
            cout << endl;
            ++iter;
        }
        ++it;
    }
}