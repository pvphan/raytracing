FROM python:3.10-slim-buster

RUN apt-get update
RUN apt-get -y install clang lldb lld

WORKDIR /raytracing
