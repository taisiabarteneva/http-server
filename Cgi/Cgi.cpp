#include "CGI.hpp"

CGI::CGI(Request & req): request(req)
{
    char dir[128];

    getcwd(dir, 128);
    abs_path = string(dir);

    prepareEnv();
    // prepareCGIArgs();
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
        env = rhs.env;
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
    return *this;
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
    std::vector<std::string>    envs;
    int                         i;

    /* 
        CGI environment variables
        CGI scripts are given predefined environment variables that provide information about the web server as well as the client
    */

    /* relative path for the CGI script */
    envs.push_back("PATH_INFO=" + request.getURI());
    /* absolute path for the CGI script */
    envs.push_back("PATH_TRANSLATED=" + abs_path);
    /* URL-encoded information that is sent with GET method request */
    // envs.push_back("QUERY_STRING=" + request);
    /* method used to make the request */
    envs.push_back("REQUEST_METHOD=" + request.getMethod());
    /* data type of the content, used when the client is sending attached content to the server */
    envs.push_back("CONTENT_TYPE=" + request.getHeaderValue("Content-Type"));
    /* length of the query information that is available only for POST requests */
    envs.push_back("CONTENT_LENGTH=" + request.getHeaderValue("Content-Length"));

    env = new char*[envs.size() + 1];
    std::vector<std::string>::iterator it = envs.begin(); i = 0;
    for (; it != envs.end(); it++, i++)
    {
        this->env[i] = new char[it->size() + 1];
        strcpy(env[i], it->c_str()); 
    }
    env[i] = NULL;
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

/*  
    int execve(const char *pathname, char *const argv[], char *const envp[]) 

    - pathname must be either a binary executable or a script 
    - argv is an array of pointers to strings passed to the new program
    as its command-line arguments
    - envp is an array of pointers to strings, conventionally of the
    form key=value
*/

void CGI::handleChildProcess(void)
{
    int inputFd, outputFd;
    int status;

    outputFd = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (outputFd == -1)
    {
        perror("open");
        std::cerr << "[Error] : open() system call failed\n";
        exit(EXIT_FAILURE);
    }
    dup2(outputFd, STDOUT_FILENO);
    status = execve(args[0], &(args[0]), env);
    if (status == -1)
    {
        std::cerr << "[Error] : execve() system call failed\n";
        exit(EXIT_FAILURE);
    }
}

int CGI::start(Location * location)
{   
    int             pid, id;
    int             status;
    std::string     path;
    std::string     scriptFile;

    scriptFile = request.getURI(); // filename // path.substr(path.find_last_of('/' + 1))

    // path = abs_path + "/" + location->getCgiPath() + scriptFile;
    path = "/Users/wurrigon/Desktop/http-server/resources/cgi-bin/test.py";

    std::cout << "Path to CGI file is : [ " << path << " ]\n";
    // args.push_back(scriptFile.c_str());

    if (access(path.c_str(), X_OK) == 0)            /* X_OK used to check for execute permissions on a file */
        args.push_back((char *)path.c_str());
    args.push_back(NULL);

    pid = fork();
    if (pid == -1)
    {
        std::cerr << "[Error] : fork() system call failed\n";
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        handleChildProcess();
    }
    else 
    {
        id = waitpid(-1, &status, WNOHANG);
        if (id == -1)
        {
            std::cerr << "[Error] : waitpid() system call failed\n";
            exit(EXIT_FAILURE);
        }
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 0;
}