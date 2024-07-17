#include <saucer/smartview.hpp>
#include <saucer/webview.hpp>

#include <framework/ExtendedFramework.h>
#include <modules/InMemorySchemaHandler.h>

#include <embedded/all.hpp>

using namespace std;

ExtendedFramework * exFramework = nullptr;

int main()
{

    exFramework = new ExtendedFramework();   

    //saucer::webview webview;
    saucer::smartview<saucer::default_serializer, InMemorySchemaHandler> webview;         // Instantiate smartview
    webview.set_title("bismika framework"); // Set the window title to "Hello World!"
    webview.embed(saucer::embedded::all());
    webview.set_size(500, 600);

    webview.execute(R"js(
        const text = document.createElement('p');
        text.innerText = "Padabummmmm!";

        document.body.append(text);
    )js");

    webview.serve("src/index.html");
    webview.set_dev_tools(true);

    //smartview.set_url("https://google.com"); // Navigate to google.com
    webview.show();                        // Show the smartview
    webview.run();                         // And finally enter the run-loop.

    delete exFramework;
    
    return 0;
}