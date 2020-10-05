#include <napi.h>
#include <string>
#include "greeting.h"
#include "show_chassis.h"


Napi::String dontShowTheChassis(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string result = dontShowChassis();
    return Napi::String::New(env, result);
}

Napi::String showTheChassis(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string result = showChassis();
    return Napi::String::New(env, result);
}

//Napi::Object InitGreet(Napi::Env env, Napi::Object exports) {
//    exports.Set(Napi::String::New(env, "greetHello"), Napi::Function::New(env, greetHello));
//    exports.Set(Napi::String::New(env, "showChassis"), Napi::Function::New(env, showTheChassis));
//    return exports;
//}

Napi::Object InitShowChassis(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "showChassis"), Napi::Function::New(env, showTheChassis));
    exports.Set(Napi::String::New(env, "dontShowChassis"), Napi::Function::New(env, dontShowTheChassis));
    return exports;
}

// Regisister the 'greet' module which calls the 'Init' method
//NODE_API_MODULE(greet, InitGreet);
NODE_API_MODULE(showChassis, InitShowChassis);