#include "app.hh"
#include "util/fs.hh"

using namespace pl;
using namespace upl;

pl::App::App(int argc, const char* argv[]) {
    getBinaryPath(argc, argv, this->binaryPath);
}
