#include <napi.h>
#include <iostream>

#include<stdio.h>
#include<string.h>

template<class Policy>
class Vec : public Napi::ObjectWrap<Vec<Policy>> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = Napi::ObjectWrap<Vec<Policy>>::DefineClass(env, Policy::name, {});

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set(Policy::name, func);
    return exports;
  }

  explicit Vec(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Vec<Policy>>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }

private:
  static Napi::FunctionReference constructor;
};

template<class Policy>
Napi::FunctionReference Vec<Policy>::constructor;

struct Vec2dPolicy {
  constexpr static char *name = "Vec2";
  constexpr static int  Count  = 2;
  using ElementType = double;
};

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
  Vec<Vec2dPolicy>::Init(env, exports);

  return exports;
}

NODE_API_MODULE(hello, Init)
