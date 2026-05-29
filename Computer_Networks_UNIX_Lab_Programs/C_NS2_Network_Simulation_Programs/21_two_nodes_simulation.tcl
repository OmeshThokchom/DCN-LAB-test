# Aim: Two Nodes Simulation in NS2

set ns [new Simulator]
set tracefile [open two_nodes.tr w]
$ns trace-all $tracefile

proc finish {} {
    global ns tracefile
    $ns flush-trace
    close $tracefile
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]
$ns duplex-link $n0 $n1 1Mb 10ms DropTail

set tcp [new Agent/TCP]
set sink [new Agent/TCPSink]
$ns attach-agent $n0 $tcp
$ns attach-agent $n1 $sink
$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp

$ns at 1.0 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 5.0 "finish"
$ns run

