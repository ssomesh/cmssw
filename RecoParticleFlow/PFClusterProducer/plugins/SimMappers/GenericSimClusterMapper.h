#ifndef __RecoParticleFlow_PFClusterProducer_GenericSimClusterMapper_H__
#define __RecoParticleFlow_PFClusterProducer_GenericSimClusterMapper_H__
#include "FWCore/Framework/interface/ESHandle.h"
#include "RecoParticleFlow/PFClusterProducer/interface/InitialClusteringStepBase.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHitFraction.h"

#include "RecoLocalCalo/HGCalRecAlgos/interface/RecHitTools.h"
#include "SimDataFormats/CaloAnalysis/interface/SimClusterFwd.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"



class GenericSimClusterMapper : public InitialClusteringStepBase {
  typedef GenericSimClusterMapper B2DGT;
 public:
 GenericSimClusterMapper(const edm::ParameterSet& conf,
			 edm::ConsumesCollector& sumes) :
    InitialClusteringStepBase(conf,sumes) { 
      _simClusterToken = sumes.consumes<SimClusterCollection>(conf.getParameter<edm::InputTag>("simClusterSrc"));
    }
  virtual ~GenericSimClusterMapper() {}
  GenericSimClusterMapper(const B2DGT&) = delete;
  B2DGT& operator=(const B2DGT&) = delete;

  virtual void updateEvent(const edm::Event&) override final;
  virtual void update(const edm::EventSetup&) override final;

  void buildClusters(const edm::Handle<reco::PFRecHitCollection>&,
		     const std::vector<bool>&,
		     const std::vector<bool>&, 
		     reco::PFClusterCollection&) override;
  
 private:  
  void retrieveLayerZPositions();
  edm::EDGetTokenT<SimClusterCollection> _simClusterToken;
  edm::Handle<SimClusterCollection> _simClusterH;
  hgcal::RecHitTools _rhtools;
  const MagneticField* _bField;
  std::vector<float> _layerZPositions;



};

DEFINE_EDM_PLUGIN(InitialClusteringStepFactory,
		  GenericSimClusterMapper,
		  "GenericSimClusterMapper");

#endif
