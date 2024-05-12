FROM alpine:3.19

RUN apk update && \
    apk add --no-cache \
    make \
    gcc \
    ncurses-dev \
    ncurses-libs \
    libc-dev \
    && rm -rf /var/cache/apk/*

COPY . /app
WORKDIR /app

ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8
ENV TERM xterm-256color

RUN make re
