/*
 * ndi-player
 * ndi-player.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// Standard includes
#include <cstdlib>
#include <memory>

// Unix includes
#include <unistd.h>

// local includes
#include "glfwwindow.hpp"
#include "ndireciever.hpp"

typedef struct CommandLineArguments {
    std::string mdns;
    std::string source;
} COMMANDLINEARGUMENTS, *PCOMMANDLINEARGUMENTS;

void Usage(const char *const argv0) {
    printf("\n%s\n"
            "\t-m mdns_name\n"
            "\t-s ndi_source\n\n", argv0);
}

// Process command line arguments
ERRORTYPE ParseCommandLineArguments(COMMANDLINEARGUMENTS &cmdlineargs, int argc, char **argv) {

    int opt = 0;
    while ((opt = getopt(argc, argv, "m:s:h")) != -1) {
        switch (opt) {
            case 'm':
                cmdlineargs.mdns = std::string(optarg);
                break;
            case 's':
                cmdlineargs.source = std::string(optarg);
                break;
            case 'h':
            default:
                return FAILED;
        }
    }

    return SUCCESSFUL;
}


int main(int argc, char **argv) {
    COMMANDLINEARGUMENTS cmdlineargs;
    if(!ParseCommandLineArguments(cmdlineargs, argc, argv)) {
        Usage(argv[0]);
        return EXIT_FAILURE;
    }

    AV::AvErrorCode averr;
    Window::GlfwErrorCode werr;
    std::shared_ptr<AV::NDIReciever> ndi_reciever;
    std::shared_ptr<Window::GLFWWindow> window;

    // Create NDI Reciever
    if(cmdlineargs.mdns == "" && cmdlineargs.source == "") {
        ndi_reciever = std::make_shared<AV::NDIReciever>();
    } else {
        ndi_reciever = std::make_shared<AV::NDIReciever>(cmdlineargs.mdns, cmdlineargs.source);
    }
    
    if((averr = ndi_reciever->GetLastError()) != AV::AvErrorCode::NoError)
        FATAL("%s", AV::AvErrorStr(averr).c_str());

    // Create window
    window = std::make_shared<Window::GLFWWindow>();
    if((werr = window->GetLastError()) != Window::GlfwErrorCode::NoError)
        FATAL("%s", Window::GlfwErrorStr(werr).c_str());

    // Main loop
    while((werr = window->PollEvents()) == Window::GlfwErrorCode::NoError) {

    }

    if(werr != Window::GlfwErrorCode::WindowClosed) {
        FATAL("%s", Window::GlfwErrorStr(werr).c_str());
    }

    return EXIT_SUCCESS;
}