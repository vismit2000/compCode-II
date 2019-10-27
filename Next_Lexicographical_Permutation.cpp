// https://www.nayuki.io/page/next-lexicographical-permutation-algorithm

template <typename T>
bool nextPermutation(std::vector<T> &vec) 
{
	// Find non-increasing suffix
	if (vec.empty())
		return false;
	typename std::vector<T>::iterator i = vec.end() - 1;
	while (i > vec.begin() && *(i - 1) >= *i)
		--i;
	if (i == vec.begin())
		return false;
	
	// Find successor to pivot
	typename std::vector<T>::iterator j = vec.end() - 1;
	while (*j <= *(i - 1))
		--j;
	std::iter_swap(i - 1, j);
	
	// Reverse suffix
	std::reverse(i, vec.end());
	return true;
}
