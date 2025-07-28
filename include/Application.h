#ifndef APPLICATION_H__
#define APPLICATION_H__

#include "Framework.h"
#include <string>

class Application {
    private:
        std::string name;
        Application *runtimeApp;
        Framework   *framework;

    public:
        Application();

    protected:
        int run( std::string name, Application *app );
};

#endif // APPLICATION_H__
