#include <cppmicroservices/BundleActivator.h>
#include <resources_plugin_export.h>

using namespace cppmicroservices;

//namespace {

    class ResourcesPluginActivator : public BundleActivator
    {
        public:
            void Start(cppmicroservices::BundleContext context) override {
                std::cout << "Bundle started";
            }

            void Stop(BundleContext) override {
                std::cout << "Bundle stopped";
            }
    };

//}

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(ResourcesPluginActivator)