# get_text_from_file

C source code

Program may be used in a bash script to extract needed data from the
output of a program that is executed by the script

e.g. script does a gpg --list-key and then needs the fingerprint data

gpg --list-key alice >alice-key.txt
get_test_from_file alice-key.txt 2 7 40 message.txt
fingerprint="$(<message.txt)"
//
