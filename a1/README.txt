compile:
    g++ bloom_filter.cpp -o bloom_filter

run:
    ./bloom_filter -d dictionary.txt -i input.txt -o output3.txt output5.txt    

a) What hash functions did you choose and why (Hint: Cryptographic ornon-cryptographic)? What is the output range of the hash functions? What is thesize of the Bloom filter in each case?
Answer:
The first bloomfliter I use SDBMHash/RSHash/JSHash hash functions, the second bloomfliter I use PJWHash/ELFHash/BKDRHash/DJBHash/APHash hash functions. They all string hash functions, but have different efficient.The range of hash functions is [0,2147483647], for the first bloom filter, the size is 20, which is size 20 = 2^20 bits = 1 048 576 bits, the second bloom filter has size equals to 24, which is 16 777 216 bits
b) How long does it take for your Bloom Filter to check 1 password in each case?Why does one perform better than other?
Answer:
According to the running result from the my mac(different laptops may have different result according to the hardware efficiency), output3 will use 3.82353 ms, which means the first bloom filter use around 3.8 ms, output5 will use 5.05882 ms, which means the second bloom filter use around 5.06 ms. So the first one is better than the second one because it use less time for calculating. 
c) What is the probability of False Positive in your Bloom Filter in each case? Whatis the probability of False Negative in your Bloom Filter?
Answer:
Go thought the result from output3.txt and output5.txt, finally we get the probability of false positive: first bloom filter is 0.1176 and second bloom filter is 0, probability of false negative: first bloom filter is 0, second bloom filter is 0.
d) How can you reduce the rate of False Positives?
Answer: 
we can increase the size of bloom filter in order to reduce the rate of false positives.