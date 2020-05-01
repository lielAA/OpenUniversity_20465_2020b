# main Purpose
This program include main method that received from the user string
in addition include f_sequence method that received from the main the relevant string.
f_sequence method send to the user a relevant message if his string is:
1) strictly ascending 2) only ascending 3) strictly descending 4) only descending 5) mismatch

### methods
- <b>int  main()</b>
<br>main method received from the user string of chars (by max size of 100 chars),
and send it to f_sequence method
- <b>int f_sequence(char str1[])</b>
<br>f_sequence method received  from main method string of chars,
send to the user a relevant message if his string is:
1)Strictly ascending, e.g: "abcd".
2)Only ascending, e.g: "abbcd".
3)Strictly descending, e.g: "dcba".
4)Only descending, e.g: "dcbba".
5)Mismatch string, e.g: "suddenly".
Note: all decisions above are defined by ascii codes.
