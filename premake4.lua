-- See "paths.lua.sample" for instructions on creating the file.
dofile ( "paths.lua" )

-- return a new array containing the concatenation of all of its
-- parameters. Scaler parameters are included in place, and array
-- parameters have their values shallow-copied to the final array.
-- Note that userdata and function values are treated as scalar.
function array_concat(...)
    local t = {}
    for n = 1,select("#",...) do
        local arg = select(n,...)
        if type(arg)=="table" then
            for _,v in ipairs(arg) do
                t[#t+1] = v
            end
        else
            t[#t+1] = arg
        end
    end
    return t
end

INC  = array_concat ( SFML_INC, SFML_EXT_INC, "src" )
LIB  = array_concat ( SFML_LIB, SFML_EXT_LIB )

LINKS = {}
if os.is("macosx") then

    KIND       = "WindowedApp"
    LINKS      = { "sfml-graphics.framework", "sfml-window.framework", "sfml-system.framework", "CoreFoundation.framework", "freetype.framework" }
    -- LINKS      = { "sfml-graphics-d", "sfml-window-d", "sfml-system-d", "CoreFoundation.framework" }
    PLATFORMS  = { "x32" }
    BUILD_OPTS = "-std=c++11 -stdlib=libc++ -g"
    LINK_OPTS  = "-stdlib=libc++"
    DEFINES    = ""
    POST_BUILD_CMDS = { "scripts/copy-res-mac.sh" }

elseif os.is("windows") then

    KIND       = "ConsoleApp"
    LINKS      = { "sfml-graphics-s-d", "sfml-window-s-d", "sfml-system-s-d", "jpeg", "glew", "freetype", "ws2_32", "gdi32", "opengl32", "winmm" }
    PLATFORMS  = {}
    BUILD_OPTS = "-g"
    LINK_OPTS  = "-static-libgcc -static-libstdc++"
    DEFINES    = { "GLEW_STATIC", "SFML_STATIC", "UNICODE" }
    POST_BUILD_CMDS = {}

elseif os.is("linux") then

    KIND       = "ConsoleApp"
    LINKS      = { "sfml-graphics-d", "sfml-window-d", "sfml-system-d" }
    PLATFORMS  = {}
    BUILD_OPTS = "-g"
    LINK_OPTS  = ""
    DEFINES    = { "SFML_STATIC" }
    POST_BUILD_CMDS = {}

end

solution "SFML Joystick Testbed"
  configurations { "Debug", "Release" }

  project "SFML Joystick Testbed"
    kind(KIND)
    language "C++"
    files { "**.h", "**.cpp", "**.hpp", "**.c", "**.ttf" }
    links(LINKS)
    libdirs(LIB)
    includedirs(INC)
    buildoptions(BUILD_OPTS)
    linkoptions(LINK_OPTS)
    defines(DEFINES)
    platforms(PLATFORMS)
    postbuildcommands(POST_BUILD_CMDS)


    configuration "Debug"

    configuration "Release"
