# Particle-Interaction

A small graphics project in C++ using SFML library. This code was written to understand the SFML library, Graphics and to revamp C++ skills.

The user is allowed to input the number of particles, the varierty and the radius.

We start with a black scrren, where the user can see multiple particles (circles in different colours) following different trajectories. 
The particles collide with the boundaries and stay within the window.

On pressing 'L' the particles interact with their co-particles if their distance is less than or equal to 50 units. You can see the lines drawn from one particle to another.

The code was inspired by CodeParade's Particle-Life: https://youtu.be/Z_zmZ23grXE and is based on @HackerPoet design.
Github: https://github.com/HackerPoet/Particle-Life

This is written in C++ for windows, using Visual Studio.

To use SFML in your visual studio project, refer: https://www.sfml-dev.org/tutorials/2.5/start-vc.php

Also, a few dlls needs to be copied at the location of your executable:
sfml-graphics-2.dll
sfml-graphics-d-2.dll
sfml-system-d-2.dll
sfml-system-2.dll
sfml-window-d-2.dll
sfml-window-2.dll

These are a part of the SFML SDK: SFML-2.5.1-windows-vc15-64-bit\SFML-2.5.1\bin

The code is written for x64 architecture, so the target should be updated for a successful build.

Single Particle:

![Image of Single Particle](https://github.com/harshsikhwal/Particle-Interaction/blob/master/resources/single.png)


Multiple Particles:

![Image of Multi Particle](https://github.com/harshsikhwal/Particle-Interaction/blob/master/resources/multi.png)
