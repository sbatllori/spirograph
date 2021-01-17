# Spirograph

## Analog Spirograph Study
This is a short study of the mechanics of an analog spirograph in order to understand how it works and programmatically simulate its behaviour and resultant drawings.


### Study of the Mechanics
<img src="doc/disks.jpeg" width="50%"> <img src="doc/mechanics.gif" width="41.45%">

These mechanics are defined by 3 disks:
+ a static disk (the *ring*),
+ a disk rotating along the ring (the *wheel*), and
+ a disk rotating along the wheel (the *brush*), from wich the resultant curves are drawn.

For the study, both the wheel and the brush rotate internally. This means, the wheel rotates inside the ring, and the brush rotates inside the wheel (as shown in the gif).

There are a lot of possibilities regarding to rings, wheels or brushes and their combination. The picture with the red box shows the disks offered by the analog version, and some parameters to identify or differentiate them. Let's take a look at them in more detail!

On the left side of the red box, there is a collection of disks with holes. Those disks represent both the wheels and the brushes. Each disk is a wheel, and the number next to it defines the amount of cogwheels of the wheel (e.g. 84, 80, 75, etc.). At the same time, each wheel presents several holes forming a spiral. Each one of these holes defines a different brush for that specific wheel. Hence, a single wheel can offer multiple resultant spirographs by using a different brush/hole!

On the right side, there are two circles and two bars. The bars are not covered by these study, so let's ignore them for now. The circles represent the rings, and the numbers written as a fraction represent the amount of cogwheels of the external (numerator) and the internal (denominator) part of the ring.

Any wheel can be placed attached to any cogwheel of any ring. With a pen on any hole of the chosen wheel, one can start rolling along the ring in order to draw the spirograph. In short, the resultant spirograph will depend on the following parameters:
- the size of the ring,
- the size of the wheel,
- the hole where the pen is placed (i.e. the brush), and
- the cogwheel of the ring where the wheel starts rotating.

Note that a spirograph can be defined either by one specific combination of ring, wheel, brush and starting position or multiple of them. In other words, one can combine multiple curves on the same spirograph to generate more complex drawings.

### Simulation
The mechanics and pieces of the analog spirograph generator have been translated into code, so that given a set of parameters the corresponding spirograph (or combination of spirographs) is drawn.

The following examples show a single spirograph and a combination of spirographs, and the parameters used to generate each of them:

<img src="doc/example1.png" width="48%"> <img src="doc/example2.png" width="48%">

The parameters are listed in the box. Each line represents a set of curves defined by the same ring and wheel, following the same rotation rules, and drawn with the same color. The numbers of a line represent the parameters as follows:
```
RING WHEEL BRUSHES, R STATIC_ROTATION:DYNAMIC_ROTATION
```
- `RING` defines the diameter of the ring, i.e. the number of cogwheels of the internal side of the ring. On both examples it is 96.
- `WHEEL` defines the diameter of the wheel, i.e. the number of cogwheels of the external side of the wheel. On the simple example it is 60 and on all sets of the complex example it is 56.
- `BRUSHES` defines the list of brushes that must be used to draw a spirograph with the specified combination of ring and wheel. Each number represents here the radius of the brush, i.e. the distance between the hole/brush and the center of the wheel. On the simple example only one brush with distance 15 to the center of the wheel must be used. On the complex example, for instance for the black line, two brushes must be used: with radii 1 and 13.
- `STATIC_ROTATION` defines the static rotation of the curves, i.e. it defines the angle where the spirograph must start its path. In other words, this rotation translates to which cogwheel is the starting point of the spirograph. It is represented in degrees (0-360) and on both examples this value is 0.
- `DYNAMIC_ROTATION` defines the dynamic rotation between the curves on the same set, i.e. how many degrees further must the next curve start in respect to the previous one. This value makes sense only if a set defines more than one brush, since each following brush will start its path some cogwheels further. It is represented in degrees (0-360) and on both examples this value is 0.

In addition, the order of the parameter list matters. The spirographs are drawn in the reverse order of the list, so that the last one is drawn first, the second-to-last is drawn second (and might hide some parts of the previous one), etc. That way, the order of the parameter list reflects the priority of the spirographs (the first one will be always drawn complete since it is drawn on top of all the others).