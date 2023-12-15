#ifndef SORTER_HPP
#define SORTER_HPP

#include <vector>
#include <queue>

// A class for sorting!
// You will finish this for project 4
// Yay
// All of the sorts will take a std::vector<int> and return a sorted std::vector<int>

struct Sorter {

	// sort a vector using bubble sort
	static std::vector<int> bubblesort(const std::vector<int>&);

	// sort a vector using insertion sort
	static std::vector<int> insertionsort(const std::vector<int>&);

	// sort a vector using radix sort
	static std::vector<int> radixsort(const std::vector<int>&);

	// sort a vector using quicksort
	static std::vector<int> quicksort(const std::vector<int>&);

	// sort a vector using mergesort
	static std::vector<int> mergesort(const std::vector<int>&);

};

std::vector<int> Sorter::bubblesort(const std::vector<int>& vec) {
	// you need to change this
	//Made a copy vector to be returned
	std::vector<int> retVec = vec;
	int n = retVec.size();
	//Go through each element in the vector
	for (int i = 0; i < retVec.size(); i++) {
		for (int j = 0; j < n - 1; ++j) {
			//Swap if the left value is greater than the right value looking at two elements
			if (retVec[j] > retVec[j + 1]) {
				int temp = retVec[j];
				retVec[j] = retVec[j + 1];
				retVec[j + 1] = temp;
			}
		}
		//After going through the elements the first time, we know the last one is in the correct spot
		//This means n is decreased to save an additional useless check that will always be true
		n--;
	}
	return retVec;
}

std::vector<int> Sorter::insertionsort(const std::vector<int>& vec) {
	// you need to change this
	//Made a copy vector to be returned
	std::vector<int> retVec = vec;
	//Starting at the second element to the end, put them in the correct spot of the sorted side of the vector
	for (int i = 1; i < retVec.size(); i++){
		int temp = retVec[i];
		int placeToInsert = i;
		//Startring at the end of the sorted vector, work up to the begining to find where to insert the next value
		while (placeToInsert > 0 && retVec[placeToInsert-1] > temp){
			retVec[placeToInsert] = retVec[placeToInsert - 1];
			--placeToInsert;
		}
		//After everything is shifted over, it's safe to insert the value in it's corresponding place
		retVec[placeToInsert] = temp;
	}
	return retVec;
}

std::vector<int> Sorter::radixsort(const std::vector<int>& vec) {

	// our main queue that will be turned into a vector at the end
	// also temporary storage as we move along the digits
	std::queue<int> main_queue;

	// see if the vector is empty
	if (vec.size() > 0) {

		// fill our main queue with the numbers in the vector
		// also find the largest value in the vector
		int largest = vec[0];
		for (int i = 0; i < vec.size(); ++i) {
			main_queue.push(vec[i]);
			largest = largest < vec[i] ? vec[i] : largest;
		}

		// compute the number of digits in the largest value
		int digits = 0;
		do {
			largest /= 10;
			++digits;
		} while (largest != 0);

		// we need an array of queues for our buckets
		std::queue<int> buckets[10];

		//set a variable to hold the denominator
		int den = 1;

		// evaluate each digit for each number in the main_queue and put them
		// in the correct bucket for that digit's value
		for (int i = 0; i < digits; ++i) {
			// while the main queue has elements in it
			while (main_queue.size() > 0) {
				// store the number for storage later
				int temp = main_queue.front();
				main_queue.pop();
				// store the temp in the correct bucket
				buckets[(temp / den) % 10].push(temp);
			}

			// for each bucket
			for (int j = 0; j < 10; ++j) {
				// while there is something in the bucket
				while (buckets[j].size() > 0) {
					// enqueue the value into our main queue
					main_queue.push(buckets[j].front());
					buckets[j].pop();
				}
			}

			// adjust the denominator for digit lookup later
			den *= 10;
		}
	}

	// move the sorted main queue into the return vector
	std::vector<int> ret;
	while (main_queue.size() > 0) {
		ret.push_back(main_queue.front());
		main_queue.pop();
	}
	return ret;
}

