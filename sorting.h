#pragma once

#include <functional> // std::less
#include <iterator> // std::iterator_traits

namespace sort {

	// This is C++ magic which will allows our function
	// to default to using a < b if the comparator arg
	// is unspecified. It uses defines std::less<T>
	// for the iterator's value_type.
	//
	// For example: if you have a vector<float>, the 
	// iterator's value type will be float. std::less 
	// will select the < for sorting floats as the 
	// default comparator.
	template<typename RandomIter>
	using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>;

	/* Efficiently swap two items - use this to implement your sorts */
	template<typename T>
	void swap(T & a, T & b) noexcept {
		T temp = std::move(a);
		a = std::move(b);
		b = std::move(temp);
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		// Random access iterators have the same traits you defined in the Vector class
		// For instance, difference_type represents an iterator difference
		// You may delete the types you don't use to remove the compiler warnings
		using _it             = std::iterator_traits<RandomIter>;
        using difference_type = typename _it::difference_type;
        //using value_type      = typename _it::value_type;
        //using reference       = typename _it::reference;
        //using pointer         = typename _it::pointer;

		difference_type n = end - begin;
		bool check = true;
		while(check){
			check = false;
			n -= 1;
			for(difference_type i = 0; i < n; i++){
				if (comp(*(begin+i+1),*(begin+i))){
					check = true;
					swap(*(begin + i+1),*(begin + i));
				}
			}
		}
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		using _it             = std::iterator_traits<RandomIter>;
        using difference_type = typename _it::difference_type;
        //using value_type      = typename _it::value_type;
        //using reference       = typename _it::reference;
        //using pointer         = typename _it::pointer;


		difference_type n = end - begin;
		for (difference_type i = 0; i < n; i++){
			difference_type j = i-1;
			difference_type g = i;
			while (j >= 0){
				if (comp(*(begin + g),*(begin + j))){
					swap(*(begin + g), *(begin + j));
					g--;
					j--;
					continue;
				}else{
					break;
				}
			}
		}
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		using _it             = std::iterator_traits<RandomIter>;
        using difference_type = typename _it::difference_type;
        //using value_type      = typename _it::value_type;
        //using reference       = typename _it::reference;
        //using pointer         = typename _it::pointer;

		difference_type n = end - begin;
		for (difference_type i = 0; i < n - 1; i++){
			difference_type smallest = i;
			for (difference_type j = i + 1; j < n; j++){
				if ( comp( *(begin + j), *(begin + smallest) ) ){
					smallest = j;
				}
			}
			swap( *(begin + i), *(begin + smallest));
		}

	}
}
