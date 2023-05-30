#pragma once
#ifndef DSY_LOWSHELF_H
#define DSY_LOWSHELF_H

#include <stdint.h>
#ifdef __cplusplus

namespace daisysp
{
/** Two pole recursive lowshelf filter

    Original author(s) : Hans Mikelson

    Year: 1998

    Ported from soundpipe by Ben Sergentanis, May 2020
*/
class Lowshelf
{
  public:
    Lowshelf() {}
    ~Lowshelf() {}
    /** Initializes the lowshelf module.
        \param sample_rate - The sample rate of the audio engine being run. 
    */
    void Init(float sample_rate);


    /** Filters the input signal
        \return filtered output
    */
    float Process(float in);


    /** Sets resonance amount
        \param res : Set filter resonance.
    */
    inline void SetRes(float res)
    {
        res_ = res;
        Reset();
    }


    /** Sets filter cutoff in Hz
        \param cutoff : Set filter cutoff.
    */
    inline void SetFreq(float freq)
    {
        freq_ = freq;
        Reset();
    }

        /** Sets filter gain in dB
        \param gain : Set filter gain.
    */
    inline void SetGain(float gain)
    {
        gain_ = gain;
        Reset();
    }



  private:
    float sample_rate_, freq_, gain_, res_, b0_, b1_, b2_, a0_, a1_, a2_,
        two_pi_d_sr_, xnm1_, xnm2_, ynm1_, ynm2_, z1_, z2_;
    void Reset();
};
} // namespace daisysp
#endif
#endif
