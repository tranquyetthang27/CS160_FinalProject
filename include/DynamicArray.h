#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include<iostream>
#include<stdexcept>

template<typename T>
class DynamicArray
{
    private:
        T* m_data;
        int m_size;
        int m_capacity;
        //Update the array's size when the initial array is full
        void resize(int newCapacity)
        {
            T* newData = new T[newCapacity];
            for (int i = 0; i < m_size; ++i) newData[i] = m_data[i];
            delete[] m_data;
            m_data = newData;
            m_capacity = newCapacity;
        }
    public:
        //Default value
        DynamicArray(int initialCapacity = 16)
        {
            if (initialCapacity <= 0) initialCapacity = 16;
            m_size = 0;
            m_capacity = initialCapacity;
            m_data = new T[m_capacity];
        }
        //Copy the array
        DynamicArray(const DynamicArray<T> &other)
        {
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = new T[m_capacity];
            for (int i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
        }

        DynamicArray<T> &operator = (const DynamicArray<T> &other)
        {
            if (this != &other)
            {
                delete[] m_data;

                m_size = other.m_size;
                m_capacity = other.m_capacity;
                m_data = new T[m_capacity];
                for (int i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
            }
            return *this;
        }

        ~DynamicArray()
        {
            if (m_data != nullptr) delete[] m_data;
        }

        void push_back(const T &value)
        {
            if (m_size >= m_capacity) resize(2 * m_capacity);
            m_data[m_size++] = value;
        }

        void removeAt(int index)
        {
            if (index < 0 || index >= m_size)
            {
                throw std::out_of_range();
            }
            for (int i = index; i < m_size - 1; ++i) m_data[i] = m_data[i + 1];
            m_size--;
        }

        T& operator[] (int index)
        {
            if (index < 0 || index >= m_size)
            {
                throw std::out_of_range();
            }
            return m_data[index];
        }
        const T& operator[] (int index)const
        {
            if (index < 0 || index >= m_size)
            {
                throw std::out_of_range();
            }
            return m_data[index];
        }

        void clear()
        {
            m_size = 0;
        }

        int getSize() const
        {
            return m_size;
        }

        bool isEmpty() const
        {
            return m_size == 0;
        }

        int find(const T &value)
        {
            for (int i = 0; i < m_size; ++i)
            {
                if (m_data[i] == value) return i;
            }
            return -1;
        }
};

#endif