std::vector<int> Sorter::quicksort(const std::vector<int>& vec) {
	// you need to change this
	//Since this call is recursive, there are two base cases. 1 or 0 is the vector size, return that vector.
	if (vec.size() < 2)
		return vec;
	std::vector<int> retVec = vec;
	//Another base case to manually check two numbers and swap if needed
	if (retVec.size() == 2) {
		if (retVec[0] > retVec[1]) {
			int temp = retVec[0];
			retVec[0] = retVec[1];
			retVec[1] = temp;
		}
		return retVec;
	}
	//I decided to get the median of 3 to choose a pivot. Mid value of first, middle, and last positions
	int a = retVec.front(), b = retVec[retVec.size() / 2+1], c = retVec.back();
	int pivot = ((a - b)*(b - c) > -1 ? retVec.size()/2+1 : ((a - b)*(a - c) < 1 ? 0 : retVec.size()-1));
	//Swap pivot with the last element in the vector
	int temp = retVec[pivot];
	retVec[pivot] = retVec[retVec.size()-1];
	retVec[retVec.size()-1] = temp;
	pivot = retVec.size()-1;

	//Implemented pseudo code discussed in class to put all elements less than pivot to the left of it
	//and all elements greater than the pivot to the right of it
	int i = -1;
	int j = retVec.size() - 1;
	do{
		while (retVec[++i] < retVec[pivot]);
		while (i < j && retVec[--j] > retVec[pivot]);
		temp = retVec[i];
		retVec[i] = retVec[j];
		retVec[j] = temp;
	} while (i < j);
	//Put the pivot in the middle of numbers smaller and greater than itself
	temp = retVec[pivot];
	retVec[pivot] = retVec[i];
	retVec[i] = temp;
	//The following created two subvectors to call this function recrusively
	//One subvector is everything left of the pivot
	std::vector<int>::const_iterator first = retVec.begin();
	std::vector<int>::const_iterator last = retVec.begin() + i;
	std::vector<int> leftVector(first, last);
	first = retVec.begin() + (i+1);
	last = retVec.end();
	//The other subvector is everything to the right of the pivot
	std::vector<int> rightVector(first, last);
	//Recursive calls being made
	leftVector = quicksort(leftVector);
	rightVector = quicksort(rightVector);
	//Replace the newly sorted vectors that were returned with the vector we will return
	for (int z = 0; z < leftVector.size(); z++) {
		retVec[z] = leftVector[z];
	}
	for (int z = 0; z < rightVector.size(); z++) {
		retVec[retVec.size()-1-z] = rightVector[rightVector.size()-1-z];
	}
	return retVec;
}

std::vector<int> Sorter::mergesort(const std::vector<int>& vec) {
	// you need to change this
	//Recursive function with a base case to return if vector is size one or zero
	if (vec.size() < 2)
		return vec;
	std::vector<int> retVec = vec;
	//Another base case to manually handle if there are only two numbers
	if(retVec.size() == 2)
		if(retVec[0] > retVec[1]) {
			int temp = retVec[0];
			retVec[0] = retVec[1];
			retVec[1] = temp;
			return retVec;
		}
	//Recursively spilt the vectos into halves until two or less items are in the subvectors
	//This is the "Divide" aspect of Divide and Conquer
	int halfPoint = retVec.size() / 2;
	std::vector<int> firstHalf(retVec.begin(), retVec.begin() + halfPoint);
	std::vector<int> secondHalf(retVec.begin() + halfPoint, retVec.end());
	firstHalf = mergesort(firstHalf);
	secondHalf = mergesort(secondHalf);
	int i = 0, j = 0, count = 0;
	//Now with two sorted vectors, the remaining part of this function will start adding the values in order
	//to the return vector, similar to the idea in class but with implementation and not theory
	while(i < firstHalf.size() && j < secondHalf.size()){
		if(firstHalf[i] <= secondHalf[j]){
			retVec[count] = firstHalf[i];
			++i;
		}
		else{
			retVec[count] = secondHalf[j];
			++j;
		}
		count++;
	}
	//After one subvector has emptied out, put the rest of the other subvector at the end of the return subvector
	if (i < j)
		for (int k = i; k < firstHalf.size(); k++){
			retVec[count] = firstHalf[k];
			count++;
		}
	else for (int k = j; k < secondHalf.size(); k++) {
		retVec[count] = secondHalf[k];
		count++;
	}
	
	return retVec;
}

#endif
