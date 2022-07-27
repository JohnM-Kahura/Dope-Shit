#!/usr/bin/perl
print "What is the postal code?\n";
$postal_code=<STDIN>;
chomp $postal_code;

$regex=~m/A-Z/\d{1,2}/A-Z;