#include<ResourcesPluginActivator.h>

using namespace cppmicroservices;

void ResourcesPluginActivator::Start(BundleContext ctx){
}

void ResourcesPluginActivator::Stop(BundleContext){
}

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(ResourcesPluginActivator)

#include <cppmicroservices_init.cpp>
