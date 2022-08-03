const addon = require('bindings')('native');

console.time('rawArrayBuffers');
console.log(addon.rawArrayBuffers().length); // 434ms
console.timeEnd('rawArrayBuffers');
