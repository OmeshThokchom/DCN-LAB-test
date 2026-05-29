# Aim: Hybrid Topology Simulation in NS2

set ns [new Simulator]
set tracefile [open hybrid.tr w]
$ns trace-all $tracefile

proc finish {} {
    global ns tracefile
    $ns flush-trace
    close $tracefile
    exit 0
}

for {set i 0} {$i < 7} {incr i} {
    set node($i) [$ns node]
}

$ns duplex-link $node(0) $node(1) 1Mb 10ms DropTail
$ns duplex-link $node(1) $node(2) 1Mb 10ms DropTail
$ns duplex-link $node(2) $node(3) 1Mb 10ms DropTail
$ns duplex-link $node(3) $node(0) 1Mb 10ms DropTail
$ns duplex-link $node(0) $node(4) 1Mb 10ms DropTail
$ns duplex-link $node(4) $node(5) 1Mb 10ms DropTail
$ns duplex-link $node(4) $node(6) 1Mb 10ms DropTail

$ns at 5.0 "finish"
$ns run

