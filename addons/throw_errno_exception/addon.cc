#include "nan.h"

#define ArgType(arg, Type, msg) \
if(!info[arg]->Is##Type()) { \
    return Nan::ThrowTypeError(msg); \
}

#define Int32Value(arg) info[arg]->Int32Value()

#define StringValue(arg) *(Nan::Utf8String(info[arg]))

NAN_METHOD(ThrowErrnoException) {
    ArgType(0, Int32, "First Argument Must be an Integer (valid errno)")
    ArgType(1, String, "Second Argument Must be a String (syscal)")
    ArgType(2, String, "Third Argument Must be a String (path)")
    return Nan::ThrowError(Nan::ErrnoException(Int32Value(0), StringValue(1),  NULL, StringValue(2)));   
}

void InitAll(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
    Nan::SetMethod(module, "exports", ThrowErrnoException);
}

NODE_MODULE(ioctl, InitAll)