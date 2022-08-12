#include "config_file.hpp"
#include "config_utils.hpp"
#include <cstring>
#include <vector>

using namespace std;

ConfigFile::ConfigFile() {
	setDefaultConfigValues();
	setConfigModules();
}

void ConfigFile::setDefaultConfigValues() {
	config_file["listen"] = "127.0.0.1:8080";
	config_file["server_name"] = "";
	config_file["accepted_methods"] = "";
	config_file["client_max_body_size"] = "";
	config_file["root"] = "";
	config_file["autoindex"] = "off";
	config_file["index"] = "";
	config_file["cgi_ext"] = "";
	config_file["cgi_path"] = "";
	config_file["authentication"] = "";
}

void ConfigFile::setConfigModules() {
	modules["server"] = SERVER;
	modules["listen"] = LISTEN;
	modules["server_name"] = SERVER_NAME;
	modules["accepted_methods"] = ACCEPTED_METHODS;
	modules["client_max_body_size"] = CLIENT_MAX_BODY_SIZE;
	modules["root"] = ROOT;
	modules["autoindex"] = AUTOINDEX;
	modules["index"] = INDEX;
	modules["cgi_ext"] = CGI_EXT;
	modules["cgi_path"] = CGI_PATH;
	modules["authentication"] = AUTHENTICATION;
	modules["error_page"] = ERROR_PAGE;
	modules["location"] = LOCATION;
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
//		locationList = file.locationList;
//		locationListExt = file.locationListExt;
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

		string tmp_listen = words[1].substr(0, words[1].length() - 1);
		if (find(words.begin(), words.end(), tmp_listen) == words.end())
		{
			cout << "5" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_listen = true;
		config_file["listen"] = words[1].substr(0, words[1].find(';') - 1);
		all_listen.push_back(tmp_listen);
		cur_listen = tmp_listen;
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
		config_file["server_name"] = words[1].substr(0, words[1].find(';') - 1);
		return true;
	}
	cout << "8" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkAcceptedMethods(ConfigFlags &flags, vector<string> &words) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_accepted_methods)
		{
			cout << "9" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_accepted_methods = true;
		config_file["accepted_methods"] = words[1].substr(0, words[1].find(';') - 1);
		return true;
	}
	cout << "10" << endl;
	exit(EXIT_FAILURE);
}

bool ConfigFile::checkRoot(ConfigFlags &flags, vector<string> &words) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_root)
		{
			cout << "11" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_root = true;
		config_file["root"] = words[1].substr(0, words[1].find(';') - 1);
		return true;
	}
	cout << "12" << endl;
	exit(EXIT_FAILURE);
}

bool ConfigFile::checkClientMaxBodySize(ConfigFlags &flags, vector<string> &words) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_max_body_size)
		{
			cout << "13" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_max_body_size = true;
		config_file["client_max_body_size"] = words[1].substr(0, words[1].find(';') - 1);
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

//		parseLocation(); // спарсить локацию

		return true;
	}
	cout << "15" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkIsAutoindex(ConfigFlags &flags, vector<string> &words) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_autoindex)
		{
			cout << "16" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_autoindex = true;
		config_file["autoindex"] = words[1].substr(0, words[1].find(';') - 1);
		return true;
	}
	cout << "17" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkIsIndex(ConfigFlags &flags, vector<string> &words) {
	if (flags.check_server && words.size() == 2) {
		if (flags.check_index)
		{
			cout << "18" << endl;
			exit(EXIT_FAILURE);
		}

		flags.check_index = true;
		config_file["index"] = words[1].substr(0, words[1].find(';') - 1);
		return true;
	}
	cout << "19" << endl;
	exit(EXIT_FAILURE);
}

bool    ConfigFile::checkIsErrorPage(ConfigFlags &flags, vector<string> &words) {
	if (flags.check_server && words.size() == 3) { // error_page code html
		if (config_file.count(words[1]) == 1)
		{
			cout << "20" << endl;
			exit(EXIT_FAILURE);
		}

		config_file[words[1]] = words[2].substr(0, words[2].find(';') - 1);
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
		// здесь еще что-то будет
		config_file.clear();
		setDefaultConfigValues();
		return true;
	}
	cout << "22" << endl;
	exit(EXIT_FAILURE);
}

void ConfigFile::parsingConfigFile(const string &file) {
	string file_str;
	ConfigFlags utils_flags;
	vector<string> str_words;

	memset(&utils_flags, 0, sizeof(ConfigFlags));
	while (getline(file_fd, file_str, '\n')) {
		str_words = getTokens(file_str, ' ');

		for (int i = 0; i < str_words.size(); ++i) {
			cout << str_words[i] << " ";
		}

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
			cout << endl;
			continue;
		}

		try {
			modules.at(str_words[0]);
		} catch (out_of_range &e) {
			modules[str_words[0]] = DEFAULT;
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
			case ACCEPTED_METHODS:
				checkAcceptedMethods(utils_flags, str_words);
				break;
			case ROOT:
				checkRoot(utils_flags, str_words);
				break;
			case CLIENT_MAX_BODY_SIZE:
				checkClientMaxBodySize(utils_flags, str_words);
				break;
			case AUTOINDEX:
				checkIsAutoindex(utils_flags, str_words);
				break;
			case INDEX:
				checkIsIndex(utils_flags, str_words);
				break;
			case LOCATION:
				checkIsLocation(utils_flags, str_words);
				break;
			case ERROR_PAGE:
				checkIsErrorPage(utils_flags, str_words);
				break;
			case CGI_EXT:
				break;
			case CGI_PATH:
				break;
			case AUTHENTICATION:
				break;
			case BRACKET:
				checkClosingBracket(utils_flags, str_words);
				break;
			default:
				cout << str_words[0] << endl;
				cout << "Config_file is invalid" << endl;
				exit(EXIT_FAILURE);
		}

		str_words.clear();
		cout << endl;
	}

	if (utils_flags.check_server && (!utils_flags.check_all_read
		                                 || !utils_flags.check_server_name || !utils_flags.check_location))
	{
		cout << "24" << endl;
		exit(EXIT_FAILURE);
	}
}

vector<string> ConfigFile::getTokens(string &str, char sep) {
	vector<string>	words;
	size_t          i = 0;
	size_t          j = 0;

	while (str[i]) {
		while (str[i] && str[i] == sep)
			++i;
		j = i;
		while (str[i] && str[i] != sep)
			++i;
		string word = str.substr(j, i - j);
		words.push_back(word);
		j = i;
	}
	words.push_back(str.substr(j, i - j));
	return (words);
}
