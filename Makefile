.PHONY: about init install install-dependencies compile build start generate-protoc

VCPKG_DIR := ./include/vcpkg
VCPKG := ./include/vcpkg/vcpkg

about:
	@echo
	@echo "Makefile to help manage subscale gpu project"

##
# init
#
init: ## make sure vcpkg ist cloned as submodule
	git submodule update --init --recursive && $(VCPKG_DIR)/bootstrap-vcpkg.sh

##
# install
#
install: ## install vcpkg package
	$(VCPKG) install $(p)

##
# install-dependencies
#
install-dependencies: ## install all vcpkg dependencies
	$(VCPKG) install nlohmann-json && $(VCPKG) install mlpack && $(VCPKG) install grpc

##
# build
#
build: ## build cmake changes
	cmake -S . -B ./debug

##
# compile
#
compile: ## compile the code
	cmake --build ./debug

##
# start
#
start-subscale: ##start subscale
	./debug/SubscaleGPU/subscale

##
# start
#
start-server: ##start subscale
	./debug/Server/server

##
# start
#
start-client: ##start subscale
	./debug/Client/client