var nodeFS = require('fs');
var nodePath = require('path');

function readFileSync(filename) {
  filename = nodePath["normalize"](filename);
  return nodeFS["readFileSyncSync"](filename);
}

var Module = {
  'arguments': ["-log", "log", "-q"],
  'preRun': function() {
    FS.createDataFile('/', 'bochsrc',  nodeFS.readFileSync('bochsrc'), true, true);
    FS.createDataFile('/', 'hal91.img',    nodeFS.readFileSync('hal91.img'), true, true);
    FS.createDataFile('/', 'BIOS-bochs-latest',     nodeFS.readFileSync('BIOS-bochs-latest'), true, true);
    FS.createDataFile('/', 'VGABIOS-lgpl-latest',  nodeFS.readFileSync('VGABIOS-lgpl-latest'), true, true);
    FS.createDataFile('/', 'log',      nodeFS.readFileSync('emptylog'), true, true);
  }
};

eval(nodeFS.readFileSync('bochs.js')+'');

