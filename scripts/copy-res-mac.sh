#!/bin/bash

# Put us in the same folder as this script.
cd "$(dirname "$0")"
app_name="SFML_Gamepad_Test.app"

PROJ_ROOT=..

rm -rf $PROJ_ROOT/build/Debug/$app_name/Contents/Resources
# At some point make this more selective so we aren't copying all the source assets
# as well.
cp -R $PROJ_ROOT/Resources $PROJ_ROOT/build/Debug/$app_name/Contents/Resources