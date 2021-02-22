# get_text_from_file

C source code

Program may be used in a bash script to extract needed data from the
output of a program that is executed by the script

e.g. script does a gpg --list-key and then needs the fingerprint data

gpg --list-key alice >alice-key.txt
get_test_from_file alice-key.txt 2 7 40 message.txt
fingerprint="$(<message.txt)"

return codes: 0 successful
  1 wrong number of command line arguments;
  2 source file not found;
  3 impropper command line arguments max line is 1024; arguments are out of range;
  4 source line too short;
  5 file too short -- source line not reached;

compile this and store the executable in usr/local/bin
