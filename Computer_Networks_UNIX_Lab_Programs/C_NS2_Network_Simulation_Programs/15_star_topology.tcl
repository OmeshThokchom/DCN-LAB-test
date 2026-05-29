# Aim: Star Topology Simulation in NS2

set ns [new Simulator]
set tracefile [open star.tr w]
$ns trace-all $tracefile

proc finish {} {
    global ns tracefile
    $ns flush-trace
    close $tracefile
    exit 0
}

set center [$ns node]
for {set i 0} {$i < 5} {incr i} {
    set node($i) [$ns node]
    $ns duplex-link $center $node($i) 1Mb 10ms DropTail
}

$ns at 5.0 "finish"
$ns run

