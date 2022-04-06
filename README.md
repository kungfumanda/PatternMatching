# PatternMatching
Pattern Matching Tool

This project as been created as part of the IF767 classes.

Students:
 - Rodrigo Farias Rodrigues Lemos (rfrl)
 - Amanda Nunes Silvestre Costa (ansc)

# How to compile

This program uses `g++` as the default compiler but could also use `gcc`.

To compile just run the following command:

`make pmt`

# How to run

By running the previous command a `pmt` binary file will be included in the `/bin/` folder and can be executen by running `./bin/pmt` or can be added directly to the PATH variable and executed everywhere.


```
Usage: pmt [options] pattern textfile [textfile...]
Options:
  -a, --algorithm ALGORITHM     Set the algorithm to be used (options are AhoCorasick, BruteForce, KMP, Ukkonen and WuManber)
  -p, --pattern PATTERN_FILE    Grabs multiple patterns at once from a file, when this option is passed, the pattern parameter should not be passed.
  -c, --count                   Hides the line results and displays only the total number of occurences
  -e, --edit DISTANCE           Finds all approximate occurrences of the pattern within the given editing distance, will be ignored if non appliable in given algorithm
  -h, --help                    Shows this guide
```