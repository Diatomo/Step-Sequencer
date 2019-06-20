# Step-Sequencer
Code to Drive a Step Sequencer

There are two parts to this.

1) Teensy -> Muxer -> ButtonBoard -> Muxer -> Teensy -> PC

This gets the input from the buttonboard and relays it to the python script on a computer

2) PC -> Python Serial I/O -> Ableton Live

I'm having a difficult time finding a well-developed python library to interface with audio files. I'm hoping to interface with ableton because it has powerful features including recording, effects, and audio playback. 

This link has me thinking it might be possible. http://remotescripts.blogspot.com/
