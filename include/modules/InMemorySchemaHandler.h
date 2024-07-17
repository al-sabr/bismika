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
    ~InMemorySchemaHandler(){

    };
    
    InMemorySchemaHandler(saucer::smartview_core *smartview) : saucer::module(smartview){
        
    };

    template <typename Serializer, typename... Modules>
    InMemorySchemaHandler(saucer::smartview<Serializer, Modules...> *smartview) : saucer::module(smartview)
    {
        smartview->expose("module_add", [](int a, int b) { return a + b; });
    }

    void init(saucer::native::window *window, saucer::native::webview *webview) override
    {
        m_window  = window;
        m_webview = webview;
    }

    void initBundleContext(cppmicroservices::BundleContext *ctx)
    {
        this->ctx = ctx;
    }

    void my_awesome_feature()
    {
        m_window->window->setWindowTitle("Hello from Module!");
        m_webview->web_view->page()->setAudioMuted(true);
    }

    private:
    cppmicroservices::BundleContext *ctx;
    saucer::native::window *m_window;
    saucer::native::webview *m_webview;
};