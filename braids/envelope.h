// Copyright 2012 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BRAIDS_ENVELOPE_H_
#define BRAIDS_ENVELOPE_H_

#include "stmlib/stmlib.h"

#include "stmlib/utils/dsp.h"

#include "braids/resources.h"

namespace braids {

using namespace stmlib;

enum EnvelopeSegment {
  ENV_SEGMENT_ATTACK = 0,
  ENV_SEGMENT_DECAY = 1,
  ENV_SEGMENT_SUSTAIN = 2,
  ENV_SEGMENT_RELEASE = 3,
  ENV_SEGMENT_DEAD = 4,
  ENV_NUM_SEGMENTS,
};

class Envelope {
 public:
  Envelope() { }
  ~Envelope() { }

  void Init() {
    target_[ENV_SEGMENT_ATTACK] = 65535;
    target_[ENV_SEGMENT_RELEASE] = 0;
    target_[ENV_SEGMENT_DEAD] = 0;
    
    increment_[ENV_SEGMENT_SUSTAIN] = 0;
    increment_[ENV_SEGMENT_DEAD] = 0;
  }

  inline EnvelopeSegment segment() const {
    return static_cast<EnvelopeSegment>(segment_);
  }

  inline void Update(int32_t a, int32_t d, int32_t s, int32_t r) {
    increment_[ENV_SEGMENT_ATTACK] = lut_env_portamento_increments[a];
    increment_[ENV_SEGMENT_DECAY] = lut_env_portamento_increments[d];
    increment_[ENV_SEGMENT_RELEASE] = lut_env_portamento_increments[r];
    target_[ENV_SEGMENT_DECAY] = s << 9;
    target_[ENV_SEGMENT_SUSTAIN] = target_[ENV_SEGMENT_DECAY];
  }
  
  inline void Trigger(EnvelopeSegment segment) {
    if (segment == ENV_SEGMENT_DEAD) {
      value_ = 0;
    }
    a_ = value_;
    b_ = target_[segment];
    segment_ = segment;
    phase_ = 0;
  }

  inline uint16_t Render(bool LfoMode, uint8_t EnvType) {
    uint32_t increment = increment_[segment_];
    phase_ += increment;
    // Kickstart the LFO if in LFO mode and not already looping
    if (LfoMode && segment_ > ENV_SEGMENT_DECAY) {        
         Trigger(static_cast<EnvelopeSegment>(ENV_SEGMENT_ATTACK));  
    } 

    if (phase_ < increment) {
      value_ = Mix(a_, b_, 65535);
      // This makes the envelope loop if LFO mode selected in META
      if (LfoMode && segment_ == ENV_SEGMENT_DECAY) {        
         Trigger(static_cast<EnvelopeSegment>(ENV_SEGMENT_ATTACK));  
      } 
      else { 
         Trigger(static_cast<EnvelopeSegment>(segment_ + 1));
      }
    }
    if (increment_[segment_]) {
      if (EnvType == 0) {
         value_ = Mix(a_, b_, Interpolate824(lut_env_expo, phase_));
      }
      else if (EnvType == 1) {
         value_ = Mix(a_, b_, Interpolate824(lut_env_linear, phase_));
      }         
      else if (EnvType == 2) {
         value_ = Mix(a_, b_, Interpolate824(lut_env_wiggly, phase_));
      }         
    }
    return value_;
  }
  
  inline uint16_t value() const { return value_; }

 private:
  // Phase increments for each segment.
  uint32_t increment_[ENV_NUM_SEGMENTS];
  
  // Value that needs to be reached at the end of each segment.
  uint16_t target_[ENV_NUM_SEGMENTS];
  
  // Pointer to the shape table.
  const uint16_t* shape_[ENV_NUM_SEGMENTS];
  
  // Current segment.
  size_t segment_;
  
  // Start and end value of the current segment.
  uint16_t a_;
  uint16_t b_;
  uint16_t value_;

  uint32_t phase_increment_;
  uint32_t phase_;

  DISALLOW_COPY_AND_ASSIGN(Envelope);
};

}  // namespace braids

#endif  // BRAIDS_ENVELOPE_H_
