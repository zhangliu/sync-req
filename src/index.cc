#include <node.h>
#include "./curl.cc"

namespace sr_index
{

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

const char *ToCString(const v8::String::Utf8Value &value)
{
  return *value ? *value : "<string conversion failed>";
}

void Upload(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  v8::String::Utf8Value v8Url(args[0]);
  const char *url = ToCString(v8Url);
  v8::String::Utf8Value v8FilePath(args[1]);
  const char *filePath = ToCString(v8FilePath);
  char const *result = sr_curl::upload(url, filePath);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, result));
}

void Zip(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  v8::String::Utf8Value v8Url(args[0]);
  const char *url = ToCString(v8Url);
  v8::String::Utf8Value v8FilePath(args[1]);
  const char *filePath = ToCString(v8FilePath);
  char const *result = sr_curl::upload(url, filePath);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, result));
}

void Initialize(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "upload", Upload);
  // NODE_SET_METHOD(exports, "zip", Zip);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace sr_index