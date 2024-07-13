#include <framework/ExtendedFramework.h>

ExtendedFramework::ExtendedFramework(){
    
    this->fw = std::make_shared<cppmicroservices::Framework>(cppmicroservices::FrameworkFactory().NewFramework());

    try {
        // Initialize the framework, such that we can call
        // GetBundleContext() later.
        fw->Init();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }

    // finding and printing the current working directory.
    std::string path = PathInformer::abs_exe_directory();
    
    std::filesystem::path plugins_path = path + "/plugins";
    std::filesystem::file_status status = std::filesystem::status(plugins_path);

    if(!std::filesystem::is_directory(status))
        std::filesystem::create_directories(plugins_path);

    pl = new PluginsListener(fw, plugins_path);

}

ExtendedFramework::~ExtendedFramework(){
    fw = nullptr;
    delete pl;
}