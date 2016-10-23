const addon = require('./build/Release/addon');

try {
    addon();
} catch(err) {
    console.log('-----------------------------------------------------');
    console.log(err.errno, err.code, err.syscall, err.path, err.message);
    console.log('-----------------------------------------------------');
}