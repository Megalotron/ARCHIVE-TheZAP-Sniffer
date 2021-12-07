all:
	@./scripts/build_project.sh

tests:
	@./scripts/build_tests.sh

clean:
	@rm -rf build
	@rm -rf build_tests
	@rm -rf TheZap
	@rm -rf TheZapTests