#include "lowshelf.h"
#include <math.h>
#include "dsp.h"

using namespace daisysp;

// V1 based on https://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
// V2 based on audio eq cookbook (https://webaudio.github.io/Audio-EQ-Cookbook/Audio-EQ-Cookbook.txt)

void Lowshelf::Reset()
{
    float capitalA = pow10f(gain_ / 40.);
    float w0 = freq_ * two_pi_d_sr_;

    float alpha = sinf(w0) / (2 * qVal_);

    float cosW0 = cosf(w0);
    float twoTimesSqrtATimesAlpha = 2 * sqrtf(capitalA) * alpha;
    float capitalAMinusOneTimesCosW0 = (capitalA - 1) * cosW0;
    float capitalAPlusOneTimesCosW0 = (capitalA + 1) * cosW0;

    a0_ = (capitalA + 1) - capitalAMinusOneTimesCosW0 + twoTimesSqrtATimesAlpha;
    a1_ = -2 * ((capitalA - 1) + capitalAPlusOneTimesCosW0);
    a2_ = (capitalA + 1) - capitalAMinusOneTimesCosW0 - twoTimesSqrtATimesAlpha;
    b0_ = capitalA * a0_;
    b1_ = -1 * capitalA * a1_;
    b2_ = capitalA * a2_;
    


    // float alpha = 1.0f - 2.0f * res_ * cosf(con) * cosf(con)
    //               + res_ * res_ * cosf(2 * con);
    // float beta  = 1.0f + cosf(con);
    // float gamma = 1 + cosf(con);
    // float m1    = alpha * gamma + beta * sinf(con);
    // float m2    = alpha * gamma - beta * sinf(con);
    // float den   = sqrtf(m1 * m1 + m2 * m2);

    // b0_ = 1.5f * (alpha * alpha + beta * beta) / den;
    // b1_ = b0_;
    // b2_ = 0.0f;
    // a0_ = 1.0f;
    // a1_ = -2.0 * res_ * cosf(con);
    // a2_ = res_ * res_;
}

void Lowshelf::Init(float sample_rate)
{
    sample_rate_ = sample_rate;
    two_pi_d_sr_ = TWOPI_F / sample_rate_;

    freq_ = 500;
    qVal_ = 0.7;
    gain_ = 0.0;

    Reset();

    xnm1_ = xnm2_ = ynm1_ = ynm2_ = 0.0f;
}

float Lowshelf::Process(float in)
{
    float xn, yn;
    float a0 = a0_, a1 = a1_, a2 = a2_;
    float b0 = b0_, b1 = b1_, b2 = b2_;
    float xnm1 = xnm1_, xnm2 = xnm2_, ynm1 = ynm1_, ynm2 = ynm2_;

    xn   = in;
    yn   = b0/a0 * xn + b1/a0 * xnm1 + b2/a0 * xnm2 - a1/a0 * ynm1 - a2/a0 * ynm2;
    xnm2 = xnm1;
    xnm1 = xn;
    ynm2 = ynm1;
    ynm1 = yn;

    xnm1_ = xnm1;
    xnm2_ = xnm2;
    ynm1_ = ynm1;
    ynm2_ = ynm2;

    return yn;
}