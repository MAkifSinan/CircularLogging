// CircularLogging.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//
#include <exception>
#include <iostream>
#include"ConfigReader.h"
int main()
{
    try {
        std::cout << "Hello World!\n";
        ConfigReader config("config.txt");
        std::cout << " ***************************\n" << std::endl;
        config.printConfig();


        return 0;
    }

    catch (std::exception& e) {
        std::cout << " exception ::"<< e.what() << std::endl;
    }
    /*
    if (configReader.readConfigFile("config.txt")) {
        configReader.printConfig();
    }
    */
   
}
