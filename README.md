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
* i7 3770k in wsl2 ~750k words/second

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
Executed in   81.33 secs   fish           external
   usr time   78.87 secs  251.00 micros   78.87 secs
   sys time    2.46 secs  354.00 micros    2.46 secs
~~~