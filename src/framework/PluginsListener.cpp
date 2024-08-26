#include "cppmicroservices/Bundle.h"
#include "framework/PluginsListener.h"

PluginsListener::PluginsListener(const std::shared_ptr<cppmicroservices::Framework>& fw, std::filesystem::path plugins_path){

    this->framework = fw;
    this->plugins_path = plugins_path;
    // The framework inherits from the Bundle class; it is
    // itself a bundle.
    auto ctx = this->framework->GetBundleContext();
    if (!ctx) {
        std::cerr << "Invalid framework context" << std::endl;
    }

    try {
        // Start the framwork itself.
        this->framework->Start();

        // Our bundles depend on each other in the sense that the consumer
        // bundle expects a ServiceTime service in its activator Start()
        // function. This is done here for simplicity, but is actually
        // bad practice.
        auto bundles = ctx.GetBundles();
        
        // Now start all bundles.
        for (auto& bundle : bundles) {
            bundle.Start();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    watchPlugins();
}

void PluginsListener::watchPlugins(){

    // Create the file system watcher instance
    // efsw::FileWatcher allow a first boolean parameter that indicates if it should start with the
    // generic file watcher instead of the platform specific backend
    fileWatcher = new efsw::FileWatcher();

    // Add a folder to watch, and get the efsw::WatchID
    // It will watch the /tmp folder recursively ( the third parameter indicates that is recursive )
    // Reporting the files and directories changes to the instance of the listener
    watchID = fileWatcher->addWatch(plugins_path.c_str(), this, true);

    // Start watching asynchronously the directories
    fileWatcher->watch();

}

PluginsListener::~PluginsListener(){
    if(watchID > 0){
        // Remove the second watcher added
        // You can also call removeWatch by passing the watch path ( it must end with an slash or backslash
        // in windows, since that's how internally it's saved )
        fileWatcher->removeWatch(watchID);
    }
}

void PluginsListener::handleFileAction(efsw::WatchID watchid, const std::string& dir,
                           const std::string& filename, efsw::Action action,
                           std::string oldFilename ){
        switch ( action ) {
            case efsw::Actions::Add:
            case efsw::Actions::Modified:
                std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Added or Modified "
                          << std::endl;
                try
                {
                    std::vector<cppmicroservices::Bundle> installedBundles = this->framework->GetBundleContext().InstallBundles(dir + filename);
                    for(cppmicroservices::Bundle bundle : installedBundles)
                        if(bundle.GetState() == cppmicroservices::Bundle::STATE_INSTALLED)
                            bundle.Start();
                }
                catch (std::exception &exc)
                {
                    std::cerr << exc.what() << std::endl;;
                }
                
                break;
            case efsw::Actions::Delete:
                std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Delete"
                          << std::endl;
                break;
            
            case efsw::Actions::Moved:
                std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Moved from ("
                          << oldFilename << ")" << std::endl;
                break;
            default:
                std::cout << "Should never happen!" << std::endl;
        }
    }