#include "ConfigFile.hpp"
#include "ConfigUtils.hpp"

#define DEFAULT_IP_PORT "127.0.0.1:8080";

using namespace std;

ConfigFile::ConfigFile() {
	setDefaultConfigValues(config_file);
	setConfigModules();

    cgi_extension.push_back("cgi");
    cgi_extension.push_back("php");
}

void ConfigFile::setDefaultConfigValues(map<string, string>& config) {
    config["listen"] = DEFAULT_IP_PORT;
	config["server_name"] = "";
	config["allow_methods"] = "GET/POST/DELETE";
	config["client_max_body_size"] = "10M";
	config["root"] = "";
	config["autoindex"] = "off";
	config["index"] = "";
	config["cgi_dir"] = "";
	config["path"] = "/";
	config["redirection"] = "";
	config["authentication"] = "no";
}

void ConfigFile::setConfigModules() {
	modules["server"] = SERVER;
	modules["listen"] = LISTEN;
	modules["server_name"] = SERVER_NAME;
	modules["allow_methods"] = ALLOW_METHODS;
	modules["client_max_body_size"] = CLIENT_MAX_BODY_SIZE;
	modules["root"] = ROOT;
	modules["autoindex"] = AUTOINDEX;
	modules["index"] = INDEX;
	modules["cgi_dir"] = CGI_DIR;
	modules["authentication"] = AUTHENTICATION;
	modules["error"] = ERROR;
	modules["location"] = LOCATION;
	modules["redirection"] = REDIRECTION;
	modules["}"] = BRACKET;
}

ConfigFile::~ConfigFile() {}

ConfigFile::ConfigFile(const ConfigFile& cfg) {
	*this = cfg;
}

ConfigFile& ConfigFile::operator=(const ConfigFile& cfg) {
	if (this != &cfg) {
		config_file = cfg.config_file;
		all_listen = cfg.all_listen;
		all_locations = cfg.all_locations;
	}
	return (*this);
}

void ConfigFile::openConfigFile(const string &file) {
	if (file.find(".cfg") == string::npos && file.find(".conf") == string::npos
		&& file.find(".config") == string::npos)
	{
		cout << "1" << endl;
		exit(EXIT_FAILURE);
	}

	file_fd.open(file);
	if (!file_fd.is_open())
	{
		cout << "2" << endl;
		exit(EXIT_FAILURE);
	}
	parsingConfigFile(file);
}

bool    ConfigFile::checkIsServer(ConfigFlags &flags, vector<string> &words) {
	if (!flags.check_server && words.size() == 2 && words[1] == "{") {
		flags.check_server = true;
		return true;
	}
	cout << "3" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkIsListen(ConfigFlags& flags, vector<string>& words) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_listen)
		{
			cout << "4" << endl;
			exit(EXIT_FAILURE);
		}

		string tmp_listen = words[1].substr(0, words[1].length());
//        cout << tmp_listen << endl;
		if (find(all_listen.begin(), all_listen.end(), tmp_listen) != all_listen.end())
		{
			cout << "5" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_listen = true;
		config_file["listen"] = words[1].substr(0, words[1].find(';'));
		all_listen.push_back(tmp_listen);
		return true;
	}
	cout << "6" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkIsServerName(ConfigFlags &flags, vector<string> &words) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_server_name)
		{
			cout << "7" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_server_name = true;
		config_file["server_name"] = words[1].substr(0, words[1].find(';'));
		return true;
	}
	cout << "8" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkAllowMethods(ConfigFlags &flags, vector<string> &words, map<string, string>& config) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_allow_methods)
		{
			cout << "9" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_allow_methods = true;
		config["allow_methods"] = words[1].substr(0, words[1].find(';'));
		return true;
	}
	cout << "10" << endl;
	exit(EXIT_FAILURE);
}

bool ConfigFile::checkRoot(ConfigFlags &flags, vector<string> &words, map<string, string>& config) {
	if (flags.check_server && words.size() == 2) {

		if (flags.check_root)
		{
			cout << "11" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_root = true;
		config["root"] = words[1].substr(0, words[1].find(';') );
		return true;
	}
	cout << "12" << endl;
	exit(EXIT_FAILURE);
}

bool ConfigFile::checkClientMaxBodySize(ConfigFlags &flags, vector<string> &words, map<string, string>& config) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_max_body_size)
		{
			cout << "13" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_max_body_size = true;
		config["client_max_body_size"] = words[1].substr(0, words[1].find(';'));
		return true;
	}
	cout << "14" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkIsLocation(ConfigFlags &flags, vector<string> &words) {
	if (flags.check_server && words.size() == 3 && words[2] == "{") {
		if (words[1] == "/")
			flags.check_root_location = true;
		flags.check_location = true;
        flags.is_opening_bracket = true;
		return true;
	}
	cout << "15" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkIsAutoindex(ConfigFlags &flags, vector<string> &words, map<string, string>& config) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_autoindex)
		{
			cout << "16" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_autoindex = true;
		config["autoindex"] = words[1].substr(0, words[1].find(';'));
		return true;
	}
	cout << "17" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkIsIndex(ConfigFlags &flags, vector<string> &words, map<string, string>& config) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_index)
		{
			cout << "18" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_index = true;
		config["index"] = words[1].substr(0, words[1].find(';'));
		return true;
	}
	cout << "19" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkIsErrorPage(ConfigFlags &flags, vector<string> &words, map<string, string>& config) {
	if (flags.check_server && words.size() == 3) { // error code html
		if (config_file.count(words[1]) == 1)
		{
			cout << "20" << endl;
			exit(EXIT_FAILURE);
		}

		config[words[1]] = words[2].substr(0, words[2].find(';'));
		return true;
	}
	cout << "21" << endl;
	exit(EXIT_FAILURE);
} 

