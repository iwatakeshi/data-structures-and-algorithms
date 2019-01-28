#ifndef ARRAY_H
#define ARRAY_H
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>

using std::function;
using std::ostream;
using std::string;
using std::is_fundamental;

template <class T>
class NaiveArray {
private:
  T * array_ = nullptr;
  uint64_t length_ = 0;
public:
  NaiveArray() {}
  NaiveArray(uint64_t count) {
    array_ = new T[count];
    length_ = count;
  }
  ~NaiveArray() {
    delete [] array_;
    length_ = 0;
  }

  /**
   * Return the value at the specified index.
   */
  T& operator [] (uint64_t index) {
    if (index >= length_) {
      throw "Index out of bounds.";
    }
    
    return array_[index];
  }

  /**
   * Return a concantenated array.
   */
  NaiveArray<T> operator + (const NaiveArray<T> & right) {
    NaiveArray<T> temp = *this;
    for (uint64_t i = 0; i < right.length_; i++) {
      temp.push(right.array_[i]);
    }
    return temp;
  }

  /**
   * Return an array its value(s) n times.
   */
  NaiveArray<T> operator * (const uint64_t & right) {
    NaiveArray<T> temp;
    for (uint64_t i = 0; i < right; i++) {
     for (uint64_t j = 0; j < this->length_; j++) {
       temp.push(this->array_[j]);
     }
    }

    return temp;
  }

  /**
   * Assign an array.
   */
  NaiveArray<T>& operator = (const NaiveArray<T> & right) {
    if (length_ < right.length_) {
      T * temp = new T[right.length_];
      for (uint64_t i = 0; i < right.length_; i++) {
        temp[i] = right.array_[i];
      }
      length_ = right.length_;
      delete [] array_;
      array_ = temp;
      return *this;
    }

    for (uint64_t i = 0; i < right.length_; i++) {
      array_[i] = right.array_[i];
    }

    length_ = right.length_;

    return *this;
  }

  /**
   * Assign a concantenated array.
   */
  NaiveArray<T>& operator += (const NaiveArray<T> & right) {
    for (uint64_t i = 0; i < right.length_; i++) {
      this->push(right.array_[i]);
    }

    return *this;
  }

  /**
   * Assign an array with its value(s) n times.
   */
  NaiveArray<T>& operator *= (const uint64_t & right) {
    T * temp = new T[this->length_ * right];
    uint64_t index = 0;
    for (uint64_t i = 0; i < this->lenght_ * right; i++) {
     for (uint64_t j = 0; j < this->length_; j++) {
       temp[index] = this->array_[j];
       index += 1;
     }
    }

    delete [] array_;
    array_ = temp;
    length_ = length_ * right;

    return *this;
  }

  /**
   * Return an output stream representation of the array.
   */
  friend ostream& operator << (ostream& os, const NaiveArray<T>& array) {
    string seperator = ", ";
    string result = "";
    for(uint64_t i = 0; i < array.length_; i++) {
      if (i == array.length_ - 1) {
        seperator = "";
      }
      if (is_fundamental<T>::value) {
        result += (std::to_string(array.array_[i]) + seperator);
      } else {
        result += (typeid(array).name() + seperator);
      }
    }
    os  << "[" << result << "]";
    return os;
  }

  /**
   * Remove a value from the front.
   */
  T& shift() {
    if (length_ == 0) {
      throw "Array is empty.";
    }
    
    auto value = array_[0];
    if (length_ == 1) {
      delete [] array_;
      length_ -= 1;
      return value;
    }


    T * temp = new T[length_ - 1];
    for (uint64_t i = 1; i < length_; i++) {
      temp[i - 1] = array_[i];
    }

    delete [] array_;
    array_ = temp;
    length_ -= 1;

    return value;
  }
   
   /**
     * Add a value to the front.
     */
   void unshift(const T& value) {
     T * temp = new T[length_ + 1];
     temp[0] = value;

     for (uint64_t i = 1; i < length_ + 1; i++) {
       temp[i] = array_[i - 1];
     }

     delete [] array_;
     array_ = temp;
     length_ += 1;
   }

