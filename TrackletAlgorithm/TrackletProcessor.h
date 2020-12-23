#ifndef TrackletAlgorithm_TrackletProcessor_h
#define TrackletAlgorithm_TrackletProcessor_h

#include <cmath>

#include "AllStubMemory.h"
#include "AllStubInnerMemory.h"
#include "TrackletParameterMemory.h"
#include "TrackletProjectionMemory.h"
#include "VMStubTEOuterMemoryCM.h"
#include "TEBuffer.h"
#include "TrackletEngineUnit.h"


namespace TC {
////////////////////////////////////////////////////////////////////////////////
// Typedefs, enums, and constants needed by TrackletCalculator.
////////////////////////////////////////////////////////////////////////////////
  namespace Types {
    typedef ap_uint<2> nASMem;

    typedef ap_int<13> rmean;
    typedef ap_int<14> zmean;
    typedef ap_int<15> rinv;
    typedef ap_int<11> z0;
    typedef ap_uint<20> phiL;
    typedef ap_int<15> zL;
    typedef ap_int<11> der_phiL;
    typedef ap_int<10> der_zL;
    typedef ap_uint<16> phiD;
    typedef ap_int<14> rD;
    typedef ap_int<10> der_phiD;
    typedef ap_int<10> der_rD;
    typedef ap_uint<1> flag;
  }

  enum seed {UNDEF_SEED, L1L2 = 0, L2L3 = 1, L3L4 = 2, L5L6 = 3, D1D2 = 4, D3D4 = 5, L1D1 = 6, L2D1 = 7};
  enum itc {UNDEF_ITC, A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7, I = 8, J = 9, K = 10, L = 11, M = 12, N = 13, O = 14};
  enum layer {L1 = 0, L2 = 1, L3 = 2, L4 = 3, L5 = 4, L6 = 5};
  enum disk {D1 = 0, D2 = 1, D3 = 2, D4 = 3, D5 = 4};
  enum projout_index_barrel_ps {L1PHIA = 0, L1PHIB = 1, L1PHIC = 2, L1PHID = 3, L1PHIE = 4, L1PHIF = 5, L1PHIG = 6, L1PHIH = 7, L2PHIA = 8, L2PHIB = 9, L2PHIC = 10, L2PHID = 11, L3PHIA = 12, L3PHIB = 13, L3PHIC = 14, L3PHID = 15, N_PROJOUT_BARRELPS = 16};
  enum projout_index_barrel_2s {L4PHIA = 0, L4PHIB = 1, L4PHIC = 2, L4PHID = 3, L5PHIA = 4, L5PHIB = 5, L5PHIC = 6, L5PHID = 7, L6PHIA = 8, L6PHIB = 9, L6PHIC = 10, L6PHID = 11, N_PROJOUT_BARREL2S = 12};
  enum projout_index_disk      {D1PHIA = 0, D1PHIB = 1, D1PHIC = 2, D1PHID = 3, D2PHIA = 4, D2PHIB = 5, D2PHIC = 6, D2PHID = 7, D3PHIA = 8, D3PHIB = 9, D3PHIC = 10, D3PHID = 11, D4PHIA = 12, D4PHIB = 13, D4PHIC = 14, D4PHID = 15, N_PROJOUT_DISK = 16};

  static const uint8_t nproj_L1 = L1PHIH - L1PHIA + 1;
  static const uint8_t nproj_L2 = L2PHID - L2PHIA + 1;
  static const uint8_t nproj_L3 = L3PHID - L3PHIA + 1;
  static const uint8_t nproj_L4 = L4PHID - L4PHIA + 1;
  static const uint8_t nproj_L5 = L5PHID - L5PHIA + 1;
  static const uint8_t nproj_L6 = L6PHID - L6PHIA + 1;
  static const uint8_t nproj_D1 = D1PHID - D1PHIA + 1;
  static const uint8_t nproj_D2 = D2PHID - D2PHIA + 1;
  static const uint8_t nproj_D3 = D3PHID - D3PHIA + 1;
  static const uint8_t nproj_D4 = D4PHID - D4PHIA + 1;

  static const uint8_t shift_L1 = 0;
  static const uint8_t shift_L2 = shift_L1 + nproj_L1;
  static const uint8_t shift_L3 = shift_L2 + nproj_L2;
  static const uint8_t shift_L4 = shift_L3 + nproj_L3;
  static const uint8_t shift_L5 = shift_L4 + nproj_L4;
  static const uint8_t shift_L6 = shift_L5 + nproj_L5;

  static const uint8_t shift_D1 = 0;
  static const uint8_t shift_D2 = shift_D1 + nproj_D1;
  static const uint8_t shift_D3 = shift_D2 + nproj_D2;
  static const uint8_t shift_D4 = shift_D3 + nproj_D3;

  static const uint32_t mask_L1 = 0xFF << shift_L1;
  static const uint32_t mask_L2 = 0xF << shift_L2;
  static const uint32_t mask_L3 = 0xF << shift_L3;
  static const uint32_t mask_L4 = 0xF << shift_L4;
  static const uint32_t mask_L5 = 0xF << shift_L5;
  static const uint32_t mask_L6 = 0xF << shift_L6;
  static const uint32_t mask_D1 = 0xF << shift_D1;
  static const uint32_t mask_D2 = 0xF << shift_D2;
  static const uint32_t mask_D3 = 0xF << shift_D3;
  static const uint32_t mask_D4 = 0xF << shift_D4;

// the 1.0e-1 is a fudge factor needed to get the floating point truncation
// right
  static const float ptcut = 1.91;
  static const ap_uint<13> rinvcut = 0.01 * 0.299792458 * 3.8112 / ptcut / krinv;
  static const ap_uint<9> z0cut_L1L2 = 15.0 / kz0 + 1.0e-1;
  static const ap_uint<9> z0cut = 1.5 * 15.0 / kz0 + 1.0e-1;
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions that are defined in TrackletCalculator_calculate_LXLY.h,
// TrackletProcessor.cc, and the bottom of this file.
////////////////////////////////////////////////////////////////////////////////
  template<seed Seed, regionType InnerRegion, regionType OuterRegion>
  void calculate_LXLY (
    const typename AllStub<InnerRegion>::ASR r1_input,
    const typename AllStub<InnerRegion>::ASPHI phi1_input,
    const typename AllStub<InnerRegion>::ASZ z1_input,
    const typename AllStub<OuterRegion>::ASR r2_input,
    const typename AllStub<OuterRegion>::ASPHI phi2_input,
    const typename AllStub<OuterRegion>::ASZ z2_input,
    const Types::rmean r1mean_input,
    const Types::rmean r2mean_input,
    const Types::rmean rproj0_input,
    const Types::rmean rproj1_input,
    const Types::rmean rproj2_input,
    const Types::rmean rproj3_input,
    const Types::zmean zproj0_input,
    const Types::zmean zproj1_input,
    const Types::zmean zproj2_input,
    const Types::zmean zproj3_input,

    Types::rinv * const rinv_output,
    TrackletParameters::PHI0PAR * const phi0_output,
    TrackletParameters::TPAR * const t_output,
    Types::z0 * const z0_output,
    Types::phiL * const phiL_0_output,
    Types::phiL * const phiL_1_output,
    Types::phiL * const phiL_2_output,
    Types::phiL * const phiL_3_output,
    Types::zL * const zL_0_output,
    Types::zL * const zL_1_output,
    Types::zL * const zL_2_output,
    Types::zL * const zL_3_output,
    Types::der_phiL * const der_phiL_output,
    Types::der_zL * const der_zL_output,
    Types::phiD * const phiD_0_output,
    Types::phiD * const phiD_1_output,
    Types::phiD * const phiD_2_output,
    Types::phiD * const phiD_3_output,
    Types::rD * const rD_0_output,
    Types::rD * const rD_1_output,
    Types::rD * const rD_2_output,
    Types::rD * const rD_3_output,
    Types::der_phiD * const der_phiD_output,
    Types::der_rD * const der_rD_output
  );

