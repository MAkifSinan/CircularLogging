#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include "ConfigReader.h"
class CircularLog
{

public:
    CircularLog(size_t max_size, const std::string& base_filename, int interval_seconds);

    CircularLog(size_t max_size, const std::string & base_filename, int interval_seconds ,const ConfigReader& );
    ~CircularLog();
    void add_data(const std::string & data);

protected:
    ConfigReader Reader;

private:
    void set_logging_settings(std::map<std::string, std::string>)const;
    void start_background_thread();
    void stop_background_thread();
    void write_to_file();

    std::vector<std::string> logs;
    size_t max_size;
    std::mutex mutex;
    std::string log_path; // Yeni eklenen parametre
    std::string base_filename;
    int interval_seconds;
    std::thread background_thread;
    std::atomic<int> counter;
    bool running;
};

