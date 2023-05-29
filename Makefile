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

# TODO: coverage, lint

# TODO: подумать над неймингами :)

.PHONY: run
run: # Run development container and up all dependences.
	docker compose run --build --publish 8080:8080 dev

.PHONY: resume
resume: # Resume existing development container.
	docker start --attach --interactive \
		`docker ps --filter status=exited --quiet --latest`

.PHONY: remove
remove: # Remove development container and down all dependences.
	docker compose down
	docker rm `docker ps --filter status=exited --quiet --latest`

.PHONY: debug
debug: # Run application
	./build/Calendula \
		--docroot . \
		--http-address 0.0.0.0 \
		--http-port 8080 \
		--resources-dir='/usr/local/share/Wt/resources, ../static'

# TODO: prod

