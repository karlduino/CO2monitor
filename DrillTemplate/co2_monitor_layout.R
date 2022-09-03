## layout for screws for CO2 monitor

# box is 3 3/16 x 3 3/16 (inches)
# lcd display screw holes are at 75mm x 31mm
# arduino nano every screw holes are at 40.64mm x 15.24mm
# micro-usb port is 0.3165" wide, centered on nano every
# senseair s8 opening is 0.68" wide x 0.54" wide

w <- (3 + 3/16)*1000
lmargin <- 750
tmargin <- 750

pdf("co2_monitor_layout.pdf", height=11, width=8.5)
par(bty="n", mar=rep(0,4), oma=rep(0,4))

plot(0,0,xlim=c(0,8500), ylim=c(11000,0), xaxs="i", yaxs="i",
     xaxt="n", yaxt="n", xlab="", ylab="", type="n")


make_layout <- function(lmargin, tmargin) {

    # box
    rect(lmargin, tmargin, w+lmargin, w+tmargin, col=NA, border="black")

    # screws for LCD display
    led_width <- (75/25.4)*1000
    left <- w/2 - led_width/2 + lmargin
    right <- w/2 + led_width/2 + lmargin
    top <- tmargin+ 250
    bottom <- top + (31/25.4)*1000

    points(c(left, right), c(bottom, top), cex=0.6)

    text(right-150, top, '7/64" drill bit\n1/2" 4/40 screw',
         cex=0.6, adj=c(1, 0.5))


    # screws for arduino
    arduino_width <- 4.064/2.54*1000
    arduino_height <- 1.524/2.54*1000
    top <- bottom + 650
    bottom <- top+arduino_height
    right <- left+arduino_width

    points(c(left, left, right), c(top, bottom, top), cex=0.4)

    text(left+150, top, '1/16" drill bit\n11/32" 0/80 screw',
         cex=0.6, adj=c(0, 0.5))

    # where to cut for the usb-mini port
    usb_height <- 316.5
    arduino_center <- top + arduino_height/2
    arrows(rep(lmargin+200,2), arduino_center+c(-1,1)*usb_height/2,
           rep(lmargin,2), arduino_center+c(-1,1)*usb_height/2, len=0.05)
    segments(lmargin+200, arduino_center-usb_height/2,
             lmargin+200, arduino_center+usb_height/2)
    text(lmargin+260, arduino_center+usb_height/2-60,
         "micro-USB port cut-out", cex=0.5, adj=c(0,0.5))

    # opening for senseair s8
    s8_width <- 680
    s8_height <- 540

    bottom <- tmargin + w - 250
    right <- lmargin + w - 250
    top <- bottom - s8_height
    left <- right - s8_width
    rect(left, top, right, bottom, col=NA, border="black")
    points(c(left, left, right, right), c(top, bottom, top, bottom), cex=0.6)
    text((left+right)/2, (top+bottom)/2, "cut out", cex=0.6)

    # arrow pointing to lid opening
    arrows(lmargin + w/2, tmargin+w-300, lmargin+w/2, tmargin+w-100, len=0.05)
    text(lmargin+w/2-150, tmargin+w-380, "lid opening", cex=0.6)

}

make_layout(lmargin, tmargin)

make_layout(lmargin, tmargin*4/3+w)

make_layout(lmargin*4/3+w, tmargin)

make_layout(lmargin*4/3+w, tmargin*4/3+w)



dev.off()
