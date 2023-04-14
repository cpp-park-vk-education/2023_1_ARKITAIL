.PHONY: clean generate build test

clean:
	rm -rf build .cache

generate:
	cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
		-DCMAKE_BUILD_TYPE=Debug \
		-DBUILD_TESTS=ON \
		-B build

silent-build:
	cmake --build build/

build:
	@make -s silent-build 

test:
	ctest --test-dir build
