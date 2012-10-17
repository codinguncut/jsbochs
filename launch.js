var nodeFS = require('fs');
var nodePath = require('path');

function output(ch) {
  process.stdout.write(String.fromCharCode(ch));
}

var Module = {
  'print': function(asdf) {console.log('hello');},
  'arguments': ["-q"],
  'preInit': function() {
    FS.init(null, output, null);
  },
  'preRun': function() {
    FS.createDataFile('/', 'bochsrc',  nodeFS.readFileSync('bochsrc'), true, true);
    FS.createDataFile('/', 'hal91.img',    nodeFS.readFileSync('hal91.img'), true, true);
    FS.createDataFile('/', 'BIOS-bochs-latest',     nodeFS.readFileSync('BIOS-bochs-latest'), true, true);
    FS.createDataFile('/', 'VGABIOS-lgpl-latest',  nodeFS.readFileSync('VGABIOS-lgpl-latest'), true, true);
    //FS.createDataFile('/', 'log',      nodeFS.readFileSync('log'), true, true);
  }
};

eval(nodeFS.readFileSync('bochs.js')+'');