  /**
   * Add a value to the back.
   */
  void push(const T& value) {
    if (array_ == nullptr) {
      array_ = new T[1];
      array_[0] = value;
      length_ += 1;
      return;
    }

    T * temp = new T[length_ + 1];
    
    for (uint64_t i = 0; i < length_; i++) {
      temp[i] = array_[i];
    }

    temp[length_] = value;

    delete [] array_;
    array_ = temp;
    
    length_ += 1;
  }


  /**
   * Remove a value from the back.
   */
  T& pop() {
    if (length_ == 0) {
      throw "Array is empty.";
    }
    T& value = array_[length_ - 1];
    array_[length_ - 1] = 0;
    length_ -= 1;
    return value;
  }

  /**
   * Iterate through each value in the array. 
   */
  void for_each(function<void(T)>const& lambda) {
    for(uint64_t i = 0; i < length_; i++) {
      lambda(array_[i]);
    }
  }

  /**
   * Iterate through each value in the array. 
   */
  void for_each(function<void(T, uint64_t)>const& lambda) {
    for(uint64_t i = 0; i < length_; i++) {
      lambda(array_[i], i);
    }
  }

  /**
   * Filter the array based on a condition.
   */
  NaiveArray<T> filter(function<bool (T)> const& lambda) {
    NaiveArray<T> temp;
    for(uint64_t i = 0; i < length_; i++) {
      if (lambda(array_[i])) {
        temp.push(array_[i]);
      }
    }
    return temp;
  }

  /**
   * Filter the array based on a condition.
   */
  NaiveArray<T> filter(function<bool (T, uint64_t)> const& lambda) {
    NaiveArray<T> temp;
    for(uint64_t i = 0; i < length_; i++) {
      if (lambda(array_[i], i)) {
        temp.push(array_[i]);
      }
    }
    return temp;
  }

  /**
   * Map the values in the array and return a new array.
   */
  NaiveArray<T> map(function<T (T)> const& lambda) {
    NaiveArray<T> temp;
    for(uint64_t i = 0; i < length_; i++) {
      temp.push(lambda(array_[i]));
    }
    return temp;
  }

  /**
   * Map the values in the array and return a new array.
   */
  NaiveArray<T> map(function<T (T, uint64_t)> const& lambda) {
    NaiveArray<T> temp;
    for(uint64_t i = 0; i < length_; i++) {
      temp.push(lambda(array_[i], i));
    }
    return temp;
  }

  /**
   * Map the values in the array and return a new array.
   */
  template <typename U>
  NaiveArray<U> map(function<U (T)> const& lambda) {
    NaiveArray<U> temp;
    for(uint64_t i = 0; i < length_; i++) {
      temp.push(lambda(array_[i]));
    }
    return temp;
  }

  /**
   * Map the values in the array and return a new array.
   */
  template <typename U>
  NaiveArray<U> map(function<U (T, uint64_t)> const& lambda) {
    NaiveArray<U> temp;
    for(uint64_t i = 0; i < length_; i++) {
      temp.push(lambda(array_[i], i));
    }
    return temp;
  }

  string join() {
    return this->join(",");
  }

  string join(const string& seperator) {
    string result = "";
    this->for_each([&] (T x) {
      result += (((string) x) + seperator);
    });
    return result;
  }

  /**
   * Reserve additional space for the array.
   */
  void reserve(uint64_t count) {
    if (length_ == 0) {
      array_ = new T[count];
      length_ = count;
      return;
    }

    T * temp = new T[length_ + count];

    for(uint64_t i = 0; i < length_; i++) {
      temp[i] = array_[i];
    }

    delete [] array_;
    array_ = temp;
    
    length_ = length_ + count;
  }

  void clear() {
    delete [] array_;
    length_ = 0;
  }

  /**
   * Return the number of items in the array.
   */
  uint64_t length() {
    return length_;
  }
};


#endif