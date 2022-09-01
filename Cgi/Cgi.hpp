#ifndef     CGI_HPP
# define    CGI_HPP

# include   <unistd.h>
# include   <fcntl.h>
# include   <string>
# include   <vector> 

# include "../Http/Request.hpp"
# include "../Parser/Location.hpp"

# define TMP_FILE "cgi.serv"

class CGI
{
    private:
        Request                     request;
        std::string                 abs_path;
        char**                      env;
        std::vector<char *>         args;
    
    public:
        CGI();
        CGI(Request & req);
        CGI(const CGI & rhs);
        const CGI &operator=(const CGI & rhs);
        ~CGI();
        int            start(Location * location);

    private:
        // void            clearArgsArray(void);
        // void            clearEnvArray(void);
        void            prepareEnv(void);
        void            prepareArgs(void);
        void            handleChildProcess(void);
};

#endif
