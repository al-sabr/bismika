
#include <modules/InMemorySchemaHandler.h>

InMemorySchemaHandler::InMemorySchemaHandler(saucer::smartview_core *smartview, cppmicroservices::BundleContext ctx) : saucer::module(smartview){
    
    this->ctx = ctx;
    
}

InMemorySchemaHandler::~InMemorySchemaHandler(){

}


void InMemorySchemaHandler::init(saucer::native::window *window, saucer::native::webview *webview)
{
    m_window  = window;
    m_webview = webview;
}

void InMemorySchemaHandler::my_awesome_feature()
{
    m_window->window->setWindowTitle("Hello from Module!");
    m_webview->web_view->page()->setAudioMuted(true);
}
    