#pragma once
#include <stdexcept>

#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"
#define NEGATIVE_SIZE_MESSAGE "size is negative"
#define ZERO_SIZE_MESSAGE "size is 0"

template <class T>
class LinkedList
{

private:

    struct Record
    {
        T data = T();
        Record* next = nullptr;
    };

    int size = 0;
    Record* head = nullptr;

public:


    LinkedList() : size(0), head(nullptr) {};

    LinkedList(int size) : LinkedList() {
        if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

        Record** tmp = &(this->head);
        for (int i = 0; i < size; i++) {
            *tmp = new Record;
            (*tmp)->data = T();
            tmp = &((*tmp)->next);
        }
        this->size = size;
    }

    LinkedList(const T* data, const int size) : LinkedList()
    {

        if (size < 0) throw std::out_of_range(NEGATIVE_SIZE_MESSAGE);

        this->size = size;
        Record** newptr = &(this->head);
        for (int i = 0; i < size; ++i)
        {
            (*newptr) = new Record;
            (*newptr)->data = data[i];
            newptr = &((*newptr)->next);
        }

    }

    LinkedList(const LinkedList<T>& list) {
        //if (list.head == nullptr) return;
        Record* ptr = list.head;
        Record** newptr = &(this->head);

        for (int i = 0; i < list.size; i++, ptr = ptr->next) {
            *newptr = new Record;
            (*newptr)->data = ptr->data;
            newptr = &((*newptr)->next);

        }

        this->size = list.size;
    }

    ~LinkedList() {
        Record* ptr = this->head;
        Record* next;
        if (this->size == 1)
            delete ptr;
        else {
            while (ptr != nullptr) {
                next = ptr->next;
                delete ptr;
                ptr = next;
            }
        }
        this->size = 0;
        //std::cout << "mmmm";
    }

    //Methods of class
    T GetFirst() const
    {

        if (this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);
        return this->head->data;

    }

    T GetLast() const
    {

        if (this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);
        Record* ptr = this->head;
        while (ptr->next != nullptr) ptr = ptr->next;

        return ptr->data;

    }

    T Get(const int index) const
    {
        if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        Record* ptr = this->head;
        for (int i = 0; i < index; i++) ptr = ptr->next;

        return ptr->data;
    }


    LinkedList<T>* GetSublist(const int start_index, const int end_index) const
    {
        if (start_index < 0 || start_index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (end_index < 0 || end_index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (start_index > end_index) throw std::logic_error("end must be not less than start");

        int newsize = end_index - start_index;
        Record* ptr = this->head;
        T* newdata = new T[newsize];

        for (int i = 0; i < end_index; ++i)
        {
            if (i >= start_index) newdata[i - start_index] = ptr->data;
            ptr = ptr->next;
        }

        LinkedList<T>* newptr = new LinkedList<T>(newdata, newsize);
        delete[] newdata;

        return  newptr;

    }

    int GetSize() const
    {
        return  this->size;
    }

    void Append(const T &data)
    {
        Record** ptr = &(this->head);
        while (*ptr != nullptr) ptr = &((*ptr)->next);

        (*ptr) = new Record;
        (*ptr)->data = data;

        this->size++;

    };

    void Prepend(const T &data)
    {
        Record* ptr = new Record{ data, this->head };
        this->head = ptr;

        this->size++;
        
    }

    void Set(const T& data, int index) {
        if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


        Record* ptr;
        {
            int i = 0;
            for (i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
        }

        ptr->data = data;
    }

    void Insert(const T& data, const int index) {
        if (index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

        if (index == 0)
        {
            this->Prepend(data);
        }
        else
        {
            Record* ptr = new Record{ data, this->head };
            Record* newptr = new Record{ data, this->head };
            for (int i = 0; i < index ; i++) 
                ptr = ptr->next;
            newptr->next = ptr->next;
            ptr->next = newptr;
            this->size++;
        }
    }

    void Remove(int index) {
        if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


        Record preHead;
        preHead.next = this->head;
        Record* ptr;
        ptr = &preHead;
        for (int i = 0; i < index; i++)
            ptr = ptr->next;
        Record* tmp = ptr->next;
        ptr->next = ptr->next->next;
        delete tmp;

        this->head = preHead.next;

        this->size--;
    }

    LinkedList<T>* Concat(const LinkedList<T> &list)
    {
        Record* ptr1 = this->head;
        Record* ptr2 = list.head;

        LinkedList<T>* newList = new LinkedList<T>();
        Record** ptr = &(newList->head);
        while (ptr1 != nullptr) {
            *ptr = new Record{
                ptr1->data,
                ptr1->next
            };

            ptr1 = ptr1->next;
            ptr = &((*ptr)->next);
        }
        while (ptr2 != nullptr) {
            *ptr = new Record{ptr2->data,ptr2->next};
            ptr2 = ptr2->next;
            ptr = &((*ptr)->next);
        }

        newList->size = this->size + list.size;
        return newList;
    }


    T& operator [] (const int index) const
    {

        if (this->head == nullptr || index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

        Record* ptr = this->head;

        for (int i = 0; i < index; ++i) ptr = ptr->next;

        return ptr->data;

    }

    bool operator==(const LinkedList<T>& list) const {
        if (this->size != list.size) return false;

        for (int i = 0; i < this->size; i++) {
            if (this->Get(i) != list.Get(i)) return false;
        }

        return true;
    }
};

template <class T>
std::ostream& operator<< (std::ostream& out, const LinkedList<T> seq) {
    out << "<";
    for (int i = 0; i < seq.GetSize(); i++) {
        out << seq.Get(i);
    }
    out << ">";
    return out;
};
