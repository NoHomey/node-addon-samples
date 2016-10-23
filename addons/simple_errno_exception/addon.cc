#include <node.h>

namespace addon {

void ThrowErrnoException(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    isolate->ThrowException(node::ErrnoException(isolate, 9, "open", nullptr, "/dev/nullptr"));
}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  NODE_SET_METHOD(module, "exports", ThrowErrnoException);
}

NODE_MODULE(addon, Init)

}