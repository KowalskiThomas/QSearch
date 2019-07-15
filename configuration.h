#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QSettings>

enum class OS { Linux, Mac, Windows };

class Configuration
{

public:
    Configuration();

    //Translate the macros to C++ at a single point in the application
    #ifdef __linux__
    static constexpr OS os = OS::Linux;
    #elif __APPLE__
    static constexpr OS os = OS::Mac;
    #elif __WIN32
    static constexpr OS os = OS::Windows;
    #endif

    static constexpr bool caseInsensitive = os == OS::Windows;

};

#endif // CONFIGURATION_H
