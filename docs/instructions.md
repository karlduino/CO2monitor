## CO~2~ monitor assembly instructions

The goal of this project was to have a low-cost but accurate CO~2~ monitor, so
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

When printing the drilling template, make sure the sizes are kept the
same (in particular, don’t let it “shrink to printable area”).

Tape the template to the bottom of the box, making sure the lid
opening is oriented correctly. most important is lining up the top and
sides, because the lcd display is a very tight fit.

![box with drilling template, with punch tool for marking drilling locations](https://karlduino.org/docs/pics/01_with_template.jpg)

I use a punch tool to put a dent into each of the 9 spots I want to
drill. This really helps to get the drill bit started and at the right
spot, but only if the punch is done very carefully with no slipping. I
like the double-head kind that's a big spring (see the image above),
but it takes some practice to get enough force to make a good mark
that you can find with the drill bit, but not so much force that you
puch all they way through the plastic.

Before removing the template, mark the cut-out for the micro-USB with
a sharpie.

![box with marks for drilling and cutting locations](https://karlduino.org/docs/pics/02_with_marks.jpg)

I use a 7/64" drill bit for the two holes for the LED display
(top-right and middle-left on the template). They'll take 1/2" 4/40
screws. I use a 1/16" drill bit for the three holes for the Arduino
and the four holes for the corners of the sensor cut-out.

![box with holes all drilled](https://karlduino.org/docs/pics/03_drilled.jpg)

When cutting in plastic, it can be useful to heat the blade with a
lighter or small torch. (I didn't heat the drill bit for the drilling;
doing so made it harder to find my starting dents and the bit tended
to just melt right through, no drilling required, but generally not in
the right location.)

For the cut-out for the sensor, I drill 1/16” holes in the corners to
help get started with cutting the rectangle. I use a very thin exacto
saw (see the photo below).

For the cut-out for the micro-USB, I don't use starting holes. I just
heat the blade and let it melt down through the plastic and then start
cutting.

I should have said: don’t forget to wear eye protection (for me,
reading glasses).

![box fully prepared, with my cutting tool and torch](https://karlduino.org/docs/pics/04_holes_cut.jpg)


### Solder headers onto the components

I’m using two pairs of breakaway male header pins for the s8 sensor. it’s tricky to hold them in place for aoldering

for the arduino, i use a full 16-pin header, but I only solder the pins being used. could go back and solder the rest later, if the arduino were to be reused for a different project



### Mount the components

To mount the lcd display, I use two 1/2” 4/40 screws with round heads, with the heads outside the box, and two lock nuts

To mount the arduino, I use three 11/32” 0/80 screws, with the heads instead the box, and three hez nuts. I practically need tweezers to handle these.



### Make connections

To make the connections, I use 8 female-to-female jumpers, 2 each of four colors: green, yellow, black, and red.



### Load the software



### Tape the box shut

If it's working, you can arrange the sensor as you want it and then
delicately close the lid so the wires all stay inside and so they push
the sensor down against its opening.

Tape the box shut with a couple of pieces of clear tape.
