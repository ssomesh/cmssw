#if !defined(FWCORE_FRAMEWORK_EDLOOPER_H)
#define FWCORE_FRAMEWORK_EDLOOPER_H
// -*- C++ -*-
//
// Package:     Framework
// Module:      EDLooper
// 
/**\class EDLooper EDLooper.h package/EDLooper.h

 Description: Base class for all looping components

 Usage:
    <usage>

*/
//
// Author:      Valentin Kuznetsov
// Created:     Wed Jul  5 11:42:17 EDT 2006
// $Id$
//
// Revision history
//
// $Log$

// system include files
#include <string>
#include <set>

// user include files
#include "DataFormats/Common/interface/PassID.h"
#include "FWCore/Framework/interface/ProducerBase.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDLooperHelper.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

// forward declarations

namespace edm {
  namespace eventsetup {
    class EventSetupRecordKey;
  }
class EDLooper
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum Status {kContinue, kStop};

      // ---------- Constructors and destructor ----------------
      EDLooper();
      virtual ~EDLooper();

      // ---------- member functions ---------------------------
      virtual void beginOfJob(const edm::EventSetup&); 
      virtual void startingNewLoop(unsigned int ) = 0; 
      virtual Status duringLoop(const edm::Event&, const edm::EventSetup&) = 0; 
      virtual Status endOfLoop(const edm::EventSetup&) = 0; 
      virtual void endOfJob();
      void loop(EDLooperHelper& iHelper, unsigned long numberToProcess); 
      void setLooperName(const std::string& name) {name_=name;};
      void setLooperPassID(const PassID& id) {passID_=id; processID_=passID_; }
      PassID getLooperPassID() {return passID_;}
      std::string getLooperName() {return name_;}

      // ---------- const member functions ---------------------
      virtual std::set<eventsetup::EventSetupRecordKey> modifyingRecords() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      EDLooper( const EDLooper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const EDLooper& operator=( const EDLooper& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      std::string name_;
      PassID passID_, processID_;

      // ---------- static data members ------------------------

};

// inline function definitions

}

#endif /* FWCORE_FRAMEWORK_EDLOOPER_H */
