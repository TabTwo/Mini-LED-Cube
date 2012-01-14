#!/usr/bin/perl -w
#
# author: Kai Lauterbach (klaute at gmail dot com)
# date: 01/2012
# license: GPL v3
#
#

use strict;
use Time::HiRes qw(usleep nanosleep);

my $odelay = 0;
my $olayer = 0;
my $oled = 0;

print "./param2HexFrame.pl ";
for (my $i = 0; $i < 32; $i++)
{
    print "\"";
    my $r = 0;
    while ($r < 1 || $r > 5 || $odelay == $r)
    {
        $r = int(rand(6));
    }
    $odelay = $r;
    print $r. ";";
    $r = 0;
    while ($r < 1 || $r > 3 || $olayer == $r)
    {
        $r = int(rand(4));
    }
    $olayer = $r;
    print $r;
    print ",";
    $r = 0;
    while ($r < 1 || $r > 9 || $oled == $r)
    {
        $r = int(rand(10));
    }
    $oled = $r;
    print $r;
    print "\" ";
}

