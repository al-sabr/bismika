#include <FractalPluginActivator.h>

using namespace cppmicroservices;

namespace bismika{

    namespace plugins{

        FractalPluginActivator::ResourcesPluginActivator(){}

        FractalPluginActivator::~ResourcesPluginActivator(){}

        void FractalPluginActivator::Start(cppmicroservices::BundleContext context){
            std::cout << "Bundle started";
        }

        void FractalPluginActivator::Stop(BundleContext){
            std::cout << "Bundle stopped";
        }

    }
}

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(bismika::plugins::FractalPluginActivator)