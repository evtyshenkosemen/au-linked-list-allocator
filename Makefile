all: build tests

tests:
	cd ./libAuLiLiAllocatorTests && make all

build:
	cd ./libAuLiLiAllocator && make all
