# libuv-based C language web server

#### Demonstration of the libuv usage inside Node.js runtime to achieve asynchronous IO operations.

I have always wanted to understand the underlying internals of Node.js. libuv is Node's asynchronous heart.
It wraps the C/C++ OS operations in asynchronous nature to avoid its thread of execution getting blocked by the kernel upon invoking an IO, network, etc system calls.

I thought the best way to understand this asynchronous heart of node is to take it out and use it in a standalone fashion and see how it interacts with the operating system.

I will keep explaining this concept and updating this code continuously.
