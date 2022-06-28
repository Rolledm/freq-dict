# freq-dict
Frequency dictionary

Deps: g++, make

To use:
* clone repo;
* cd to repo;
* make;
* built bin is in ./bin folder

Usage: ./freq [OPTIONS] in.txt out.txt
-h
    Show this message.
-v
    Show progress.
-f
    Override output file if exists. By default, program will exit.

Tested speed:
* i7 3770k in wsl2 ~16M words/second

Example:
~~~
rolledm@rolledm ~/r/f/bin (develop)> time wc huge.txt
  6455997  57474834 336183276 huge.txt

________________________________________________________
Executed in    2.34 secs   fish           external
   usr time    2.28 secs  271.00 micros    2.28 secs
   sys time    0.06 secs  459.00 micros    0.06 secs

rolledm@rolledm ~/r/f/bin (develop)> time ./freq huge.txt out.txt -f -v
Parsing file...
File parsed. Preparing output...
Done. Sorting...
Done. Dumping to file...
Freeing memory...
Finished!

________________________________________________________
Executed in    3.57 secs   fish           external
   usr time    2.92 secs  285.00 micros    2.92 secs
   sys time    0.64 secs  484.00 micros    0.64 secs
~~~