# main purpose
This program include main method that received from the user two strings(pattern & text)
in addition include match method that received from the main that two string.
match method find the position inside text string that represent the minimum un-matching of pattetrn string and return it to main method

## methods

- <b>int main()</b>
main method received from the user two strings (pattern & text) of chars that including white letters(by max size of 100 chars), and send it to match method. 
The main method print original pattern and text string, send them to match method, and finaly print the best matching position including: the string himself and index location
- <b>int match(char pattern[], char text[])</b>
match method received from main method two strings (pattern & text) and return to main integer number 
that represent the index of text string which start the minimum un-matching of pattetrn string.
By inside for loop we check if pattern char compare to text char (up to patten length).
By outside for loop we start the checking text string from +i location and up to the difference between text length to pattern
length (text - pattern).
