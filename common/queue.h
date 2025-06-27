#ifndef QUEUE_H_
#define QUEUE_H_

#include <climits>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <memory>  // Para std::unique_ptr
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>

struct ClosedQueue: public std::runtime_error {
    ClosedQueue(): std::runtime_error("The queue is closed") {}
};

struct QueueAlreadyClosed: public std::runtime_error {
    QueueAlreadyClosed(): std::runtime_error("The queue is already closed.") {}
};

/*
 * Multiproducer/Multiconsumer Blocking Queue (MPMC)
 *
 * Queue is a generic MPMC queue with blocking operations
 * push() and pop().
 *
 * Two additional methods, try_push() and try_pop() allow
 * non-blocking operations.
 *
 * On a closed queue, any method will raise ClosedQueue.
 *
 * */
template <typename T, class C = std::deque<T>>
class Queue {
protected:
    std::queue<T, C> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

public:
    Queue(): max_size(UINT_MAX - 1), closed(false) {}
    explicit Queue(const unsigned int max_size): max_size(max_size), closed(false) {}

    bool try_push(T const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
        return true;
    }

    // Sobrecarga para manejar rvalue references (para mover en lugar de copiar)
    bool try_push(T&& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(std::move(val));
        return true;
    }

    bool try_pop(T& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return false;
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        val = std::move(q.front());  // Usar std::move para evitar copias innecesarias
        q.pop();
        return true;
    }

    void push(T const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
    }

    // Sobrecarga para manejar rvalue references (para mover en lugar de copiar)
    void push(T&& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(std::move(val));
    }

    T pop() {
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        T val = std::move(q.front());
        q.pop();

        return val;
    }

    bool empty() {
        std::unique_lock<std::mutex> lck(mtx);
        return q.empty();
    }

    void close() {
        std::unique_lock<std::mutex> lck(mtx);
        /*
        if (closed) {
            throw QueueAlreadyClosed();
        }
        */

        closed = true;
        is_not_empty.notify_all();
    }

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

// Especialización para punteros sin modificar
template <>
class Queue<void*> {
protected:
    std::queue<void*> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

public:
    explicit Queue(const unsigned int max_size): max_size(max_size), closed(false) {}

    virtual ~Queue() = default;

    bool try_push(void* const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
        return true;
    }

    bool try_pop(void*& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return false;
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        val = q.front();
        q.pop();
        return true;
    }

    void push(void* const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
    }

    void* pop() {
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        void* const val = q.front();
        q.pop();

        return val;
    }

    bool empty() {
        std::unique_lock<std::mutex> lck(mtx);
        return q.empty();
    }

    void close() {
        std::unique_lock<std::mutex> lck(mtx);
        /*
        if (closed) {
            throw QueueAlreadyClosed();
        }
        */

        closed = true;
        is_not_empty.notify_all();
    }


private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

template <typename T>
class Queue<T*>: public Queue<void*> {
public:
    explicit Queue(const unsigned int max_size): Queue<void*>(max_size) {}

    bool try_push(T* const& val) { return Queue<void*>::try_push(val); }

    bool try_pop(T*& val) { return Queue<void*>::try_pop((void*&)val); }

    void push(T* const& val) { return Queue<void*>::push(val); }

    T* pop() { return (T*)Queue<void*>::pop(); }

    void close() { return Queue<void*>::close(); }

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

// Especialización parcial para std::unique_ptr
template <typename T, class C>
class Queue<std::unique_ptr<T>, C> {
private:
    std::queue<std::unique_ptr<T>, C> q;
    const unsigned int max_size;
    bool closed = false;
    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

public:
    Queue(): max_size(UINT_MAX - 1), closed(false) {}
    explicit Queue(const unsigned int max_size): max_size(max_size), closed(false) {}

    bool try_push(std::unique_ptr<T> val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(std::move(val));
        return true;
    }

    bool try_pop(std::unique_ptr<T>& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return false;
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        val = std::move(q.front());
        q.pop();
        return true;
    }

    void push(std::unique_ptr<T> val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(std::move(val));
    }

    std::unique_ptr<T> pop() {
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        std::unique_ptr<T> val = std::move(q.front());
        q.pop();

        return val;
    }

    void close() {
        std::unique_lock<std::mutex> lck(mtx);
        /*
        if (closed) {
            throw QueueAlreadyClosed();
        }
        */


        closed = true;
        is_not_empty.notify_all();
    }

    bool empty() {
        std::unique_lock<std::mutex> lck(mtx);
        return q.empty();
    }

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};


#endif
