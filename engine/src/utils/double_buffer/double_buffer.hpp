template<typename Type>
DoubleBuffer<Type>::DoubleBuffer(size_t size)
: frontId(0)
, backId(0)
, frontBuffer(std::make_unique<std::vector<Type>>(size))
, backBuffer(std::make_unique<std::vector<Type>>(size))
{
}

template<typename Type>
size_t DoubleBuffer<Type>::size() const
{
    return backBuffer->size();
}

template<typename Type>
void DoubleBuffer<Type>::setSize(size_t size)
{
    backBuffer->resize(size);
}

template<typename Type>
void DoubleBuffer<Type>::setId(unsigned int id)
{
    backId = id;
}

template<typename Type>
std::vector<Type>& DoubleBuffer<Type>::getBackBuffer()
{
    return *backBuffer;
}

template<typename Type>
void DoubleBuffer<Type>::copyBuffer(std::vector<Type>& buffer)
{
    std::lock_guard<std::mutex> lock {bufferMutex};

    buffer = *frontBuffer;
}

template<typename Type>
unsigned int DoubleBuffer<Type>::copyBuffer(unsigned int id, std::vector<Type>& buffer)
{
    std::lock_guard<std::mutex> lock {bufferMutex};

    if (id == frontId) {
        buffer = *frontBuffer;
    }

    return frontId;
}

template<typename Type>
void DoubleBuffer<Type>::swapBuffers()
{
    {
        std::lock_guard<std::mutex> lock {bufferMutex};

        std::swap(backBuffer, frontBuffer);
        std::swap(backId, frontId);
    }

    if (backBuffer->size() != frontBuffer->size()) {
        backBuffer->resize(frontBuffer->size());
    }
    backId = frontId;
}