  template<seed Seed, regionType InnerRegion, regionType OuterRegion> bool barrelSeeding(const AllStub<InnerRegion> &innerStub, const AllStub<OuterRegion> &outerStub, Types::rinv * const rinv, TrackletParameters::PHI0PAR * const phi0, Types::z0 * const z0, TrackletParameters::TPAR * const t, Types::phiL phiL[4], Types::zL zL[4], Types::der_phiL * const der_phiL, Types::der_zL * const der_zL, Types::flag valid_proj[4], Types::phiD phiD[4], Types::rD rD[4], Types::der_phiD * const der_phiD, Types::der_rD * const der_rD, Types::flag valid_proj_disk[4]);

  template<seed Seed, itc iTC> const TrackletProjection<BARRELPS>::TProjTCID ID();

  template<regionType TProjType, uint8_t NProjOut, uint32_t TPROJMask> bool addProj(const TrackletProjection<TProjType> &proj, const BXType bx, TrackletProjectionMemory<TProjType> projout[NProjOut], int nproj[NProjOut], const bool success);

  template<TC::seed Seed, regionType InnerRegion, regionType OuterRegion, uint32_t TPROJMaskBarrel, uint32_t TPROJMaskDisk> void
    processStubPair(
		    const BXType bx,
		    const ap_uint<kNBits_MemAddr> innerIndex,
		    const AllStub<InnerRegion> &innerStub,
		    const ap_uint<kNBits_MemAddr>  outerIndex,
		    const AllStub<OuterRegion> &outerStub,
		    const TrackletProjection<BARRELPS>::TProjTCID TCID,
		    TrackletProjection<BARRELPS>::TProjTrackletIndex &trackletIndex,
		    TrackletParameterMemory * const trackletParameters,
		    TrackletProjectionMemory<BARRELPS> projout_barrel_ps[N_PROJOUT_BARRELPS],
		    TrackletProjectionMemory<BARREL2S> projout_barrel_2s[N_PROJOUT_BARREL2S],
		    TrackletProjectionMemory<DISK> projout_disk[N_PROJOUT_DISK],
		    int &npar,
		    int nproj_barrel_ps[N_PROJOUT_BARRELPS],
		    int nproj_barrel_2s[N_PROJOUT_BARREL2S],
		    int nproj_disk[N_PROJOUT_DISK]
		    );


}

template<TC::seed Seed> constexpr regionType InnerRegion() {
  return (
    (Seed == TC::L1L2 || Seed == TC::L2L3 || Seed == TC::L3L4 || Seed == TC::L1D1 || Seed == TC::L2D1) ? BARRELPS : (
      (Seed == TC::L5L6) ? BARREL2S : DISK
    )
  );
}
template<TC::seed Seed> constexpr regionType OuterRegion() {
  return (
    (Seed == TC::L1L2 || Seed == TC::L2L3) ? BARRELPS : (
      (Seed == TC::L3L4 || Seed == TC::L5L6) ? BARREL2S : DISK
    )
  );
}
template<TC::seed Seed, TC::itc iTC> constexpr uint8_t NASMemInner();
template<TC::seed Seed, TC::itc iTC> constexpr uint8_t NASMemOuter();
template<TC::seed Seed, TC::itc iTC> constexpr uint8_t NSPMem();
template<TC::seed Seed, TC::itc iTC> constexpr uint16_t ASInnerMask();
template<TC::seed Seed, TC::itc iTC> constexpr uint16_t ASOuterMask();
template<TC::seed Seed, TC::itc iTC> constexpr uint32_t TPROJMaskBarrel();
template<TC::seed Seed, TC::itc iTC> constexpr uint32_t TPROJMaskDisk();

ap_uint<1> nearFullTEBuff(const ap_uint<3>&, const ap_uint<3>&);
ap_uint<(1<<(2*TrackletEngineUnit<BARRELPS>::kNBitsBuffer))> nearFullTEUnitInit();

void TrackletProcessor_L1L2D(const BXType bx,
			     const ap_uint<1+2*TrackletEngineUnit<BARRELPS>::kNBitsRZFine+TrackletEngineUnit<BARRELPS>::kNBitsRZBin> lut[1<<(kNbitszfinebintable+kNbitsrfinebintable)],
			     const ap_uint<(1<<TrackletEngineUnit<BARRELPS>::kNBitsPhiBins)> regionlut[1<<(AllStubInner<BARRELPS>::kASBendSize+AllStubInner<BARRELPS>::kASFinePhiSize)],
			     const AllStubInnerMemory<BARRELPS> innerStubs[2],
			     const AllStubMemory<BARRELPS>* outerStubs,
			     const VMStubTEOuterMemoryCM<BARRELPS,3,3,4> outerVMStubs,
			     TrackletParameterMemory * trackletParameters,
			     TrackletProjectionMemory<BARRELPS> projout_barrel_ps[TC::N_PROJOUT_BARRELPS],
			     TrackletProjectionMemory<BARREL2S> projout_barrel_2s[TC::N_PROJOUT_BARREL2S],
			     TrackletProjectionMemory<DISK> projout_disk[TC::N_PROJOUT_DISK]
			     );

////////////////////////////////////////////////////////////////////////////////

#include "TrackletCalculator_calculate_LXLY.h"
#include "TrackletProcessor_parameters.h"

