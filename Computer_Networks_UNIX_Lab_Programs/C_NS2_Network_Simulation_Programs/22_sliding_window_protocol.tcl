# Aim: Sliding Window Protocol Simulation in NS2

set ns [new Simulator]
set tracefile [open sliding_window.tr w]
$ns trace-all $tracefile

proc finish {} {
    global ns tracefile
    $ns flush-trace
    close $tracefile
    exit 0
}

set sender [$ns node]
set receiver [$ns node]
$ns duplex-link $sender $receiver 1Mb 10ms DropTail

set tcp [new Agent/TCP]
$tcp set window_ 4
set sink [new Agent/TCPSink]

$ns attach-agent $sender $tcp
$ns attach-agent $receiver $sink
$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp

$ns at 1.0 "$ftp start"
$ns at 5.0 "$ftp stop"
$ns at 6.0 "finish"
$ns run

