#ifndef _CSCREEN_
#define _CSCREEN_

#include <SFML/Graphics.hpp>


// SFML way for having multiple screens
class cScreen {
    public :
        virtual int Run () = 0;
};

#endif