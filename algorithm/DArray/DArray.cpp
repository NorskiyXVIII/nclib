#include "DArray.hpp"

void DArray::_resize_array(int size_new) {
	if(size_new < capacity) return;
	
	while(capacity < size_new) {
		capacity *= resize_factor;
		if(capacity >= max_len_arr) {
			capacity = max_len_arr;
			break;
		}
	}
	
	int *p = new int[capacity];
	for (int i = 0; i < length; i++) {
		p[i] = data[i];
	}
	delete[] data;
	data = p;
}

const DArray& DArray::operator=(const DArray& other) {
	if (this == &other) return other;
	
	length = other.length;
	capacity = other.capacity;
	
	delete[] data;
	data = new int[capacity];
	
	for (int i = 0; i < length; i++) {
		data[i] = other.data[i];
	}
	
	return other;
}

void DArray::push_back(int value) {
	if (length >= capacity) _resize_array(capacity * resize_factor);
	if (length < capacity) data[length++] = value;
}
int DArray::pop_back() {
	if(length > 0) return data[--length];
	
	return value_err;
}

int DArray::Item::operator=(int right) {
	if (index >= max_len_arr || index < 0) return right;
	
	if (index >= current->capacity) current->_resize_array(index+1);
	
	for (int i = current->length; i < index; i++) current->data[i] = 0;
	
	current->data[index] = right;
	
	if (index >= current->length) current->length = index + 1;
	
	return right;
}

DArray::Item::operator int() const {
	if (index >= current->length || index < 0) return value_err;
	
	return current->data[index];
}

int DArray::Item::_assign_operator(int right, type_assign t) {
	if (index >= current->length || index < 0) return right;
	
	switch(t) {
		case iadd_operator:
			current->data[index] += right;
			break;
		case imin_operator:
			current->data[index] -= right;
			break;
		case imul_operator:
			current->data[index] *= right;
			break;
		case idiv_operator:
			current->data[index] /= right;
			break;
		case iddiv_operator:
			current->data[index] %= right;
			break;
	}
	
	return current->data[index];
}

		int DArray::Item::operator +=(int right) {
			return _assign_operator(right, iadd_operator);
		}
		int DArray::Item::operator -=(int right) {
			return _assign_operator(right, imin_operator);
		}
		int DArray::Item::operator *=(int right) {
			return _assign_operator(right, imul_operator);
		}
		int DArray::Item::operator /=(int right) {
			return _assign_operator(right, idiv_operator);
		}
		int DArray::Item::operator %=(int right) {
			return _assign_operator(right, iddiv_operator);
		}
		
const DArray& DArray::operator+=(const DArray& other) {
	int size_new = length + other.length;
	if(size_new > max_len_arr) size_new = max_len_arr;
	_resize_array(size_new);
	
	for (int i = length, j = 0; i < size_new; i++, j++) {
		data[i] = other.data[j];
	}
	length = size_new;
	
	return *this;
}

DArray DArray::operator+(const DArray& other) const {
	DArray new_arr;
	int size_new = length + other.length;
	if(size_new > max_len_arr) size_new = max_len_arr;
	new_arr._resize_array(size_new);
	
	for (int i = 0, j = 0; i < size_new; i++) {
		if(i < length) new_arr.data[i] = data[i];
		if(i >= length) {
			new_arr.data[i] = other.data[j];
			j++;
		}
	}
	
	new_arr.length = size_new;
	
	return new_arr;
}

int DArray::Item::operator ++() {
	if (index >= current->length || index < 0) return value_err;
	
	current->data[index]++;
	return current->data[index];
}
int DArray::Item::operator --() {
	if (index >= current->length || index < 0) return value_err;
	
	current->data[index]--;
	return current->data[index];
}

int DArray::Item::operator ++(int) {
	if (index >= current->length || index < 0) return value_err;
	
	return current->data[index]++;
}
int DArray::Item::operator --(int) {
	if (index >= current->length || index < 0) return value_err;
	
	return current->data[index]--;
}