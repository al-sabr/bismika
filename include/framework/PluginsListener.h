#include <cppmicroservices/Bundle.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/BundleImport.h>
#include <cppmicroservices/Framework.h>
#include <cppmicroservices/FrameworkFactory.h>
#include <filesystem>

#include <efsw/efsw.hpp>

class PluginsListener : public efsw::FileWatchListener{
    public:
    PluginsListener(const std::shared_ptr<cppmicroservices::Framework>& fw, std::filesystem::path plugins);
    ~PluginsListener();
    void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, 
                            efsw::Action action, std::string oldFilename ) override;

    private:
    void watchPlugins();

    private:
    efsw::WatchID watchID;
    efsw::FileWatcher* fileWatcher;
    std::filesystem::path plugins_path;
    std::shared_ptr<cppmicroservices::Framework> framework;

};