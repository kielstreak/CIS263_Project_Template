#ifndef     __H_SORTING_aLGORITHMS__
#define     __H_SORTING_aLGORITHMS__

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
void printVec(const std::vector<T> vec){
	for( T item : vec ){
		std::cout << item << ", ";
	}
	std::cout << std::endl;
}


template <typename Comparable>
void insertion(std::vector<Comparable> & a){
	for(int i=1; i<a.size(); i++){
		Comparable x = a[i];
		int j = i - 1;
		while(j >= 0 and a[j] > x){
			a[j+1] = a[j];
			j = j - 1;
		}
		a[j+1] = x;
	}
}

template <typename Comparable>
void insertion(std::vector<Comparable> & a, int left, int right){
	for(int i = left; i<=right; i++){
		Comparable x = a[i];
		int j = i - 1;
		while(j >= left and a[j] > x){
			a[j+1] = a[j];
			j = j -1;
		}
		a[j+1] = x;
	}
}

template <typename Comparable>
void selection(std::vector<Comparable> & a){
	int min;

	for(int i=0; i < a.size() - 1; i++){
		min = i;
		for(int j=i+1; j< a.size(); j++){
			if(a[j] < a[min]){
				min = j;
			}
		}
		// Way fewer swaps than Insertion sort!
		// Insertion has to move so many elements
		// whenever it "inserts".  Swap just places
		// the next min where it needs to go.
		std::swap(a[min], a[i]);
 	}
}

template <typename Comparable>
void bubble(std::vector<Comparable> & a){
	for(int i=0; i< a.size() - 1; i++){
		bool swapped = false;
		for(int j=0; j< a.size() - i - 1; j++){
			if(a[j] > a[j+1]){
				std::swap(a[j], a[j+1]);
				swapped = true;
			}
		}
		if(!swapped){
			break;
		}
	}
}


template <typename Comparable>
void shell(std::vector<Comparable> & a){
	for(int gap = a.size() / 2; gap > 0; gap /=2){
		for(int i=gap; i<a.size(); ++i){
			Comparable tmp = std::move( a[i] );
			int j = i;
			for( ; j>= gap && tmp < a[j - gap]; j-= gap){
				a[j] = std::move(a[j - gap]);
			}
			a[j] = std::move(tmp);
		}
	}
}

inline int leftChild( int i ){
	return 2 * i + 1;
}


template <typename Comparable>
void percDown( std::vector<Comparable> & a, int i, int n ){
	int child;
	Comparable tmp;

	for(tmp = std::move( a[i] ); leftChild(i) < n; i = child){
		child = leftChild(i);
		if(child != n - 1 && a[child] < a[child + 1]){
			++child;
		}
		if(tmp < a[child]){
			a[i] = std::move( a[child] );
		} else {
			break;
		}
	}
	a[i] = std::move(tmp);
}


template <typename Comparable>
void heap(std::vector<Comparable> & a){
	for(int i=a.size() / 2 - 1; i>=0; --i){
		percDown(a, i, a.size());
	}
	for(int j=a.size() - 1; j>0; --j){
		std::swap( a[0], a[j]);
		percDown (a, 0, j);
	}
}


template <typename Comparable>
void merge( std::vector<Comparable> & a, std::vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd ){
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	while( leftPos <= leftEnd && rightPos <= rightEnd ){
		if( a[leftPos] <= a[rightPos]){
			tmpArray[tmpPos++] = std::move(a[leftPos++]);
		} else {
			tmpArray[tmpPos++] = std::move(a[rightPos++]);
		}
	}

	while(leftPos <= leftEnd){
		tmpArray[ tmpPos++ ] = std::move(a[leftPos++]);
	}

	while(rightPos <= rightEnd){
		tmpArray[tmpPos++] = std::move(a[rightPos++]);
	}

	for(int i=0; i<numElements; ++i, --rightEnd){
		a[rightEnd] = std::move(tmpArray[rightEnd]);
	}
}


template <typename Comparable>
void mergeSort( std::vector<Comparable> & a, std::vector<Comparable> & tmpArray, int left, int right){
	if( left < right ){
		int center = (left + right) / 2;
		mergeSort( a, tmpArray, left, center);
		mergeSort( a, tmpArray, center+1, right);
		merge( a, tmpArray, left, center+1, right);
	}
}


template<typename Comparable>
void mergeSort( std::vector<Comparable> & a){
	std::vector<Comparable> tmpArray( a.size() );
	mergeSort(a, tmpArray, 0, a.size() - 1);
}


template <typename Comparable>
const Comparable & median3( std::vector<Comparable> & a, int left, int right){
	int center = (left + right) / 2;
	std::cout << center << std::endl;
	if(a[center] < a[left]){
		std::swap( a[left], a[center] );
	}
	if(a[right] < a[left]){
		std::swap( a[left], a[right] );
	}
	if(a[right] < a[center]){
		std::swap(a[center], a[right]);
	}
	std::swap(a[center], a[right - 1]);
	return a[right - 1];
}


template <typename Comparable>
void quicksort( std::vector<Comparable> & a, int left, int right){

	if( left + 10 <= right){
		const Comparable & pivot = median3( a, left, right );
		int i=left, j=right - 1;
		for(; ;){
			while(a[++i] < pivot){ }
			while(pivot < a[--j]){ }
			if(i < j){
				std::swap( a[i], a[j] );
			} else {
				break;
			}
		}
	
		std::swap( a[i], a[right - 1]);
		quicksort( a, left, i - 1);
		quicksort( a, i+1, right);
	} else {
		insertion(a, left, right);
	}
}


template <typename Comparable>
void quicksort( std::vector<Comparable> & a){
	quicksort(a, 0, a.size() - 1);
}

#endif
