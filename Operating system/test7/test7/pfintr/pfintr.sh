echo "Use time: 5s"
pgfault1=$(cat /proc/vmstat | grep pgfault | cut -d ' ' -f2)
echo "Now the number of page fault is $pgfault1"
sleep 5
pgfault2=$(cat /proc/vmstat | grep pgfault | cut -d ' ' -f2)
echo "Now the number of page fault is $pgfault2"
((page_fault=$pgfault2-$pgfault1))
echo "In 5 seconds,system calls $page_fault page fault!"
