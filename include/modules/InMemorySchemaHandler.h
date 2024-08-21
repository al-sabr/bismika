#if defined(SAUCER_WEBVIEW2)
    #include <saucer/modules/native/webview2.hpp>
#elif(SAUCER_QT6 || SAUCER_QT5)
    #include <saucer/modules/native/qt.hpp>
#endif

#include <iostream>

#include <QByteArray>
#include <QWebEngineProfile>
#include <QWebEngineUrlScheme>
#include <QWebEngineUrlRequestJob>
#include <QWebEngineUrlSchemeHandler>

#include <saucer/modules/module.hpp>

#include <cppmicroservices/Bundle.h>
#include <cppmicroservices/Framework.h>
#include <cppmicroservices/BundleResource.h>
#include <cppmicroservices/BundleResourceStream.h>
#include <cppmicroservices/BundleContext.h>

#include <utils/StringUtils.h>
#include <utils/MimeTypes.h>

using namespace cppmicroservices;

class InMemorySchemaHandler : public saucer::module{

    public:
    InMemorySchemaHandler(saucer::smartview_core *smartview) : saucer::module(smartview){}

    template <typename Serializer, typename... Modules>
    InMemorySchemaHandler(saucer::smartview<Serializer, Modules...> *smartview) : saucer::module(smartview)
    {
        this->m_smartview = reinterpret_cast<saucer::smartview_core *>(smartview);
    }

    void init(saucer::native::window *window, saucer::native::webview *webview) override
    {
        m_window  = window;
        m_webview = webview;
    }

    void initBundleContext(cppmicroservices::BundleContext *ctx)
    {
        this->ctx = ctx;

        this->m_smartview->handle_scheme("dynamic", [this](const saucer::request &req) -> saucer::scheme_handler::result_type{

                std::vector<cppmicroservices::Bundle> bundles = this->ctx->GetBundles();

               	std::cout << "User requested url: " << req.url() << std::endl;

                //std::vector<std::string> infos = this->splitString((char*)request.url().c_str(), (char*)"://");
                std::vector<std::string> request = stringutils::split(req.url(), "://");
                std::vector<std::string> paths = stringutils::split(request.at(1), "/");
                std::string bundleName = paths.at(0); paths.erase(paths.begin());
                std::string filePath = stringutils::join(paths, "/");

                std::string file;
                std::string mime;

                cppmicroservices::Bundle foundBundle;

                for (auto const& bundle : bundles) {
                    if(bundle.GetSymbolicName() != bundleName)
                        continue;
                    if (bundle.GetState() == Bundle::STATE_UNINSTALLED)
                        continue;
                    foundBundle = bundle;
                    break;              
                }

                if (!foundBundle){
                    file = R"html(<!DOCTYPE html> <html> <body> <h1>Bundle not found</h1> </body> </html>)html";
                    mime = "text/html";
                }else{
                    auto headers = foundBundle.GetHeaders();
                    auto iter = headers.find("service-component");
                    std::string componentPath = (iter == headers.end()) ? std::string() : iter->second.ToString();
                    if (!componentPath.empty())
                    {
                        std::cout << "service-component found" << std::endl;
                    }
                    
                    BundleResource componentResource = foundBundle.GetResource(filePath);
                    
                    if (!componentResource.IsValid() || componentResource.IsDir()){
                        std::string msg= R"html(<!DOCTYPE html> <html> <body> <h1>Invalid resource file</h1> </body>)html";
                        file = msg;
                        mime = "text/html";
                    }else{
                        BundleResourceStream resStream(componentResource);
                        std::string data(std::istreambuf_iterator<char>(resStream), {});
                        file = data;
                        mime = MimeTypes::getType(filePath.c_str());
                    }
                }

                return saucer::response{
                    .data = saucer::stash<>::from({file.begin(), file.end()}), //saucer::make_stash(file),
                    .mime = mime,
                };
            }
        );

    }

    cppmicroservices::BundleContext * getBundleContext(){
        return ctx;
    }

    private:

    cppmicroservices::BundleContext *ctx;
    saucer::native::window *m_window;
    saucer::native::webview *m_webview;
    saucer::smartview_core *m_smartview;
};