// This function calls calculate_LXLY, defined in
// TrackletCalculator_calculate_LXLY.h, and applies cuts to the results.
template<TC::seed Seed, regionType InnerRegion, regionType OuterRegion> bool
TC::barrelSeeding(const AllStub<InnerRegion> &innerStub, const AllStub<OuterRegion> &outerStub, TC::Types::rinv * const rinv, TrackletParameters::PHI0PAR * const phi0, TC::Types::z0 * const z0, TrackletParameters::TPAR * const t, TC::Types::phiL phiL[4], TC::Types::zL zL[4], TC::Types::der_phiL * const der_phiL, TC::Types::der_zL * const der_zL, TC::Types::flag valid_proj[4], TC::Types::phiD phiD[4], TC::Types::rD rD[4], TC::Types::der_phiD * const der_phiD, TC::Types::der_rD * const der_rD, TC::Types::flag valid_proj_disk[4])
{
  TC::Types::rmean r1mean, r2mean, rproj[4];
  switch (Seed) {
    case TC::L1L2:
      r1mean   = rmean[L1];
      r2mean   = rmean[L2];
      rproj[0] = rmean[L3];
      rproj[1] = rmean[L4];
      rproj[2] = rmean[L5];
      rproj[3] = rmean[L6];
      break;
    case TC::L3L4:
      rproj[0] = rmean[L1];
      rproj[1] = rmean[L2];
      r1mean   = rmean[L3];
      r2mean   = rmean[L4];
      rproj[2] = rmean[L5];
      rproj[3] = rmean[L6];
      break;
    case TC::L5L6:
      rproj[0] = rmean[L1];
      rproj[1] = rmean[L2];
      rproj[2] = rmean[L3];
      rproj[3] = rmean[L4];
      r1mean   = rmean[L5];
      r2mean   = rmean[L6];
      break;
  }
  TC::Types::zmean zproj[4] = {zmean[D1], zmean[D2], zmean[D3], zmean[D4]};
  calculate_LXLY<Seed, InnerRegion, OuterRegion>(
      innerStub.getR(),
      innerStub.getPhi(),
      innerStub.getZ(),
      outerStub.getR(),
      outerStub.getPhi(),
      outerStub.getZ(),
      r1mean,
      r2mean,
      rproj[0],
      rproj[1],
      rproj[2],
      rproj[3],
      zproj[0],
      zproj[1],
      zproj[2],
      zproj[3],

      rinv,
      phi0,
      t,
      z0,
      &phiL[0],
      &phiL[1],
      &phiL[2],
      &phiL[3],
      &zL[0],
      &zL[1],
      &zL[2],
      &zL[3],
      der_phiL,
      der_zL,
      &phiD[0],
      &phiD[1],
      &phiD[2],
      &phiD[3],
      &rD[0],
      &rD[1],
      &rD[2],
      &rD[3],
      der_phiD,
      der_rD
  );

  //return false; //ryd

// Determine which layer projections are valid.
  valid_proj: for (ap_uint<3> i = 0; i < 4; i++) {
#pragma HLS unroll

    bool valid_zmin=zL[i] >= -(1 << (TrackletProjection<BARRELPS>::kTProjRZSize - 1));
    bool valid_zmax=zL[i] < (1 << (TrackletProjection<BARRELPS>::kTProjRZSize - 1));
    bool valid_phimax=phiL[i] < ((1 << TrackletProjection<BARREL2S>::kTProjPhiSize) - 1);
    bool valid_phimin=phiL[i] > 0;

    valid_proj[i] = valid_zmin && valid_zmax && valid_phimax && valid_phimin;

    /*
    valid_proj[i] = true;
    if (zL[i] < -(1 << (TrackletProjection<BARRELPS>::kTProjRZSize - 1)))
      valid_proj[i] = false;
    if (zL[i] >= (1 << (TrackletProjection<BARRELPS>::kTProjRZSize - 1)))
      valid_proj[i] = false;
    if (phiL[i] >= ((1 << TrackletProjection<BARREL2S>::kTProjPhiSize) - 1))
      valid_proj[i] = false;
    if (phiL[i] <= 0)
      valid_proj[i] = false;
    */

    if (rproj[i] < 2048) {
      phiL[i] >>= (TrackletProjection<BARREL2S>::kTProjPhiSize - TrackletProjection<BARRELPS>::kTProjPhiSize);
      if (phiL[i] >= (1 << TrackletProjection<BARRELPS>::kTProjPhiSize) - 1)
        phiL[i] = (1 << TrackletProjection<BARRELPS>::kTProjPhiSize) - 2;
    }
    else
      zL[i] >>= (TrackletProjection<BARRELPS>::kTProjRZSize - TrackletProjection<BARREL2S>::kTProjRZSize);
  }

// Determine which disk projections are valid.
  valid_proj_disk: for (ap_uint<3> i = 0; i < 4; i++) {
#pragma HLS unroll
    bool valid_t=abs(*t)>=512;
    bool valid_phimin=phiD[i]>0;
    bool valid_phimax=phiD[i]<(1 << TrackletProjection<BARRELPS>::kTProjPhiSize) - 1;
    bool valid_r=rD[i] >= 342 && rD[i] <= 2048;

    valid_proj_disk[i] = valid_t && valid_phimin && valid_phimax && valid_r;

  }

// Reject tracklets with too high a curvature or with too large a longitudinal
// impact parameter.

  bool valid_rinv=abs(*rinv) < rinvcut;
  bool valid_z0=abs(*z0) < ((Seed == TC::L1L2) ? z0cut_L1L2 : z0cut);

  const ap_int<TrackletParameters::kTParPhi0Size + 2> phicrit = *phi0 - (*rinv<<1);
  const bool keep = (phicrit > 9253) && (phicrit < 56269);

  return valid_rinv && valid_z0 && keep;
}

// Returns a unique identifier assigned to each TC.
template<TC::seed Seed, TC::itc iTC> const TrackletProjection<BARRELPS>::TProjTCID
TC::ID()
{
  return ((TrackletProjection<BARRELPS>::TProjTCID(Seed) << 4) + iTC);
}

// Writes a tracklet projection to the appropriate tracklet projection memory.
template<regionType TProjType, uint8_t NProjOut, uint32_t TPROJMask> bool
TC::addProj(const TrackletProjection<TProjType> &proj, const BXType bx, TrackletProjectionMemory<TProjType> projout[NProjOut], int nproj[NProjOut], const bool success)
{
  bool proj_success = true;

// Reject projections with extreme r/z values.
  if (TProjType != DISK) {
    if ((proj.getRZ() == (-(1 << (TrackletProjection<TProjType>::kTProjRZSize - 1))) || (proj.getRZ() == ((1 << (TrackletProjection<TProjType>::kTProjRZSize - 1)) - 1))))
      proj_success = false;
    if (abs(proj.getRZ()) > 2048)
      proj_success = false;
  }
  else {
    if (proj.getRZ() < 205 || proj.getRZ() > 1911)
      proj_success = false;
  }

// Fill correct TrackletProjectionMemory according to phi bin of projection.
  TC::Types::phiL phi = proj.getPhi() >> (TrackletProjection<TProjType>::kTProjPhiSize - 5);
  if (TProjType == BARRELPS && NProjOut == nproj_L1)
    phi >>= 2;
  else
    phi >>= 3;

  if (NProjOut > 0 && TPROJMask & (0x1 << 0) && success && proj_success && phi == 0)
    projout[0].write_mem(bx, proj, nproj[0]++);
  if (NProjOut > 1 && TPROJMask & (0x1 << 1) && success && proj_success && phi == 1)
    projout[1].write_mem(bx, proj, nproj[1]++);
  if (NProjOut > 2 && TPROJMask & (0x1 << 2) && success && proj_success && phi == 2)
    projout[2].write_mem(bx, proj, nproj[2]++);
  if (NProjOut > 3 && TPROJMask & (0x1 << 3) && success && proj_success && phi == 3)
    projout[3].write_mem(bx, proj, nproj[3]++);
  if (NProjOut > 4 && TPROJMask & (0x1 << 4) && success && proj_success && phi == 4)
    projout[4].write_mem(bx, proj, nproj[4]++);
  if (NProjOut > 5 && TPROJMask & (0x1 << 5) && success && proj_success && phi == 5)
    projout[5].write_mem(bx, proj, nproj[5]++);
  if (NProjOut > 6 && TPROJMask & (0x1 << 6) && success && proj_success && phi == 6)
    projout[6].write_mem(bx, proj, nproj[6]++);
  if (NProjOut > 7 && TPROJMask & (0x1 << 7) && success && proj_success && phi == 7)
    projout[7].write_mem(bx, proj, nproj[7]++);

  return (success && proj_success);
}

