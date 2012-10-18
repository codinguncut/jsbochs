## Instructions per second (IPS)

jsbochs runs terribly slow for some reason.
For comparison, bochs compiled with gcc runs at ca. 33MIPS on my computer

<pre>
-O0             0.7M
-O1             1.0M
-O2 --closure 0 1.0M
</pre>

Compiling with "--closure 1" does not work at the moment because of some bit-twiddling overflow code.

## configure options effects with -O1
<pre>
--enable-repeat-speedups    -0.0M
--enable-handlers-chaining  -0.1M
--disable-alignment-check   -0.1M
--disable-a20-pin           -0.15M
</pre>
