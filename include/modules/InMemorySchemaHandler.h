#if defined(SAUCER_WEBVIEW2)
    #include <saucer/modules/native/webview2.hpp>
#elif(SAUCER_QT6 || SAUCER_QT5)
    #include <saucer/modules/native/qt.hpp>
#endif

#include <saucer/modules/module.hpp>
#include <cppmicroservices/Framework.h>
#include <cppmicroservices/BundleContext.h>

class InMemorySchemaHandler : public saucer::module{
    public:
    InMemorySchemaHandler(saucer::smartview_core *smartview, cppmicroservices::BundleContext ctx);
    ~InMemorySchemaHandler();
    void init(saucer::native::window *window, saucer::native::webview *webview) override;
    void my_awesome_feature();

    private:
    cppmicroservices::BundleContext ctx;
    saucer::native::window *m_window;
    saucer::native::webview *m_webview;
};