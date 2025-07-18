#include "BirdGeneratorApp.h"

int main()
{
    BirdGeneratorApp app;
    if (!app.init()) return -1;
    app.run();
    return 0;
}