// Processes a given stub pair and writes the calculated tracklet parameters
// and tracklet projections to the appropriate memories.
template<TC::seed Seed, regionType InnerRegion, regionType OuterRegion, uint32_t TPROJMaskBarrel, uint32_t TPROJMaskDisk> void
TC::processStubPair(
    const BXType bx,
    const ap_uint<kNBits_MemAddr> innerIndex,
    const AllStub<InnerRegion> &innerStub,
    const ap_uint<kNBits_MemAddr>  outerIndex,
    const AllStub<OuterRegion> &outerStub,
    const TrackletProjection<BARRELPS>::TProjTCID TCID,
    TrackletProjection<BARRELPS>::TProjTrackletIndex &trackletIndex,
    TrackletParameterMemory * const trackletParameters,
    TrackletProjectionMemory<BARRELPS> projout_barrel_ps[N_PROJOUT_BARRELPS],
    TrackletProjectionMemory<BARREL2S> projout_barrel_2s[N_PROJOUT_BARREL2S],
    TrackletProjectionMemory<DISK> projout_disk[N_PROJOUT_DISK],
    int &npar,
    int nproj_barrel_ps[N_PROJOUT_BARRELPS],
    int nproj_barrel_2s[N_PROJOUT_BARREL2S],
    int nproj_disk[N_PROJOUT_DISK]
)
{
  TC::Types::rinv rinv;
  TrackletParameters::PHI0PAR phi0;
  TC::Types::z0 z0;
  TrackletParameters::TPAR t;
  TC::Types::phiL phiL[4];
  TC::Types::zL zL[4];
  TC::Types::der_phiL der_phiL;
  TC::Types::der_zL der_zL;
  TC::Types::flag valid_proj[4];
  TC::Types::phiD phiD[4];
  TC::Types::rD rD[4];
  TC::Types::der_phiD der_phiD;
  TC::Types::der_rD der_rD;
  TC::Types::flag valid_proj_disk[4];
  bool success;
#pragma HLS array_partition variable=rD complete

  //std::cout << "barrelSeeding: innerStub phi z r : "<<innerStub.getPhi()<<" "<<innerStub.getZ()<<" "<<innerStub.getR()<<std::endl;
  //std::cout << "barrelSeeding: outerStub phi z r : "<<outerStub.getPhi()<<" "<<outerStub.getZ()<<" "<<outerStub.getR()<<std::endl;


// Calculate the tracklet parameters and projections.
  success = TC::barrelSeeding<Seed, InnerRegion, OuterRegion>(innerStub, outerStub, &rinv, &phi0, &z0, &t, phiL, zL, &der_phiL, &der_zL, valid_proj, phiD, rD, &der_phiD, &der_rD, valid_proj_disk);

// Write the tracklet parameters and projections to the output memories.
  const TrackletParameters tpar(innerIndex, outerIndex, rinv, phi0, z0, t);
  if (success) trackletParameters->write_mem(bx, tpar, npar++);

  //return; //ryd

  bool addL3 = false, addL4 = false, addL5 = false, addL6 = false;

  switch (Seed) {
    case TC::L1L2:
      {
        const TrackletProjection<BARRELPS> tproj_L3(TCID, trackletIndex, phiL[0], zL[0], der_phiL, der_zL);
        const TrackletProjection<BARREL2S> tproj_L4(TCID, trackletIndex, phiL[1], zL[1], der_phiL, der_zL);
        const TrackletProjection<BARREL2S> tproj_L5(TCID, trackletIndex, phiL[2], zL[2], der_phiL, der_zL);
        const TrackletProjection<BARREL2S> tproj_L6(TCID, trackletIndex, phiL[3], zL[3], der_phiL, der_zL);

        addL3 = TC::addProj<BARRELPS, nproj_L3, ((TPROJMaskBarrel & mask_L3) >> shift_L3)> (tproj_L3, bx, &projout_barrel_ps[L3PHIA], &nproj_barrel_ps[L3PHIA], success && valid_proj[0]);
        addL4 = TC::addProj<BARREL2S, nproj_L4, ((TPROJMaskBarrel & mask_L4) >> shift_L4)> (tproj_L4, bx, &projout_barrel_2s[L4PHIA], &nproj_barrel_2s[L4PHIA], success && valid_proj[1]);
        addL5 = TC::addProj<BARREL2S, nproj_L5, ((TPROJMaskBarrel & mask_L5) >> shift_L5)> (tproj_L5, bx, &projout_barrel_2s[L5PHIA], &nproj_barrel_2s[L5PHIA], success && valid_proj[2]);
        addL6 = TC::addProj<BARREL2S, nproj_L6, ((TPROJMaskBarrel & mask_L6) >> shift_L6)> (tproj_L6, bx, &projout_barrel_2s[L6PHIA], &nproj_barrel_2s[L6PHIA], success && valid_proj[3]);
      }

      break;

    case TC::L3L4:
      {
        const TrackletProjection<BARRELPS> tproj_L1(TCID, trackletIndex, phiL[0], zL[0], der_phiL, der_zL);
        const TrackletProjection<BARRELPS> tproj_L2(TCID, trackletIndex, phiL[1], zL[1], der_phiL, der_zL);
        const TrackletProjection<BARREL2S> tproj_L5(TCID, trackletIndex, phiL[2], zL[2], der_phiL, der_zL);
        const TrackletProjection<BARREL2S> tproj_L6(TCID, trackletIndex, phiL[3], zL[3], der_phiL, der_zL);

        TC::addProj<BARRELPS, nproj_L1, ((TPROJMaskBarrel & mask_L1) >> shift_L1)> (tproj_L1, bx, &projout_barrel_ps[L1PHIA], &nproj_barrel_ps[L1PHIA], success && valid_proj[0]);
        TC::addProj<BARRELPS, nproj_L2, ((TPROJMaskBarrel & mask_L2) >> shift_L2)> (tproj_L2, bx, &projout_barrel_ps[L2PHIA], &nproj_barrel_ps[L2PHIA], success && valid_proj[1]);
        addL3 = addL4 = true;
        addL5 = TC::addProj<BARREL2S, nproj_L5, ((TPROJMaskBarrel & mask_L5) >> shift_L5)> (tproj_L5, bx, &projout_barrel_2s[L5PHIA], &nproj_barrel_2s[L5PHIA], success && valid_proj[2]);
        addL6 = TC::addProj<BARREL2S, nproj_L6, ((TPROJMaskBarrel & mask_L6) >> shift_L6)> (tproj_L6, bx, &projout_barrel_2s[L6PHIA], &nproj_barrel_2s[L6PHIA], success && valid_proj[3]);
      }

      break;

    case TC::L5L6:
      {
        const TrackletProjection<BARRELPS> tproj_L1(TCID, trackletIndex, phiL[0], zL[0], der_phiL, der_zL);
        const TrackletProjection<BARRELPS> tproj_L2(TCID, trackletIndex, phiL[1], zL[1], der_phiL, der_zL);
        const TrackletProjection<BARRELPS> tproj_L3(TCID, trackletIndex, phiL[2], zL[2], der_phiL, der_zL);
        const TrackletProjection<BARREL2S> tproj_L4(TCID, trackletIndex, phiL[3], zL[3], der_phiL, der_zL);

        TC::addProj<BARRELPS, nproj_L1, ((TPROJMaskBarrel & mask_L1) >> shift_L1)> (tproj_L1, bx, &projout_barrel_ps[L1PHIA], &nproj_barrel_ps[L1PHIA], success && valid_proj[0]);
        TC::addProj<BARRELPS, nproj_L2, ((TPROJMaskBarrel & mask_L2) >> shift_L2)> (tproj_L2, bx, &projout_barrel_ps[L2PHIA], &nproj_barrel_ps[L2PHIA], success && valid_proj[1]);
        addL3 = TC::addProj<BARRELPS, nproj_L3, ((TPROJMaskBarrel & mask_L3) >> shift_L3)> (tproj_L3, bx, &projout_barrel_ps[L3PHIA], &nproj_barrel_ps[L3PHIA], success && valid_proj[2]);
        addL4 = TC::addProj<BARREL2S, nproj_L4, ((TPROJMaskBarrel & mask_L4) >> shift_L4)> (tproj_L4, bx, &projout_barrel_2s[L4PHIA], &nproj_barrel_2s[L4PHIA], success && valid_proj[3]);
        addL5 = addL6 = true;
      }

      break;
  }

  const TrackletProjection<DISK> tproj_D1(TCID, trackletIndex, phiD[0], rD[0], der_phiD, der_rD);
  const TrackletProjection<DISK> tproj_D2(TCID, trackletIndex, phiD[1], rD[1], der_phiD, der_rD);
  const TrackletProjection<DISK> tproj_D3(TCID, trackletIndex, phiD[2], rD[2], der_phiD, der_rD);
  const TrackletProjection<DISK> tproj_D4(TCID, trackletIndex, phiD[3], rD[3], der_phiD, der_rD);

  TC::addProj<DISK, nproj_D1, ((TPROJMaskDisk & mask_D1) >> shift_D1)> (tproj_D1, bx, &projout_disk[D1PHIA], &nproj_disk[D1PHIA], success && valid_proj_disk[0] && !addL6);
  TC::addProj<DISK, nproj_D2, ((TPROJMaskDisk & mask_D2) >> shift_D2)> (tproj_D2, bx, &projout_disk[D2PHIA], &nproj_disk[D2PHIA], success && valid_proj_disk[1] && !addL5);
  TC::addProj<DISK, nproj_D3, ((TPROJMaskDisk & mask_D3) >> shift_D3)> (tproj_D3, bx, &projout_disk[D3PHIA], &nproj_disk[D3PHIA], success && valid_proj_disk[2] && !addL4);
  TC::addProj<DISK, nproj_D4, ((TPROJMaskDisk & mask_D4) >> shift_D4)> (tproj_D4, bx, &projout_disk[D4PHIA], &nproj_disk[D4PHIA], success && valid_proj_disk[3] && !addL3);

  if (success) trackletIndex++;
}



