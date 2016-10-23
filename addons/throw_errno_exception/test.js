const addon = require('bindings')('addon.node');

try {
    addon(9, 'open', '/dev/addon/node');
} catch(err) {
    console.log('----------------------------------------');
    console.log(err.errno, err.code, err.syscall, err.path);
    console.log('----------------------------------------');
    throw err;
}