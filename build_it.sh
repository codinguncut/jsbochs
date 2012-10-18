#!/bin/bash

emconfigure ./configure --disable-plugs --disable-x86-64 --enable-cpu-level=4 --with-term  --disable-large-ramfile --disable-cdrom --disable-debugger-gui --disable-readline --disable-iodebug --enable-show-ips --enable-logging --disable-idle-hack --disable-debugger --disable-disasm --enable-fpu --disable-long-phy-address && \
echo "Finished emconfigure" && \
emmake make && \
echo "Finished emmake" && \
emcc -O1 bochs.bc -o bochs.js && \
echo "Finished building bochs.js. You can start jsbochs by executing 'node launch.js'"

