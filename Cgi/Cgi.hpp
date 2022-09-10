#ifndef     CGI_HPP
# define    CGI_HPP

# include   <algorithm>
# include   <unistd.h>
# include   <fcntl.h>
# include   <string>
# include   <vector>

# include "../Http/Request.hpp"
# include "../Parser/Location.hpp"

# define TMP_FILE           "resources/cgi.serv"
# define DEFAULT_CGI_DIR    "resources/cgi-bin/"

class CGI
{
    private:
        Request*                     request;
        std::string                 abs_path;
        char**                      env;
        char**                      args;
        int                         env_len;
    
    public:
        CGI();
        CGI(Request * req, Location *location);
        CGI(const CGI & rhs);
        const CGI &operator=(const CGI & rhs);
        ~CGI();
        int            start();

    private:
        void            clearArgsArray(void);
        void            clearEnvArray(void);
        void            prepareEnv(void);
        void            prepareArgs(Location* location);
        void            handleChildProcess(void);
        void            parseEnvFromRequest(std::vector<std::string> & env);
};

#endif
