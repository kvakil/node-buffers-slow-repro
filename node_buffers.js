const addon = require('bindings')('native');

console.time('nodeBuffers');
console.log(addon.nodeBuffers().length); // 1697ms
console.timeEnd('nodeBuffers');
