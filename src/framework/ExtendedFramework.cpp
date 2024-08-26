
#include <vector>
#include <framework/ExtendedFramework.h>
#include <cppmicroservices/Bundle.h>

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

    // Retrieve the bundle context.
    this->ctx = this->fw->GetBundleContext();

    // finding and printing the current working directory.
    std::string path = PathInformer::abs_exe_directory();
    
    std::string initial_plugins_folder = path + "/plugins";
    std::filesystem::path plugins_path = initial_plugins_folder;
    std::vector<std::string> init_plugins = {initial_plugins_folder + "/libfractal_plugin.so", initial_plugins_folder + "/libresources_plugin.so"};
    std::filesystem::file_status status = std::filesystem::status(plugins_path);

    if(!std::filesystem::is_directory(status))
        std::filesystem::create_directories(plugins_path);

    pl = new PluginsListener(fw, plugins_path);

    try
    {
        for(auto const &bundle : init_plugins){
            this->ctx.InstallBundles(bundle);
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        // Start the framwork itself.
        fw->Start();

        // Our bundles depend on each other in the sense that the consumer
        // bundle expects a ServiceTime service in its activator Start()
        // function. This is done here for simplicity, but is actually
        // bad practice.
        std::vector<cppmicroservices::Bundle> bundles = this->ctx.GetBundles();
        for_each(bundles.begin(), bundles.end(), [](cppmicroservices::Bundle & bundle){
            try{
                bundle.Start();
            }catch (std::exception const& e)
            {
                std::cerr << e.what() << std::endl;
            }
        });
        
    } catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

ExtendedFramework::~ExtendedFramework(){
    fw->Stop();
    fw = nullptr;
    delete pl;
}