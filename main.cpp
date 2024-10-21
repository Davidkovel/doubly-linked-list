#include "library.h"

struct Logger {
    void log(const string& message) const {
        cout << "[LOG]: " << message << endl;
    }

    void info(const string& message) const {
        cout << "[INFO]: " << message << endl;
    }

    void warn(const string& message) const {
        cout << "[WARN]: " << message << endl;
    }

    void error(const string& message) const {
        cout << "[ERROR]: " << message << endl;
    }
};


template <typename T> class Element {
public:
    T value;
    Element* next;
    Element* prev;
    Element() : value(), next(nullptr), prev(nullptr) {}
    Element(T value) : value(value), next(nullptr), prev(nullptr) {}
    ~Element() = default;
};

template <typename T>
class DoublyLinkedList {
private:
    Element<T>* head;
    Element<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Element<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void Enqueue_front(T val) {
        Element<T>* newElement = new Element<T>(val);
        if (tail == nullptr) {
            head = tail = newElement;
        }
        else {
            tail->next = newElement;
            newElement->prev = tail;
            tail = newElement;
        }
        size++;
    }

    void pop_front() {
        if (head == nullptr) return;
        Element<T>* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        else {
            head->prev = nullptr;
        }
        delete temp;
        size--;
    }

    bool IsEmpty() const {
        return head == nullptr;
    }

    T* GetHeadValue() const {
        if (head != nullptr) {
            return head->value;
        }
        throw runtime_error("Queue is empty");
    }

    Element<T>* getHead() const {
        return head;
    }

    void Show() const {
        Element<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }

};

template <typename T>
class Queue {
private:
    DoublyLinkedList<T> list;
    Logger logger;
public:
    void Enqueue(T val) {
        list.Enqueue_front(val);
    }

    void Dequeue() {
        list.pop_front();
    }

    bool IsEmpty() const {
        return list.IsEmpty();
    }

    T Front() const {
        return list.GetHeadValueValue();
    }

    T* getHead() const {
        return list.GetHeadValue();
    }

    void Show() const {
        list.Show();
    }

    Queue clone() const {
        Queue newQueue;
        Element* temp = this->getHead();;
        Queue tempQueue;
        logger.log("Start cloning");
        while (temp) {
            tempQueue.Enqueue(temp->data);
            logger.info("Enqueueed to tempQueue: " + to_string(temp->data));
            temp = temp->next;
        }
        logger.log("Finished Enqueueing to tempQueue");
        temp = tempQueue.getHead();;
        while (temp) {
            newQueue.Enqueue(temp->data);
            logger.info("Enqueueed to newQueue: " + to_string(temp->data));
            temp = temp->next;
        }
        logger.log("Finished cloning");

        return newQueue;
    }

    Queue operator+(const Queue& other) {
        Queue result;
        Element<T>* current = this->getHead();;
        logger.log("Start adding Queues");

        while (current != nullptr) {
            result.Enqueue(current->data);
            logger.info("Added from first Queue: " + to_string(current->data));
            current = current->next;
        }

        Element<T>* current2 = other.getHead();;
        while (current2 != nullptr) {
            result.Enqueue(current2->data);
            logger.info("Added from second Queue: " + to_string(current2->data));
            current2 = current2->next;
        }

        logger.log("Finished adding Queues");
        return result;
    }

    Queue operator*(const Queue& other) {
        Queue result;
        Element<T>* current1 = this->list.getHead();
        Element<T>* current2;

        while (current1 != nullptr) {
            current2 = other.list.getHead();
            while (current2 != nullptr) {
                if (current1->value == current2->value) {
                    result.Enqueue(current1->value);
                    break;
                }
                current2 = current2->next;
            }
            current1 = current1->next;
        }

        return result;
    }
};



int main() {

    cout << "[INFO] The program has launched" << endl;

    Queue<int> queue1;
    queue1.Enqueue(1);
    queue1.Enqueue(2);
    queue1.Enqueue(3);

    Queue<int> queue2;
    queue2.Enqueue(2);
    queue2.Enqueue(3);
    queue2.Enqueue(4);

    Queue<int> intersection = queue1 * queue2;

    cout << "Result: ";
    intersection.Show();
    /* Queue<int> queue;
     queue.Enqueue(1);
     queue.Enqueue(2);
     queue.Enqueue(3);
     queue.Show(); // Виведе: 1 2 3
     queue.Dequeue();
     queue.Show(); // Виведе: 2 3
     queue.Dequeue();
     queue.Show(); // Виведе: 3
     queue.Dequeue();
     queue.Show(); // Виведе: (порожній рядок)*/
    return 0;
}

/*
[INFO] The program has launched
Result: 2 3

C:\Users\David\source\repos\Queue double linked list\x64\Debug\Queue double linked list.exe (процесс 16292) завершил работу с кодом 0 (0x0).
Нажмите любую клавишу, чтобы закрыть это окно:


*/