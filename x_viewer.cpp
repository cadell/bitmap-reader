//#include <X11/Xlib.h>
#include <X11/Xlib.h>
#include <iostream>

/*To create a display window on x we need to connect to the X-server with the display function,
 * Next we create a child window whith inherited properties from the root window that is created when you connect to the X server?
 * this is followed by mapping the window which displays the window ? followed by a flush for us not to exit the program we need a random loop to hold the window*/
int main()
{
    auto display = XOpenDisplay(NULL); // contains all the information about the x server and stuff
    // we need to pass the root window as a parameter and thats what XROOTWINDOW method returns,copy stuff from parent and set the rest of the parameters to 0
    auto window  = XCreateWindow(display,XRootWindow(display,0),0,0,500,500,1,0,CopyFromParent,CopyFromParent,0,0);
    //show the display
    XMapWindow(display, window);
    XFlush(display); //display wont actually show until we flush the display buffer.... 
    while(1); //while loop to prevent the display from closing
    return 0;
}
