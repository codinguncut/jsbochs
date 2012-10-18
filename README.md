## jsbochs - Bochs PC Emulator for the Browser

Emscripten "port" to Javascript of the [Bochs PC Emulator](http://bochs.sourceforge.net/).

Inspired by Fabrice Bellard's fantastic [jslinux](http://bellard.org/jslinux).

(Being) Ported by [Johannes Ahlmann](http://codinguncut.com)

## Status

The code runs flawlessly under javascript.
The only issue is that it runs SLOOOOW.
It runs the BIOS code reasonably fast, but then goes down to 0.04MIPS instead of native 30MIPS.

Also, I have almost no output options yet.

This git repo is currently my work bench and a bastadization of the original bochs code. I have removed all files that were not absolutely necessary for compilation in order to get my bearings.

## Install

### Requirements

* [llvm](http://llvm.org/)
* [emscripten](https://github.com/kripken/emscripten/wiki)
* possibly [node](http://nodejs.org/)

### Building

Simply run the `build_it.sh` script which will configure and build the bochs.js file. 

Alternatively follow the steps below:

<pre>
emconfigure ./configure --disable-plugins --disable-x86-64 --enable-cpu-level=4 \
--with-term  --disable-large-ramfile --disable-cdrom --disable-debugger-gui \
--disable-readline --disable-iodebug --enable-show-ips --enable-logging \
--disable-idle-hack --disable-debugger --disable-disasm --enable-fpu

emmake make

emcc -O1 bochs.bc -o bochs.js

node launch.js
</pre>

## TODO

* Currently it runs under node in the console. Get main loop running for browser
* Get an output running. Either a nicer terminal output or SDL output in the browser
* Get it to compile with -O2. This would be a tremendous speedup, but currently there are compiler errors about bit arithmetic.


## Issues

### Resolved Issues

* [64bit pointer casting](https://github.com/kripken/emscripten/issues/652)
* [Division error with long double](https://github.com/kripken/emscripten/issues/650)
* [Memory Alignment](https://github.com/kripken/emscripten/issues/647)

### Open Issues

* Browser main loop
* Compile with closure (bit arithmetic errors)
* Speed

## License

* Bochs (and jsbochs) as a whole is released under the GNU Lesser General Public License

* Parts of Bochs have specific licenses which are compatible with the
   GNU Lesser General Public License. Hence each source file contains its
   own licensing information.
