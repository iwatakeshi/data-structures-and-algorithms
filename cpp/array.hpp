#ifndef ARRAY_H
#define ARRAY_H
#include <functional>
using std::function;

template <class T>
class Array {
private:
  T * array_ = nullptr;
  unsigned long long count_ = 0;
public:
  Array() {}
  Array(unsigned long long count) {
    array_ = new T[count];
    count_ = count;
  }
  ~Array() {
    delete [] array_;
    count_ = 0;
  }

  /**
   * Return the value at the specified index.
   */
  T& operator [] (unsigned long long index) {
    if (index >= count_) {
      throw "Index out of bounds.";
    }
    return array_[index];
  }

  /**
   * Return a concantenated array.
   */
  Array<T> operator + (const Array<T> & right) {
    Array<T> temp = *this;
    for (unsigned long long i = 0; i < right.count_; i++) {
      temp.push(right.array_[i]);
    }
    return temp;
  }

  /**
   * Return an array its value(s) n times.
   */
  Array<T> operator * (const unsigned long long int & right) {
    Array<T> temp;
    for (unsigned long long i = 0; i < right; i++) {
     for (unsigned long long j = 0; j < this->count_; j++) {
       temp.push(this->array_[j]);
     }
    }

    return temp;
  }

  /**
   * Assign an array.
   */
  Array<T>& operator = (const Array<T> & right) {
    if (count_ < right.count_) {
      T * temp = new T[right.count_];
      for (unsigned long long i = 0; i < right.count_; i++) {
        temp[i] = right.array_[i];
      }
      count_ = right.count_;
      delete [] array_;
      array_ = temp;
      return *this;
    }

    for (unsigned long long i = 0; i < right.count_; i++) {
      array_[i] = right.array_[i];
    }

    count_ = right.count_;

    return *this;
  }

  /**
   * Assign a concantenated array.
   */
  Array<T>& operator += (const Array<T> & right) {
    for (unsigned long long i = 0; i < right.count_; i++) {
      this->push(right.array_[i]);
    }

    return *this;
  }

  /**
   * Assign an array with its value(s) n times.
   */
  Array<T>& operator *= (const Array<T> & right) {
    T * temp = new T[this->count_ * right.count_];
    unsigned long long index = 0;
    for (unsigned long long i = 0; i < right.count_; i++) {
     for (unsigned long long j = 0; j < this->count_; j++) {
       temp[index] = this->array_[j];
       index += 1;
     }
    }

    delete [] array_;
    array_ = temp;
    count_ = count_ * right.count_;

    return *this;
  }

  /**
   * Remove a value from the front.
   */
  void shift() {
    if (count_ == 0) {
      throw "Array is empty.";
    }

    if (count_ == 1) {
      delete [] array_;
      count_ -= 1;
      return;
    }

    T * temp = new T[count_ - 1];
    for (unsigned long long i = 1; i < count_; i++) {
      temp[i - 1] = array_[i];
    }

    delete [] array_;
    array_ = temp;
    count_ -= 1;
  }
   
   /**
     * Add a value to the front.
     */
   void unshift(const T& value) {
     T * temp = new T[count_ + 1];
     temp[0] = value;

     for (unsigned long long i = 1; i < count_ + 1; i++) {
       temp[i] = array_[i - 1];
     }

     delete [] array_;
     array_ = temp;
     count_ += 1;
   }

  /**
   * Add a value to the back.
   */
  void push(const T& value) {
    if (array_ == nullptr) {
      array_ = new T[1];
      array_[0] = value;
      count_ += 1;
      return;
    }

    T * temp = new T[count_ + 1];
    
    for (unsigned long long i = 0; i < count_; i++) {
      temp[i] = array_[i];
    }

    temp[count_] = value;

    delete [] array_;
    array_ = temp;

    count_ += 1;
  }


  /**
   * Remove a value from the back.
   */
  T& pop() {
    if (count_ == 0) {
      throw "Array is empty.";
    }
    T& value = array_[count_ - 1];
    array_[count_ - 1] = 0;
    count_ -= 1;
    return value;
  }

  void forEach(function<void(T)>const& lambda) {
    for(unsigned long long i = 0; i < count_; i++) {
      lambda(array_[i]);
    }
  }

  void forEach(function<void(T, unsigned long long)>const& lambda) {
    for(unsigned long long i = 0; i < count_; i++) {
      lambda(array_[i], i);
    }
  }

  Array<T> map(function<T (T)> const& lambda) {
    Array<T> temp;
    for(unsigned long long i = 0; i < count_; i++) {
      temp.push(lambda(array_[i]));
    }
    return temp;
  }

  Array<T> map(function<T (T, unsigned long long)> const& lambda) {
    Array<T> temp;
    for(unsigned long long i = 0; i < count_; i++) {
      temp.push(lambda(array_[i], i));
    }
    return temp;
  }

  void reserve(unsigned long long count) {
    if (count_ == 0) {
      array_ = new T[count];
      count_ = count;
      return;
    }

    T * temp = new T[count_ + count];

    for(unsigned long long i = 0; i < count_; i++) {
      temp[i] = array_[i];
    }

    delete [] array_;
    array_ = temp;
    
    count_ = count_ + count;
  }

  template <typename U>
  Array<U> map(function<U (T)> const& lambda) {
    Array<U> temp;
    for(unsigned long long i = 0; i < count_; i++) {
      temp.push(lambda(array_[i]));
    }
    return temp;
  }

  template <typename U>
  Array<U> map(function<U (T, unsigned long long)> const& lambda) {
    Array<U> temp;
    for(unsigned long long i = 0; i < count_; i++) {
      temp.push(lambda(array_[i], i));
    }
    return temp;
  }

  /**
   * Return the number of items in the array.
   */
  unsigned long long count() {
    return count_;
  }
};


#endif