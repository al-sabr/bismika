#include <memory>
#include <filesystem>
#include <iostream>
#include <string>

#include <framework/PluginsListener.h>
#include <framework/PathInformer.h>

#include <cppmicroservices/Bundle.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/BundleImport.h>
#include <cppmicroservices/Framework.h>
#include <cppmicroservices/FrameworkFactory.h>

class ExtendedFramework{
    public:
    ExtendedFramework();
    ~ExtendedFramework();

    protected:
    cppmicroservices::BundleContext ctx;
    
    private:
    // Create a new framework with a default configuration.
    std::shared_ptr<cppmicroservices::Framework> fw = nullptr;
    PluginsListener * pl = nullptr;
};
