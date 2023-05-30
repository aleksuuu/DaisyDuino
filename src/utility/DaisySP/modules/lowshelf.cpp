#include "lowshelf.h"
#include <math.h>
#include "dsp.h"

using namespace daisysp;

void Lowshelf::Reset()
{
    float norm;
    float V = pow(10, fabs(gain_) / 20.0);
    float K = tan(M_PI * freq_);
    float sqrt2V = M_SQRT2 * sqrt(V);
    float sqK = K * K;
    float vTimesSqK = V * sqK;

    if (gain_ >= 0)
    { // boost
        norm = 1 / (1 + M_SQRT2 * K + sqK);
        a0_ = (1 + sqrt2V * K + vTimesSqK) * norm;
        a1_ = 2 * (vTimesSqK - 1) * norm;
        a2_ = (1 - sqrt2V * K + vTimesSqK) * norm;
        b1_ = 2 * (sqK - 1) * norm;
        b2_ = (1 - M_SQRT2 * K + sqK) * norm;
    }
    else
    {
        norm = 1 / (1 + sqrt2V * K + vTimesSqK);
        a0_ = (1 + M_SQRT2 * K + sqK) * norm;
        a1_ = 2 * (sqK - 1) * norm;
        a2_ = (1 - M_SQRT2 * K + sqK) * norm;
        b1_ = 2 * (vTimesSqK - 1) * norm;
        b2_ = (1 - sqrt2V * K + vTimesSqK) * norm;
    }

    // float capitalA = pow(10, gain_ / 40.);
    // float con = freq_ * two_pi_d_sr_;
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
    res_ = 0.7;
    gain_ = 0.0;

    Reset();

    xnm1_ = xnm2_ = ynm1_ = ynm2_ = 0.0f;

    z1_ = z2_ = 0.0f;
}

float Lowshelf::Process(float in)
{
    // float xn, yn;
    // float a0 = a0_, a1 = a1_, a2 = a2_;
    // float b0 = b0_, b1 = b1_, b2 = b2_;
    // float xnm1 = xnm1_, xnm2 = xnm2_, ynm1 = ynm1_, ynm2 = ynm2_;

    // xn = in;
    // yn = (b0 * xn + b1 * xnm1 + b2 * xnm2 - a1 * ynm1 - a2 * ynm2) / a0;
    // xnm2 = xnm1;
    // xnm1 = xn;
    // ynm2 = ynm1;
    // ynm1 = yn;

    // xnm1_ = xnm1;
    // xnm2_ = xnm2;
    // ynm1_ = ynm1;
    // ynm2_ = ynm2;

    float out = in * a0_ + z1_;
    z1_ = in * a1_ + z2_ - b1_ * out;
    z2_ = in * a2_ - b2_ * out;

    return out;
}
