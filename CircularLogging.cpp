// CircularLogging.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//
#include <exception>
#include <iostream>
#include <thread>
#include"ConfigReader.h"
#include"CircularLog.h"
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
        
        CircularLog logger(10, "log", 6 , config); // Maksimum 10 log saklayacak şekilde ayarlayın, 60 saniyede bir dosyaya yaz


    }

    catch (std::exception& e) {
        std::cout << "exception ::"<< e.what() << std::endl;
    }

   
}


