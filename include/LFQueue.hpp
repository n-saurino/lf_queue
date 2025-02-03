#pragma once
#include <vector>
#include <atomic>
#include <optional>

template<typename T>
class LFQueue{
public:
    LFQueue(int capacity): capacity_(capacity + 1), head_{0}, tail_{0},
                           buffer_(capacity + 1){
        
    }
    
    ~LFQueue(){
        
    }
    
    bool Push(T& val){
        // double lock checking
        while(true){
            int tail{tail_.load(std::memory_order_relaxed)};
            int head{head_.load(std::memory_order_acquire)};
            if((tail + 1) % capacity_ == head){
                return false;
            }

            if(tail_.compare_exchange_weak(tail, (tail+1)%capacity_, 
                                        std::memory_order_release,
                                        std::memory_order_relaxed)){
                buffer_[tail] = val;
                return true;
            } 
        }
    }
    
    std::optional<T> Pop(){
        while(true){
            int head{head_.load(std::memory_acquire_relaxed)};
            int tail{tail_.load(std::memory_acquire_relaxed)};
            if(tail == head){
                return std::nullopt;
            }

            if(head_.compare_exchange_weak(head, (head+1)%capacity_,
                                           std::memory_order_release,
                                           std::memory_order_relaxed)){
                return buffer[head];
            }
        }
    }

private:
    std::vector<T> buffer_{};
    std::atomic<int> head_{};
    std::atomic<int> tail_{};
    int capacity_{};
};