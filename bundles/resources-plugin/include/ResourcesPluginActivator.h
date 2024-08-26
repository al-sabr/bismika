#ifndef RESOURCESPLUGINSACTIVATOR_HPP
#define RESOURCESPLUGINSACTIVATOR_HPP

#include <cppmicroservices/BundleActivator.h>
#include <resources_plugin_export.h>

using namespace cppmicroservices;

namespace bismika{

    namespace plugins{

        class ResourcesPluginActivator final : public BundleActivator
        {
            public:
                ResourcesPluginActivator() override;
                ~ResourcesPluginActivator() override;

                void Start(cppmicroservices::BundleContext context) override;
                void Stop(BundleContext) override;
        };
    }
}

#endif