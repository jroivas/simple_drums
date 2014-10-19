# Simple drums

Supports USB pluggable Rock Band drum set.


## Dependencies

On Debian/Ubuntu based system:

    $ sudo apt-get install qtbase5-dev qtmultimedia5-dev libqt5multimedia5-plugins


Build qtgamepad:

    $ sudo apt-get install libudev-dev
    $ git clone https://github.com/nezticle/qtgamepad
    $ cd qtgamepad
    $ qmake && make


If you have error about "Missing CMake tests", add this line to all .pro files under qtgamepad:

    CMAKE_MODULE_TESTS=-


## Build


    $ qmake
    $ make

## Run

    $ LD_LIBRARY_PATH=./qtgamepad/lib ./simple_drums
