#!/urs/bin/perl

use warnings ;
use strict ;
sub hello
{
   foreach my $passval(@_)
{
   print"hi there $passval";
}
}
my $value="richa";
my $d= length($value);
print"$d\n";
hello($value);
