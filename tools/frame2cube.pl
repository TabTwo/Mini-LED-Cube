#!/usr/bin/perl -w
#
# author: Kai Lauterbach (klaute at gmail dot com)
# date: 01/2012
# license: GPL v3
#
# usage:
#
#   ./frame2cube.pl "frame 1 data" "frame 2 data" ... "frame N data"
#
#   frame X data = delay; layer 1; layer 2; layer 3
#
#   delay = 0 to 31 (multiplied by 8 in firmware and equals to the ISR calls (delay/300 seconds)
#           0 equals to a delay of 255/300 seconds.
#
#   layer Y = layer no(1,2,3), bit0, bit1, bit2, ..., bit8 (bitN = 1 ... 9)
#
# Sample usage which generates 5 frames:
#
# perl ./frame2cube.pl "25;3,2,5,8;" "14;3,3,5,7" "3;3,4,5,6;2,6,5,4" "23;3,1,5,9" "0;2,1,2,3,4,5,6,7,8,9;1,5"
# Frame 0 = 0xca480000 = hi:0xca48 = lo:0x0000 = 0b11001010010010000000000000000000
# Frame 1 = 0x71500000 = hi:0x7150 = lo:0x0000 = 0b01110001010100000000000000000000
# Frame 2 = 0x18e07000 = hi:0x18e0 = lo:0x7000 = 0b00011000111000000111000000000000
# Frame 3 = 0xbc440000 = hi:0xbc44 = lo:0x0000 = 0b10111100010001000000000000000000
# Frame 4 = 0x0003fe10 = hi:0x0003 = lo:0xfe10 = 0b00000000000000111111111000010000
#
# perl ./frame2cube.pl "5;3,2,5,8" "5;3,3,5,7" "5;3,4,5,6;" "5;3,1,5,9" "15;2,2,5,8" "15;2,3,5,7" "15;2,4,5,6" "15;2,1,5,9" "30;1,2,5,8" "30;1,3,5,7" "30;1,4,5,6" "30;1,1,5,9"
#

use strict;
use Time::HiRes qw(usleep nanosleep);

for (my $i=0; $i<=$#ARGV; $i++)
{
    printf("Frame %02d = ", $i);

    my @list  = split(";", $ARGV[$i]);
    my $frame  = 0;
    my $status = 1;
    foreach my $ele (@list)
    {
        my @list2 = split(",", $ele);

        my $status2 = 1;
        my $layer  = 0;
        my $bit    = 0;
        if ($status == 1) { # read the delay
            $status = 0;
            # minimum delay is  0 (equals to a delay of 255 ISR calls)
            # maximum delay is 31 (equals to a delay of 31*8 ISR calls)
            if ($ele > -1 && $ele < 32)
            {
                $frame |= $ele << 27;
            }
        } else {
            if ($#list >= 0 && $#list <= 9)
            {
                my $ele = 0;
                foreach my $ele2 (@list2)
                {
                    if ($status2 == 1) # read the layer
                    {
                        # the layer has to be in range of 1 to 3
                        if ($ele2 > 0 && $ele2 < 4)
                        {
                            $layer = ($ele2 - 1) * 9;
                            $status2 = 0;
                        }
                    } else {
                        if ($ele2 > 0 && $ele2 < 10) # bit 1 to 9 allowed
                        {
                            $bit = $layer + $ele2-1;
                            $frame |= (1 << $bit);
                        }
                    }
                }
            }
        }
    }
    printf("0x%08x = ", $frame);
    printf("hi:0x%04x = ", $frame >> 16);
    printf("lo:0x%04x = ", $frame & 0xffff);
    printf("0b%032b\n", $frame);
    my $tmp = "";
    $tmp = sprintf("0x%08x", $frame);
    system("../client/clcc --save --pos $i --delay ". ($frame >> 27)." --frame $tmp");
    #print("../client/clcc --save $i ". ($frame >> 27)." $tmp\n");
    usleep(250000);
    #sleep 1;
}

