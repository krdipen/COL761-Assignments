README for Assignment 1 : COL761 (Data Mining)
Prof. Sayan Ranu, Semester 1, 2021-22


Team Members -

Dipen Kumar (2018CS50098)
Umesh Parmar (2018CS50424)
Aniket Shetty (2018EE10443)


Bash Scripts-

1. install.sh
	a. Clones the github repository.
	b. Loads all the required modules.
2. compile.sh
	a. Creates all the required binaries - apriori, prefixspan (?)
3. 2018CS50098.sh
	a. ./2018CS50098.sh -apriori webdocs.dat X <filename>
		=> This runs the binary apriori with webdocs.dat, X, filename as the arguments.
		=> More details follows in apriori.cpp section.
	
	b. ./2018CS50098.sh webdocs.dat -plot
		=> This runs the python script which runs the fptree and apriori for the given dataset and plots the data.
		=> The program is terminated within 1 hours.

	c. ./2018CS50098.sh -prefixspan paths_finished.dat X <filename>
		=> this run the prefixspan algorithm on path_finished.dat with support threshold greater as X and write the itemset with support >= X in filename.txt file.


Part(Q3) pre-processing step:
Assumptions:
	- prepocessor.cpp takes the name of .tsv file as command line argument. and genrate path_finished.dat file.
	- two items in path_finished.dat are saperated by space(" ") and in the last line of the file is an empty line.

Code Explaination-

2a. apriori.cpp
	=> runs the binary apriori, which uses apriori algorithms, to generate frequent itemsets.
	=> reads the data from the webdocs.dat (the location provided), uses X% as support and outputs a file with the name of filename.txt
	=> each line of the output contains a frequent item set (space separate), sorted in ascending order of ASCII.
	=> prints an empty line in the end.

3. prefixspan.cpp
	=> The input format is same as specified in the document the output file will contains an empty line in the end.
	=> I tried to optimise the algorithm at my level. I mapped all the the distinct item to an integer and operate on that only to reduce the memory uses.
	=> Further i use only one vector<vector<int>> to store the data and after that i just edit the pass the pointers.  


Explaination for Q2.b.

We observe that the time required for the Apriori algorithm is very much larger than that required by the FP-tree algorithm. This difference in the running times is very much prominent for smaller values of X (support).

Apriori algorithm involves creating candidates of size k, from frequent itemsets of size k-1. Then, we prune the candidates to get rid of non-frequent set. In this pruning step we access the dataset which is stored on the disk. Thus, this multiple disk slows down the Apriori algorithm significantly.

In FP-Tree algorithm, all the transactions are stored in the memory in the form of an FP-Tree. Thus, being a compressed way of storage, fits in the memory.(This is an assumption made by the FPTree algorithm, if the tree doesn't fit in the memory, then the code fails). Thus, FP-Tree algorithm just accesses the disk only once, to build the FP-Tree, and hence is faster than Apriori algorithm.

Apriori algorithm follows a BFS-type approach, unlike the FP-Tree algorithm which uses DFS type approach.
In Apriori algorithm, we generate a large number of candidates and then prune the data according to the count of the candidates in the transaction datasets. Thus, since, we generate and prune such large numbers of candidates, it is highly time consuming.

Statistically, for X being very large, say 50% or 90%, the frequent data sets are generally small in number, and small in size, thus the apriori algorithm in less time. But, as we decrease the support, the number and size of frequent data sets increases. Thus, the execution time of apriori increases a lot compared to that of FP-Tree for small values of support, eg. 20%, 10%, 5%.
On the given dataset,

FP-Tree algorithm runs within 50 minutes for X=5%.
But, the apriori algorithm takes more than 1 hr for X=20%, and more than 12 hrs for X=5% and X=10%.

Thus, this shows justifies the explaination given above.
