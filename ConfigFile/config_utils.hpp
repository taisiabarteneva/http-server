#ifndef CONFIG_UTILS_H
#define CONFIG_UTILS_H

enum ConfigModules {
	SERVER,
	LISTEN,
	SERVER_NAME,
	ACCEPTED_METHODS,
	ROOT,
	CLIENT_MAX_BODY_SIZE,
	AUTOINDEX,
	INDEX,
	CGI_EXT,
	CGI_PATH,
	AUTHENTICATION,
	LOCATION,
	ERROR_PAGE,
	BRACKET,
	DEFAULT
};

struct ConfigFlags {
	bool    check_server;
	bool    check_listen;
	bool    check_server_name;
	bool    check_accepted_methods;
	bool    check_root;
	bool    check_max_body_size;
	bool    check_root_location;
	bool    check_location;
	bool    check_autoindex;
	bool    check_index;
	bool    check_all_read;

	bool    isAuth;
	bool    isCgiPath;
	bool    isCgiExtension;
	bool	isExt;
};


#endif
