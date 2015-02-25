This software contains the C++ implementation of the "branch-and-mincut" framework for image segmentation
with various high-level priors as described in the paper:

V. Lempitsky, A. Blake, C. Rother. Image Segmentation by Branch-and-Mincut. 
In proceedings of European Conference on Computer Vision (ECCV), October 2008.

The software contains the core algorithm and an example of its application (globally-optimal 
segmentations under Chan-Vese functional).

----------------------------

This implementation has the following restrictions:
1) 8-connected image grids
2) Pairwise terms are assumed independent on the high-level parameter omega
Note, that these are just the restrictions of this particular implementation, not the original framework.

----------------------------

Required packages:

Before you can compile the code you need to download the maxflow software by Vladimir Kolmogorov and Yuri Boykov
and unpack the files into the Maxflow subfolder. You can obtain the code at the homepage of Vladimir Kolmogorov:
http://www.adastral.ucl.ac.uk/~vladkolm/software.html
Version 3.0 of the maxflow software is needed.

Image.h contains routines for loading and displaying images based on Intel OpenCV (tested with version OpenCV 1.0,
October 18, 2006). These routines are used solely in the main function in the end of ChanVeseSegmentation.cpp.
If you want to use these, you need to install Intel OpenCV from http://sourceforge.net/projects/opencvlibrary/
Alternatively, you may use your own preferred image I/O library.

Finally, the implementation requires STL (Standard Template Library). Without it, you should still be able
to run the slower depth-first-search algorithm.

----------------------------

File descriptions:

1) Branch-and-Mincut.h and Branch-and-Mincut.cpp

This is the core of the branch-and-mincut algorithm. To adapt the framework to your needs, you need to derive a class
from the class Branch and (re)define the virtual functions. See the commentaries in Branch-and-Mincut.h.
STL (Standard Template Library) is needed.

2) ChanVeseSegmentation.h and ChanVeseSegmentation.cpp

An example of the usage - globally optimal segmentations under the (discretized) Chan-Vese functional.
ChanVeseSegmentation.cpp contains an example of the main function in the end.

3) Image.h

Routines for loading and displaying images based on Intel OpenCV (tested with version OpenCV 1.0, October 18, 2006)
These routines are used solely in the main function in the end of ChanVeseSegmentation.cpp.
If you want to use these, you need to install Intel OpenCV from http://sourceforge.net/projects/opencvlibrary/
Alternatively, you may use your own preferred image I/O library

----------------------------

Required acknowledgements.
if you use this software in your research work, please acknowledge by citing the following three work in the resulting publications:

1) Victor Lempitsky, Andrew Blake, and Carsten Rother. "Image Segmentation by Branch-and-Mincut." 
European Conference on Computer Vision (ECCV), 2008.

Since you will be using maxflow software by V. Kolmogorov and Y. Boykov, you would also need to cite the following two works it
is based upon (see readme.txt in the maxflow software for the further details):

2) Yuri Boykov and Vladimir Kolmogorov.	"An Experimental Comparison of Min-Cut/Max-Flow Algorithms for Energy Minimization in Vision."
In IEEE Transactions on Pattern Analysis and Machine Intelligence (PAMI), September 2004

3) Pushmeet Kohli and Philip H.S. Torr. "Efficiently Solving Dynamic Markov Random Fields Using Graph Cuts."
International Conference on Computer Vision (ICCV), 2005