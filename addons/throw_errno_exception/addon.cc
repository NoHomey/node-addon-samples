#include "nan.h"

NAN_METHOD(/* method */) {
    info.GetReturnValue().Set(/* return */);
}

void InitAll(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
    Nan::SetMethod(module, "exports", /* method */);
}

NODE_MODULE(ioctl, InitAll)