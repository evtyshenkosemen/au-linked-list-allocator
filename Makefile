all: restore_env build tests

restore_env:
	./restore_env.sh

tests: restore_env
	cd ./libAuLiLiAllocatorTests && make all

build: restore_env
	cd ./libAuLiLiAllocator && make all
