//    DaisySP is a DSP Library targeted at the Electrosmith Daisy Product Line.
//    Author: Stephen Hensley, 2019
//
//    However, this is decoupled from the hardware in such a way that it
//        should be useful outside of the ARM context with different build configurations.
//
//    A few general notes about the contents of the library:
//        - all memory usage is static.
//        - in cases of potentially large memory usage: the user will either supply a buffer and a size, or the class will be a template that can have size set at compile time.
//        - all modules will have an Init() function, and a Process() function.
//        - all modules, unless otherwise noted, will process a single sample at a time.
//        - all processing will be done with 'float' type unless otherwise noted.
//
#pragma once
#ifndef DSYSP_H
#define DSYSP_H

/** Control Modules */
#include "modules/adenv.h"
#include "modules/adsr.h"
#include "modules/line.h"
#include "modules/phasor.h"

/** Drum Modules */
#include "modules/analogbassdrum.h"
#include "modules/analogsnaredrum.h"
#include "modules/hihat.h"
#include "modules/synthbassdrum.h"
#include "modules/synthsnaredrum.h"

/** Dynamics Modules */
#include "modules/balance.h"
#include "modules/compressor.h"
#include "modules/crossfade.h"
#include "modules/limiter.h"

/** Effects Modules */
#include "modules/autowah.h"
#include "modules/bitcrush.h"
#include "modules/chorus.h"
#include "modules/decimator.h"
#include "modules/flanger.h"
#include "modules/fold.h"
#include "modules/overdrive.h"
#include "modules/reverbsc.h"
#include "modules/phaser.h"
#include "modules/pitchshifter.h"
#include "modules/sampleratereducer.h"
#include "modules/tremolo.h"

/** Filter Modules */
#include "modules/allpass.h"
#include "modules/atone.h"
#include "modules/biquad.h"
#include "modules/comb.h"
#include "modules/mode.h"
#include "modules/moogladder.h"
#include "modules/nlfilt.h"
#include "modules/svf.h"
#include "modules/tone.h"
#include "modules/fir.h"

#include "modules/lowshelf.h"

/** Noise Modules */
#include "modules/clockednoise.h"
#include "modules/dust.h"
#include "modules/fractal_noise.h"
#include "modules/grainlet.h"
#include "modules/particle.h"
#include "modules/whitenoise.h"

/** Physical Modeling Modules */
#include "modules/drip.h"
#include "modules/modalvoice.h"
#include "modules/pluck.h"
#include "modules/PolyPluck.h"
#include "modules/resonator.h"
#include "modules/KarplusString.h"
#include "modules/stringvoice.h"

/** Synthesis Modules */
#include "modules/blosc.h"
#include "modules/fm2.h"
#include "modules/formantosc.h"
#include "modules/harmonic_osc.h"
#include "modules/oscillator.h"
#include "modules/oscillatorbank.h"
#include "modules/variablesawosc.h"
#include "modules/variableshapeosc.h"
#include "modules/vosim.h"
#include "modules/zoscillator.h"

/** modules Modules */
#include "modules/dcblock.h"
#include "modules/delayline.h"
#include "modules/dsp.h"
#include "modules/jitter.h"
#include "modules/looper.h"
#include "modules/maytrig.h"
#include "modules/metro.h"
#include "modules/port.h"
#include "modules/samplehold.h"
#include "modules/smooth_random.h"

#endif
