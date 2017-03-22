//
//  LimitLessLEDModule.cpp
//  modsample
//
//  Created by Alex Skalozub on 22/02/15.
//  Copyright (c) 2014 pieceofsummer@gmail.com. All rights reserved.
//
//  Sample native module for z-way-server
//

#include "LimitLessLEDModule.h"

// initialization (skeleton)

#ifdef _WINDOWS

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  if (fdwReason == DLL_PROCESS_ATTACH)
  {
    // some other Windows-specific initialization may go here
    zwjs::LimitLessLEDModule::Register();
  }
  return TRUE;
}
                        
#else
                        
__attribute__((constructor)) static void init() 
{
  // some other Unix-specific initialization may go here
  zwjs::LimitLessLEDModule::Register();
}
                            
#endif

// implementation

namespace zwjs
{

  bool LimitLessLEDModule::m_registered = false;

  // js module source
  const char* LimitLessLEDModule::kSource = "native function ModuleFunc();";

  // In kSource constant you can define any JavaScript code.
  // To define native functions:
  //   native function ModuleFunc();
  // This ModuleFunc name will be passed to LimitLessLEDModule::GetFunction.
  // You can defined many native functions.
  // There are some more V8 specific extensions:
  //   %_IsConstructCall() - check if function was called with "new" or not.
  //   %FunctionRemovePrototype(object) - remove prototype from object.
  //   %FunctionSetName(object, name) - tells V8 to return name if object converted to string.
  //   %FunctionSetInstanceClassName(object, name) - tells V8 to return class name.

  void LimitLessLEDModule::Register()
  {
    static LimitLessLEDModule ext;
    if (!m_registered)
    {
      // common initialization may go here                                                      
      v8::RegisterExtension(&ext);
      m_registered = true;
    }
  }

  // GetFunction() is called by V8 engine when linking JS code in kSource to resolve native functions
  v8::Handle<v8::FunctionTemplate> LimitLessLEDModule::GetFunction(Environment* env, v8::Isolate *isolate, std::string name)
  {
    if (name == "ModuleFunc")
    {
      return v8::FunctionTemplate::New(isolate, ModuleFunc);
    }
    // else if (name == "...")
    // {
    //   ... for all other exported functions ...
    // }
    else
    {
      return v8::Handle<v8::FunctionTemplate>();  
    }
  }
  
  // this sample function which just logs and returns it's own first argument value
  METHOD_IMPL(LimitLessLEDModule, ModuleFunc)
  {
    // typically we need isolate and environment references in every handler,
    // so the following lines are advised in every handler
    v8::Isolate *isolate = info.GetIsolate();
            
    Environment *env = GET_ENVIRONMENT();
    if (env == NULL) RETURN_EMPTY();
    
    // handler logic goes next:
  
    if (info.Length() == 0)
    {
      // ThrowException() is throwing JS exception after handler returns
      RETURN(ThrowException(isolate, "Function should have a single argument"));
    }

    // log into system logger  
    // GetString() returns an std::string representation of a JS object
    env->Log(Information, GetString(info[0]), "test"); // optional third parameter is category, defaults to "core"
  
    // return first arg
    RETURN(info[0]);
  }
  
}