#include <errno.h>
#include <string.h>
#include <node.h>
#include <node_version.h>

#if NODE_VERSION_AT_LEAST(0, 11, 0)

#define STRING(v) v8::String::NewFromUtf8(isolate, v)

#define THROW_EXCEPTION(exception) isolate->ThrowException(exception)

#else

#define STRING(v) v8::String::New(v)

#define THROW_EXCEPTION(exception) v8::ThrowException(exception)

#endif

#define ERRNO_CASE(e) case e: return #e

#define THROW_ERRNO_EXCEPTION(errorno, syscall) THROW_EXCEPTION(addon::ErrnoException(isolate, errorno, #syscall))

namespace addon {

inline const char *errno_string(int errorno) {
  switch(errorno) {
#ifdef EACCES
  ERRNO_CASE(EACCES);
#endif
    default: return "";
  }
}

inline v8::Local<v8::Value> ErrnoException(v8::Isolate* isolate, int errorno, const char* syscall) {
    v8::Local<v8::String> errno_string = STRING(addon::errno_string(errorno));
    v8::Local<v8::Value> exception_error = v8::Exception::Error(STRING(strerror(errorno)));
    v8::Local<v8::Object> error_object = exception_error->ToObject(isolate);
    error_object->Set(STRING("errno"), errno_string);
    error_object->Set(STRING("code"), errno_string);
    error_object->Set(STRING("syscall"), STRING(syscall));
    error_object->Set(STRING("path"), STRING(""));

    return exception_error;
}

void ThrowErrnoException(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    THROW_ERRNO_EXCEPTION(EACCES, open);
}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  NODE_SET_METHOD(module, "exports", ThrowErrnoException);
}

NODE_MODULE(addon, Init)

}