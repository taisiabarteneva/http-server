#include "Cgi.hpp"

CGI::CGI(Request * req, Location * location)
{
    request = req;
    char dir[128];
    getcwd(dir, 128);
    abs_path = string(dir);

    prepareEnv();
    prepareArgs(location);
}

CGI::CGI(const CGI & rhs) 
{
	*this = rhs;
}

const CGI & CGI::operator=(const CGI & rhs)
{
    int     i, len;
    char    **tmp_env;
    char    **tmp_arg;

    /* ToDo : check memory leaks */
    if (this != &rhs)
    {
        request = rhs.request;
        abs_path = rhs.abs_path;

        tmp_arg = new char*[2];
        tmp_arg[0] = new char[strlen(args[0]) + 1];
        strcpy(tmp_arg[0], rhs.args[0]);
        clearArgsArray();
        args = tmp_arg;

        tmp_env = new char*[env_len];
        for (i = 0; i < env_len; i++)
        {
            len = strlen(rhs.env[i]);
            tmp_env[i] = new char[len];
            strcpy(tmp_env[i], rhs.env[i]); 
        }
        env[i] = NULL;
        clearEnvArray();
        env = tmp_env;
    }
    return *this;
}

CGI::~CGI()
{
    if (env)
        clearEnvArray();
    if (args)
        clearArgsArray();
};

/* --------------------------------------------------------- private */
void CGI::clearArgsArray(void)
{
    for (int i = 0; i < 2; ++i) 
    {
        if (args[i])
            delete[] args[i];
    }
    delete[] args;
}

void CGI::clearEnvArray(void)
{
    for (int i = 0; i < env_len; ++i) 
    {
        if (env[i])
            delete[] env[i];
    }
    delete[] env;
}

void    CGI::parseEnvFromRequest(std::vector<std::string> & env)
{
    int             contentLen;
    std::string     body(request->getBuffer());
    std::string     envVar;

    contentLen = atoi(request->getHeaderValue("Content-Length").c_str());
    body.erase(0, body.find_last_of("\r\n") + 1);  /* http-message body */
    
    for (int i = 0; i < contentLen; i++)
    {
        if (body[i] != '&')
            envVar += body[i];
        else
        {
            env.push_back(envVar);
            envVar = "";
        }
    }
    env.push_back(envVar);
    for (std::vector<std::string>::iterator it = env.begin(); it != env.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}

void up(char & c)
{
    toupper(c);
}

void    CGI::prepareEnv(void) 
{
    std::vector<std::string>    envs;
    int                         i;

    /* 
        CGI environment variables
        CGI scripts are given predefined environment variables that provide information about the web server as well as the client
    */

    parseEnvFromRequest(envs);
    /* relative path for the CGI script */
    envs.push_back("PATH_INFO=" + request->getURI());
    /* absolute path for the CGI script */
    envs.push_back("PATH_TRANSLATED=" + abs_path);
    /* URL-encoded information that is sent with GET method request */
    // envs.push_back("QUERY_STRING=" + request);
    /* method used to make the request */
    envs.push_back("REQUEST_METHOD=" + request->getMethod());
    
    std::map<std::string, std::string> headers = request->getHeaders();
    for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); it++)
    {
        std::string tmp = it->first;
        for (char & c : tmp) 
        {
            c = std::toupper(c, std::locale());
        }
        std::cout << "tmp is:" << tmp << std::endl;
        tmp += "=";
        tmp += it->second;
        envs.push_back(tmp);
    }

    env_len = envs.size() + 1;
    env = new char*[env_len];
    std::vector<std::string>::iterator it = envs.begin(); i = 0;
    for (; it != envs.end(); it++, i++)
    {
        this->env[i] = new char[it->size() + 1];
        strcpy(env[i], it->c_str()); 
    }
    env[i] = NULL;
}

void    CGI::prepareArgs(Location* location)
{
    std::string     path, scriptFile, cgiDir;
    
    scriptFile = request->getURI();
    scriptFile.erase(0, scriptFile.find_first_not_of('/'));
    cgiDir = location->getCgiDir();
    if (cgiDir.empty())
        cgiDir = DEFAULT_CGI_DIR;
    path = abs_path + "/" + cgiDir + scriptFile;
        
    std::cout << "Path to CGI file is : [ " << path << " ]\n";

    args = new char*[2];
    args[0] = new char[path.size() + 1];
    if (access(path.c_str(), X_OK) == 0)        /* X_OK used to check for execute permissions on a file */
        args[0] = strcpy(args[0], path.c_str());
    // else ?
    args[1] = NULL;
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

int CGI::start()
{   
    int             pid, id;
    int             status;

    pid = fork();
    if (pid == -1)
    {
        std::cerr << "[Error] : fork() system call failed\n";
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
        handleChildProcess();
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