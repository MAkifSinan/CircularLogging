#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include <thread>
#include <mutex>

#include <ctime>

#include "ConfigReader.h"

class CircularLogger
{

public:
    CircularLogger( const std::string& base_filename );

    CircularLogger(const std::string& base_filename,const ConfigReader&);
    ~CircularLogger();
    void add_data(const std::string& data);
    void print_settings(void)const;
    void operator<(std::string str);

protected:
    ConfigReader Reader;

private:
    std::string get_current_time();
    void set_logging_settings(std::map<std::string, std::string> a);
    std::string getValue(const std::string& key) const;
    int check_config_data(int);
    std::string check_config_data(std::string);
    void start_background_thread();
    void stop_background_thread();
    void write_to_file();


    std::vector<std::string> LogFiles; // to cehck total og files.
    std::vector<std::string> LogsDatas; // to hold data which want to save
    int max_size;
    int logging_frequency;
    std::string logging_type;
    bool use_thread_for_Log;
    std::string file_Output_path_for_Logs;
    std::string log_path; // Yeni eklenen parametre
    std::string base_filename;
    int interval_seconds;
    std::map<std::string, std::string> settings;
    std::map<std::string, std::string> verified_settings;

    bool running;
};

