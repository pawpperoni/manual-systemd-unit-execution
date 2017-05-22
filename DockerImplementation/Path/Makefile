# Bruno Mondelo Giaramita                                    
# mondelob14@gmail.com                                       
# isx48185462                                                
# Escola del Treball de Barcelona 2017-05-22

.SILENT:

# Docker
DOCKER_IMAGE=path-activation
DOCKER_CONTAINER=msue-path

# C compiler
CC=gcc
CCOUTPUT=--output

# The conversion files
TARGETS=bin bin/path-activation bin/*py

# Rules

all: $(TARGETS)

bin:
	mkdir bin/ && echo "Created bin directory!" || echo "Directory bin already exits"

bin/path-activation: src/path-activation.c
	echo "Compiling $@"
	$(CC) $(CCOUTPUT) $@ $<
	echo "Succesfully compiled"
	
bin/*py: src/*py
	echo "Copying py dependences $@"
	cp src/*py bin/
	
# The utilities
build: clean all

build-docker: clean clean-docker all docker-image docker-container

docker-image:
	echo "Builind docker image"
	docker build -t $(DOCKER_IMAGE) . && echo "Successfully created image" || echo "Error creating image"
	
docker-container:
	echo "Building docker container"
	docker run --name="$(DOCKER_CONTAINER)" --hostname="$(DOCKER_CONTAINER)" --detach $(DOCKER_IMAGE) && echo "Successfully created docker container" || echo "Error creating docker container"
	
clean:
	echo "Cleaning all targets"
	rm -rf $(TARGETS)
	
clean-docker:
	echo "Erasing docker"
	docker rmi $(DOCKER_IMAGE) && echo "Erased docker image" || echo "Canno't erase docker image"
	docker rm $(DOCKER_CONTAINER) && echo "Erased docker container" || echo "Canno't erase docker container"
