#ifndef CONFIG_FILE_HPP
# define CONFIG_FILE_HPP

# include <string>
# include <fstream>
# include <sstream>
# include <map>
# include <iostream>
# include <string>
#include <list>
#include <vector>

#include "config_utils.hpp"
#include "location.hpp"
#include "../Server/Server.hpp"

using namespace std;

class ConfigFile {

public:

	ConfigFile();
	~ConfigFile();
	ConfigFile(const ConfigFile& file);
	ConfigFile& operator=(const ConfigFile& file);

	void            setDefaultConfigValues(map<string, string>& config_file);
	void            setConfigModules();
	void            openConfigFile(const string& file);
	void            parsingConfigFile(const string& file);
	vector<string>  getTokens(string& str);
    void            parsingLocation(vector<string>& words, ConfigFlags& loc_utils_flags,
                                        map<string, string>& tmp_config);

	bool    checkIsServer(ConfigFlags& flags, vector<string>& words);
	bool    checkIsListen(ConfigFlags& flags, vector<string>& words);
	bool    checkIsServerName(ConfigFlags &flags, vector<string> &words);
	bool	checkAllowMethods(ConfigFlags &flags, vector<string> &words, map<string, string>& config);
	bool    checkRoot(ConfigFlags &flags, vector<string> &words, map<string, string>& config);
	bool    checkClientMaxBodySize(ConfigFlags &flags, vector<string> &words, map<string, string>& config);
	bool    checkIsLocation(ConfigFlags &flags, vector<string> &words);
	bool    checkIsAutoindex(ConfigFlags &flags, vector<string> &words, map<string, string>& config);
	bool    checkClosingBracket(ConfigFlags &flags, vector<string> &words);
	bool    checkIsErrorPage(ConfigFlags &flags, vector<string> &words, map<string, string>& config);
	bool    checkIsIndex(ConfigFlags &flags, vector<string> &words, map<string, string>& config);
    bool    checkLocationClosingBracket(ConfigFlags &flags, vector<string> &words,
                                        map<string, string>& config, ConfigFlags& utils_flags);
    bool    checkIsCgiPath(ConfigFlags &flags, vector<string> &words, map<string, string>& config);
    string  checkMaintainCgiExtension(ConfigFlags &flags, string word, map<string, string>& config);

    Server      createNewServer(string ip_port, vector<Location>& locations);
    Location    createNewLocation(map<string, string>& config);


private:
	map<string, ConfigModules>  modules;
	map<string, string>         config_file;
	ifstream                    file_fd;
	string					    cur_listen;
	vector<string>              all_listen;
    vector<string>              cgi_extension;
	vector<Location>			all_locations;
    vector<Server>              all_servers;
};

#endif