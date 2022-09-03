## CO2 monitor assembly instructions

The goal of this project was have a low-cost but accurate CO2 monitor, so
that we could make a bunch of them to hand out to university workers
to assess the air quality in their work spaces, including classrooms.

### Overview

We got a pile of small clear plastic boxes, 3.2" square and a bit less
than 1" tall. It just barely fits the LCD display we're using.

We mount the LCD display and the arduino inside the box, with the LCD
display facing down and out. We need to drill holes in the box for
screws to mount these components, plus a cut-out for the sensor (so
that it can get outside air) and a cut-out for a micro- or mini-USB
cable give power to the arduino.

The arduino may need header pins soldered on; the sensor definitely
will. The drilling and cutting and soldering are the hard parts of
this assembly. We then connect the components with premade
female-to-female jumper cables.


### Prepare the box

There's a [drill
template](DrillTemplate/co2_monitor_drill_template.pdf) document
that you should print out, to guide the positioning of the drill holes
and cut-outs.


- when printing the drilling template, make sure the sizes are kept the same (in particular, don’t let it “shrink to printable area”)
- tape the template to the bottom of the box, making sure the lid opening is oriented correctly. most important is lining up the top and sides, because the lcd display is a very tight fit
- I use a punch to put a dent into each of the 9 spots I want to drill. really helps to get the drill bit started and at the right spot, but only if the punch is done very carefully with no slipping
- before removing the template, mark the cut-out for the micro-USB with a sharpie
- when cutting in plastic, it can be useful to heat the blade with a lighter or small torch.
- for cut-out for sensor, I drill 1/16” holes in cores to help get started with cutting the rectangle
- for cut-out for micro-usb, i just heat the blade and let it melt through the plastic
- don’t forget to wear goggles (for me, reading glasses)



### Solder headers onto the components

I’m using two pairs of breakaway male header pins for the s8 sensor. it’s tricky to hold them in place for aoldering

for the arduino, i use a full 16-pin header, but I only solder the pins being used. could go back and solder the rest later, if the arduino were to be reused for a different project



### Mount the components

To mount the lcd display, I use two 1/2” 4/40 screws with round heads, with the heads outside the box, and two lock nuts

To mount the arduino, I use three 7/32” 0/80 screws, with the heads instead the box, and three hez nuts. I practically need tweezers to handle these.



### Make connections

To make the connections, I use 8 female-to-female jumpers, 2 each of four colors: green, yellow, black, and red.



### Tape the box shut



### Load the software
