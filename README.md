This repository is a fork of the code released by Mutable Instruments for its range of 
audio synthesiser modules. 

The Braids code has been modified to add various features - see below un "Bees-in-Trees".

Forks of source code for the following modules are here: 
* Braids: Macro-oscillator.
* Edges: Quad chiptune digital oscillator.
* Ripples: Liquid 2-pole BP, 2-pole LP and 4-pole LP filter.
* Grids: Topographic drum sequencer.
* Links: Utility module - buffer, mixer.
* Frames: Keyframer/mixer.
* Tides: Tidal modulator.
* Yarns: MIDI interface.
* Volts: +5V power module.

Upstream code can be found at https://github.com/pichenettes/eurorack

License
=======

Code (AVR projects): GPL3.0.
Code (STM32F projects): MIT license.
Hardware: cc-by-sa-3.0
Original code by: Olivier Gillet (olivier@mutable-instruments.net)
Modifications by: Tim Churches (tim.churches@gmail.com)

Bees-in-Trees
=============

Bees-in-Trees v1 adds the following features to Braids v1.6:

* Square-sawtooth-triangle triple oscillator model: this works identically to the existing triple sawtooth and triple square oscillator models, except that instead of sawtooth or square waveforms for each paraphonic voice, it uses one square, one sawtooth and one triangle waveform. The result is appreciably different from the existing triple waveform models.
* Triple triangle oscillator model (^^x3): this works identically to the existing triple sawtooth and triple square oscillator models, except that it uses a triangle waveform for all three oscillators. Due to the much less bright harmonics in a triangle wave, it can be used effectively without any filtering, if desired.
* Triple sine wave oscillator model (SINS): this works identically to the existing triple sawtooth and triple square oscillator models, except that it uses a sine waveform for all three oscillators. Due to the absent harmonics in a sine wave, it can be used effectively without any filtering, if desired, although there are some harmonics because all three waves are summed – nonetheless, it sounds very smooth and rounded, sans filtering, as you might expect.
* WTx2 duophonic wavetable model with second voice offset controlled by the Color parameter: this model is the love-child of the existing triple waveform models and the existing WTx4 model. Unlike the WTx4 model, it has only two paraphonic “voices”, not four, and the pitch of the second voice is offset from the first voice by an amount set by the Color parameter (both Color potentiometer and Color CV input), in the same way that the Color parameter controls the third voice in the triple oscillator models. Timbre scans the same wavetable in the same manner as it does in the WTx4 model. However, each of the two “voices” consists of two wavetable oscillator instances, each detuned from each other by a small amount. The degree of detune is different for each pair of oscillators, and also varies as the Color parameter changes. The result is a thick chorus effect on both “voices”, an effect which varies as the Color parameter is swept.
* Color is now also a target for the internal envelope: the available choices under the TDST menu are now: SYNC, TIMB, LEVL, T+L, COLR, T+C, L+C, ALL. The compound destinations are self-explanatory. The ability to modulate Color with the internal envelope significantly enhances some of the oscillator models, in others, not so much, and in a few, it is useless, but not harmful.
* Voltage control over the attack and decay of the internal envelope, via the FM input (and fine tune knob), as in the existing META mode: instead of offering just ON or OFF, the META menu now offers the following choices: OFF , MODL, ATTK, DCAY, AD.1, AD.2, AD.3, AD.4, AD.5, AD.6, AD.7, AD.8, AD.9, A=D, DA.9, DA.8, DA.7, DA.6, DA.5, DA.4, DA.3, DA.2, DA.1. MODL is identical to the existing META=ON mode. ATTK and DCAY use the voltage on the FM input (plus the fine tune knob setting) to override the attack and decay parameters, respectively, of whatever envelope is currently selected in the TENV menu. In other words, in ATTK mode, the envelope attack time is voltage-controlled via the FM input, but the decay time honours the decay time for whatever fixed envelope type is selected in TENV. Vice-versa for DCAY mode. The remaining new META modes, AD.1 through to DA.1, put both attack time and decay time of the internal envelope under voltage control via the FM input (and fine tune knob). The numbers refer to the ratio of attack to decay time e.g. for AD.1 mode, the ratio of attack time to decay time is 0.1, while for AD.8, the ratio is 0.8. By extension, DA.6 means the ratio of decay time to attack time is 0.6, which is the same as the ratio of the attack to decay time being 1.66. A=D mode means the attack time equals the decay time. However, although the ratios are fixed for each mode, the actual times are not – they are under voltage control via the FM input. Why did I do it this way? Because it was easiest to code, and requires no change to the format of the data saved on the MPU.

Plus an anti-feature:

* A _paschal oophorectomy_ has been performed: the Easter egg oscillator model has been removed and the ability to trigger Easter egg mode has been disabled. One could say that the code for it has been Pynchoned off… This was necessary to free up space for the enhancements described above. Sorry!

The intention is to add all these features (and anti-feature) to the Braids v1.7 code, as soon as it is released – it is hoped they will fit while keeping the new-in-1.7 KICK, SNAR and CYMB models. If anything else does need to go, I’ll probably remove the QPSK model. But I’d rather not unless necessary.

This release of Bees-in-Trees is still decidedly beta. I have done some testing, and have not encountered any problems or bugs, but more testing is required, and I would be grateful for any assistance in that regard. There are also some aspects that need further tweaking and optimisation: the linearity of the envelope ratios needs to be adjusted, and I suspect that the degree of modulation for Color provided by the internal envelope is not right (too little?).

The source code for all these enhancements is available here on GitHub. If you are really keen, then please compile it, flash it to your Braids and try it out. However, you do so at your own risk – this a a beta version of hacked code! Although it is will not physically damage your Braids, it could possibly render it non-functional, and I am afraid that I cannot offer any assistance beyond posts to this forum, should that occur. I have tested upgrading from Bees-in-Trees v1 to Braids v1.7 via the WAV audio upgrade mechanism, and it works, but you need to ensure that you have set META to OFF and TDST to SYNC and then save those parameters by exiting menu mode, before you attempt to replace the Bees-in-Trees firmware with Braids v1.7. This is because Bees-in-Trees uses additional values in those settings, and if you have those additional values stored when you happen to change to Braids v1.7, then META mode may not operate, at least at first. I found that resetting the values by exiting the menu and going back, twice, after upgrading to Braids v1.7, fixed the issue. None of these concerns apply if you are loading firmware via the FTDI serial or JTAG/SWD OCD interfaces on Braids, because they completely overwrite everything on the chip AFAIK. Anyway, YOU HAVE BEEN WARNED! If in doubt, don’t load the Bees-in-Trees v1 firmware via the audio upgrade mechanism. I’ll do further testing of the upgrade/downgrade issues after porting the Bees-in-Trees changes to Braids v1.7 code, when available. As an aside, Braids would benefit from a menu option that re-initialises all stored data – such a menu option would overcome issues such as these.