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
2. We look at a middle element, check its left/right neighbours, cut the smaller side of the array. Repeat until 1 element remains, which is, definitionally, a peak.
    - Pros:
        - Potentially faster
    - Cons:
        - Not as easy to implement

### 2D Array

> Given [[a, b, c, ...], [d, e, f, ...], [g, h, i, ...], ...] b is a peak if e ≥ b && e ≥ d && e ≥ f && e ≥ h

2 ideas here:
1. Grab the global maximum of the array. It is definitionally a peak.
    - Pros:
        - Super Easy to implement
    - Cons:
        - Extremely Slow, comparitively. (O(r×c))
        - Will ignore any peak it comes across before it global maximum.
2. As with 1D, we look at a middle element and cut smaller sides. Use the 1D Algorithm to find a peak in a row, then compare it's column neighbours, and cut the smaller side.
    - Pros:
        - Definitely faster
    - Cons:
        - Not easy

### 3D Array
Same as 2D, look at a slice, look at the peak in that slice using the 2D algorithm, cut off a section if it's smaller.

### XD Array
Given that the algorithms all look eerily similar, it should be possible to abstract out a generic algorithm of log^d n.
