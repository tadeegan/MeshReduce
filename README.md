MeshReduce
==========

This is a linux port of [Stan Melax's](http://www.melax.com/polychop) mesh reduction algorithm for windows.  It has been modified to take .obj files as input and output a lower resolution model. A full description of the algorithm can be found [here](http://dev.gameres.com/program/visual/3d/PolygonReduction.pdf).

Some things to work on in the future:
- manifold meshes dont seem to work well
- speed improvements shouldnt bee too dificult to implement
- preserve obj vt's and vn's

usage: 

``$ make``

``$ ./testing <filename> <ratio deciamtion>``
