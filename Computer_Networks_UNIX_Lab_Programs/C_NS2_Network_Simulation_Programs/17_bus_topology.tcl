# Aim: Bus Topology Simulation in NS2

set ns [new Simulator]
set tracefile [open bus.tr w]
$ns trace-all $tracefile

proc finish {} {
    global ns tracefile
    $ns flush-trace
    close $tracefile
    exit 0
}

for {set i 0} {$i < 5} {incr i} {
    set node($i) [$ns node]
}

for {set i 0} {$i < 4} {incr i} {
    $ns duplex-link $node($i) $node([expr {$i + 1}]) 1Mb 10ms DropTail
}

$ns at 5.0 "finish"
$ns run

