#include <napi.h>

class Vec : public Napi::ObjectWrap<Vec> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = Napi::ObjectWrap<Vec>::DefineClass(env, "Vec", {});

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Vec", func);
    return exports;
  }

  explicit Vec(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Vec>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }

private:
  static Napi::FunctionReference constructor;
};

Napi::FunctionReference Vec::constructor;

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
  Vec::Init(env, exports);

  return exports;
}

NODE_API_MODULE(hello, Init)
