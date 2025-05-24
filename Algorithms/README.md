# Algorithms
How I would implement algorithms. Not necessarily the best implementations; probably the worst in fact. My only goal, I suppose is to not go n!...

## Binary Search
Given a sorted array, find a given value.

This is a classic™ divide and conquer algorithm.

We can do the slow thing of searching from left→right or right→left which is $\Theta(n)$, or we can look at the middle, ask if our value is smaller or larger than the found value, look at the middle value of that quarter, etc etc; classic Divide and Conquer— $\Theta(\ln n)$

$T(1)=\Theta(1)$<br>
$T(n)=\Theta(1) + T(n/2)$<br>
$T(n)=\Theta(1) + \Theta(1) + T(n/4)$<br>
$\cdots$<br>
$T(n)=\Theta(1)\cdot i + T(n/{2^i})$<br>
$n/2^i=1$<br>
$n=2^i$<br>
$\log_2n=\log_2(2^i)$<br>
$\log_2n=i$<br>
$\therefore$<br>
$T(n)=\Theta(1)\cdot \log_2n + T(n/{2^{\log_2n}})$<br>
$T(n)=\log_2n + T(n/n)$<br>
$T(n)=\log_2n + T(1)$<br>
$T(n)=\log_2n + \Theta(1)$<br>
$T(n)=\log_2n$

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
            - $T(x,y)=\Theta(1)+\Theta(1)\times\Theta(x\times y)=\Theta(x\times y)$
        - Will ignore any peak it comes across before it global maximum.
2. As with 1D, we look at a middle element and cut smaller sides. Use the 1D Algorithm to find a peak in a row, then compare it's column neighbours, and cut the smaller side.
    - Pros:
        - Definitely faster
    - Cons:
        - Not as easy
            - $T_1(x)=\Theta(\lg x)$
            - $T_2(x,y)=\Theta(1)+T_1(x)\times T_2(x,y/2)$
            - $T_t(x,y)=\Theta(1)+\Theta(\ln x)\times\Theta(\ln y)=\Theta(\ln x\times \ln y)$


### 3D Array
Same as 2D, look at a slice, look at the peak in that slice using the 2D algorithm, cut off a section if it's smaller.
$T_1(x)=\Theta(\ln x)$<br>
$T_2(x,y)=\Theta(1)+T_1(x)\times T_2(x,y/2)$<br>
$T_3(x,y,z)=\Theta(1)+T_1(x,y)\times T_2(x,y,z/2)$<br>
$T_t(x,y,z)=\Theta(1)+\Theta(\ln x)\times\Theta(\ln y)\times\Theta(\ln z)=\Theta(\ln x\times\ln y\times\ln z)$


### XD Array
Given that the algorithms all look eerily similar, it should be possible to abstract out a generic algorithm of log^d n.
$T_d(n_1,n_2,\cdots,n_d)=\Theta(1)+\Theta(\ln n_1)\times\Theta(\ln n_2)\times\cdots\times\Theta(\ln n_d)=\Theta(\ln n_1\times\ln n_2\times\cdots\times\ln n_d)$

## <s>Quick Sort</s> Merge Sort
I have heard about Quick Sort here and there online; however, I could not say if I have ever seen it. From a description I recall of it, I thought it was Merge Sort. But, it turns out, what I thought was Merge Sort was Quick Sort... So... <s>changes title</s><br>
Merge Sort! A good old (1945 according to google) algorithm for all your array sorting needs! A divide and conquer algorithm that splits your array into smaller arrays and sticky tapes (or merges, if you want) them back together.

## Quick Sort
Quick Sort! The Merge Sort of my past! Or so I thought... looking into Quick Sort more, I really don't think it's what I thought... The sorting algorithm I'm thinking of is an inplace divide and conquer method, like Quick Sort, but from what I have found online, it's not Quick Sort... and now I'm going to find a list of sorting algorithms just to try and find the one I was thinking of.<br>
Anyway, Quick Sort— An inplace sorting algorithm that's primary draw over a merge sort is that it uses less memory.
