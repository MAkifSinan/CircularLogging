// CircularLoggerging.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//
#include <exception>
#include <iostream>
#include <thread>
#include"ConfigReader.h"
#include"CircularLogger.h"
void yazdir(std::string a)
{

    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
    for (int i = 0; i < 100; i++)
        std::cout << a;

}
int main()
{
    try {
        
        std::cout << "Hello World!\n";
        ConfigReader config("config.txt");
        std::cout << " ***************************\n" << std::endl;
        //config.printConfig();
        
        CircularLogger logger("log2", config); // Maksimum 10 log saklayacak şekilde ayarlayın, 60 saniyede bir dosyaya yaz

        //logger.print_settings();
        logger<"deneme+thread";


        logger.start_background_thread();
        
        logger.stop_background_thread();
    }

    catch (std::exception& e) {
        std::cout << "exception ::"<< e.what() << std::endl;
    }

   
}


