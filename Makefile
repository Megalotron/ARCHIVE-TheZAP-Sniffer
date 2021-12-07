all:
	cmake . -B build/ -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/

tests:
	cmake . -B build-tests/ -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
	cmake --build build-tests/

clean:
	@rm -rf build
	@rm -rf build_tests
	@rm -rf TheZap
	@rm -rf TheZapTests