#!/usr/bin/perl
use strict;
use warnings;

sub _time {
    my $hour = shift; $hour *= 60;
    my $minutes = shift;


    if($hour >= 24*60 || $minutes >= 60) { print("INVALID FORMAT, time exceed the limits\n"); exit(1); }
    print("VALID FORMAT. Total minutes: ", $hour + $minutes, "\n");
    exit(0);
}

sub ampm {
    return 0 if(/am/);
    return 12;
}

$_ = $ARGV[1] || <>;

_time($1 + ampm($3), $2) if(/(^\d+):(\d\d)(am|pm)/);
_time($1 + ampm($2), 0) if(/(^\d+)(am|pm)/);
_time($1, $2) if(/(^\d+):(\d\d)/);
