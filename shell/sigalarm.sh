#! /bin/bash
function allow_time {
(
 #echo timer allowing $1 seconds for execution
       sleep $1
       kill -ALRM $$
) &
alarmPID=$! 
taskTimedOut=0
}

function timeout_handler {
#echo allowable time for execution exceeded.
taskTimedOut=1 }

function timeTask {
trap timeout_handler SIGALRM allow_time $2
#echo "alarmPID=$alarmPID" $1
if [ $taskTimedOut -eq 0 ]; then kill -9 $alarmPID
wait >/dev/null 2>&1
true
return else
false
return fi
}

echo "Finishes soon enough"
timeTask "sleep 2" 4 || (echo "task 1 took too long"; exit 1;)
echo "Takes too long"
timeTask "sleep 5" 4 || (echo "task 2 took too long"; exit 1;)