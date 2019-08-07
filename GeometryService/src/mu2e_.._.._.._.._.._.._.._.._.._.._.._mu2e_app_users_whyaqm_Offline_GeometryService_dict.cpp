// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME GeometryServicedIsrcdImu2e_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_mu2e_app_users_whyaqm_Offline_GeometryService_dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "GeometryService/src/classes.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR_Dictionary();
   static void artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR_TClassManip(TClass*);
   static void *new_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(void *p = 0);
   static void *newArray_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(Long_t size, void *p);
   static void delete_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(void *p);
   static void deleteArray_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(void *p);
   static void destruct_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::art::Wrapper<mu2e::Mu2eEnvelope>*)
   {
      ::art::Wrapper<mu2e::Mu2eEnvelope> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::art::Wrapper<mu2e::Mu2eEnvelope>));
      static ::ROOT::TGenericClassInfo 
         instance("art::Wrapper<mu2e::Mu2eEnvelope>", ::art::Wrapper<mu2e::Mu2eEnvelope>::Class_Version(), "canvas/Persistency/Common/Wrapper.h", 64,
                  typeid(::art::Wrapper<mu2e::Mu2eEnvelope>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR_Dictionary, isa_proxy, 4,
                  sizeof(::art::Wrapper<mu2e::Mu2eEnvelope>) );
      instance.SetNew(&new_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR);
      instance.SetNewArray(&newArray_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR);
      instance.SetDelete(&delete_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR);
      instance.SetDeleteArray(&deleteArray_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR);
      instance.SetDestructor(&destruct_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::art::Wrapper<mu2e::Mu2eEnvelope>*)
   {
      return GenerateInitInstanceLocal((::art::Wrapper<mu2e::Mu2eEnvelope>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::art::Wrapper<mu2e::Mu2eEnvelope>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::art::Wrapper<mu2e::Mu2eEnvelope>*)0x0)->GetClass();
      artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR_TClassManip(theClass);
   return theClass;
   }

   static void artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *artcLcLWrapperlEmu2ecLcLWorldG4gR_Dictionary();
   static void artcLcLWrapperlEmu2ecLcLWorldG4gR_TClassManip(TClass*);
   static void *new_artcLcLWrapperlEmu2ecLcLWorldG4gR(void *p = 0);
   static void *newArray_artcLcLWrapperlEmu2ecLcLWorldG4gR(Long_t size, void *p);
   static void delete_artcLcLWrapperlEmu2ecLcLWorldG4gR(void *p);
   static void deleteArray_artcLcLWrapperlEmu2ecLcLWorldG4gR(void *p);
   static void destruct_artcLcLWrapperlEmu2ecLcLWorldG4gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::art::Wrapper<mu2e::WorldG4>*)
   {
      ::art::Wrapper<mu2e::WorldG4> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::art::Wrapper<mu2e::WorldG4>));
      static ::ROOT::TGenericClassInfo 
         instance("art::Wrapper<mu2e::WorldG4>", ::art::Wrapper<mu2e::WorldG4>::Class_Version(), "canvas/Persistency/Common/Wrapper.h", 64,
                  typeid(::art::Wrapper<mu2e::WorldG4>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &artcLcLWrapperlEmu2ecLcLWorldG4gR_Dictionary, isa_proxy, 4,
                  sizeof(::art::Wrapper<mu2e::WorldG4>) );
      instance.SetNew(&new_artcLcLWrapperlEmu2ecLcLWorldG4gR);
      instance.SetNewArray(&newArray_artcLcLWrapperlEmu2ecLcLWorldG4gR);
      instance.SetDelete(&delete_artcLcLWrapperlEmu2ecLcLWorldG4gR);
      instance.SetDeleteArray(&deleteArray_artcLcLWrapperlEmu2ecLcLWorldG4gR);
      instance.SetDestructor(&destruct_artcLcLWrapperlEmu2ecLcLWorldG4gR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::art::Wrapper<mu2e::WorldG4>*)
   {
      return GenerateInitInstanceLocal((::art::Wrapper<mu2e::WorldG4>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::art::Wrapper<mu2e::WorldG4>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *artcLcLWrapperlEmu2ecLcLWorldG4gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::art::Wrapper<mu2e::WorldG4>*)0x0)->GetClass();
      artcLcLWrapperlEmu2ecLcLWorldG4gR_TClassManip(theClass);
   return theClass;
   }

   static void artcLcLWrapperlEmu2ecLcLWorldG4gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLWorldG4_Dictionary();
   static void mu2ecLcLWorldG4_TClassManip(TClass*);
   static void delete_mu2ecLcLWorldG4(void *p);
   static void deleteArray_mu2ecLcLWorldG4(void *p);
   static void destruct_mu2ecLcLWorldG4(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::WorldG4*)
   {
      ::mu2e::WorldG4 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::WorldG4));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::WorldG4", "GeometryService/inc/WorldG4.hh", 28,
                  typeid(::mu2e::WorldG4), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLWorldG4_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::WorldG4) );
      instance.SetDelete(&delete_mu2ecLcLWorldG4);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLWorldG4);
      instance.SetDestructor(&destruct_mu2ecLcLWorldG4);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::WorldG4*)
   {
      return GenerateInitInstanceLocal((::mu2e::WorldG4*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::WorldG4*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLWorldG4_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::WorldG4*)0x0)->GetClass();
      mu2ecLcLWorldG4_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLWorldG4_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLMu2eEnvelope_Dictionary();
   static void mu2ecLcLMu2eEnvelope_TClassManip(TClass*);
   static void delete_mu2ecLcLMu2eEnvelope(void *p);
   static void deleteArray_mu2ecLcLMu2eEnvelope(void *p);
   static void destruct_mu2ecLcLMu2eEnvelope(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::Mu2eEnvelope*)
   {
      ::mu2e::Mu2eEnvelope *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::Mu2eEnvelope));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::Mu2eEnvelope", "GeometryService/inc/Mu2eEnvelope.hh", 23,
                  typeid(::mu2e::Mu2eEnvelope), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLMu2eEnvelope_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::Mu2eEnvelope) );
      instance.SetDelete(&delete_mu2ecLcLMu2eEnvelope);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLMu2eEnvelope);
      instance.SetDestructor(&destruct_mu2ecLcLMu2eEnvelope);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::Mu2eEnvelope*)
   {
      return GenerateInitInstanceLocal((::mu2e::Mu2eEnvelope*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::Mu2eEnvelope*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLMu2eEnvelope_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::Mu2eEnvelope*)0x0)->GetClass();
      mu2ecLcLMu2eEnvelope_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLMu2eEnvelope_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::art::Wrapper<mu2e::Mu2eEnvelope> : new ::art::Wrapper<mu2e::Mu2eEnvelope>;
   }
   static void *newArray_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::art::Wrapper<mu2e::Mu2eEnvelope>[nElements] : new ::art::Wrapper<mu2e::Mu2eEnvelope>[nElements];
   }
   // Wrapper around operator delete
   static void delete_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(void *p) {
      delete ((::art::Wrapper<mu2e::Mu2eEnvelope>*)p);
   }
   static void deleteArray_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(void *p) {
      delete [] ((::art::Wrapper<mu2e::Mu2eEnvelope>*)p);
   }
   static void destruct_artcLcLWrapperlEmu2ecLcLMu2eEnvelopegR(void *p) {
      typedef ::art::Wrapper<mu2e::Mu2eEnvelope> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::art::Wrapper<mu2e::Mu2eEnvelope>

namespace ROOT {
   // Wrappers around operator new
   static void *new_artcLcLWrapperlEmu2ecLcLWorldG4gR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::art::Wrapper<mu2e::WorldG4> : new ::art::Wrapper<mu2e::WorldG4>;
   }
   static void *newArray_artcLcLWrapperlEmu2ecLcLWorldG4gR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::art::Wrapper<mu2e::WorldG4>[nElements] : new ::art::Wrapper<mu2e::WorldG4>[nElements];
   }
   // Wrapper around operator delete
   static void delete_artcLcLWrapperlEmu2ecLcLWorldG4gR(void *p) {
      delete ((::art::Wrapper<mu2e::WorldG4>*)p);
   }
   static void deleteArray_artcLcLWrapperlEmu2ecLcLWorldG4gR(void *p) {
      delete [] ((::art::Wrapper<mu2e::WorldG4>*)p);
   }
   static void destruct_artcLcLWrapperlEmu2ecLcLWorldG4gR(void *p) {
      typedef ::art::Wrapper<mu2e::WorldG4> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::art::Wrapper<mu2e::WorldG4>

namespace ROOT {
   // Wrapper around operator delete
   static void delete_mu2ecLcLWorldG4(void *p) {
      delete ((::mu2e::WorldG4*)p);
   }
   static void deleteArray_mu2ecLcLWorldG4(void *p) {
      delete [] ((::mu2e::WorldG4*)p);
   }
   static void destruct_mu2ecLcLWorldG4(void *p) {
      typedef ::mu2e::WorldG4 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::WorldG4

namespace ROOT {
   // Wrapper around operator delete
   static void delete_mu2ecLcLMu2eEnvelope(void *p) {
      delete ((::mu2e::Mu2eEnvelope*)p);
   }
   static void deleteArray_mu2ecLcLMu2eEnvelope(void *p) {
      delete [] ((::mu2e::Mu2eEnvelope*)p);
   }
   static void destruct_mu2ecLcLMu2eEnvelope(void *p) {
      typedef ::mu2e::Mu2eEnvelope current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::Mu2eEnvelope

namespace {
  void TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_mu2e_app_users_whyaqm_Offline_GeometryService_dict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/pnfs/mu2e/scratch/users/whyaqm/workflow/Final-CRV-FOVa-5mm/outstage/1535666/00/00001",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/art/v2_07_03/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/canvas/v2_00_02/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/BTrk/v1_02_02/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/messagefacility/v2_00_02/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/fhiclcpp/v4_05_01/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/sqlite/v3_16_02_00a/Linux64bit+2.6-2.12/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/cetlib/v3_00_01/slf6.x86_64.e14.prof/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/cetlib_except/v1_01_02/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/boost/v1_63_0b/Linux64bit+2.6-2.12-e14-prof/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/clhep/v2_3_4_4/Linux64bit+2.6-2.12-e14-prof/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/cppunit/v1_13_2/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/heppdt/v3_04_01f/Linux64bit+2.6-2.12-e14-prof/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/root/v6_08_06g/Linux64bit+2.6-2.12-e14-prof/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/xerces_c/v3_1_4a/Linux64bit+2.6-2.12-e14-prof/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/tbb/v2017_3c/Linux64bit+2.6-2.12-e14-prof/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/mu2e_artdaq_core/v1_02_00/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/artdaq_core/v1_07_08/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/TRACE/v3_08_01/include",
"/cvmfs/mu2e.opensciencegrid.org/artexternals/root/v6_08_06g/Linux64bit+2.6-2.12-e14-prof/include",
"/mu2e/app/users/whyaqm/Offline/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libmu2e_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_mu2e_app_users_whyaqm_Offline_GeometryService_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace mu2e{class __attribute__((annotate("$clingAutoload$GeometryService/inc/Mu2eEnvelope.hh")))  Mu2eEnvelope;}
namespace art{template <class T> class __attribute__((annotate("$clingAutoload$GeometryService/inc/Mu2eEnvelope.hh")))  Wrapper;
}
namespace mu2e{class __attribute__((annotate("$clingAutoload$GeometryService/inc/WorldG4.hh")))  WorldG4;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libmu2e_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_mu2e_app_users_whyaqm_Offline_GeometryService_dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef NDEBUG
  #define NDEBUG 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
//
// Original author Andrei Gaponenko
//

#include "GeometryService/inc/WorldG4.hh"
#include "GeometryService/inc/Mu2eEnvelope.hh"
#include "canvas/Persistency/Common/Wrapper.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"art::Wrapper<mu2e::Mu2eEnvelope>", payloadCode, "@",
"art::Wrapper<mu2e::WorldG4>", payloadCode, "@",
"mu2e::Mu2eEnvelope", payloadCode, "@",
"mu2e::WorldG4", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libmu2e_.._.._.._.._.._.._.._.._.._.._.._mu2e_app_users_whyaqm_Offline_GeometryService_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_mu2e_app_users_whyaqm_Offline_GeometryService_dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_mu2e_app_users_whyaqm_Offline_GeometryService_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_mu2e_app_users_whyaqm_Offline_GeometryService_dict() {
  TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_dOdO_mu2e_app_users_whyaqm_Offline_GeometryService_dict_Impl();
}
