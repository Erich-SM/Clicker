# Clicker

This is NOT A GAME, this is an engine, or a game, depending on what you make of it.

It uses a file called "images.txt" to load image paths, also hearts/(any other image) on click

Images are defined in input.txt, ex (I /home/foo/bar.png) or (I C:\\foo\bar.png), for an odd reason it only execpts pngs
now please note, a file may look like a png (aka have thhe .png extension), but THIS IS NOT CORRECT.
PNG files have a specific signature at the begining of the file, and most images you download online are jpeg images.
Please use a tool such as farbfeld or something for windows, to convert them to png! the supreme file format!

Music is defined in input.txt as well, starts with M, ex (M /home/bar/foo.(wav,ogg,anything really).
NOTE, the sound that plays when you click the clicker thing is in a sperate file, define it as S.

statics.txt, this file has all the predefined things like sprites, they can be changed, but, ehh, complexi-mo. so ill explain

the first line defines the "gotonext" button, this is the arrow that switches the images.
the second one pertains to the thing that pops up when you click the image.
the third is the sound when you click the image.


# NOTE IF YOU DONT WANT SOMETHING DEFINED REPLACE THE LINE WITH (NULL)
