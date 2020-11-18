#ifndef PRBUFFERARRAY_HH
#define PRBUFFERARRAY_HH

#include "ProjectionRouterBuffer.h"

template<int kNBitsBuffer> class ProjectionRouterBufferArray {
public:
  inline ProjectionRouterBuffer<BARREL> read() {
    ap_uint<kNBitsBuffer> tmpptr = ptr_;
    ptr_++;
    if(empty()) reset(); //read all projections, reset array to 0
    //std::cout << std::hex << "reading projbuffer proj=" << projbuffer[tmpptr].raw() << "\ttmpptr=" << tmpptr << "\tmoving ptr_=" << ptr_ << "\twidth_=" << width_ << std::endl;
    //print();
    return projbuffer[tmpptr];

  }

  inline void add(ProjectionRouterBuffer<BARREL> &proj) {
    projbuffer[width_] = proj;
    //std::cout << std::hex << "adding proj=" << proj.raw() << "\tprojid=" << proj.getIndex() << "\twidth= " << width_ << std::endl;
    width_++;
    //print();
  }

  inline bool empty() { 
    //std::cout << "Empty projbuffer? " << (ptr_ == width_) << std::endl;
    return ptr_ == width_;
  }

  inline void reset() {
    ptr_ = 0;
    width_ = 0;
    //std::cout << "Resetting proj buffer array!" << std::endl;
    empty();
  }

  ProjectionRouterBufferArray() {
#pragma HLS ARRAY_PARTITION variable=projbuffer complete dim=0
    reset();
  }

  #ifndef __SYNTHESIS__
  void print() {
    if(empty()) {
      std::cout << "unread contents in projbuffer empty!" << std::endl;
    }
    else {
      std::cout << "Unread contents in projbuffer" << std::endl;
      for(int i = ptr_; i < width_; ++i){
        std::cout << std::hex << i << ": " << projbuffer[i].raw() << std::endl;
      }
    }
  }
  #endif

private:
  ap_uint<kNBitsBuffer> ptr_ = 0;
  ap_uint<kNBitsBuffer> width_ = 0;
  ProjectionRouterBuffer<BARREL> projbuffer[1<<kNBitsBuffer];

};

#endif
