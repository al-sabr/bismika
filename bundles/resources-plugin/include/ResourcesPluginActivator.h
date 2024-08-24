#include <cppmicroservices/BundleActivator.h>
#include <resources_plugin_export.h>

using namespace cppmicroservices;

namespace {

    class ResourcesPluginActivator : public BundleActivator
    {
        public:
            void Start(BundleContext ctx){
                std::cout << "Bundle started";
            }

            void Stop(BundleContext){
                std::cout << "Bundle stopped";
            }
    };

}

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(ResourcesPluginActivator)