#include <saucer/webview.hpp>
#include <saucer/smartview.hpp>

#include <modules/InMemorySchemaHandler.h>

#include <framework/ExtendedFramework.h>

#include <embedded/all.hpp>

ExtendedFramework * exFramework = nullptr;

int main(){

    exFramework = new ExtendedFramework();   

    //saucer::webview::register_scheme("dynamic");
    
    saucer::smartview<saucer::default_serializer, InMemorySchemaHandler> webview;         // Instantiate smartview

    webview.initBundleContext(&exFramework->ctx);
    webview.set_dev_tools(true);
    webview.set_title("bismika framework"); // Set the window title to "Hello World!"
    webview.set_size(500, 600);
    //webview.embed(saucer::embedded::all());
    
    webview.execute(R"js(
        
    )js");

    //webview.serve("bundle1/src/index.html", "dynamic");
    webview.set_url("dynamic://resources-plugin/src/index.html");
    //webview.set_url("saucer:/src/index.html");

    saucer::webview::register_scheme("dynamic");

    webview.show();                        // Show the smartview
    webview.run();                         // And finally enter the run-loop.

    delete exFramework;
    
    return 0;
}