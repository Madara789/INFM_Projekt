.PHONY: about init install-dependencies build compile start-subscale start-server start-client kill-server clean

VCPKG_DIR := ./include/vcpkg
VCPKG := ./include/vcpkg/vcpkg

about:
	@echo "Makefile to help manage subscale gpu project"
	@echo "commands:"
	@echo "     - init: make sure vcpkg ist cloned as   submodule"
	@echo "     - install-dependencies: install all vcpkg   dependencies"
	@echo "     - build: build cmake changes"
	@echo "     - compile: compile the code"
	@echo "     - start-subscale: start subscale local"
	@echo "     - start-server: starts a server to which the client sends data to calculate"
	@echo "						default port is 8080, else set with -p=<port-number>"
	@echo "     - start-client: starts execution subscale distributed"
	@echo "		- kill-server: kills all servers still running in background"
	@echo "		- removes builded files"

init:
	git submodule update --init --recursive && $(VCPKG_DIR)/bootstrap-vcpkg.sh && mkdir Proto/generated

install-dependencies:
	$(VCPKG) install nlohmann-json && $(VCPKG) install mlpack && $(VCPKG) install grpc

build:
	cmake -S . -B ./debug

compile:
	cmake --build ./debug

start-subscale:
	./debug/Subscale/subscale

start-server:
	./debug/Server/server $(p)

start-client:
	./debug/Client/client

kill-server:
	killall ./debug/Server/server

clean:
	rm -rf ./debug
