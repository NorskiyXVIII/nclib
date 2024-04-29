#ifndef __DARRAY__HPP__
#define __DARRAY__HPP__

class DArray {
	enum {
		start_len_arr = 8,
		resize_factor = 2,
		max_len_arr   = 30,
		value_err     = 2123456789,
	};
	
	int* data {nullptr};
	int length {0};
	int capacity {0};
	
	class Item {
		enum type_assign { iadd_operator, imin_operator, imul_operator, idiv_operator, iddiv_operator };
		DArray* current {nullptr};
		int index {-1};
		
		int _assign_operator(int right, type_assign t);
		
	public:
		Item(DArray* obj, int indx) : current{obj}, index{indx} {}
		
		int operator =(int right);
		int operator +=(int right);
		int operator -=(int right);
		int operator *=(int right);
		int operator /=(int right);
		int operator %=(int right);
		// prefix
		int operator ++();
		int operator --();
		// postfix
		int operator ++(int);
		int operator --(int);
		
		operator int() const;
	};
	
	void _resize_array(int size_new); 
public:
	DArray() : length(0), capacity(start_len_arr) {
		data = new int[capacity];
	}
	
	DArray(const DArray& other) : length(other.length), capacity(other.capacity) {
		data = new int[capacity];
		for (int i = 0; i < length; i++) {
			this->data[i] = other.data[i];
		}
	}
	
	~DArray() { delete[] data; }
	
	int size() const { return this->length; }
	int get_capacity() const { return this->capacity; }
	const int* get_data() const { return data; }
	
	const DArray& operator=(const DArray& other);
	Item operator[](const int index) {
		return Item(this, index);
	}
	
	const DArray& operator+=(const DArray& other);
	DArray operator+(const DArray& other) const;
	
	void push_back(int value);
	int pop_back();
};


#endif /* __DARRAY__HPP__ */