/*****************************************************************************
 * Copyright 2017 SoundHound, Incorporated.  All rights reserved.
 *****************************************************************************/
#include <node.h>
#include "PhraseSpotterAPI.h"


using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Exception;
using v8::Int16Array;


void getThreshold(const FunctionCallbackInfo<Value>& args) 
{
  Isolate* isolate = args.GetIsolate();

  Local<Number> num = Number::New(isolate, PhraseSpotterGetThreshold());
  args.GetReturnValue().Set(num);
}


void setThreshold(const FunctionCallbackInfo<Value>& args) 
{
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1 || !args[0]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Requires a Number as an argument.")));
    return;
  }

  PhraseSpotterSetThreshold(args[0]->NumberValue());
}


void processSamples(const FunctionCallbackInfo<Value>& args) 
{
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1 || !args[0]->IsInt16Array()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Requires a Int16Array as an argument.")));
    return;
  }

  Local<Int16Array> input = Local<Int16Array>::Cast(args[0]);
  
  uint32_t num_samples = input->Length();

  int16_t samples[num_samples];
  for (uint32_t i = 0; i < num_samples; i++) {
    samples[i] = input->Get(i)->NumberValue();
  }

  Local<Number> num = Number::New(isolate, PhraseSpotterProcessSamples(samples, num_samples)); 
  args.GetReturnValue().Set(num);
}



void init(Local<Object> exports) 
{
  NODE_SET_METHOD(exports, "getThreshold", getThreshold);
  NODE_SET_METHOD(exports, "setThreshold", setThreshold);
  NODE_SET_METHOD(exports, "processSamples", processSamples);
}


NODE_MODULE(okhound, init)
