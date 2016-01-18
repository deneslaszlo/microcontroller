The goal of this project is to design a circuit and write a sketch to accomplish the followings:
- if the brightness in the room is under the threshold, the LED(s) should not light
- the threshold should be able to modified without updating the sketch
- if the brightness of the room is under the threshold and there is movement in the room, the LEDs should light
- if the brightness of the room goes under the threshold and there is no motion in the room, but there was motion in the previous 5 seconds, the LEDs should light
- when the LEDs are turned on, they have to light continuously until there is motion + 5 seconds, or until there is brightness in the room again

- power consumption should be as low as reasonably possible, so power blocking is required

Try it: 
https://123d.circuits.io/circuits/1416567-light-when-dark-motion

The PIR sensor is substituted with a push-button in the 123circuits example due to the lack of PIR sensor component