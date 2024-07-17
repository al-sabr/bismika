#include <saucer/smartview.hpp>
#include <framework/ExtendedFramework.h>

using namespace std;

ExtendedFramework * exFramework = nullptr;

int main()
{

    exFramework = new ExtendedFramework();   

    saucer::smartview smartview;         // Instantiate smartview
    smartview.set_title("bismika framework"); // Set the window title to "Hello World!"

    smartview.set_url("https://google.com"); // Navigate to google.com
    smartview.show();                        // Show the smartview
    smartview.run();                         // And finally enter the run-loop.

    delete exFramework;
    
    return 0;
}