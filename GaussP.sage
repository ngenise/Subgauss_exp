#This code generates random matrices from U{-1,1} and measures the average singular values.
from sage.stats.distributions.discrete_gaussian_integer import DiscreteGaussianDistributionIntegerSampler
n = 512; its = 50; Listn = []; List1 = []; m = 256*24;
P = [0.25, 0.5, 0.25]; scale = 1; sigma = RR(scale/sqrt(2))
X = GeneralDiscreteDistribution(P)

M = matrix(RDF,n,m)
s1SampleVar = 0; snSampleVar = 0;

for k in range(0, its):
    for i in range(0, n):
        for j in range(0, m):
            M[i,j] = X()
    [U, D, V] = M.SVD()
    List1 = List1 + [D[0,0]]
    Listn = Listn + [D[n-1,n-1]]

avg_S1 = RR(sum(List1)/its)
avg_Sn = RR(sum(Listn)/its)
for k in range(0, its):
    s1SampleVar = s1SampleVar + (RR(List1[k]) - avg_S1)^2/(its-1)
    snSampleVar = snSampleVar + (RR(Listn[k]) - avg_Sn)^2/(its-1)

testCmax = RR(( avg_S1/sigma - sqrt(m) )/( sqrt(n) ))
testCmin = RR(( sqrt(m) -  avg_Sn/sigma )/( sqrt(n) ))
print "sigma * [sqrt m + sqrt n] = ", RR((sqrt(m) + sqrt(n))*sigma)
print "sigma * [sqrt m - sqrt n] = ", RR((sqrt(m) - sqrt(n))*sigma)
print "avg test s_1(A), s_n(A) = ", avg_S1, avg_Sn
print "s1,sn Sample Var = ", s1SampleVar, snSampleVar
print "text C*s^2 via max = ", testCmax
print "text C*s^2 via min = ", testCmin
