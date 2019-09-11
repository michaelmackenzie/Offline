// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME DataProductsdIsrcdImu2e_dOdO_dOdO_DataProducts_dict

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
#include "DataProducts/src/classes.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *mu2ecLcLCRSScintillatorBarIndex_Dictionary();
   static void mu2ecLcLCRSScintillatorBarIndex_TClassManip(TClass*);
   static void *new_mu2ecLcLCRSScintillatorBarIndex(void *p = 0);
   static void *newArray_mu2ecLcLCRSScintillatorBarIndex(Long_t size, void *p);
   static void delete_mu2ecLcLCRSScintillatorBarIndex(void *p);
   static void deleteArray_mu2ecLcLCRSScintillatorBarIndex(void *p);
   static void destruct_mu2ecLcLCRSScintillatorBarIndex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::CRSScintillatorBarIndex*)
   {
      ::mu2e::CRSScintillatorBarIndex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::CRSScintillatorBarIndex));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::CRSScintillatorBarIndex", "DataProducts/inc/CRSScintillatorBarIndex.hh", 22,
                  typeid(::mu2e::CRSScintillatorBarIndex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLCRSScintillatorBarIndex_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::CRSScintillatorBarIndex) );
      instance.SetNew(&new_mu2ecLcLCRSScintillatorBarIndex);
      instance.SetNewArray(&newArray_mu2ecLcLCRSScintillatorBarIndex);
      instance.SetDelete(&delete_mu2ecLcLCRSScintillatorBarIndex);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLCRSScintillatorBarIndex);
      instance.SetDestructor(&destruct_mu2ecLcLCRSScintillatorBarIndex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::CRSScintillatorBarIndex*)
   {
      return GenerateInitInstanceLocal((::mu2e::CRSScintillatorBarIndex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::CRSScintillatorBarIndex*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLCRSScintillatorBarIndex_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::CRSScintillatorBarIndex*)0x0)->GetClass();
      mu2ecLcLCRSScintillatorBarIndex_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLCRSScintillatorBarIndex_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLStrawIndex_Dictionary();
   static void mu2ecLcLStrawIndex_TClassManip(TClass*);
   static void delete_mu2ecLcLStrawIndex(void *p);
   static void deleteArray_mu2ecLcLStrawIndex(void *p);
   static void destruct_mu2ecLcLStrawIndex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::StrawIndex*)
   {
      ::mu2e::StrawIndex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::StrawIndex));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::StrawIndex", "DataProducts/inc/StrawIndex.hh", 35,
                  typeid(::mu2e::StrawIndex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLStrawIndex_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::StrawIndex) );
      instance.SetDelete(&delete_mu2ecLcLStrawIndex);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLStrawIndex);
      instance.SetDestructor(&destruct_mu2ecLcLStrawIndex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::StrawIndex*)
   {
      return GenerateInitInstanceLocal((::mu2e::StrawIndex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::StrawIndex*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLStrawIndex_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::StrawIndex*)0x0)->GetClass();
      mu2ecLcLStrawIndex_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLStrawIndex_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLPanelId_Dictionary();
   static void mu2ecLcLPanelId_TClassManip(TClass*);
   static void *new_mu2ecLcLPanelId(void *p = 0);
   static void *newArray_mu2ecLcLPanelId(Long_t size, void *p);
   static void delete_mu2ecLcLPanelId(void *p);
   static void deleteArray_mu2ecLcLPanelId(void *p);
   static void destruct_mu2ecLcLPanelId(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::PanelId*)
   {
      ::mu2e::PanelId *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::PanelId));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::PanelId", "DataProducts/inc/PanelId.hh", 26,
                  typeid(::mu2e::PanelId), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLPanelId_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::PanelId) );
      instance.SetNew(&new_mu2ecLcLPanelId);
      instance.SetNewArray(&newArray_mu2ecLcLPanelId);
      instance.SetDelete(&delete_mu2ecLcLPanelId);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLPanelId);
      instance.SetDestructor(&destruct_mu2ecLcLPanelId);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::PanelId*)
   {
      return GenerateInitInstanceLocal((::mu2e::PanelId*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::PanelId*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLPanelId_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::PanelId*)0x0)->GetClass();
      mu2ecLcLPanelId_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLPanelId_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLLayerId_Dictionary();
   static void mu2ecLcLLayerId_TClassManip(TClass*);
   static void *new_mu2ecLcLLayerId(void *p = 0);
   static void *newArray_mu2ecLcLLayerId(Long_t size, void *p);
   static void delete_mu2ecLcLLayerId(void *p);
   static void deleteArray_mu2ecLcLLayerId(void *p);
   static void destruct_mu2ecLcLLayerId(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::LayerId*)
   {
      ::mu2e::LayerId *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::LayerId));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::LayerId", "DataProducts/inc/LayerId.hh", 25,
                  typeid(::mu2e::LayerId), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLLayerId_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::LayerId) );
      instance.SetNew(&new_mu2ecLcLLayerId);
      instance.SetNewArray(&newArray_mu2ecLcLLayerId);
      instance.SetDelete(&delete_mu2ecLcLLayerId);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLLayerId);
      instance.SetDestructor(&destruct_mu2ecLcLLayerId);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::LayerId*)
   {
      return GenerateInitInstanceLocal((::mu2e::LayerId*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::LayerId*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLLayerId_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::LayerId*)0x0)->GetClass();
      mu2ecLcLLayerId_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLLayerId_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLStrawId_Dictionary();
   static void mu2ecLcLStrawId_TClassManip(TClass*);
   static void *new_mu2ecLcLStrawId(void *p = 0);
   static void *newArray_mu2ecLcLStrawId(Long_t size, void *p);
   static void delete_mu2ecLcLStrawId(void *p);
   static void deleteArray_mu2ecLcLStrawId(void *p);
   static void destruct_mu2ecLcLStrawId(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::StrawId*)
   {
      ::mu2e::StrawId *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::StrawId));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::StrawId", "DataProducts/inc/StrawId.hh", 24,
                  typeid(::mu2e::StrawId), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLStrawId_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::StrawId) );
      instance.SetNew(&new_mu2ecLcLStrawId);
      instance.SetNewArray(&newArray_mu2ecLcLStrawId);
      instance.SetDelete(&delete_mu2ecLcLStrawId);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLStrawId);
      instance.SetDestructor(&destruct_mu2ecLcLStrawId);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::StrawId*)
   {
      return GenerateInitInstanceLocal((::mu2e::StrawId*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::StrawId*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLStrawId_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::StrawId*)0x0)->GetClass();
      mu2ecLcLStrawId_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLStrawId_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLExtMonFNALModuleId_Dictionary();
   static void mu2ecLcLExtMonFNALModuleId_TClassManip(TClass*);
   static void *new_mu2ecLcLExtMonFNALModuleId(void *p = 0);
   static void *newArray_mu2ecLcLExtMonFNALModuleId(Long_t size, void *p);
   static void delete_mu2ecLcLExtMonFNALModuleId(void *p);
   static void deleteArray_mu2ecLcLExtMonFNALModuleId(void *p);
   static void destruct_mu2ecLcLExtMonFNALModuleId(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::ExtMonFNALModuleId*)
   {
      ::mu2e::ExtMonFNALModuleId *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::ExtMonFNALModuleId));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::ExtMonFNALModuleId", "DataProducts/inc/ExtMonFNALModuleId.hh", 10,
                  typeid(::mu2e::ExtMonFNALModuleId), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLExtMonFNALModuleId_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::ExtMonFNALModuleId) );
      instance.SetNew(&new_mu2ecLcLExtMonFNALModuleId);
      instance.SetNewArray(&newArray_mu2ecLcLExtMonFNALModuleId);
      instance.SetDelete(&delete_mu2ecLcLExtMonFNALModuleId);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLExtMonFNALModuleId);
      instance.SetDestructor(&destruct_mu2ecLcLExtMonFNALModuleId);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::ExtMonFNALModuleId*)
   {
      return GenerateInitInstanceLocal((::mu2e::ExtMonFNALModuleId*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::ExtMonFNALModuleId*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLExtMonFNALModuleId_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::ExtMonFNALModuleId*)0x0)->GetClass();
      mu2ecLcLExtMonFNALModuleId_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLExtMonFNALModuleId_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLExtMonFNALChipId_Dictionary();
   static void mu2ecLcLExtMonFNALChipId_TClassManip(TClass*);
   static void *new_mu2ecLcLExtMonFNALChipId(void *p = 0);
   static void *newArray_mu2ecLcLExtMonFNALChipId(Long_t size, void *p);
   static void delete_mu2ecLcLExtMonFNALChipId(void *p);
   static void deleteArray_mu2ecLcLExtMonFNALChipId(void *p);
   static void destruct_mu2ecLcLExtMonFNALChipId(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::ExtMonFNALChipId*)
   {
      ::mu2e::ExtMonFNALChipId *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::ExtMonFNALChipId));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::ExtMonFNALChipId", "DataProducts/inc/ExtMonFNALChipId.hh", 18,
                  typeid(::mu2e::ExtMonFNALChipId), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLExtMonFNALChipId_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::ExtMonFNALChipId) );
      instance.SetNew(&new_mu2ecLcLExtMonFNALChipId);
      instance.SetNewArray(&newArray_mu2ecLcLExtMonFNALChipId);
      instance.SetDelete(&delete_mu2ecLcLExtMonFNALChipId);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLExtMonFNALChipId);
      instance.SetDestructor(&destruct_mu2ecLcLExtMonFNALChipId);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::ExtMonFNALChipId*)
   {
      return GenerateInitInstanceLocal((::mu2e::ExtMonFNALChipId*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::ExtMonFNALChipId*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLExtMonFNALChipId_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::ExtMonFNALChipId*)0x0)->GetClass();
      mu2ecLcLExtMonFNALChipId_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLExtMonFNALChipId_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLExtMonFNALPixelId_Dictionary();
   static void mu2ecLcLExtMonFNALPixelId_TClassManip(TClass*);
   static void *new_mu2ecLcLExtMonFNALPixelId(void *p = 0);
   static void *newArray_mu2ecLcLExtMonFNALPixelId(Long_t size, void *p);
   static void delete_mu2ecLcLExtMonFNALPixelId(void *p);
   static void deleteArray_mu2ecLcLExtMonFNALPixelId(void *p);
   static void destruct_mu2ecLcLExtMonFNALPixelId(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::ExtMonFNALPixelId*)
   {
      ::mu2e::ExtMonFNALPixelId *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::ExtMonFNALPixelId));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::ExtMonFNALPixelId", "DataProducts/inc/ExtMonFNALPixelId.hh", 18,
                  typeid(::mu2e::ExtMonFNALPixelId), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLExtMonFNALPixelId_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::ExtMonFNALPixelId) );
      instance.SetNew(&new_mu2ecLcLExtMonFNALPixelId);
      instance.SetNewArray(&newArray_mu2ecLcLExtMonFNALPixelId);
      instance.SetDelete(&delete_mu2ecLcLExtMonFNALPixelId);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLExtMonFNALPixelId);
      instance.SetDestructor(&destruct_mu2ecLcLExtMonFNALPixelId);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::ExtMonFNALPixelId*)
   {
      return GenerateInitInstanceLocal((::mu2e::ExtMonFNALPixelId*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::ExtMonFNALPixelId*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLExtMonFNALPixelId_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::ExtMonFNALPixelId*)0x0)->GetClass();
      mu2ecLcLExtMonFNALPixelId_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLExtMonFNALPixelId_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *mu2ecLcLIndexMap_Dictionary();
   static void mu2ecLcLIndexMap_TClassManip(TClass*);
   static void *new_mu2ecLcLIndexMap(void *p = 0);
   static void *newArray_mu2ecLcLIndexMap(Long_t size, void *p);
   static void delete_mu2ecLcLIndexMap(void *p);
   static void deleteArray_mu2ecLcLIndexMap(void *p);
   static void destruct_mu2ecLcLIndexMap(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mu2e::IndexMap*)
   {
      ::mu2e::IndexMap *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mu2e::IndexMap));
      static ::ROOT::TGenericClassInfo 
         instance("mu2e::IndexMap", "DataProducts/inc/IndexMap.hh", 17,
                  typeid(::mu2e::IndexMap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &mu2ecLcLIndexMap_Dictionary, isa_proxy, 4,
                  sizeof(::mu2e::IndexMap) );
      instance.SetNew(&new_mu2ecLcLIndexMap);
      instance.SetNewArray(&newArray_mu2ecLcLIndexMap);
      instance.SetDelete(&delete_mu2ecLcLIndexMap);
      instance.SetDeleteArray(&deleteArray_mu2ecLcLIndexMap);
      instance.SetDestructor(&destruct_mu2ecLcLIndexMap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mu2e::IndexMap*)
   {
      return GenerateInitInstanceLocal((::mu2e::IndexMap*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mu2e::IndexMap*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mu2ecLcLIndexMap_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mu2e::IndexMap*)0x0)->GetClass();
      mu2ecLcLIndexMap_TClassManip(theClass);
   return theClass;
   }

   static void mu2ecLcLIndexMap_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *boostcLcLarraylEdoublecO5gR_Dictionary();
   static void boostcLcLarraylEdoublecO5gR_TClassManip(TClass*);
   static void *new_boostcLcLarraylEdoublecO5gR(void *p = 0);
   static void *newArray_boostcLcLarraylEdoublecO5gR(Long_t size, void *p);
   static void delete_boostcLcLarraylEdoublecO5gR(void *p);
   static void deleteArray_boostcLcLarraylEdoublecO5gR(void *p);
   static void destruct_boostcLcLarraylEdoublecO5gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::boost::array<double,5>*)
   {
      ::boost::array<double,5> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::boost::array<double,5>));
      static ::ROOT::TGenericClassInfo 
         instance("boost::array<double,5>", "boost/array.hpp", 60,
                  typeid(::boost::array<double,5>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &boostcLcLarraylEdoublecO5gR_Dictionary, isa_proxy, 4,
                  sizeof(::boost::array<double,5>) );
      instance.SetNew(&new_boostcLcLarraylEdoublecO5gR);
      instance.SetNewArray(&newArray_boostcLcLarraylEdoublecO5gR);
      instance.SetDelete(&delete_boostcLcLarraylEdoublecO5gR);
      instance.SetDeleteArray(&deleteArray_boostcLcLarraylEdoublecO5gR);
      instance.SetDestructor(&destruct_boostcLcLarraylEdoublecO5gR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::boost::array<double,5>*)
   {
      return GenerateInitInstanceLocal((::boost::array<double,5>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::boost::array<double,5>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *boostcLcLarraylEdoublecO5gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::boost::array<double,5>*)0x0)->GetClass();
      boostcLcLarraylEdoublecO5gR_TClassManip(theClass);
   return theClass;
   }

   static void boostcLcLarraylEdoublecO5gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *CLHEPcLcLHepRotationX_Dictionary();
   static void CLHEPcLcLHepRotationX_TClassManip(TClass*);
   static void *new_CLHEPcLcLHepRotationX(void *p = 0);
   static void *newArray_CLHEPcLcLHepRotationX(Long_t size, void *p);
   static void delete_CLHEPcLcLHepRotationX(void *p);
   static void deleteArray_CLHEPcLcLHepRotationX(void *p);
   static void destruct_CLHEPcLcLHepRotationX(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CLHEP::HepRotationX*)
   {
      ::CLHEP::HepRotationX *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::CLHEP::HepRotationX));
      static ::ROOT::TGenericClassInfo 
         instance("CLHEP::HepRotationX", "CLHEP/Vector/RotationX.h", 44,
                  typeid(::CLHEP::HepRotationX), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &CLHEPcLcLHepRotationX_Dictionary, isa_proxy, 4,
                  sizeof(::CLHEP::HepRotationX) );
      instance.SetNew(&new_CLHEPcLcLHepRotationX);
      instance.SetNewArray(&newArray_CLHEPcLcLHepRotationX);
      instance.SetDelete(&delete_CLHEPcLcLHepRotationX);
      instance.SetDeleteArray(&deleteArray_CLHEPcLcLHepRotationX);
      instance.SetDestructor(&destruct_CLHEPcLcLHepRotationX);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CLHEP::HepRotationX*)
   {
      return GenerateInitInstanceLocal((::CLHEP::HepRotationX*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CLHEP::HepRotationX*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *CLHEPcLcLHepRotationX_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::CLHEP::HepRotationX*)0x0)->GetClass();
      CLHEPcLcLHepRotationX_TClassManip(theClass);
   return theClass;
   }

   static void CLHEPcLcLHepRotationX_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *CLHEPcLcLHepRotationY_Dictionary();
   static void CLHEPcLcLHepRotationY_TClassManip(TClass*);
   static void *new_CLHEPcLcLHepRotationY(void *p = 0);
   static void *newArray_CLHEPcLcLHepRotationY(Long_t size, void *p);
   static void delete_CLHEPcLcLHepRotationY(void *p);
   static void deleteArray_CLHEPcLcLHepRotationY(void *p);
   static void destruct_CLHEPcLcLHepRotationY(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CLHEP::HepRotationY*)
   {
      ::CLHEP::HepRotationY *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::CLHEP::HepRotationY));
      static ::ROOT::TGenericClassInfo 
         instance("CLHEP::HepRotationY", "CLHEP/Vector/RotationY.h", 43,
                  typeid(::CLHEP::HepRotationY), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &CLHEPcLcLHepRotationY_Dictionary, isa_proxy, 4,
                  sizeof(::CLHEP::HepRotationY) );
      instance.SetNew(&new_CLHEPcLcLHepRotationY);
      instance.SetNewArray(&newArray_CLHEPcLcLHepRotationY);
      instance.SetDelete(&delete_CLHEPcLcLHepRotationY);
      instance.SetDeleteArray(&deleteArray_CLHEPcLcLHepRotationY);
      instance.SetDestructor(&destruct_CLHEPcLcLHepRotationY);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CLHEP::HepRotationY*)
   {
      return GenerateInitInstanceLocal((::CLHEP::HepRotationY*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CLHEP::HepRotationY*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *CLHEPcLcLHepRotationY_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::CLHEP::HepRotationY*)0x0)->GetClass();
      CLHEPcLcLHepRotationY_TClassManip(theClass);
   return theClass;
   }

   static void CLHEPcLcLHepRotationY_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *CLHEPcLcLHepRotationZ_Dictionary();
   static void CLHEPcLcLHepRotationZ_TClassManip(TClass*);
   static void *new_CLHEPcLcLHepRotationZ(void *p = 0);
   static void *newArray_CLHEPcLcLHepRotationZ(Long_t size, void *p);
   static void delete_CLHEPcLcLHepRotationZ(void *p);
   static void deleteArray_CLHEPcLcLHepRotationZ(void *p);
   static void destruct_CLHEPcLcLHepRotationZ(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CLHEP::HepRotationZ*)
   {
      ::CLHEP::HepRotationZ *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::CLHEP::HepRotationZ));
      static ::ROOT::TGenericClassInfo 
         instance("CLHEP::HepRotationZ", "CLHEP/Vector/RotationZ.h", 43,
                  typeid(::CLHEP::HepRotationZ), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &CLHEPcLcLHepRotationZ_Dictionary, isa_proxy, 4,
                  sizeof(::CLHEP::HepRotationZ) );
      instance.SetNew(&new_CLHEPcLcLHepRotationZ);
      instance.SetNewArray(&newArray_CLHEPcLcLHepRotationZ);
      instance.SetDelete(&delete_CLHEPcLcLHepRotationZ);
      instance.SetDeleteArray(&deleteArray_CLHEPcLcLHepRotationZ);
      instance.SetDestructor(&destruct_CLHEPcLcLHepRotationZ);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CLHEP::HepRotationZ*)
   {
      return GenerateInitInstanceLocal((::CLHEP::HepRotationZ*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CLHEP::HepRotationZ*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *CLHEPcLcLHepRotationZ_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::CLHEP::HepRotationZ*)0x0)->GetClass();
      CLHEPcLcLHepRotationZ_TClassManip(theClass);
   return theClass;
   }

   static void CLHEPcLcLHepRotationZ_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *CLHEPcLcLHepRotation_Dictionary();
   static void CLHEPcLcLHepRotation_TClassManip(TClass*);
   static void *new_CLHEPcLcLHepRotation(void *p = 0);
   static void *newArray_CLHEPcLcLHepRotation(Long_t size, void *p);
   static void delete_CLHEPcLcLHepRotation(void *p);
   static void deleteArray_CLHEPcLcLHepRotation(void *p);
   static void destruct_CLHEPcLcLHepRotation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CLHEP::HepRotation*)
   {
      ::CLHEP::HepRotation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::CLHEP::HepRotation));
      static ::ROOT::TGenericClassInfo 
         instance("CLHEP::HepRotation", "CLHEP/Vector/Rotation.h", 48,
                  typeid(::CLHEP::HepRotation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &CLHEPcLcLHepRotation_Dictionary, isa_proxy, 4,
                  sizeof(::CLHEP::HepRotation) );
      instance.SetNew(&new_CLHEPcLcLHepRotation);
      instance.SetNewArray(&newArray_CLHEPcLcLHepRotation);
      instance.SetDelete(&delete_CLHEPcLcLHepRotation);
      instance.SetDeleteArray(&deleteArray_CLHEPcLcLHepRotation);
      instance.SetDestructor(&destruct_CLHEPcLcLHepRotation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CLHEP::HepRotation*)
   {
      return GenerateInitInstanceLocal((::CLHEP::HepRotation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CLHEP::HepRotation*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *CLHEPcLcLHepRotation_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::CLHEP::HepRotation*)0x0)->GetClass();
      CLHEPcLcLHepRotation_TClassManip(theClass);
   return theClass;
   }

   static void CLHEPcLcLHepRotation_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *HepGeomcLcLTransform3D_Dictionary();
   static void HepGeomcLcLTransform3D_TClassManip(TClass*);
   static void *new_HepGeomcLcLTransform3D(void *p = 0);
   static void *newArray_HepGeomcLcLTransform3D(Long_t size, void *p);
   static void delete_HepGeomcLcLTransform3D(void *p);
   static void deleteArray_HepGeomcLcLTransform3D(void *p);
   static void destruct_HepGeomcLcLTransform3D(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HepGeom::Transform3D*)
   {
      ::HepGeom::Transform3D *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HepGeom::Transform3D));
      static ::ROOT::TGenericClassInfo 
         instance("HepGeom::Transform3D", "CLHEP/Geometry/Transform3D.h", 172,
                  typeid(::HepGeom::Transform3D), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &HepGeomcLcLTransform3D_Dictionary, isa_proxy, 4,
                  sizeof(::HepGeom::Transform3D) );
      instance.SetNew(&new_HepGeomcLcLTransform3D);
      instance.SetNewArray(&newArray_HepGeomcLcLTransform3D);
      instance.SetDelete(&delete_HepGeomcLcLTransform3D);
      instance.SetDeleteArray(&deleteArray_HepGeomcLcLTransform3D);
      instance.SetDestructor(&destruct_HepGeomcLcLTransform3D);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HepGeom::Transform3D*)
   {
      return GenerateInitInstanceLocal((::HepGeom::Transform3D*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HepGeom::Transform3D*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *HepGeomcLcLTransform3D_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::HepGeom::Transform3D*)0x0)->GetClass();
      HepGeomcLcLTransform3D_TClassManip(theClass);
   return theClass;
   }

   static void HepGeomcLcLTransform3D_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *artcLcLWrapperlEmu2ecLcLIndexMapgR_Dictionary();
   static void artcLcLWrapperlEmu2ecLcLIndexMapgR_TClassManip(TClass*);
   static void *new_artcLcLWrapperlEmu2ecLcLIndexMapgR(void *p = 0);
   static void *newArray_artcLcLWrapperlEmu2ecLcLIndexMapgR(Long_t size, void *p);
   static void delete_artcLcLWrapperlEmu2ecLcLIndexMapgR(void *p);
   static void deleteArray_artcLcLWrapperlEmu2ecLcLIndexMapgR(void *p);
   static void destruct_artcLcLWrapperlEmu2ecLcLIndexMapgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::art::Wrapper<mu2e::IndexMap>*)
   {
      ::art::Wrapper<mu2e::IndexMap> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::art::Wrapper<mu2e::IndexMap>));
      static ::ROOT::TGenericClassInfo 
         instance("art::Wrapper<mu2e::IndexMap>", ::art::Wrapper<mu2e::IndexMap>::Class_Version(), "", 41,
                  typeid(::art::Wrapper<mu2e::IndexMap>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &artcLcLWrapperlEmu2ecLcLIndexMapgR_Dictionary, isa_proxy, 4,
                  sizeof(::art::Wrapper<mu2e::IndexMap>) );
      instance.SetNew(&new_artcLcLWrapperlEmu2ecLcLIndexMapgR);
      instance.SetNewArray(&newArray_artcLcLWrapperlEmu2ecLcLIndexMapgR);
      instance.SetDelete(&delete_artcLcLWrapperlEmu2ecLcLIndexMapgR);
      instance.SetDeleteArray(&deleteArray_artcLcLWrapperlEmu2ecLcLIndexMapgR);
      instance.SetDestructor(&destruct_artcLcLWrapperlEmu2ecLcLIndexMapgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::art::Wrapper<mu2e::IndexMap>*)
   {
      return GenerateInitInstanceLocal((::art::Wrapper<mu2e::IndexMap>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::art::Wrapper<mu2e::IndexMap>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *artcLcLWrapperlEmu2ecLcLIndexMapgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::art::Wrapper<mu2e::IndexMap>*)0x0)->GetClass();
      artcLcLWrapperlEmu2ecLcLIndexMapgR_TClassManip(theClass);
   return theClass;
   }

   static void artcLcLWrapperlEmu2ecLcLIndexMapgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_mu2ecLcLCRSScintillatorBarIndex(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::CRSScintillatorBarIndex : new ::mu2e::CRSScintillatorBarIndex;
   }
   static void *newArray_mu2ecLcLCRSScintillatorBarIndex(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::CRSScintillatorBarIndex[nElements] : new ::mu2e::CRSScintillatorBarIndex[nElements];
   }
   // Wrapper around operator delete
   static void delete_mu2ecLcLCRSScintillatorBarIndex(void *p) {
      delete ((::mu2e::CRSScintillatorBarIndex*)p);
   }
   static void deleteArray_mu2ecLcLCRSScintillatorBarIndex(void *p) {
      delete [] ((::mu2e::CRSScintillatorBarIndex*)p);
   }
   static void destruct_mu2ecLcLCRSScintillatorBarIndex(void *p) {
      typedef ::mu2e::CRSScintillatorBarIndex current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::CRSScintillatorBarIndex

namespace ROOT {
   // Wrapper around operator delete
   static void delete_mu2ecLcLStrawIndex(void *p) {
      delete ((::mu2e::StrawIndex*)p);
   }
   static void deleteArray_mu2ecLcLStrawIndex(void *p) {
      delete [] ((::mu2e::StrawIndex*)p);
   }
   static void destruct_mu2ecLcLStrawIndex(void *p) {
      typedef ::mu2e::StrawIndex current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::StrawIndex

namespace ROOT {
   // Wrappers around operator new
   static void *new_mu2ecLcLPanelId(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::PanelId : new ::mu2e::PanelId;
   }
   static void *newArray_mu2ecLcLPanelId(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::PanelId[nElements] : new ::mu2e::PanelId[nElements];
   }
   // Wrapper around operator delete
   static void delete_mu2ecLcLPanelId(void *p) {
      delete ((::mu2e::PanelId*)p);
   }
   static void deleteArray_mu2ecLcLPanelId(void *p) {
      delete [] ((::mu2e::PanelId*)p);
   }
   static void destruct_mu2ecLcLPanelId(void *p) {
      typedef ::mu2e::PanelId current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::PanelId

namespace ROOT {
   // Wrappers around operator new
   static void *new_mu2ecLcLLayerId(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::LayerId : new ::mu2e::LayerId;
   }
   static void *newArray_mu2ecLcLLayerId(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::LayerId[nElements] : new ::mu2e::LayerId[nElements];
   }
   // Wrapper around operator delete
   static void delete_mu2ecLcLLayerId(void *p) {
      delete ((::mu2e::LayerId*)p);
   }
   static void deleteArray_mu2ecLcLLayerId(void *p) {
      delete [] ((::mu2e::LayerId*)p);
   }
   static void destruct_mu2ecLcLLayerId(void *p) {
      typedef ::mu2e::LayerId current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::LayerId

namespace ROOT {
   // Wrappers around operator new
   static void *new_mu2ecLcLStrawId(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::StrawId : new ::mu2e::StrawId;
   }
   static void *newArray_mu2ecLcLStrawId(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::StrawId[nElements] : new ::mu2e::StrawId[nElements];
   }
   // Wrapper around operator delete
   static void delete_mu2ecLcLStrawId(void *p) {
      delete ((::mu2e::StrawId*)p);
   }
   static void deleteArray_mu2ecLcLStrawId(void *p) {
      delete [] ((::mu2e::StrawId*)p);
   }
   static void destruct_mu2ecLcLStrawId(void *p) {
      typedef ::mu2e::StrawId current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::StrawId

namespace ROOT {
   // Wrappers around operator new
   static void *new_mu2ecLcLExtMonFNALModuleId(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::ExtMonFNALModuleId : new ::mu2e::ExtMonFNALModuleId;
   }
   static void *newArray_mu2ecLcLExtMonFNALModuleId(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::ExtMonFNALModuleId[nElements] : new ::mu2e::ExtMonFNALModuleId[nElements];
   }
   // Wrapper around operator delete
   static void delete_mu2ecLcLExtMonFNALModuleId(void *p) {
      delete ((::mu2e::ExtMonFNALModuleId*)p);
   }
   static void deleteArray_mu2ecLcLExtMonFNALModuleId(void *p) {
      delete [] ((::mu2e::ExtMonFNALModuleId*)p);
   }
   static void destruct_mu2ecLcLExtMonFNALModuleId(void *p) {
      typedef ::mu2e::ExtMonFNALModuleId current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::ExtMonFNALModuleId

namespace ROOT {
   // Wrappers around operator new
   static void *new_mu2ecLcLExtMonFNALChipId(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::ExtMonFNALChipId : new ::mu2e::ExtMonFNALChipId;
   }
   static void *newArray_mu2ecLcLExtMonFNALChipId(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::ExtMonFNALChipId[nElements] : new ::mu2e::ExtMonFNALChipId[nElements];
   }
   // Wrapper around operator delete
   static void delete_mu2ecLcLExtMonFNALChipId(void *p) {
      delete ((::mu2e::ExtMonFNALChipId*)p);
   }
   static void deleteArray_mu2ecLcLExtMonFNALChipId(void *p) {
      delete [] ((::mu2e::ExtMonFNALChipId*)p);
   }
   static void destruct_mu2ecLcLExtMonFNALChipId(void *p) {
      typedef ::mu2e::ExtMonFNALChipId current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::ExtMonFNALChipId

namespace ROOT {
   // Wrappers around operator new
   static void *new_mu2ecLcLExtMonFNALPixelId(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::ExtMonFNALPixelId : new ::mu2e::ExtMonFNALPixelId;
   }
   static void *newArray_mu2ecLcLExtMonFNALPixelId(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::ExtMonFNALPixelId[nElements] : new ::mu2e::ExtMonFNALPixelId[nElements];
   }
   // Wrapper around operator delete
   static void delete_mu2ecLcLExtMonFNALPixelId(void *p) {
      delete ((::mu2e::ExtMonFNALPixelId*)p);
   }
   static void deleteArray_mu2ecLcLExtMonFNALPixelId(void *p) {
      delete [] ((::mu2e::ExtMonFNALPixelId*)p);
   }
   static void destruct_mu2ecLcLExtMonFNALPixelId(void *p) {
      typedef ::mu2e::ExtMonFNALPixelId current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::ExtMonFNALPixelId

namespace ROOT {
   // Wrappers around operator new
   static void *new_mu2ecLcLIndexMap(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::IndexMap : new ::mu2e::IndexMap;
   }
   static void *newArray_mu2ecLcLIndexMap(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::mu2e::IndexMap[nElements] : new ::mu2e::IndexMap[nElements];
   }
   // Wrapper around operator delete
   static void delete_mu2ecLcLIndexMap(void *p) {
      delete ((::mu2e::IndexMap*)p);
   }
   static void deleteArray_mu2ecLcLIndexMap(void *p) {
      delete [] ((::mu2e::IndexMap*)p);
   }
   static void destruct_mu2ecLcLIndexMap(void *p) {
      typedef ::mu2e::IndexMap current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mu2e::IndexMap

namespace ROOT {
   // Wrappers around operator new
   static void *new_boostcLcLarraylEdoublecO5gR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::boost::array<double,5> : new ::boost::array<double,5>;
   }
   static void *newArray_boostcLcLarraylEdoublecO5gR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::boost::array<double,5>[nElements] : new ::boost::array<double,5>[nElements];
   }
   // Wrapper around operator delete
   static void delete_boostcLcLarraylEdoublecO5gR(void *p) {
      delete ((::boost::array<double,5>*)p);
   }
   static void deleteArray_boostcLcLarraylEdoublecO5gR(void *p) {
      delete [] ((::boost::array<double,5>*)p);
   }
   static void destruct_boostcLcLarraylEdoublecO5gR(void *p) {
      typedef ::boost::array<double,5> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::boost::array<double,5>

namespace ROOT {
   // Wrappers around operator new
   static void *new_CLHEPcLcLHepRotationX(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::CLHEP::HepRotationX : new ::CLHEP::HepRotationX;
   }
   static void *newArray_CLHEPcLcLHepRotationX(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::CLHEP::HepRotationX[nElements] : new ::CLHEP::HepRotationX[nElements];
   }
   // Wrapper around operator delete
   static void delete_CLHEPcLcLHepRotationX(void *p) {
      delete ((::CLHEP::HepRotationX*)p);
   }
   static void deleteArray_CLHEPcLcLHepRotationX(void *p) {
      delete [] ((::CLHEP::HepRotationX*)p);
   }
   static void destruct_CLHEPcLcLHepRotationX(void *p) {
      typedef ::CLHEP::HepRotationX current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CLHEP::HepRotationX

namespace ROOT {
   // Wrappers around operator new
   static void *new_CLHEPcLcLHepRotationY(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::CLHEP::HepRotationY : new ::CLHEP::HepRotationY;
   }
   static void *newArray_CLHEPcLcLHepRotationY(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::CLHEP::HepRotationY[nElements] : new ::CLHEP::HepRotationY[nElements];
   }
   // Wrapper around operator delete
   static void delete_CLHEPcLcLHepRotationY(void *p) {
      delete ((::CLHEP::HepRotationY*)p);
   }
   static void deleteArray_CLHEPcLcLHepRotationY(void *p) {
      delete [] ((::CLHEP::HepRotationY*)p);
   }
   static void destruct_CLHEPcLcLHepRotationY(void *p) {
      typedef ::CLHEP::HepRotationY current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CLHEP::HepRotationY

namespace ROOT {
   // Wrappers around operator new
   static void *new_CLHEPcLcLHepRotationZ(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::CLHEP::HepRotationZ : new ::CLHEP::HepRotationZ;
   }
   static void *newArray_CLHEPcLcLHepRotationZ(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::CLHEP::HepRotationZ[nElements] : new ::CLHEP::HepRotationZ[nElements];
   }
   // Wrapper around operator delete
   static void delete_CLHEPcLcLHepRotationZ(void *p) {
      delete ((::CLHEP::HepRotationZ*)p);
   }
   static void deleteArray_CLHEPcLcLHepRotationZ(void *p) {
      delete [] ((::CLHEP::HepRotationZ*)p);
   }
   static void destruct_CLHEPcLcLHepRotationZ(void *p) {
      typedef ::CLHEP::HepRotationZ current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CLHEP::HepRotationZ

namespace ROOT {
   // Wrappers around operator new
   static void *new_CLHEPcLcLHepRotation(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::CLHEP::HepRotation : new ::CLHEP::HepRotation;
   }
   static void *newArray_CLHEPcLcLHepRotation(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::CLHEP::HepRotation[nElements] : new ::CLHEP::HepRotation[nElements];
   }
   // Wrapper around operator delete
   static void delete_CLHEPcLcLHepRotation(void *p) {
      delete ((::CLHEP::HepRotation*)p);
   }
   static void deleteArray_CLHEPcLcLHepRotation(void *p) {
      delete [] ((::CLHEP::HepRotation*)p);
   }
   static void destruct_CLHEPcLcLHepRotation(void *p) {
      typedef ::CLHEP::HepRotation current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CLHEP::HepRotation

namespace ROOT {
   // Wrappers around operator new
   static void *new_HepGeomcLcLTransform3D(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::HepGeom::Transform3D : new ::HepGeom::Transform3D;
   }
   static void *newArray_HepGeomcLcLTransform3D(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::HepGeom::Transform3D[nElements] : new ::HepGeom::Transform3D[nElements];
   }
   // Wrapper around operator delete
   static void delete_HepGeomcLcLTransform3D(void *p) {
      delete ((::HepGeom::Transform3D*)p);
   }
   static void deleteArray_HepGeomcLcLTransform3D(void *p) {
      delete [] ((::HepGeom::Transform3D*)p);
   }
   static void destruct_HepGeomcLcLTransform3D(void *p) {
      typedef ::HepGeom::Transform3D current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HepGeom::Transform3D

namespace ROOT {
   // Wrappers around operator new
   static void *new_artcLcLWrapperlEmu2ecLcLIndexMapgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::art::Wrapper<mu2e::IndexMap> : new ::art::Wrapper<mu2e::IndexMap>;
   }
   static void *newArray_artcLcLWrapperlEmu2ecLcLIndexMapgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::art::Wrapper<mu2e::IndexMap>[nElements] : new ::art::Wrapper<mu2e::IndexMap>[nElements];
   }
   // Wrapper around operator delete
   static void delete_artcLcLWrapperlEmu2ecLcLIndexMapgR(void *p) {
      delete ((::art::Wrapper<mu2e::IndexMap>*)p);
   }
   static void deleteArray_artcLcLWrapperlEmu2ecLcLIndexMapgR(void *p) {
      delete [] ((::art::Wrapper<mu2e::IndexMap>*)p);
   }
   static void destruct_artcLcLWrapperlEmu2ecLcLIndexMapgR(void *p) {
      typedef ::art::Wrapper<mu2e::IndexMap> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::art::Wrapper<mu2e::IndexMap>

namespace ROOT {
   static TClass *vectorlEcetcLcLmap_vector_keygR_Dictionary();
   static void vectorlEcetcLcLmap_vector_keygR_TClassManip(TClass*);
   static void *new_vectorlEcetcLcLmap_vector_keygR(void *p = 0);
   static void *newArray_vectorlEcetcLcLmap_vector_keygR(Long_t size, void *p);
   static void delete_vectorlEcetcLcLmap_vector_keygR(void *p);
   static void deleteArray_vectorlEcetcLcLmap_vector_keygR(void *p);
   static void destruct_vectorlEcetcLcLmap_vector_keygR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<cet::map_vector_key>*)
   {
      vector<cet::map_vector_key> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<cet::map_vector_key>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<cet::map_vector_key>", -2, "vector", 214,
                  typeid(vector<cet::map_vector_key>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEcetcLcLmap_vector_keygR_Dictionary, isa_proxy, 4,
                  sizeof(vector<cet::map_vector_key>) );
      instance.SetNew(&new_vectorlEcetcLcLmap_vector_keygR);
      instance.SetNewArray(&newArray_vectorlEcetcLcLmap_vector_keygR);
      instance.SetDelete(&delete_vectorlEcetcLcLmap_vector_keygR);
      instance.SetDeleteArray(&deleteArray_vectorlEcetcLcLmap_vector_keygR);
      instance.SetDestructor(&destruct_vectorlEcetcLcLmap_vector_keygR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<cet::map_vector_key> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<cet::map_vector_key>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEcetcLcLmap_vector_keygR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<cet::map_vector_key>*)0x0)->GetClass();
      vectorlEcetcLcLmap_vector_keygR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEcetcLcLmap_vector_keygR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEcetcLcLmap_vector_keygR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<cet::map_vector_key> : new vector<cet::map_vector_key>;
   }
   static void *newArray_vectorlEcetcLcLmap_vector_keygR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<cet::map_vector_key>[nElements] : new vector<cet::map_vector_key>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEcetcLcLmap_vector_keygR(void *p) {
      delete ((vector<cet::map_vector_key>*)p);
   }
   static void deleteArray_vectorlEcetcLcLmap_vector_keygR(void *p) {
      delete [] ((vector<cet::map_vector_key>*)p);
   }
   static void destruct_vectorlEcetcLcLmap_vector_keygR(void *p) {
      typedef vector<cet::map_vector_key> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<cet::map_vector_key>

namespace ROOT {
   static TClass *vectorlECLHEPcLcLHep2VectorgR_Dictionary();
   static void vectorlECLHEPcLcLHep2VectorgR_TClassManip(TClass*);
   static void *new_vectorlECLHEPcLcLHep2VectorgR(void *p = 0);
   static void *newArray_vectorlECLHEPcLcLHep2VectorgR(Long_t size, void *p);
   static void delete_vectorlECLHEPcLcLHep2VectorgR(void *p);
   static void deleteArray_vectorlECLHEPcLcLHep2VectorgR(void *p);
   static void destruct_vectorlECLHEPcLcLHep2VectorgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<CLHEP::Hep2Vector>*)
   {
      vector<CLHEP::Hep2Vector> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<CLHEP::Hep2Vector>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<CLHEP::Hep2Vector>", -2, "vector", 214,
                  typeid(vector<CLHEP::Hep2Vector>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlECLHEPcLcLHep2VectorgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<CLHEP::Hep2Vector>) );
      instance.SetNew(&new_vectorlECLHEPcLcLHep2VectorgR);
      instance.SetNewArray(&newArray_vectorlECLHEPcLcLHep2VectorgR);
      instance.SetDelete(&delete_vectorlECLHEPcLcLHep2VectorgR);
      instance.SetDeleteArray(&deleteArray_vectorlECLHEPcLcLHep2VectorgR);
      instance.SetDestructor(&destruct_vectorlECLHEPcLcLHep2VectorgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<CLHEP::Hep2Vector> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<CLHEP::Hep2Vector>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlECLHEPcLcLHep2VectorgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<CLHEP::Hep2Vector>*)0x0)->GetClass();
      vectorlECLHEPcLcLHep2VectorgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlECLHEPcLcLHep2VectorgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlECLHEPcLcLHep2VectorgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<CLHEP::Hep2Vector> : new vector<CLHEP::Hep2Vector>;
   }
   static void *newArray_vectorlECLHEPcLcLHep2VectorgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<CLHEP::Hep2Vector>[nElements] : new vector<CLHEP::Hep2Vector>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlECLHEPcLcLHep2VectorgR(void *p) {
      delete ((vector<CLHEP::Hep2Vector>*)p);
   }
   static void deleteArray_vectorlECLHEPcLcLHep2VectorgR(void *p) {
      delete [] ((vector<CLHEP::Hep2Vector>*)p);
   }
   static void destruct_vectorlECLHEPcLcLHep2VectorgR(void *p) {
      typedef vector<CLHEP::Hep2Vector> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<CLHEP::Hep2Vector>

namespace {
  void TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_DataProducts_dict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"Mu2eG4/src",
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
#line 1 "libmu2e_dOdO_dOdO_DataProducts_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace mu2e{class __attribute__((annotate("$clingAutoload$DataProducts/inc/CRSScintillatorBarIndex.hh")))  CRSScintillatorBarIndex;}
namespace mu2e{class __attribute__((annotate("$clingAutoload$DataProducts/inc/StrawIndex.hh")))  StrawIndex;}
namespace mu2e{class __attribute__((annotate("$clingAutoload$DataProducts/inc/PanelId.hh")))  __attribute__((annotate("$clingAutoload$DataProducts/inc/StrawId.hh")))  PanelId;}
namespace mu2e{class __attribute__((annotate("$clingAutoload$DataProducts/inc/LayerId.hh")))  __attribute__((annotate("$clingAutoload$DataProducts/inc/StrawId.hh")))  LayerId;}
namespace mu2e{class __attribute__((annotate("$clingAutoload$DataProducts/inc/StrawId.hh")))  StrawId;}
namespace mu2e{class __attribute__((annotate("$clingAutoload$DataProducts/inc/ExtMonFNALModuleId.hh")))  ExtMonFNALModuleId;}
namespace mu2e{class __attribute__((annotate("$clingAutoload$DataProducts/inc/ExtMonFNALChipId.hh")))  ExtMonFNALChipId;}
namespace mu2e{class __attribute__((annotate("$clingAutoload$DataProducts/inc/ExtMonFNALPixelId.hh")))  ExtMonFNALPixelId;}
namespace mu2e{class __attribute__((annotate("$clingAutoload$DataProducts/inc/IndexMap.hh")))  IndexMap;}
namespace CLHEP{class __attribute__((annotate("$clingAutoload$CLHEP/Vector/TwoVector.h")))  Hep2Vector;}
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
namespace cet{class __attribute__((annotate("$clingAutoload$cetlib/map_vector.h")))  __attribute__((annotate("$clingAutoload$canvas/Persistency/Common/Wrapper.h")))  map_vector_key;}
namespace boost{template <class T, std::size_t N> class __attribute__((annotate("$clingAutoload$boost/array.hpp")))  __attribute__((annotate("$clingAutoload$canvas/Persistency/Common/Wrapper.h")))  array;
}
namespace CLHEP{class __attribute__((annotate("$clingAutoload$CLHEP/Vector/RotationX.h")))  __attribute__((annotate("$clingAutoload$CLHEP/Vector/Rotation.h")))  HepRotationX;}
namespace CLHEP{class __attribute__((annotate("$clingAutoload$CLHEP/Vector/RotationY.h")))  __attribute__((annotate("$clingAutoload$CLHEP/Vector/Rotation.h")))  HepRotationY;}
namespace CLHEP{class __attribute__((annotate("$clingAutoload$CLHEP/Vector/RotationZ.h")))  __attribute__((annotate("$clingAutoload$CLHEP/Vector/Rotation.h")))  HepRotationZ;}
namespace CLHEP{class __attribute__((annotate("$clingAutoload$CLHEP/Vector/Rotation.h")))  HepRotation;}
namespace HepGeom{class __attribute__((annotate("$clingAutoload$CLHEP/Geometry/Transform3D.h")))  Transform3D;}
namespace art{template <typename T> class __attribute__((annotate("$clingAutoload$canvas/Persistency/Common/Wrapper.h")))  Wrapper;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libmu2e_dOdO_dOdO_DataProducts_dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef NDEBUG
  #define NDEBUG 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
//
// Original author Rob Kutschke
//

#include "DataProducts/inc/CRSScintillatorBarIndex.hh"
#include "DataProducts/inc/StrawIndex.hh"
#include "DataProducts/inc/StrawId.hh"
#include "DataProducts/inc/PanelId.hh"
#include "DataProducts/inc/LayerId.hh"
#include "DataProducts/inc/PlaneId.hh"
#include "DataProducts/inc/ExtMonFNALModuleId.hh"
#include "DataProducts/inc/ExtMonFNALChipId.hh"
#include "DataProducts/inc/ExtMonFNALPixelId.hh"
#include "DataProducts/inc/IndexMap.hh"

#include "canvas/Persistency/Common/Wrapper.h"
#include "cetlib/map_vector.h"
#include "boost/array.hpp"
#include <vector>

#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/RotationX.h"
#include "CLHEP/Vector/RotationY.h"
#include "CLHEP/Vector/RotationZ.h"
#include "CLHEP/Vector/EulerAngles.h"
#include <CLHEP/Geometry/Transform3D.h>
#include "CLHEP/Matrix/Vector.h"
#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Matrix/SymMatrix.h"

template class art::Wrapper<mu2e::IndexMap>;

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"CLHEP::HepRotation", payloadCode, "@",
"CLHEP::HepRotationX", payloadCode, "@",
"CLHEP::HepRotationY", payloadCode, "@",
"CLHEP::HepRotationZ", payloadCode, "@",
"HepGeom::Transform3D", payloadCode, "@",
"art::Wrapper<mu2e::IndexMap>", payloadCode, "@",
"boost::array<double,5>", payloadCode, "@",
"mu2e::CRSScintillatorBarIndex", payloadCode, "@",
"mu2e::ExtMonFNALChipId", payloadCode, "@",
"mu2e::ExtMonFNALModuleId", payloadCode, "@",
"mu2e::ExtMonFNALPixelId", payloadCode, "@",
"mu2e::IndexMap", payloadCode, "@",
"mu2e::LayerId", payloadCode, "@",
"mu2e::PanelId", payloadCode, "@",
"mu2e::StrawId", payloadCode, "@",
"mu2e::StrawIndex", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libmu2e_.._.._DataProducts_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_DataProducts_dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_DataProducts_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_DataProducts_dict() {
  TriggerDictionaryInitialization_libmu2e_dOdO_dOdO_DataProducts_dict_Impl();
}
