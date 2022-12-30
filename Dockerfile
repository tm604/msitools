FROM ubuntu:22.04
ARG http_proxy
ENV DEBIAN_FRONTEND=noninteractive
RUN test -n "$http_proxy" \
 && (echo "Acquire::http::Proxy \"$http_proxy\";" > /etc/apt/apt.conf.d/30proxy) \
 ;  apt-get -y update \
 && apt-get -y install build-essential intltool \
    libglib2.0-dev libtool-bin libgsf-1-dev gobject-introspection \
    valac libgcab-dev uuid-dev libxml2-dev \
    libmsi-dev gir1.2-libmsi-1.0 \
    valabind bison libglib2.0-0

WORKDIR /msitools
COPY . /msitools
RUN ./autogen.sh && ./configure && make && make install
