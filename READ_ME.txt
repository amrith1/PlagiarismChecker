To compile the program, extract all the files to a fresh directory
and execute "make". This will create an executable plagiarismCatcher.

plagiarismCatcher must be executed with 3 arguments in the following order:
1. The path to the file.
2. The number of words in a plagiarized sequence
3. The number of common sequences above which two files are deemed
to be plagiarised from one another.

The program will not work without providing the arguments in this
away as specified in the assignment document. The output of the program
is also as specified in the assignment document. The number of common n word phrases
and two files which share them in common above the threshold will be displayed.

Every repeated common instance of a phrase is considered plagiarism.

For example, if the number of words in a plagiarised sequence is one, and fileA contains
the word "apple" 3 times and fileB contains "apple" 4 times, the program will consider this
3*4 = 12 instances of plagiarism. Of course, one word sequences are not a good indicator
of plagiarism.