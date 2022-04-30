# Brightness set

This program changes the brightness of screen by writing your custom brightness into the file located
on /sys/class/leds/lcd-backlight/brightness, some unix/linux derived distributions have different
file path that define the current brightness of the screen, if thats the case then just change the
macro BRIGHTNESS_FILE to your system brightness file. This program was written to work on my Android tablet
because even on lowest brightness its was not enough for me.