#include <cppmicroservices/BundleActivator.h>

using namespace cppmicroservices;

class ResourcesPluginActivator : public BundleActivator
{
    public:
        ResourcesPluginActivator();
        ~ResourcesPluginActivator();
        void Start(BundleContext ctx);
        void Stop(BundleContext);
};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(ResourcesPluginActivator)