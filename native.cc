#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#define BUFFERS 1000000
#define BUFFER_SIZE 1

using namespace v8;

char many_datas[BUFFERS][BUFFER_SIZE];

static void FreeCallback(void* data, size_t length, void* hint) {}

void RawArrayBuffers(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Value> values[BUFFERS];
  for (size_t i = 0; i < BUFFERS; i++) {
    char* data = many_datas[i];
    auto bs =
        ArrayBuffer::NewBackingStore(data, BUFFER_SIZE, FreeCallback, nullptr);
    values[i] = ArrayBuffer::New(isolate, std::move(bs));
  }
  args.GetReturnValue().Set(Array::New(isolate, values, BUFFERS));
}

static void FreeCallback2(char* _data, void* _hint) {}

void NodeBuffers(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Value> values[BUFFERS];
  for (size_t i = 0; i < BUFFERS; i++) {
    char* data = many_datas[i];
    auto buf =
        node::Buffer::New(isolate, data, BUFFER_SIZE, FreeCallback2, nullptr)
            .ToLocalChecked();
    values[i] = buf;
  }
  args.GetReturnValue().Set(Array::New(isolate, values, BUFFERS));
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "rawArrayBuffers", RawArrayBuffers);
  NODE_SET_METHOD(exports, "nodeBuffers", NodeBuffers);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
