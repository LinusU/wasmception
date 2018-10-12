FROM ubuntu:18.04

#########################
# Install prerequisites #
#########################

RUN \
  apt-get update && \
  apt-get install -y build-essential ca-certificates cmake curl git ninja-build software-properties-common ssh subversion wget

#######################
# Install Wasmception #
#######################

WORKDIR /code

COPY basics basics
COPY patches patches
COPY Makefile Makefile

# Clone LLVM
RUN make src/llvm.CLONED
RUN make src/musl.CLONED
RUN make src/compiler-rt.CLONED
RUN make src/libcxx.CLONED
RUN make src/libcxxabi.CLONED

# Build LLVM
RUN make build/llvm.BUILT
RUN make build/musl.BUILT
COPY wasm_standalone.cmake wasm_standalone.cmake
RUN make build/compiler-rt.BUILT
RUN make build/libcxx.BUILT
RUN make build/libcxxabi.BUILT

# Build Wasmception
RUN make build


COPY example example
WORKDIR /code/example
RUN make
# RUN apt-get install python
CMD python3 -m http.server
