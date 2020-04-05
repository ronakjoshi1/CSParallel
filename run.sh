for thread_count in 1 2 4 8 16 32
do
	echo "Running Threads: $thread_count"
	./part22.exe 999 $thread_count 100

	printf "######################### DONE with $thread_count \n\n\n"
done
