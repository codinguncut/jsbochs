## Instructions per second (IPS)

jsbochs runs terribly slow for some reason.
For comparison, bochs compiled with gcc runs at ca. 33MIPS on my computer

<pre>
-O0             0.7M
-O1             1.0M
-O2 --closure 0 1.0M
</pre>

Compiling with closure does not work at the moment because of some bit-twiddling overflow code.

<pre>
Read/Write -O1
  manual Read/WriteHost: 1.0M
  memcpy Read/WriteHost: 1.0M
</pre>
