max=30
rm logfile.txt
time ./decayhist_nogui 1
echo "binlen = 1" >> logfile.txt
for i in $(seq 2 ${max});do
	root mean.cxx -q -b -l >> logfile.txt&
	time ./decayhist_nogui ${i}
	echo "binlen = ${i}" >> logfile.txt
done
root mean.cxx -q -b -l >> logfile.txt
