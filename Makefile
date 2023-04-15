default: help

.PHONY: help
help: # Show help for each of the Makefile recipes.
		@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; \
		do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; \
		done

.PHONY: clean
clean: # Delete build/ and .cache/ directories.
	rm -rf build/ .cache/
	
.PHONY: generate
generate: # Generate a build recipe in a build/ directory.
	cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
		-DCMAKE_BUILD_TYPE=Debug \
		-DBUILD_TESTS=ON \
		-B build/

silent-build:
	cmake --build build/

.PHONY: build
build: # Use a generated recipe to build artifacts.
	@make -s silent-build 

.PHONY: test
test: # Run all Google tests.
	ctest --test-dir build/
