#include "CGI.hpp"

CGI::CGI(Request & req): request(req)
{
    char dir[MAXDIR];

    getcwd(dir, MAX_DIR);
    abs_path = string(dir);

    prepareCGIEnv();    
    prepareCGIArgs();
}

CGI::CGI(const CGI & rhs) 
{
	*this = rhs;
}

const CGI & CGI::operator=(const CGI & rhs)
{
    /* check memory leaks */
    if (this != &rhs)
    {
        request = rhs.request;
        abs_path = rhs.abs_path;

        args = rhs.args;
        envs = rhs.envs;
        // clearArgsArray();
        // this->args = new char*[3];
        // for (int i = 0; i < 3; i++)
        // {
        //     args[i] = new char*[rhs.args[i].size() + 1];
        //     strcpy(this->args[i], rhs.args[i]);
        // }
        // args[i] = NULL;

        // clearEnvArray();
        // this->env = new char*[rhs.env.size() + 1];
        // for (int i = 0; i < rhs.env.size(); i++)
        // {
        //     env[i] = new char[rhs.env[i].size() + 1];
        //     strcpy(this->env[i], rhs.env[i]); 
        // }
        // env[i] = NULL;
    }
}

CGI::~CGI() 
{
    // if (env)
    //     clearEnvArray();
    // if (args)
    //     clearArgsArray();
};

/* --------------------------------------------------------- private */
// void CGI::clearArgsArray(void)
// {
//     for (int i = 0; i < args.size(); ++i) 
//     {
//         delete[] args[i];
//     }
//     delete[] args;
// }

// void CGI::clearEnvArray(void)
// {
//     for (int i = 0; i < env.size(); ++i) 
//     {
//         delete[] env[i];
//     }
//     delete[] env;
// }

void    CGI::prepareEnv(void) 
{
    // std::vector<std::string>             envs;
    // int i;

    /* 
        CGI environment variables
        CGI scripts are given predefined environment variables that provide information about the web server as well as the client
    */

    /* relative path for the CGI script */
    envs.push_back("PATH_INFO=" + request.getURI());
    /* absolute path for the CGI script */
    envs.push_back("PATH_TRANSLATED=" + abs_path);
    /* URL-encoded information that is sent with GET method request */
    envs.push_back("QUERY_STRING=" + request.getQueryString());
    /* method used to make the request */
    envs.push_back("REQUEST_METHOD=" + request.getMethod());
    /* data type of the content, used when the client is sending attached content to the server */
    envs.push_back("CONTENT_TYPE=" + request.getHeaderValue("Content-Type"));
    /* length of the query information that is available only for POST requests */
    envs.push_back("CONTENT_LENGTH=" + request.getHeaderValue("Content-Length"));

    // this->env = new char*[envs.size() + 1];
    // std::vector<std::string>::iterator it = env.begin(); i = 0;
    // for (; it != env.end(); it++; i++)
    // {
    //     this->env[i] = new char[it->size() + 1];
    //     strcpy(this->env[i], it->c_str()); 
    // }
    // env[i] = NULL;
}

void    CGI::prepareArgs(void)
{
    // args = new char*[3];
    // args[0] = new char[request.getLocation.getCGIPath().size() + 1];
    // args[0] = strcpy(args[0], request.getLocation.getCGIPath().c_str());
    // args[1] = new char[abs_path.size() + 1];
    // args[1] = strcpy(args[1], abs_path.c_str());
    // args[2] = NULL;
}

void CGI::start(Location * location)
{   
    int             pid;
    int             status;
    std::string     path;
    std::string     scriptFile;

    path = location->getCgiPath();
    scriptFile = path.substr(path.find_last_of('/' + 1)); 
    args.push_back(scriptFile.c_str());
    /* X_OK used to check for execute permissions on a file */
    if (access(path, X_OK) == 0)
        args.push_back(path.c_str());

    /* execve(scriptfile, args, env) */
}