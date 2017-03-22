//
//  SampleModule.h
//  modsample
//
//  Created by Alex Skalozub on 22/02/15.
//  Copyright (c) 2014 pieceofsummer@gmail.com. All rights reserved.
//
//  Sample native module for z-way-server
//

#ifndef LimitLessLEDmod_h
#define LimitLessLEDmod_h

#include <Module.h>
#include <Environment.h>
#include <Utility.h>

namespace zwjs
{
  class LimitLessLEDModule : public Module
  {
    public:
      LimitLessLEDModule() : Module("zway/sample", kSource) { }
                            
      virtual v8::Handle<v8::FunctionTemplate> GetFunction(Environment* env, v8::Isolate* isolate, std::string name);
                                            
      static void Register();
                                                            
    private:
      static const char* kSource;
      static bool m_registered;
                                                                                        
      static std::string GetObjectLocation(Environment* env, std::string objectName);
                                                                                                        
      METHOD_DECL(LimitLessLEDModule, ModuleFunc);
      // other method declarations
  };
}

#endif
                                                                                                                                                            