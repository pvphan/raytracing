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

main: image
	mkdir -p ${CONTAINER_OUTPUT_PATH}
	docker run ${RUN_FLAGS} /bin/bash -c \
		"clang++ -Wall -std=c++14 main.cc -o ${CONTAINER_OUTPUT_PATH}/main.exe && ${CONTAINER_OUTPUT_PATH}/main.exe > ${CONTAINER_OUTPUT_PATH}/main.ppm"

shell: image
	docker run -it ${RUN_FLAGS} bash

image:
	DOCKER_BUILDKIT=1 docker build . --tag ${IMAGE_TAG}
