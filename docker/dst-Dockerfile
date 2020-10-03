FROM alpine:latest

WORKDIR /
RUN apk update && apk add curl

CMD ["nc","-l","8080"]