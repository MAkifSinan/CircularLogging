#include "CircularLog.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

CircularLog::CircularLog(size_t max_size, const std::string& base_filename, int interval_seconds)
    : max_size(max_size), logs(max_size), base_filename(base_filename), interval_seconds(interval_seconds), counter(0), running(true) {
    std::cout << " CircularLog contructor without config file \n";
}

CircularLog::CircularLog(size_t max_size, const std::string& base_filename, int interval_seconds,const ConfigReader& a):
    max_size(max_size), logs(max_size), base_filename(base_filename), interval_seconds(interval_seconds),Reader(a), counter(0), running(true)
{
    std::cout << " CircularLog contructor with config file \n";
    Reader.printConfig();
}

CircularLog::~CircularLog() {
    stop_background_thread();
}

void CircularLog::add_data(const std::string& data) {
    std::lock_guard<std::mutex> lock(mutex);
    logs.push_back(data + " " + std::to_string(counter++));
    if (logs.size() > max_size) {
        logs.erase(logs.begin());
    }
}


void CircularLog::set_logging_settings(std::map<std::string, std::string> a) const
{

}

void CircularLog::start_background_thread() {
    background_thread = std::thread([this]() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(interval_seconds));
            write_to_file();
        }
        });
}

void CircularLog::stop_background_thread() {
    if (background_thread.joinable()) {
        running = false;
        background_thread.join();
    }
}

void CircularLog::write_to_file() {
    std::lock_guard<std::mutex> lock(mutex);
    log_path = "C:/Users/sinan/Desktop/dsvsvd";
    std::string filename = log_path + "/" + base_filename + "_" + std::to_string(counter) + ".txt";
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        for (const auto& log : logs) {
            file << log << std::endl;
        }
        file.close();
        logs.clear(); // Verileri dosyaya yazdýktan sonra loglarý temizle
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    
}
