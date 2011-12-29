#!/usr/bin/perl -w

use strict;

for (my $i=0; $i<=$#ARGV; $i++)
{
    print "Frame $i = ";
    my @list = split(",", $ARGV[$i]);

    my $frame = 0;
    my $first = 1;
    my $ebene = 0;
    my $bit   = 0;
    if ($#list >= 0 && $#list <= 9)
    {
        my $ele = 0;
        foreach my $ele (@list)
        {
            if ($first == 1)
            {
                $ebene = ($ele - 1) * 9;
                $first = 2;

            } elsif ($first == 2) {
                $first = 0;
                if ($ele < 32)
                {
                    $frame |= $ele << 27;
                }
            } else {
                if ($ele < 10)
                {
                    $bit = $ebene + $ele-1;
                    $frame |= (1 << $bit);
                }
            }
        }
        printf("0x%08x = ", $frame);
        printf("0b%032b\n", $frame);
    }
}

