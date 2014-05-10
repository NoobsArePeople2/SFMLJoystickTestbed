//-------------------------------------------------------
// Uses CoreFoundation on Mac OS to return the proper
// resource path for bundled applications
//
// Based on resourcePath.mm provided with the Xcode
// templates for SFML. This version contains no
// Objective-C code, allowing it to be compiled in
// non-Xcode IDEs so the file can be used regardless of
// platform or development environment.
//
//-------------------------------------------------------

#include "ResourcePath.h"
#include <iostream>

#ifdef __APPLE__

#include <CoreFoundation/CoreFoundation.h>

std::string resourcePath(std::string file)
{
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);

    #ifdef DEBUG

        CFShow(resourcesURL);

    #endif

    CFStringRef str = CFURLCopyFileSystemPath( resourcesURL, kCFURLPOSIXPathStyle );
    CFRelease(resourcesURL);
    char path[PATH_MAX];

    CFStringGetCString( str, path, FILENAME_MAX, kCFStringEncodingASCII );
    CFRelease(str);

    std::string bpath(path);

    resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);

    #ifdef DEBUG

        CFShow(resourcesURL);

    #endif
    str = CFURLCopyFileSystemPath( resourcesURL, kCFURLPOSIXPathStyle );

    CFStringGetCString( str, path, FILENAME_MAX, kCFStringEncodingASCII );
    CFRelease(str);
    CFRelease(resourcesURL);

    std::string rpath(path);

    if (bpath != rpath)
    {
        // Packaged into app bundle
        bpath += "/" + rpath + "/";
    }
    else
    {
        // Debug (for Eclipse anyhow).
        bpath += "/Resources/";
    }

    #ifdef DEBUG

        fprintf(stderr, "%s\n", bpath.c_str());
        std::cout << "bpath: " << bpath << std::endl;

    #endif
    return bpath + file;
}

#else

std::string resourcePath(std::string file)
{
    return std::string("Resources/" + file);
}

#endif
