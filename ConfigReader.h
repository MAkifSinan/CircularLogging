#pragma once
/**
 * @file ConfigReader.h
 * @brief ConfigReader Header file containing the ConfigReader class.
 */
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <map>



 /**
  * @class ConfigReader
  * @brief A class that provides reading data from a text file which use for taking configuration settings
  */
class ConfigReader {
private:
    std::map<std::string, std::string> configMap;
    std::string configFileName;
    bool ConfigFileStatus ;

 public:
     /**
* @brief Constructor for ConfigReader class.
* @param No parameter needs for manuel config file name. After this constructor uses driver code MUST use setConfigFileName func to provide filename.
*/
    ConfigReader();    
    /**
* @brief ConfigReader for ConfigReader class.
* @param This constructor creates object within config file. 
*/
    ConfigReader(std::string filename);
 
 /**
* @brief Reads config file.
* @return A bool return type any error cause false return of this function.
*/
    bool readConfigFile(const std::string& filename);
    /**
   * @brief Sets config file.
   * @param This function sets Config filename. 
   */
    void setConfigFileName(const std::string filename);

    /**
* @brief Gets value from config map by using key string.
* @param Necessary key parameters to find data in Config datas.
* @return A string which is belongs to key parameters.
*/
    std::string getValue(const std::string& key) const;
 /**
* @brief Gets config filename.
*/
    std::string getConfigFileName() const;

/**
* @brief Gets config file.
* @return Returns all config datas by map data type.
*/
    std::map<std::string, std::string> getConfigs(void) const;
 /**
* @brief Prints all data in config file.
*/
    void printConfig() const;


};


