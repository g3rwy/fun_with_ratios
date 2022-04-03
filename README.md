# Fun with ratios
Out of lack of motivation to coding i experimented a bit with using ratios for calculations instead of floats


They are not very precise, i used **__int128_t** so its much bigger of course and made my function to print ratio as decimal.
They don't provide a lot of digits of pi, best approx ratio is [355/113](https://en.wikipedia.org/wiki/Mil%C3%BC) if you need an answer to that.
So i used it for calculating golden ratio because its basicall dividing two fibbonacci numbers.

Here is the output of compiled script:
```c
Chudnovsky
5676448184537696038498575030400 / 1806871704642899708766090718041
3.1415889517510366
-------------

Leibniz series
30720419246459942258298982638138292 / 9706767974090987674271719115507175
3.164845325288289
-------------

Just using 355/113
355 / 113
3.1415929203539823
-------------

Golden ratio using fibbonacci
26099748102093884802012313146549 / 16130531424904581415797907386349
1.61803398874989484820458683436563811772030917
-------------

Approximating a square root of 2
1572584048032918633353217 / 1111984844349868137938112
1.414213562373095048801688724209698078569671875
```
Those were the biggest numbers that the script could crunch
There is also header with some stuff to work with ratios, use it if you want, just change the type from int128 to something better. I also added approximating square root of 2, after watching [this cool video by Zach Star](https://youtu.be/kc9MinCagLQ) about approximations i felt like it should be easy to integrate into the code and yeah, i got 40 digits for sqrt(2). 

So when using ratios, they are more precise than floats in simple stuff like very popular example
0.1 + 0.2 == 0.3
won't work using floats, but it will, very easily with ratios
They do have problems with very large values, because we reach max int128 value quickly
:ukraine:
