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

using namespace std;

class ConfigFile {

public:

	ConfigFile();
	~ConfigFile();
	ConfigFile(const ConfigFile& file);
	ConfigFile& operator=(const ConfigFile& file);

	void    setDefaultConfigValues();
	void    setConfigModules();
	void    openConfigFile(const string& file);
	void    parsingConfigFile(const string& file);
	vector<string>    getTokens(string& str, char sep);

	bool    checkIsServer(ConfigFlags& flags, vector<string>& words);
	bool    checkIsListen(ConfigFlags& flags, vector<string>& words);
	bool    checkIsServerName(ConfigFlags &flags, vector<string> &words);
	bool	checkAcceptedMethods(ConfigFlags &flags, vector<string> &words);
	bool    checkRoot(ConfigFlags &flags, vector<string> &words);
	bool    checkClientMaxBodySize(ConfigFlags &flags, vector<string> &words);
	bool    checkIsLocation(ConfigFlags &flags, vector<string> &words);
	bool    checkIsAutoindex(ConfigFlags &flags, vector<string> &words);
	bool    checkClosingBracket(ConfigFlags &flags, vector<string> &words);
	bool    checkIsErrorPage(ConfigFlags &flags, vector<string> &words);
	bool    checkIsIndex(ConfigFlags &flags, vector<string> &words);


private:
	map<string, ConfigModules>  modules;
	map<string, string>         config_file;
	ifstream                    file_fd;
	string					    cur_listen;
	vector<string>              all_listen;
//	vector<Loc>					locationList;
//	vector<Loc>					locationListExt;
//	vector<Server>					serverList;
};

#endif