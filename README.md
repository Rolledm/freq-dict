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
* i7 3770k in wsl2 ~3.3M words/second

Example:
~~~
> time ./freq huge.txt out.txt -f -v
Parsing file...
File parsed. Preparing output...
Done. Sorting...
Done. Dumping to file...
Freeing memory...
Finished!

________________________________________________________
Executed in   16.68 secs   fish           external
   usr time   15.97 secs  216.00 micros   15.97 secs
   sys time    0.71 secs  334.00 micros    0.71 secs
~~~