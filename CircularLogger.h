#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include <string>
#include <vector>
#include <ctime>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "ConfigReader.h"

namespace fs = std::experimental::filesystem;


class CircularLogger
{
public:
    CircularLogger( const std::string& base_filename );
    CircularLogger(const std::string& base_filename,const ConfigReader&);
    ~CircularLogger();
    void add_data(const std::string& data);
    void print_settings(void)const;
    void operator<(std::string str);
    int write_to_file(int a=0);
    void start_background_thread();
    void stop_background_thread();
protected:
    ConfigReader Reader;

private:
    std::string get_current_time();
    void set_logging_settings(std::map<std::string, std::string> a);
    std::string getValue(const std::string& key) const;
    int check_config_data(int);
    std::string check_config_data(std::string);


    bool file_exists(const std::string& filename);
    bool create_directory(const std::string& path);

    std::vector<std::string> LogFiles; // to cehck total og files.
    std::vector<std::string> LogsDatas; // to hold data which want to save

    int max_size;
    int logging_frequency;
    std::string logging_type;
    bool use_thread_for_Log;
    std::string file_Output_path_for_Logs;

    std::string log_path; // Yeni eklenen parametre
    std::string base_filename;

    std::thread background_thread;
    std::mutex mtx;
    std::condition_variable cv;
    int interval_seconds;

    std::map<std::string, std::string> settings;
    std::map<std::string, std::string> verified_settings;

    bool running;
    bool stop_thread ;
};

