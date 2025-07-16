#include "Application.h"

int main()
{
    Application app;
    if (!app.init()) return -1;
    app.run();
    return 0;
}