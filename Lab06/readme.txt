
This homework was aimed at familiarizing with mutithreading programming.

Problems:
Initally, the first approach I tried was to break up different parts
of the main function into a few parts. And then assign the different
parts to separate threads. However, I soon realized this was an incorrect
approach as objects/variables in the function are dependent of each other.
Furthermore, it is simply not possible to break the main function into
more than 2 parts. 
For my second approach, I took note of the for loops and figured
it would be a good idea to break the loops into different parts
and run each part using a thread. Hence, I will need to find a way
to evenly break up the loop and assign that portion to a thread.
Luckily, I did not have to look into the nested loops, I can simply
achieve this by breaking up the outer for loop. Since the specs
hinted at the usage of the variable nthread as well as the thread
id, I figured a possible approach was to do some form of computation
using id and nthread. Since the id starts from 0, a reasonable appraoach
was to let each thread start at different px values and then incrementing
them with nthreads. I concluded this was the best approach as that way
I would avoid race conditions as no pixel was being rendered at the
same time by mutiple threads. 

The next part of the problem involves passing a
function pointer to pthread_create. Based on the documentation, 
pthread_create was allowed to only pass in one argument to the function. 
Hence, I need to figure out a way to achieve the optimization on the
for loops that I mentioned above using just one argument. After 
spending some time experimenting with global varaiables, I decided to
use a struct that encompases all the require information instead. The struct
would house an id, the number threads and a pointer to the scene
object. This was the apporach I stuck with as it was far neater than
declaring global variables. 

Performance results:

time ./srt 1-test.ppm >1-test.ppm.tmp
real    0m41.048s
user    0m41.034s
sys     0m0.003s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m20.637s
user    0m41.060s
sys     0m0.004s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m10.762s
user    0m42.732s
sys     0m0.003s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m5.738s
user    0m44.499s
sys     0m0.009s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
done

Conclusion:
After checking 1-test.ppm to 8-test.ppm, I was pleased to discover
that there was no distortion to the image compared to baseline.ppm.
The performance of the mutithreaded SRT implementation was also
satisfactory. We could see from the test results above that the
real execution time decreased approximately at a factor of 1/threads.
This is because the image rendering process was split into
mutiple parallel tasks and each tasks was ran independently.
In summary, it is a good idea to run independet tasks or
embarrassingly parallel programs such as image rendering
using threads.  
