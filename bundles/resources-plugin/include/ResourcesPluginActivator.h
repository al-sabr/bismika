#include <cppmicroservices/BundleActivator.h>
#include <resources_plugin_export.h>

using namespace cppmicroservices;

class RESOURCES_PLUGIN_EXPORT ResourcesPluginActivator : public BundleActivator
{
  void Start(BundleContext ctx);

  void Stop(BundleContext);
  
};