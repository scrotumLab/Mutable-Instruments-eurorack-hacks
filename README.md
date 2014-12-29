This repository is a fork of the code released by Mutable Instruments for its range of 
audio synthesiser modules. 

The Braids code has been modified to add various features:
* Square-sawtooth-triangle triple oscillator model
* Triple triangle oscillator model
* Trile sine wave oscillator model
* WTx2 duophonic wavetable model with second voice offset controlled by the Color parameter
* Color is now also a target for the internal envelope
* Voltage control over the attack and decay of the internal envelope, via the FM input, as in the existing META mode.
 
* Braids: Macro-oscillator.
* Edges: Quad chiptune digital oscillator.
* Ripples: Liquid 2-pole BP, 2-pole LP and 4-pole LP filter.
* Grids: Topographic drum sequencer.
* Links: Utility module - buffer, mixer.
* Frames: Keyframer/mixer.
* Tides: Tidal modulator.
* Yarns: MIDI interface.
* Volts: +5V power module.

License
=======

Code (AVR projects): GPL3.0.
Code (STM32F projects): MIT license.
Hardware: cc-by-sa-3.0
Original code by: Olivier Gillet (olivier@mutable-instruments.net)
Modifications by: Tim Churches (tim.churches@gmail.com)