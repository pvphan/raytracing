WORKDIR_PATH=/raytracing
REPO_PATH:=$(dir $(abspath $(firstword $(MAKEFILE_LIST))))
HOST_OUTPUT_PATH=${HOME}/Documents/raytracingoutput
CONTAINER_OUTPUT_PATH=/tmp/raytracing/output
IMAGE_TAG=pvphan/raytracing:latest
RUN_FLAGS = \
	--rm \
	--volume=${REPO_PATH}:${WORKDIR_PATH}:ro \
	--volume=${HOST_OUTPUT_PATH}:${CONTAINER_OUTPUT_PATH} \
	${IMAGE_TAG}

shell: image
	docker run -it ${RUN_FLAGS} bash

firstimage: image
	mkdir -p ${CONTAINER_OUTPUT_PATH}
	docker run ${RUN_FLAGS} /bin/bash -c \
		"clang++ -Wall -std=c++14 firstimage.cc -o ${CONTAINER_OUTPUT_PATH}/firstimage.exe && ${CONTAINER_OUTPUT_PATH}/firstimage.exe > ${CONTAINER_OUTPUT_PATH}/firstimage.ppm"

image:
	DOCKER_BUILDKIT=1 docker build . --tag ${IMAGE_TAG}
