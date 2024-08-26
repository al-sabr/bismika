#ifndef FRACTALPLUGINSACTIVATOR_HPP
#define FRACTALPLUGINSACTIVATOR_HPP

#include <cppmicroservices/BundleActivator.h>
#include <fractal_plugin_export.h>

using namespace cppmicroservices;

namespace bismika{

    namespace plugins{

        class FractalPluginActivator final : public BundleActivator
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