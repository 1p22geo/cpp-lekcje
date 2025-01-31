all: build

build: configure
	cmake --build ./build

configure:
	cmake -S ./src -B ./build

test: build
	for exe in build/test_*; do eval "./$$exe" && echo -ne "\033[32m[SUCCESS]\033[0m $$exe\n" || echo -ne "\n\033[31m[FAILED]\033[0m $$exe\n";	done

clean:
	rm -rf build/*


