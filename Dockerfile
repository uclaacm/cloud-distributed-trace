FROM gcc:latest

# Set working directory
WORKDIR /app

# Accept directory and binary name as arg
ARG BINARY
ARG DIRECTORY
COPY ./build/src/${DIRECTORY}/build/${BINARY} ./binary
CMD ["./binary"]
