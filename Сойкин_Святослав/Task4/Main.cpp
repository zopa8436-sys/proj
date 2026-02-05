#include "pch.h"
#include "App.h"

int main() {
    try {
        App app;
        app.run();
    } catch (const std::exception &e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
