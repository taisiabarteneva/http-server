#ifndef     CGI_HPP
# define    CGI_HPP

# include   <dir.h>
# include   <vector>
 
#include "../Http/Request.hpp"

class CGI
{
    private:
        Request                     request;
        std::string                 abs_path;
        std::vector<std::string>    envs;
        std::vector<char *>         args;
    
    public:
        CGI();
        CGI(const CGI & rhs);
        const CGI &operator=(const CGI & rhs);
        ~CGI();
        void            start();

    private:
        // void            clearArgsArray(void);
        // void            clearEnvArray(void);
        void            prepareEnv(void);
        void            prepareArgs(void);
};

#endif
