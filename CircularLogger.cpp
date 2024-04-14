#include "CircularLogger.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <typeinfo>  //for 'typeid' to work  

CircularLogger::CircularLogger(const std::string& base_filename)
    : base_filename(base_filename){
    std::cout << " CircularLogger contructor without config file \n";
    // requier setting configs!!!!!!!!!!!
}

CircularLogger::CircularLogger(  const std::string& base_filename,  const ConfigReader& a):
    base_filename(base_filename), Reader(a) , stop_thread(false)
{
    //std::cout << " CircularLogger contructor with config file \n";
    set_logging_settings(Reader.getConfigs());
    
    //Reader.printConfig();
}

CircularLogger::~CircularLogger() {
    stop_background_thread();
}

void CircularLogger::add_data(const std::string& data) {


}

void CircularLogger::operator<(std::string str)  {
    std::string current_time = get_current_time();
    std::string total_info= "Log added at:" + current_time + "\tInfo:" +str ;
    LogsDatas.push_back(total_info);
}

std::string CircularLogger::get_current_time()
{
    // Þu anki zamaný al
    std::time_t now;
    std::time(&now);

    // Yerel saat bilgilerini doldur
    std::tm time_info;
    localtime_s(&time_info, &now);

    // Zamaný bir stringe dönüþtür
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &time_info);

    return std::string(buffer);
}

void CircularLogger::set_logging_settings(std::map<std::string, std::string> a)
{
    std::map<std::string, std::string>::iterator it;
    for (it = a.begin(); it != a.end(); ++it) {
        //std::cout << it->first << " : " << it->second << "\n"; //data kontorlu 
        settings[it->first] = it->second;
    }
    /*
    std::cout << " burada hata bekleniyor  \n";
    std::cout << "getValue(UseLogThread) :"  << check_config_data(getValue("UseLogThread")) << "\n";
    
    max_size = std::stoi(check_config_data(getValue("MaxLogSize")));
    logging_frequency = std::stoi(check_config_data(getValue("LoggingFrequency")));
    logging_type = check_config_data(getValue("LoggingCircle"));
    file_Output_path_for_Logs = check_config_data((getValue("OutputDest")));
   
    use_thread_for_Log = std::stoi(check_config_data(getValue("UseLogThread")));
     */

    verified_settings["max_size"]=(check_config_data(getValue("MaxLogSize")));

    verified_settings["logging_frequency"]= (check_config_data(getValue("LoggingFrequency")));

    verified_settings["logging_type"]= check_config_data(getValue("LoggingCircle"));

    verified_settings["file_Output_path_for_Logs"]= check_config_data((getValue("OutputDest")));

    verified_settings["use_thread_for_Log"]= (check_config_data(getValue("UseLogThread")));

}

void CircularLogger::print_settings(void) const
{
    std::cout << "********************************************* \n";

    for (const auto& pair : verified_settings)
        std::cout << pair.first << " : " << pair.second << " \n";
}

std::string CircularLogger::getValue(const std::string& key) const
{
    auto it = settings.find(key);
    if (it != settings.end()) {
        return it->second;
    }
    else {
        return ""; // null mý yapsam ?
    }
}

void CircularLogger::start_background_thread() {
    // Baþlatýlmýþsa, iþ parçacýðýný yeniden baþlatmayýn
    if (background_thread.joinable()) {
        std::cerr << "Arka plan iþ parçacýðý zaten baþlatýldý!" << std::endl;
        return;
    }
    stop_thread = false;
    // Ýþ parçacýðýný baþlat
    background_thread = std::thread([this] {
        // Durdurulana kadar çalýþ
        int a = 0;
        while (true) {
            // Loglama iþlemini yapabilirsiniz
            // Örneðin:
            write_to_file(a);
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Belirli bir süre bekleyin
            a++;
        }
        });
}

void CircularLogger::stop_background_thread() {
    // Ýþ parçacýðý baþlatýlmamýþsa, iþlem yapma
    if (!background_thread.joinable()) {
        std::cerr << "Arka plan iþ parçacýðý zaten baþlatýlmadý!" << std::endl;
        return;
    }

    // Ýþ parçacýðýný durdur
    stop_thread = true;

    // Ýþ parçacýðýnýn tamamlanmasýný bekle
    if (background_thread.joinable())
        background_thread.join();

    // Ýþ parçacýðý durdurulduktan sonra bayraðý sýfýrla
    stop_thread = false;
}

int CircularLogger::write_to_file(int a) {


    std::string folder_name = getValue("OutputDest");  // foldername yerine folder path daha doðru ayrýca " ve \ düzenlemei yapýalbilinir
            
    std::string filename = folder_name + "/" + base_filename+ std::to_string(a) + ".txt"; // basefilename de .txt yok sonradan eklenir yada validate edilebilir
    std::cout << "filename:" << filename<<"\n";
    // Dosyanýn var olup olmadýðýný kontrol edin
    if (!file_exists(folder_name)) {
        // Klasör yoksa oluþturun
        if (!create_directory(folder_name)) {
            std::cerr << "Klasör oluþturulamadý!" << std::endl;
            return 1; // Baþarýsýz çýkýþ
        }
    }

    // Dosyayý açýn
    std::ofstream file(filename);

    // Dosya açýlma kontrolü yapýn
    if (!file.is_open()) {
        std::cerr << "Dosya açýlamadý!" << std::endl;
        return 1; // Baþarýsýz çýkýþ
    }

    // Dosyaya yazýlacak veriyi belirleyin
    std::string firstline ="*****************************\nFile name :"+base_filename+"\nStartDate: "
        + get_current_time() + "\n";

    // Veriyi dosyaya yazýn
    file << firstline;
    for (const auto& data : LogsDatas) {
        file << "Date:" << "----" << data<<"\n";
    }
    // Dosyayý kapatýn
    file.close();

    std::cout << "Veri baþarýyla dosyaya yazýldý: " << filename << std::endl;


}

bool CircularLogger::create_directory(const std::string& path)
{
    try {
        fs::create_directories(path);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Klasör oluþturulamadý: " << e.what() << std::endl;
        return false;
    } 
}

bool CircularLogger::file_exists(const std::string& filename) {
    return fs::exists(filename);
}

int CircularLogger::check_config_data(int b)
{
    if (b == NULL)
        return -999;
    else
        return b;
}

std::string CircularLogger::check_config_data(std::string a)
{
    if (a.empty())
        return "-999";
    else
        return a;
}


