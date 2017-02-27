Class 3 - OAM and Keypad
========================

Summary
-------

1. What is OAM
1. Objects memory mapping
2. Reading keypad inputs
3. What is a Sprite

1: What is OAM
--------------

OAM stands for "Object Attribute Memory". In your games you won't draw every
game object manually, as it would be a lot better if the hardware could handle
it for you. This way, you just send the object's graphics (and palette) to
VRAM, sets its location and let the hardware make the magic happen. This is
exactly why OAM exists.

More specificaly, the OAM itself handles only the attributes of the objects
(location, size, starting index of object palette memory, rotation,
scaling...). The object's bitmap data has its own place on memory and so has
it's palette. As you may observe, game objects are paletted.

2: Objects memory mapping
-------------------------

