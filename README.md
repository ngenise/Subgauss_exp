# Code for "Improved Discrete Gaussian and Subgaussian Analysis for Lattice Cryptography."


Run experiment 1 by running "sage GaussDG.sage", "sage GaussNormal.sage", "sage GaussP.sage", and "sage GaussUni.sage".
Experiment 2 can be duplicated by varying the dimensions in "GaussUni.sage".
The BKZ estimator is compiled with "g++ -std=c++11 sec.cpp -o test"
and run with "./test n m log2(q) pick_s" where n,m, logq are unsigned ints and pick_s is a
boolean where 1 runs the estimator with the updated subgaussian bound.