// This is the primary interface for the TrackletProcessor.
template<
TC::seed Seed, // seed layer combination (TC::L1L2, TC::L3L4, etc.)
  TC::itc iTC, // letter at the end of the TC name (TC_L1L2A and TC_L5L6A have
// the same iTC); generally indicates the region of the phi sector
             // being processed
  uint8_t NTEBuffer, //number of TE buffers
  uint8_t NTEUnits, //number of TE units
  regionType InnerRegion, // region type of the inner stubs
  regionType OuterRegion, // region type of the outer stubs
  uint8_t OuterPhiRegion, // outer phi region
  uint8_t RZBins,         // number of RZ bins in outer layer/disk
  uint8_t PhiBins,        // number of Phi bins in outer layer/dsik
  uint8_t NASMemInner, // number of inner all-stub memories
  uint16_t N // maximum number of steps
> void
TrackletProcessor(
    const BXType bx,
    const ap_uint<1+2*TrackletEngineUnit<BARRELPS>::kNBitsRZFine+TrackletEngineUnit<BARRELPS>::kNBitsRZBin> lut[1<<(kNbitszfinebintable+kNbitsrfinebintable)],
    const ap_uint<(1<<TrackletEngineUnit<BARRELPS>::kNBitsPhiBins)> regionlut[1<<(AllStubInner<BARRELPS>::kASBendSize+AllStubInner<BARRELPS>::kASFinePhiSize)],
    const AllStubInnerMemory<InnerRegion> innerStubs[NASMemInner],
    const AllStubMemory<OuterRegion>* outerStubs,
    const VMStubTEOuterMemoryCM<OuterRegion,RZBins,PhiBins,4> outerVMStubs,
    TrackletParameterMemory * const trackletParameters,
    TrackletProjectionMemory<BARRELPS> projout_barrel_ps[TC::N_PROJOUT_BARRELPS],
    TrackletProjectionMemory<BARREL2S> projout_barrel_2s[TC::N_PROJOUT_BARREL2S],
    TrackletProjectionMemory<DISK> projout_disk[TC::N_PROJOUT_DISK]
)
{

  static_assert(Seed == TC::L1L2, "Only L1L2 seeds have been implemented so far.");

  int npar = 0;
  int nproj_barrel_ps[TC::N_PROJOUT_BARRELPS] = {0};
  int nproj_barrel_2s[TC::N_PROJOUT_BARREL2S] = {0};
  int nproj_disk[TC::N_PROJOUT_DISK] = {0};
#pragma HLS array_partition variable=nproj_barrel_ps complete
#pragma HLS array_partition variable=nproj_barrel_2s complete
#pragma HLS array_partition variable=nproj_disk complete

// Clear all output memories before starting.
  trackletParameters->clear(bx);
 clear_barrel_ps: for (unsigned i = 0; i < TC::N_PROJOUT_BARRELPS; i++)
#pragma HLS unroll
    if (TPROJMaskBarrel<Seed, iTC>() & (0x1 << i))
      projout_barrel_ps[i].clear();
 clear_barrel_2s: for (unsigned i = 0; i < TC::N_PROJOUT_BARREL2S; i++)
#pragma HLS unroll
    if (TPROJMaskBarrel<Seed, iTC>() & (0x1 << (i + TC::N_PROJOUT_BARRELPS)))
      projout_barrel_2s[i].clear();
 clear_disk: for (unsigned i = 0; i < TC::N_PROJOUT_DISK; i++)
#pragma HLS unroll
    if (TPROJMaskDisk<Seed, iTC>() & (0x1 << i))
      projout_disk[i].clear();

  constexpr unsigned int NBitsPhiRegion=2;
  constexpr unsigned int NfinephiBits=NBitsPhiRegion+TrackletEngineUnit<BARRELPS>::kNBitsPhiBins+VMStubTEOuterBase<BARRELPS>::kVMSTEOFinePhiSize;

  static TEBuffer tebuffer[NTEBuffer];
#pragma HLS array_partition variable=tebuffer complete
  static_assert(NASMemInner <= 2, "Only handling up to two inner AS memories");
  if (NTEBuffer==2) {
    static_assert(NASMemInner == 2, "With two TE Buffers you need two AS memories");
    tebuffer[0].setMemBegin(0);
    tebuffer[0].setMemEnd(1);
    tebuffer[0].setIStub(0); 
    tebuffer[1].setMemBegin(1);
    tebuffer[1].setMemEnd(2);
    tebuffer[1].setIStub(0);
  }    
  if (NTEBuffer==1) {
    tebuffer[0].setMemBegin(0);
    tebuffer[0].setMemEnd(NASMemInner);
    tebuffer[0].setIStub(0); 
  }

 reset_tebuffers: for (unsigned i = 0; i < NTEBuffer; i++) {
#pragma HLS unroll
    tebuffer[i].reset();
  }

  TrackletEngineUnit<BARRELPS> teunits[NTEUnits];
#pragma HLS array_partition variable=teunits complete dim=1

 reset_teunits: for (unsigned i = 0; i < NTEUnits; i++) {
#pragma HLS unroll
    teunits[i].reset(i);
  }

  TrackletProjection<BARRELPS>::TProjTrackletIndex trackletIndex = 0;

  //pipeline variables
  bool goodstub__[NTEBuffer];
  bool goodstub___[NTEBuffer];
  int istub__[NTEBuffer];
  int istub___[NTEBuffer];
  AllStubInner<BARRELPS> stub__[NTEBuffer];
  AllStubInner<BARRELPS> stub___[NTEBuffer];
  ap_uint<1+2*TrackletEngineUnit<BARRELPS>::kNBitsRZFine+TrackletEngineUnit<BARRELPS>::kNBitsRZBin> lutval___[NTEBuffer];
  ap_uint<(1<<TrackletEngineUnit<BARRELPS>::kNBitsPhiBins)> useregion___[NTEBuffer];

  initializepipelinevars: for (unsigned i = 0; i < NTEBuffer; i++){
#pragma HLS unroll
    goodstub__[i]=false;
    goodstub___[i]=false;
  }


  static const ap_uint<(1<<(2*TrackletEngineUnit<BARRELPS>::kNBitsBuffer))> TENearFullUINT=nearFullTEUnitInit();

  ap_uint<16> vmstubsmask[8];
  ap_uint<64> vmstubsentries[8];
#pragma HLS array_partition variable=vmstubsentries complete dim=1
#pragma HLS array_partition variable=vmstubsmask complete dim=1
 entriesloop:for(unsigned int i=0;i<7;i++) {
#pragma HLS unroll
    vmstubsentries[i]=(outerVMStubs.getEntries8(bx,i+1),outerVMStubs.getEntries8(bx,i));
    vmstubsmask[i]=(outerVMStubs.getBinMask8(bx,i+1),outerVMStubs.getBinMask8(bx,i));
  }
  vmstubsentries[7]=(ap_uint<32>(0),outerVMStubs.getEntries8(bx,7));
  vmstubsmask[7]=(ap_uint<8>(0),outerVMStubs.getBinMask8(bx,7));


 istep_loop: for(unsigned istep=0;istep<N;istep++) {
#pragma HLS pipeline II=1

    //
    // Step 0 -  zeroth step is to cache some of data
    //

      TEData tedatatmp[NTEBuffer];
      bool tebufferempty[NTEBuffer];
      bool tebufferfull[NTEBuffer];
      TEBuffer::TEBUFFERINDEX writeptr[NTEBuffer];
      TEBuffer::TEBUFFERINDEX readptr[NTEBuffer];
      TEBuffer::TEBUFFERINDEX readptrnext[NTEBuffer];
      TEBuffer::TEBUFFERINDEX tebufferwriteptrtmp[NTEBuffer];
      TEBuffer::TEBUFFERINDEX tebufferreadptrtmp[NTEBuffer];
      TEBuffer::NSTUBS tebufferistubtmp[NTEBuffer];
      TEData::IMEM tebufferimemtmp[NTEBuffer];
  
      TrackletEngineUnit<BARRELPS>::INDEX teunitsreadindextmp[NTEUnits];
#pragma HLS array_partition variable=teunitsreadindextmp complete dim=1
      
      
      
      ap_uint<1> TEBufferData=0;
      unsigned int iTEBuff=0;

    prefetchtedata: for (unsigned i = 0; i < NTEBuffer; i++){
#pragma HLS unroll
	writeptr[i]=tebuffer[i].writeptr_;
	readptr[i]=tebuffer[i].readptr_;
	readptrnext[i]=readptr[i]+1;
	tedatatmp[i]=tebuffer[i].buffer_[readptr[i]];
	tebufferempty[i]=(writeptr[i]==readptr[i]);
	tebufferfull[i]=nearFullTEBuff(writeptr[i],readptr[i]);
	TEBufferData=TEBufferData||(!tebufferempty[i]);
	iTEBuff=tebufferempty[i]?iTEBuff:i;
      }

    TrackletEngineUnit<BARRELPS>::INDEX teuwriteindex[NTEUnits];
#pragma HLS array_partition variable=teuwriteindex complete dim=1
    TrackletEngineUnit<BARRELPS>::INDEX teureadindex[NTEUnits];
#pragma HLS array_partition variable=teureadindex complete dim=1
    TrackletEngineUnit<BARRELPS>::STUBID teudata[NTEUnits];
#pragma HLS array_partition variable=teudata complete dim=1
    bool teunearfull[NTEUnits];
#pragma HLS array_partition variable=teunearfull complete dim=1
    bool nearfulloridle[NTEUnits];
#pragma HLS array_partition variable=nearfulloridle complete dim=1
    bool teuempty[NTEUnits];
#pragma HLS array_partition variable=teuempty complete dim=1
    bool teuidle[NTEUnits];
#pragma HLS array_partition variable=teuidle complete dim=1
    bool teuidlebefore[NTEUnits];
#pragma HLS array_partition variable=teuidlebefore complete dim=1


    ap_uint<1> HaveTEData=0;
    int iTE=0;
    ap_uint<1> idlete=0;


  prefetchteudata: for (unsigned k = 0; k < NTEUnits; k++){
#pragma HLS unroll
      teuwriteindex[k]=teunits[k].writeindex_;
      teureadindex[k]=teunits[k].readindex_;
      teunearfull[k]=TENearFullUINT[ (teureadindex[k], teuwriteindex[k]) ];
      teuempty[k]=teuwriteindex[k]==teureadindex[k];
      teudata[k]=teunits[k].stubids_[teureadindex[k]];
      teuidle[k]=teunits[k].idle_;
      teuidlebefore[k]=(k==0)?false:(teuidlebefore[k-1]||teuidle[k-1]);
      idlete=idlete||teuidle[k];
      HaveTEData=HaveTEData||(!teuempty[k]);
      iTE=teuempty[k]?iTE:k;
      nearfulloridle[k]=teunearfull[k]||teuidle[k];
    }

    tebufferreadptrtmp[iTEBuff]=(idlete*TEBufferData)?readptrnext[iTEBuff]:readptr[iTEBuff];

    //
    // Step 1 - In this first step we check if there are stubs to be sent to the TC
    // we loop over the TE units and see if they have data.
    //
    
    // Check if TE unit has data - find the first instance with data

      
    AllStub<BARRELPS>::AllStubData innerStub;
    TEBuffer::NSTUBS innerIndex;
    TEBuffer::NSTUBS outerIndex;
    (outerIndex, innerStub, innerIndex)=teudata[iTE];
    //teunitsreadindextmp[iTE]=teureadindex[iTE]+HaveTEData;
    teunits[iTE].readindex_=teureadindex[iTE]+HaveTEData;


    const TrackletProjection<BARRELPS>::TProjTCID TCID(3);
      
    const auto &outerStub = outerStubs->read_mem(bx, outerIndex);

    
    if (HaveTEData) {
      TC::processStubPair<Seed, InnerRegion, OuterRegion, TPROJMaskBarrel<Seed, iTC>(), TPROJMaskDisk<Seed, iTC>()>(bx, innerIndex, AllStub<BARRELPS>(innerStub), outerIndex, outerStub, TCID, trackletIndex, trackletParameters, projout_barrel_ps, projout_barrel_2s, projout_disk, npar, nproj_barrel_ps, nproj_barrel_2s, nproj_disk);
    }
    

    //
    // Step 2 - Run the TE unit step method. If there is idle TE unit and we have stubs to process we will read from TE Buffer 
    // and initialize a TE unit
    // 

    //Now loop over the TE units and execute the step method. The first TE unit that is idle is 
    //initialized if there is data in TE Buffer from above
  step_teunits: for (unsigned int k = 0 ; k < NTEUnits; k++){
#pragma HLS unroll
      ap_uint<1> init=teuidle[k]&TEBufferData&(!teuidlebefore[k]);

      //second step

      TrackletEngineUnit<BARRELPS>::INDEX writeindexnext=teuwriteindex[k]+1;

      const VMStubTEOuter<BARRELPS>::VMSTEOFINEPHI& finephi = teunits[k].outervmstub__.getFinePhi();
      const ap_uint<1+VMStubTEOuterBase<BARRELPS>::kVMSTEOFineZSize>& rzbin = (teunits[k].next__, teunits[k].outervmstub__.getFineZ()); 

      ap_uint<NBitsPhiRegion> iAllstub=OuterPhiRegion;
      ap_uint<NfinephiBits> outerfinephi = (iAllstub, teunits[k].ireg__, finephi);
   
      constexpr unsigned int NdphiBits=5;
      ap_uint<NdphiBits> idphi;
      ap_uint<NfinephiBits-NdphiBits> overflow;
      (overflow,idphi) =  outerfinephi - AllStubInner<BARRELPS>(teunits[k].innerstub__).getFinePhi();
      
      ap_uint<1> inrange1 = overflow==0;
      ap_uint<1> inrange2 = overflow==~ap_uint<NfinephiBits-NdphiBits>(0);
      ap_uint<1> inrange = inrange1||inrange2;

      ap_uint<1> rzcut1=rzbin >= teunits[k].rzbinfirst__;
      ap_uint<1> rzcut2=rzbin <= teunits[k].rzbinfirst__+teunits[k].rzbindiffmax__;
      ap_uint<1> rzcut= rzcut1 && rzcut2;
      
      const auto& outerbend = teunits[k].outervmstub__.getBend();
      const auto& innerbend = teunits[k].innerstub__.getBend();
      
      auto ptinnerindex = (idphi, innerbend);
      auto ptouterindex = (idphi, outerbend);

      ap_uint<1> lutinner = teunits[k].stubptinnerlutnew_[ptinnerindex];
      ap_uint<1> lutouter = teunits[k].stubptouterlutnew_[ptouterindex];

      ap_uint<1> savestub = teunits[k].good__ && inrange && lutinner && lutouter && rzcut;
   
      teunits[k].stubids_[teuwriteindex[k]] = (teunits[k].outervmstub__.getIndex(), 
					       teunits[k].innerstub__.getAllStub(),
					       teunits[k].innerstub__.getIndex());
      
      teunits[k].writeindex_=savestub?writeindexnext:teuwriteindex[k];

      //first step
      
      teunits[k].rzbinfirst__=teunits[k].rzbinfirst_;
      teunits[k].rzbindiffmax__=teunits[k].rzbindiffmax_;
      teunits[k].innerstub__=teunits[k].innerstub_;
      (teunits[k].next__, teunits[k].ireg__)=teunits[k].memindex;
      teunits[k].good__=!nearfulloridle[k];

      teunits[k].innerstub_ = init?tedatatmp[iTEBuff].getAllStub():teunits[k].innerstub_;
      teunits[k].slot_=init?tedatatmp[iTEBuff].getStart():teunits[k].slot_;
      teunits[k].rzbinfirst_=init?tedatatmp[iTEBuff].getrzbinfirst():teunits[k].rzbinfirst_;
      teunits[k].rzbindiffmax_=init?tedatatmp[iTEBuff].getrzdiffmax():teunits[k].rzbindiffmax_;
      teunits[k].memmask_ = init ? tedatatmp[iTEBuff].getStubMask():teunits[k].memmask_;
      teunits[k].memindex = init ? TrackletEngineUnit<BARRELPS>::MEMINDEX(__builtin_ctz(teunits[k].memmask_)) : teunits[k].memindex;
      
      teunits[k].setnstubs16(init ? vmstubsentries[teunits[k].slot_] : teunits[k].nstubs16());

      TrackletEngineUnit<BARRELPS>::RZBIN ibin(teunits[k].slot_+teunits[k].next__);

      teunits[k].outervmstub__ = outerVMStubs.read_mem(k, bx, (ibin, teunits[k].ireg__, teunits[k].istub_));

      
#ifndef __SYNTHESIS__
      if (!nearfulloridle[k]) {
	assert(teunits[k].nstubs!=0);
	assert(teunits[k].nstubs==outerVMStubs.getEntries(bx, (ibin, teunits[k].ireg__)));
      }
#endif
      
      ap_uint<1> notallstubs = (teunits[k].istubnext_!=teunits[k].nstubs)||nearfulloridle[k];

      teunits[k].istub_=(!init&&nearfulloridle[k])?teunits[k].istub_:
	((!init&&!nearfulloridle[k]&&notallstubs)?teunits[k].istubnext_:TrackletEngineUnit<BARRELPS>::NSTUBS(0));
      teunits[k].istubnext_=teunits[k].istub_+1;
      teunits[k].memmask_[teunits[k].memindex]=notallstubs;
      
      teunits[k].memindex=__builtin_ctz(teunits[k].memmask_);
      teunits[k].nstubs=teunits[k].ns[teunits[k].memindex];

      //Can this logic by simplified?
      teunits[k].idle_=(init ? false : teuidle[k])||(!teunits[k].memmask_.or_reduce());
      


    }

   //
   // Third step - fill inner layer stubs in the TE buffer 
   // Check if inner stub has matching stubs in next layer/disk if
   // so put them in TE buffere to be picked up by a TE unit
   //

  process_tebuffers: for (unsigned i = 0; i < NTEBuffer; i++){
#pragma HLS unroll

      //Implement as a manual pipeline ugh...


      //
      // Get stubmask and save in TE Buffer
      //

     //LUT returns all 1's if not valid. (should change to returning zero.
     bool valid=!lutval___[i].and_reduce();

     //quantities looked up in LUT
     VMStubTEOuter<BARRELPS>::VMSTEOFINEZ rzfinebinfirst,rzdiffmax;
     ap_uint<3> start;
     ap_uint<1> usenext;
     (rzdiffmax, start, usenext, rzfinebinfirst) = lutval___[i];

     //Get the mask of bins that has non-zero number of hits
     ap_uint<16> stubmask16 = vmstubsmask[start];

     //Calculate the stub mask for which bins have hits _and_ are consistent with the inner stub
     ap_uint<16> mask=( (useregion___[i]*usenext,useregion___[i]) );
     ap_uint<16> stubmask=stubmask16&mask;

     //Find if there are _any_ bins with hits that needs to be tried. If so will store stub in buffer
     bool havestubs=stubmask.or_reduce();

     //addtedata is the criteria for saving stub to TE buffer:
     //valid means that r/z project is in valid range
     //havestubs means that at least one memory bin has stubs
     //goodstub means that we had a valid inner stub
     ap_uint<1> addtedata=valid&&havestubs&&goodstub___[i];

     //Create TEData and save in buffer - but only increment point if data good
     TEData tedatatmp(stubmask, rzfinebinfirst,start,rzdiffmax,stub___[i].raw());
     tebuffer[i].buffer_[tebuffer[i].writeptr_]=tedatatmp.raw();
     tebufferwriteptrtmp[i]=tebuffer[i].writeptr_+addtedata;

     //
     // Read LUTs and find valid regions in r/z and phi
     //


     //Get z-position and top bits for LUT
     auto z=stub__[i].getZ();
     auto indexz=z.range(z.length()-1,z.length()-kNbitszfinebintable);

     //Get r-position and top bits for LUT
     auto r=stub__[i].getR();
     auto indexr=r.range(r.length()-1,r.length()-kNbitsrfinebintable);
      
     //Get bend and fine phi for LUT
     auto bend=stub__[i].getBend();
     auto innerfinephi=stub__[i].getFinePhi();
      
     //This LUT tells us which range in r/z to look for stubs in the other layer/disk
     ap_uint<1+2*TrackletEngineUnit<BARRELPS>::kNBitsRZFine+TrackletEngineUnit<BARRELPS>::kNBitsRZBin> lutval = lut[(indexz,indexr)];

     //This lut tells us which range in phi to loof for stubs the other layer/disk
     ap_uint<(1<<TrackletEngineUnit<BARRELPS>::kNBitsPhiBins)> useregion=regionlut[(innerfinephi,bend)];

     lutval___[i]=lutval;
     useregion___[i]=useregion;
     goodstub___[i]=goodstub__[i];
     stub___[i]=stub__[i];
     istub___[i]=istub__[i];


     //
     // Read stub
     //


     //Extract the memory and range this TE buffer is processing
     auto& imem=tebuffer[i].getMem();
     auto imemsave=imem;
     auto imemend=tebuffer[i].getMemEnd();
     bool validmem=imem<imemend;
     
     //compute the next memory
     TEData::IMEM imemnext=imem+1;

     //Extract the current stub - check if valid. Calculate next stub (counting down!) Chech if valid
     auto& istub=tebuffer[i].getIStub();
     auto istubsave=istub;
     bool validstub=istub<innerStubs[imem].getEntries(bx);
     ap_uint<kNBits_MemAddr> istubnext=istub+1;
     bool validstubnext=istubnext<innerStubs[imem].getEntries(bx);

     //Calculate good stub - true if:
     //validmem is true - meaning that we have not exhausted all stub memories
     //tebuffer not full - can not process stub if buffere is full and we can not store 
     //validstub - should be redundant with validmem - FIXME
     ap_uint<1> goodstub=validmem&&(!tebufferfull[i])&&validstub;

     //Update istub if goodstub
     tebufferistubtmp[i]=goodstub?(validstubnext?istubnext:ap_uint<kNBits_MemAddr>(0)):istub; 
     //Update imem if the next stub isnot valid
     tebufferimemtmp[i]=(goodstub&&(!validstubnext))?imemnext:imem;

     //Read stub from memory - BRAM with latency of one or two clks
     auto stub=innerStubs[imemsave].read_mem(bx,istubsave);

     goodstub__[i]=goodstub;
     stub__[i]=stub;
     istub__[i]=istubsave;
     
    }
    
    //This could be earlier???
    //Increment TE bufer read ptr if we initalized a TE unit.
    tebuffer[iTEBuff].readptr_=tebufferreadptrtmp[iTEBuff];
    //    teunits[iTE].readindex_=teunitsreadindextmp[iTE];    

 update_tebufferss: for (unsigned int i = 0 ; i < NTEBuffer; i++){
      tebuffer[i].writeptr_=tebufferwriteptrtmp[i];
      tebuffer[i].getMem()=tebufferimemtmp[i];
      tebuffer[i].getIStub()=tebufferistubtmp[i];
    }
    
    
  } //end of istep
  
}

#endif
