#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "smart_ptr_utils.h"

template<typename Type>
class DoubleBuffer {

public:
    explicit DoubleBuffer(size_t size = 0);

    size_t size() const;
    void setSize(size_t size);
    void setId(unsigned int id);

    std::vector<Type>& getBackBuffer();

    void copyBuffer(std::vector<Type>& colorBuffer);
    unsigned int copyBuffer(unsigned int id, std::vector<Type>& colorBuffer);
    void swapBuffers();

private:
    unsigned int frontId;
    unsigned int backId;

    std::unique_ptr<std::vector<Type>> frontBuffer;
    std::unique_ptr<std::vector<Type>> backBuffer;

    std::mutex bufferMutex;

};

#include "double_buffer.hpp"
