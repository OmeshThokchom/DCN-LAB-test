# Aim: Mesh Topology Simulation in NS2

set ns [new Simulator]
set tracefile [open mesh.tr w]
$ns trace-all $tracefile

proc finish {} {
    global ns tracefile
    $ns flush-trace
    close $tracefile
    exit 0
}

for {set i 0} {$i < 4} {incr i} {
    set node($i) [$ns node]
}

for {set i 0} {$i < 4} {incr i} {
    for {set j [expr {$i + 1}]} {$j < 4} {incr j} {
        $ns duplex-link $node($i) $node($j) 1Mb 10ms DropTail
    }
}

$ns at 5.0 "finish"
$ns run

