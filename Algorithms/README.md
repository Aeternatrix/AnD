# Algorithms
How I would implement algorithms. Not necessarily the best implementations; probably the worst in fact. My only goal, I suppose is to not go n!...

## Peak Finding
A toy problem, the goal is to find if an element in an xd-array is a peak.
The element is a peak if it is greater or equal to its neighbours. (Elements outside the array are considered to be 0)

### 1D Array

> Given [a, b, c, d, ...] b is a peak if b ≥ a && b ≥ c

2 ideas here:
1. We do the obvious thing, look down the array and report back once we find a peak
    - Pros:
        - Easy to implement
    - Cons:
        - Slow
            - $T(n)=\Theta(1) + T(n-1) = \Theta(n)$
2. We look at a middle element, check its left/right neighbours, cut the smaller side of the array. Repeat until 1 element remains, which is, definitionally, a peak.
    - Pros:
        - Potentially faster
            - $T(n)=\Theta(1) + T(n/2) = \Theta(\lg n)$
    - Cons:
        - Not as easy to implement

### 2D Array

> Given [[a, b, c, ...], [d, e, f, ...], [g, h, i, ...], ...] b is a peak if e ≥ b && e ≥ d && e ≥ f && e ≥ h

2 ideas here:
1. Grab the global maximum of the array. It is definitionally a peak.
    - Pros:
        - Super Easy to implement
    - Cons:
        - Extremely Slow, comparitively.
            - $T(x,y)=\Theta(1)+\Theta(1)\cdot\Theta(x\cdot y)=\Theta(x\cdot y)$
        - Will ignore any peak it comes across before it global maximum.
2. As with 1D, we look at a middle element and cut smaller sides. Use the 1D Algorithm to find a peak in a row, then compare it's column neighbours, and cut the smaller side.
    - Pros:
        - Definitely faster
    - Cons:
        - Not as easy
            - $T_1(x)=\Theta(\lg x)$
            - $T_2(x,y)=\Theta(1)+T_1(x)\cdot T_2(x,y/2)$
            - $T_t(x,y)=\Theta(1)+\Theta(\ln x)\cdot\Theta(\ln y)=\Theta(\ln x\cdot \ln y)$


### 3D Array
Same as 2D, look at a slice, look at the peak in that slice using the 2D algorithm, cut off a section if it's smaller.
$T_1(x)=\Theta(\ln x)$<br>
$T_2(x,y)=\Theta(1)+T_1(x)\cdot T_2(x,y/2)$<br>
$T_3(x,y,z)=\Theta(1)+T_1(x,y)\cdot T_2(x,y,z/2)$<br>
$T_t(x,y,z)=\Theta(1)+\Theta(\ln x)\cdot\Theta(\ln y)\cdot\Theta(\ln z)=\Theta(\ln x\cdot\ln y\cdot\ln z)$


### XD Array
Given that the algorithms all look eerily similar, it should be possible to abstract out a generic algorithm of log^d n.
$T_d(n_1,n_2,\cdots,n_d)=\Theta(1)+\Theta(\ln n_1)\cdot\Theta(\ln n_2)\times\cdots\times\Theta(\ln n_d)=\Theta(\ln n_1\cdot\ln n_2\times\cdots\times\ln n_d)$