bool    ConfigFile::checkClosingBracket(ConfigFlags &flags, vector<string> &words) {
	if (flags.check_server && flags.check_listen && words.size() == 1) {
		flags.check_server = false;
		flags.check_all_read = true;
		flags.check_root_location = false;
		
        Server server = createNewServer(all_listen.back(), all_locations);

		all_servers.push_back(server);
		// ------------------
		// vector<Server *>::iterator it = all_servers.begin();
    	// while (it != all_servers.end())
    	// {
        // 	cout << "server's ip_port: " << (*it)->getAddress() << endl;
		// 	it++;
		// }
		// -------------------
		config_file.clear();
		all_locations.clear();
		setDefaultConfigValues(config_file);
        memset(&flags, 0, sizeof(ConfigFlags));
		return true;
	}
	cout << "22" << endl;
	exit(EXIT_FAILURE);
}

bool ConfigFile::checkLocationClosingBracket(ConfigFlags &loc_flags, vector<string> &words,
                                             map<string, string>& config, ConfigFlags& flags) {
    if (loc_flags.check_server && words.size() == 1) {
        loc_flags.check_all_read = true;
        memset(&loc_flags, 0, sizeof(ConfigFlags));
        loc_flags.check_server = true;
        loc_flags.check_listen = true;
        flags.is_opening_bracket = false;

        Location loc = createNewLocation(config);
		
        all_locations.push_back(loc);
        
		config.clear();
	    setDefaultConfigValues(config);
        words.clear();
        return true;
    }
    cout << "25" << endl;
    exit(EXIT_FAILURE);
}

Server ConfigFile::createNewServer(string ip_port, vector<Location> locations) {

	Server server(ip_port, locations);
	return server;
}

Location ConfigFile::createNewLocation(map<string, string>& config) {
	Location loc = Location(config);
	return loc;
}

//string    ConfigFile::checkMaintainCgiExtension(ConfigFlags &flags, string word, map<string, string>& config) {
//    vector<string>::iterator it = cgi_extension.begin();
//    if (word.find('.') == string::npos) {
//        cout << "28" << endl;
//        cout << "Invalid cgi extension" << endl;
//        exit(EXIT_FAILURE);
//    }
//    string ext = word.substr(word.find('.') + 1, word.find(';') - word.find('.') - 1);
//    while (it != cgi_extension.end()) {
//        if (*it == ext)
//            return ext;
//        ++it;
//    }
//    cout << "29" << endl;
//    cout << "Invalid cgi extension" << endl;
//    exit(EXIT_FAILURE);
//}

bool    ConfigFile::checkIsCgiDir(ConfigFlags &flags, vector<string> &words, map<string, string>& config) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_cgi_dir)
		{
			cout << "27" << endl;
			exit(EXIT_FAILURE);
		}
		config["cgi_dir"] = words[1].substr(0, words[1].find(';'));
		flags.check_cgi_dir = true;
		return true;
	}
	cout << "26" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkRedirection(ConfigFlags &flags, vector<string> &words, map<string, string>& config) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_redirection)
		{
			cout << "38" << endl;
			exit(EXIT_FAILURE);
		}
		config["redirection"] = words[1].substr(0, words[1].find(';'));
		flags.check_redirection = true;
		return true;
	}
	cout << "39" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkAuthentication(ConfigFlags &flags, vector<string> &words, map<string, string>& config) {
    if (flags.check_server && words.size() == 2) {
        if (flags.check_authentication)
        {
            cout << "34" << endl;
            exit(EXIT_FAILURE);
        }
        config["authentication"] = words[1].substr(0, words[1].find(';'));
        flags.check_authentication = true;
        return true;
    }
    cout << "35" << endl;
    exit(EXIT_FAILURE);
}

