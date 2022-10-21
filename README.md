# Fun with ratios
Out of lack of motivation to coding i experimented a bit with using ratios for calculations instead of floats


They are not very precise, i used **__uint128_t** so its much bigger of course and made my function to print ratio as decimal.
They don't provide a lot of digits of pi, best approx ratio is [355/113](https://en.wikipedia.org/wiki/Mil%C3%BC) (also cool [article](http://davidbau.com/archives/2010/03/14/the_mystery_of_355113.html) i found about it) if you need an answer to that.
So i used it for calculating golden ratio because its basicall dividing two fibbonacci numbers.

Here is the output of compiled script:
```c
Chudnovsky
10382008013472440090510124442400 / 3304699751778735974568524081817
3.141588886519685
-------------

Leibniz series
2733224736569501206949595963381387788 / 863902349694097903010183001280138575
3.1638121340187556
-------------

Just using 355/113
355 / 113
3.1415929203539823
-------------

Golden ratio using fibbonacci
48558529144435440119720805669229197641 / 30010821454963453907530667147829489881
1.618033988749894848204586834365638117720309179805762862135448622705260462818
-------------

Approximating a square root of 2
1572584048032918633353217 / 1111984844349868137938112
1.414213562373095048801688724209698078569671875
```
Those were the biggest numbers that the script could crunch
There is also header with some stuff to work with ratios, use it if you want, just change the type from uint128 to something better. I also added approximating square root of 2, after watching [this cool video by Zach Star](https://youtu.be/kc9MinCagLQ) about approximations i felt like it should be easy to integrate into the code and yeah, i got 40 digits for sqrt(2). 

So when using ratios, they are more precise than floats in simple stuff like very popular example
0.1 + 0.2 == 0.3
won't work using floats, but it will, very easily with ratios
They do have problems with very large values, because we reach max uint128 value quickly
:ukraine:
