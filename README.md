# SFML Joystick Testbed

A testbed for Joysticks in [SFML](http://sfml-dev.org/).

## Usage

The testbed shows all the information about connected joysticks that SFML exposes. This includes the joystick name, vendor ID, product ID, buttons and axes.

Buttons are shown as rectangles that are gray when up (not pressed) and green when down (pressed). The label next to each square is the corresponding button index.

Axes are shown as labels in the format `Axis Name: Axis Value`. "N/A" is displayed for the value if the axis is not available for a particular joystick.

The bottom of the window displays connected joysticks with a series of square indicators. The indicators are read from left to right with the leftmost indicator being index 0 with each subsequent indicator incrementing the index by 1.

Blue is the currently selected joystick (if the joystick is also connected), green means the joystick is connected but not selected, white means the joystick is not connected and yellow means the joystick is selected but not connected. The testbed supports hotplugging so you can connect and disconnect joysticks with the testbed running.

## Dependencies

- [SFML latest](https://github.com/LaurentGomila/SFML)
- [premake4](http://industriousone.com/premake)

## Building the Project

Building the project is super simple but does require a bit of setup. Fortunately setup breaks down into a few steps:

1. Install all the dependencies.
2. Clone this repo.
3. Using the command line (Terminal on Mac, Powershell, or cmd.exe if you must, on Windows) `cd` into the root of the cloned repo.
4. Open `paths.lua.sample` in your favorite text editor and save a new file based on it called `paths.lua`. `paths.lua` is used to point premake to the install locations of the SFML headers and libs. It is ignored by git.
5. In your copy of `paths.lua`,
    1. Replace "E:/absolute/path/to/SFML/headers" with the absolute path to the installed SFML headers (SFML's .hpp files) on your system.
    2. Replace "E:/absolute/path/to/SFML/libs" with the absolute path to the installed SFML libs (SFML's .a, .lib or .frameworks depending on your OS) on your system.
    3. Save `paths.lua`.
6. Use premake to generate a project for your favorite IDE.

Here are some examples of using premake to generate projects:

    # Generate a CodeBlocks project
    $ premake4 codeblocks

    # Generate an XCode 4 project
    $ premake4 xcode4

    # Generate a Visual Studio 2010 project
    $ premake4 vs2010

Once you have the project generated open it in your IDE and build away.

## License

SFML Joystick Testbed is licensed under the MIT license.