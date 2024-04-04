#include "ConfigReader.h"


ConfigReader::ConfigReader() {

}

ConfigReader::ConfigReader(std::string config_file_name) {
    setConfigFileName(config_file_name);
    readConfigFile(getConfigFileName());
    
    if (ConfigFileStatus == false)
        throw std::runtime_error("config file error");
}
void ConfigReader::setConfigFileName(const std::string a) {
    configFileName = a;
}

// Config dosyasýný okuyan fonksiyon
bool ConfigReader::readConfigFile(const std::string& filename) {
    std::ifstream configFile(filename);
    if (!configFile.is_open()) {
        std::cerr << "Error: Unable to open config file: " << filename << std::endl;
        ConfigFileStatus = false;
        return false;
    }
    std::string line;
    while (std::getline(configFile, line)) {
        size_t delimiterPos = line.find('=');
        size_t posOfComment = line.find('#');
        if (delimiterPos != std::string::npos && posOfComment ==std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            // Boþluklarý temizle
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            // Anahtar-deðer çiftini ekle
            configMap[key] = value;
        }
    }
    configFile.close();
    ConfigFileStatus = true;
    return true;
    
}


std::string  ConfigReader::getValue(const std::string& key) const {
    auto it = configMap.find(key);
    if (it != configMap.end()) {
        return it->second;
    }
    else {
        return ""; 
    }
}

std::string ConfigReader::getConfigFileName() const {
    return configFileName;
}

std::map<std::string, std::string> ConfigReader::getConfigs(void) const {
    return configMap;
}



void  ConfigReader::printConfig() const {
    for (const auto& pair : configMap) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }
}