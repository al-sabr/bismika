#include <ResourcesPluginActivator.h>

using namespace cppmicroservices;

namespace bismika{

    namespace plugins{

        ResourcesPluginActivator::ResourcesPluginActivator(){}

        ResourcesPluginActivator::~ResourcesPluginActivator(){}

        void ResourcesPluginActivator::ResourcesPluginActivator::Start(cppmicroservices::BundleContext context){
            std::cout << "Bundle started";
        }

        void ResourcesPluginActivator::Stop(BundleContext){
            std::cout << "Bundle stopped";
        }

    }
}

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(bismika::plugins::ResourcesPluginActivator)