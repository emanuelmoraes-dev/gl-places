#include "app.hh"
#include "util/fs.hh"

App::App(int argc, const char* argv[]) {
    getBinaryPath(argc, argv, this->binaryPath);
}
