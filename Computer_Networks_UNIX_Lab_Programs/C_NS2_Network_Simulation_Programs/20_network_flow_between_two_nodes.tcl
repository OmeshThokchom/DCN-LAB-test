# Aim: Network Flow Between Any Two Nodes in NS2

set ns [new Simulator]
set tracefile [open flow.tr w]
$ns trace-all $tracefile

proc finish {} {
    global ns tracefile
    $ns flush-trace
    close $tracefile
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail

set udp [new Agent/UDP]
set null [new Agent/Null]
$ns attach-agent $n0 $udp
$ns attach-agent $n3 $null
$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set packetSize_ 512
$cbr set interval_ 0.05

$ns at 1.0 "$cbr start"
$ns at 4.0 "$cbr stop"
$ns at 5.0 "finish"
$ns run

