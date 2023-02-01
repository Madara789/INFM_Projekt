    // [...]
    for (int j = 0; j < dimensions.size() - 1; j++){
        len = sprintf(buffer + bufferIndex, "%I32u", dimensions[j]);
        bufferIndex += len;
        buffer[bufferIndex++] = ',';
    }
    buffer[bufferIndex++] = ']';
    buffer[bufferIndex++] = '-';
    buffer[bufferIndex++] = '[';
    for (int j = 0; j < points.size() - 1; j++){
        len = sprintf(buffer + bufferIndex, "%I64u", points[j]->getSignature());
        bufferIndex += len;
        buffer[bufferIndex++] = ',';
    }
    buffer[bufferIndex++] = ']';
    //[...]