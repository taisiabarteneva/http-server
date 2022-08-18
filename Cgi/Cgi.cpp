#include "Cgi.hpp"

// вот здесь может все упасть если я не умею копировать нормально

using namespace std;

Cgi::Cgi(Request& req): request(req) {
    char dir[MAXDIR];
    getcwd(dir, MAX_DIR);
    abs_path = string(dir);
    prepareCgiEnv();
    prepareCgiArgs();
}

Cgi::Cgi(const Cgi &cgi_copy) {
	*this = cgi_copy;
}

Cgi::~Cgi() {
    if (env)
    {
        for (int i = 0; i < env.size(); ++i) {
            delete[] env[i];
        }
        delete[] env;
    }
    if (args)
    {
        for (int i = 0; i < args.size(); ++i) {
            delete[] args[i];
        }
        delete[] args;
    }
};

void    Cgi::prepareCgiEnv() {
    map<string, string> headers = request.getHeaders();
    vector<string> envs;

    envs.push_back("PATH_INFO" + request.getURI()); // то что после скрипта передается
    envs.push_back("PATH_TRANSLATED" + abs_path); // полный путь
    envs.push_back("QUERY_STRING" + request.getQueryString());
    // мб еще какие-то переменные нужны

    int i = 0;
    env = new char*[envs.size() + 1];
    env[envs.size() + 1] = NULL;
    vector<string>::iterator it = env.begin();
    while (it != env.end()) {
        env[i] = new char[it->size() + 1];
        env[i] = strcpy(env[i], it->c_str());
        it++;
        i++;
    }
    env[i] = NULL;
}

void    Cgi::prepareCgiArgs() {
    args = new char*[3];
    args[0] = new char[request.getLocation.getCgiPath().size() + 1];
    args[0] = strcpy(args[0], request.getLocation.getCgiPath().c_str());
    args[1] = new char[ + 1];
    args[1] = strcpy(args[1], abs_path.c_str());
    args[2] = NULL;
}

bool    Cgi::checkScriptExists() {

}