void ConfigFile::parsingConfigFile(const string &file) {
	string file_str;
	ConfigFlags utils_flags;
	vector<string> str_words;
	memset(&utils_flags, 0, sizeof(ConfigFlags));


    ConfigFlags loc_utils_flags;
    memset(&loc_utils_flags, 0, sizeof(ConfigFlags));
    loc_utils_flags.check_server = true;
    loc_utils_flags.check_listen = true;
    map<string, string> tmp_config;
    setDefaultConfigValues(tmp_config);

	while (getline(file_fd, file_str, '\n')) {
		str_words = getTokens(file_str);

//        for (int i = 0; i < str_words.size(); ++i) {
//            cout << "<" << str_words[i] << ">" << " ";
//        }
//        cout << endl;

//		cout << file_str << endl;
//		list<string>::iterator it = str_words.begin();
//		while (it != str_words.end()) {
//			cout << *it << " ";
//			it++;
//		}
//		cout << endl;

		if (str_words.size() == 0 || str_words[0][0] == '#')
		{
			str_words.clear();
			continue;
		}
        else if (utils_flags.check_location && utils_flags.is_opening_bracket)
        {
            if (str_words[0] != "}") {
	            tmp_config["listen"] = config_file["listen"];
				tmp_config["server_name"] = config_file["server_name"];
				tmp_config["client_max_body_size"] = config_file["client_max_body_size"];
                parsingLocation(str_words, loc_utils_flags, tmp_config);
                continue;
            }
            else if (str_words[0] == "}") {
                checkLocationClosingBracket(loc_utils_flags, str_words, tmp_config, utils_flags);
                continue;
            }
        }
        else
        {
            try {
                modules.at(str_words[0]);
            } catch (out_of_range &e) {
                modules[str_words[0]] = DEFAULT;
            }
        }

		switch (modules[str_words[0]]) {
			case SERVER:
				checkIsServer(utils_flags, str_words);
				break;
			case LISTEN:
				checkIsListen(utils_flags, str_words);
				break;
			case SERVER_NAME:
				checkIsServerName(utils_flags, str_words);
				break;
			case ALLOW_METHODS:
				checkAllowMethods(utils_flags, str_words, this->config_file);
				break;
			case ROOT:
				checkRoot(utils_flags, str_words, this->config_file);
				break;
			case CLIENT_MAX_BODY_SIZE:
				checkClientMaxBodySize(utils_flags, str_words, this->config_file);
				break;
			case AUTOINDEX:
				checkIsAutoindex(utils_flags, str_words, this->config_file);
				break;
			case INDEX:
				checkIsIndex(utils_flags, str_words, this->config_file);
				break;
			case LOCATION:
				checkIsLocation(utils_flags, str_words);
				tmp_config["path"] = str_words[1];
				break;
			case ERROR:
				checkIsErrorPage(utils_flags, str_words, this->config_file);
				break;
			case CGI_DIR:
                checkIsCgiDir(utils_flags, str_words, this->config_file);
			case AUTHENTICATION:
                checkAuthentication(utils_flags, str_words, this->config_file);
				break;
			case REDIRECTION:
				checkRedirection(utils_flags, str_words, this->config_file);
				break;
			case BRACKET:
				checkClosingBracket(utils_flags, str_words);
				break;
			default:
//				cout << str_words[0] << endl;
				cout << "Config_file is invalid" << endl;
				exit(EXIT_FAILURE);
		}

		str_words.clear();
	}

//    cout << "yeeeee all parsed" << endl;

	if (utils_flags.check_server && (!utils_flags.check_all_read
		                                 || !utils_flags.check_server_name || !utils_flags.check_location))
	{
		cout << "24" << endl;
		exit(EXIT_FAILURE);
	}
}

vector<string> ConfigFile::getTokens(string &str) {
	vector<string>	words;
	size_t          i = 0;
	size_t          j;

	while (str[i]) {
		while (str[i] && isspace(str[i]))
			++i;
		j = i;
		while (str[i] && !isspace(str[i]))
			++i;
		string word = str.substr(j, i - j);
		words.push_back(word);
	}
	return (words);
}

void    ConfigFile::parsingLocation(vector<string>& words, ConfigFlags& loc_utils_flags,
                                    map<string, string>& tmp_config) {

//    while (begin != words.end()) {
//
//        cout << *begin << " ";
//        begin++;
//    }
//    cout << endl;

    if (words.size() == 0 || words[0][0] == '#')
        return ;

    switch (modules[words[0]]) {
        case ALLOW_METHODS:
            checkAllowMethods(loc_utils_flags, words, tmp_config);
            break;
        case ROOT:
                checkRoot(loc_utils_flags, words, tmp_config);
            break;
        case AUTOINDEX:
                checkIsAutoindex(loc_utils_flags, words, tmp_config);
            break;
        case INDEX:
                checkIsIndex(loc_utils_flags, words, tmp_config);
            break;
        case ERROR:
                checkIsErrorPage(loc_utils_flags, words, tmp_config);
            break;
        case CGI_DIR:
            checkIsCgiDir(loc_utils_flags, words, tmp_config);
            break;
        case AUTHENTICATION:
            checkAuthentication(loc_utils_flags, words, tmp_config);
            break;
	    case REDIRECTION:
		    checkRedirection(loc_utils_flags, words, tmp_config);
		    break;
        default:
//            cout << words[0] << endl;
            cout << "Location in config_file is invalid" << endl;
            exit(EXIT_FAILURE);
    }
}

vector<Location>&    ConfigFile::getAllLocations() {
	return all_locations;
}

vector<Server>&  ConfigFile::getAllServers() {
	return all_servers;
}

