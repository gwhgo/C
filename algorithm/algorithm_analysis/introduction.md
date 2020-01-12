# Introduction

## What influence the Running Time?

- Depends on input ( e.g.  already sorted)
- Depends on input size 
  - parametrize in  input size
- Want upper bounds.



## What do we care?

- Worst-case
- Average-case



## Asymptotic notation

###  $$\theta$$  - notation



**Define** : Drop low-order terms, ignore leading constant.

Ex. 
$$
F(n) = 3n^3 + 90n^3 + 10 \\ 
\theta(F(n)) = n^3
$$
**Meaning**: 

As $$n -> \infin$$   ,  a $$\theta(n^2) $$ will beat, eventually, a $$\theta(n^3)$$ algorithm.



**How to use?**

We assume every elemental operation is going to take some constant amount of time.  The look at the loop.

## Insertion Sort Analysis

